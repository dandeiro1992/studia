use Projekt
go
ALTER VIEW widok_pierwszy 
AS
SELECT DISTINCT K.imie, K.nazwisko,K.id_kierowca,
--kolumna wiek
DateDIFF(year, cast('19'+SUBSTRING(K.pesel,1,2)+'-05-06' as date), Cast(getdate() as date)) as wiek,
SUM(kilometry) as kilometraz,
YEAR(getdate())-YEAR(K.data_otrzymania_uprawnien) as ile_lat_uprawnienia,count(T.id_transport) as ile_razy,
[CzyDostepny] = CASE WHEN (K.czy_dostepny=0) THEN 'W TRASIE' ELSE 'GOTOWY DO PRACY' END,
[czy moze niebezpieczne] = CASE WHEN (K.czy_adr=0) THEN 'NIE' ELSE 'TAK' END,
[CZY WAZNE BADANIA] = CASE WHEN (datediff (day,Cast(getdate() as date), K.data_badan_lekarskich)<100) THEN 'SKIERUJ PRACOWNIKA NA BADANIA' ELSE 'WSZYSTKO OK' END

FROM tKierowca AS K 
JOIN tTransport AS T
ON T.id_kierowca=K.id_Kierowca
join tTowar AS Towar
on T.id_towar=Towar.id_towar

group by K.imie, K.nazwisko, K.id_kierowca, K.pesel, K.data_otrzymania_uprawnien, K.czy_dostepny,K.czy_adr,K.data_badan_lekarskich




ALTER VIEW widok_drugi 
AS
SELECT top 3 F.nazwa,F.id_firma,(F.ulica+' '+F.nr_lokalu+', '+SUBSTRING(F.kod_pocztowy,1,2)+'-'+SUBSTRING(F.kod_pocztowy,3,3)+' '+F.poczta) AS adres,SUM(T.kilometry) AS kilometraz, SUM(T.koszt) AS zarobione, ROUND(AVG(T.kilometry),2) AS srednia,[CZY RENTOWNA] = CASE WHEN (COUNT(K.id_kierowca)*3000< SUM(T.koszt)) THEN 'FIRMA JEST RENTOWNA' ELSE 'FIRMA MA TYLY' END, count(T.id_kierowca) as [Liczba tras firmy]		
from tFirma as F
join tKierowca as K
on F.id_firma=K.id_firma
inner join tTransport as T
on T.id_kierowca=K.id_kierowca
join tTowar as TOWAR
on TOWAR.id_towar=T.id_towar
WHERE ((YEAR(CAST(GETDATE() As date)) -YEAR(T.kiedy))<2)
GROUP BY F.id_firma, F.nazwa,F.poczta,F.ulica, F.kod_pocztowy, F.nr_lokalu
HAVING COUNT(T.id_towar)>1 AND SUM(T.koszt)>1000
order by zarobione desc



ALTER VIEW widok_trzeci
AS
select imie,nazwisko,wiek,SUM(liczba_przyjetych_zlecen) AS liczba_zlecen, SUM(suma_zlecen) AS suma,ROUND ((SUM(suma_zlecen)/ SUM(liczba_przyjetych_zlecen)),2) AS srednia from 
(
select DISTINCT S.imie, S.nazwisko,
--kolumna wiek
DateDIFF(year, cast('19'+SUBSTRING(S.pesel,1,2)+'-05-06' as date), Cast(getdate() as date)) as wiek,

COUNT(TRANS.id_spedytor) AS liczba_przyjetych_zlecen, SUM(TRANS.koszt) AS suma_zlecen,
AVG(TRANS.koszt) AS srednia
from tTowar AS T
join tTransport AS TRANS
on TRANS.id_towar=T.id_towar
join tSpedytor	AS S
on S.id_spedytor=TRANS.id_spedytor
join tKierowca AS K
on K.id_kierowca=TRANS.id_kierowca
join tFirma AS F
on F.id_firma=K.id_firma
GROUP BY S.imie, S.nazwisko,S.pesel) jakies
GROUP BY imie,nazwisko,wiek



USE Projekt
GO
ALTER VIEW dbo.widokC
WITH SCHEMABINDING
AS
    SELECT SUM(T.kilometry) AS liczba_przejechanych_km,
       MAX( K.imie) AS imie , MAX(K.nazwisko) AS nazwisko, COUNT_BIG(*) AS tmp
    FROM dbo.tTransport T
	 join dbo.tKierowca K
    on T.id_kierowca = K.id_kierowca
    GROUP BY K.pesel
GO
--Create an index on the view.
CREATE UNIQUE CLUSTERED INDEX IDX_V2 
    ON  dbo.widokC(pesel);
GO
