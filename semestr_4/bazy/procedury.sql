USE Projekt
GO
SET ANSI_NULLS ON
GO
SET quoted_identifier ON
GO
alter PROCEDURE [dbo].[przenies]
AS
DECLARE kursor CURSOR FOR
select id_transport, id_towar, id_kierowca,id_spedytor,id_zamawiajacy,koszt,skad,dokad,kilometry,kiedy from tTransport
WHERE DateDIFF(day, kiedy, Cast(getdate() as date))>50

DECLARE @id_transport integer
DECLARE @id_towar integer
DECLARE @id_kierowca  integer
DECLARE @id_spedytor integer
DECLARE @id_zamawiajacy integer
DECLARE @koszt FLOAT
DECLARE @skad nvarchar(50)
DECLARE @dokad nvarchar(50)
DECLARE @kilometry FLOAT
DECLARE @kiedy DATE

PRINT 'Przenosze z tabeli tTransport do THistoria_Transportu'
SET IDENTITY_INSERT tHistoria_Transportu ON
OPEN kursor 
FETCH NEXT FROM kursor INTO @id_transport, @id_towar, @id_kierowca,@id_spedytor,@id_zamawiajacy,@koszt,@skad,@dokad,@kilometry,@kiedy
WHILE @@FETCH_STATUS = 0
	BEGIN
	SET IDENTITY_INSERT tHistoria_Transportu ON
	INSERT INTO tHistoria_Transportu (id, id_towar, id_kierowca,id_spedytor,id_zamawiajacy,koszt,skad,dokad,kilometry,kiedy) VALUES 
	(@id_transport, @id_towar, @id_kierowca,@id_spedytor,@id_zamawiajacy,@koszt,@skad,@dokad,@kilometry,@kiedy)
	DELETE FROM tTransport WHERE id_transport=@id_transport
	FETCH NEXT FROM kursor INTO @id_transport, @id_towar, @id_kierowca,@id_spedytor,@id_zamawiajacy,@koszt,@skad,@dokad,@kilometry,@kiedy
	SET IDENTITY_INSERT tHistoria_Transportu OFF
	END
CLOSE kursor 
DEALLOCATE kursor




USE [Projekt]
GO
/****** Object:  StoredProcedure [dbo].[zarobek]    Script Date: 2016-01-19 22:53:59 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[zarobek]
AS
DECLARE kursor CURSOR FOR
	select K.imie,K.nazwisko, SUM(T.koszt) as zarobek,  F.nazwa from
tKierowca AS K
join tTransport AS T
on T.id_kierowca=K.id_kierowca
join tFirma AS F
on K.id_firma=F.id_firma
WHERE DateDIFF(year, cast('19'+SUBSTRING(K.pesel,1,2)+'-05-06' as date), Cast(getdate() as date))<50
GROUP BY K.imie,K.nazwisko, F.nazwa


DECLARE @imie nvarchar(50)
DECLARE @nazwisko nvarchar(50)
DECLARE @zarobek FLOAT
DECLARE @nazwafirmy nvarchar(50)
PRINT 'Zarobione dla firmy pieniadze przez kierowcow poni¿ej 50 roku zycia:'

OPEN kursor 
FETCH NEXT FROM kursor INTO @imie, @nazwisko, @zarobek, @nazwafirmy
WHILE @@FETCH_STATUS = 0
	BEGIN
	PRINT @imie + ' '+@nazwisko + ' ' + CAST(@zarobek AS nvarchar(50)) +' '+@nazwafirmy
      FETCH NEXT FROM kursor INTO @imie, @nazwisko, @zarobek, @nazwafirmy
   END 
CLOSE kursor 
DEALLOCATE kursor




USE [Projekt]
GO
/****** Object:  StoredProcedure [dbo].[dystans]    Script Date: 2016-01-19 22:53:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[dystans] --exec dystans 'Widawa','Warszawa','',''…
(
@ToCity varchar(100)=null,
@FromCity varchar(100)=null,
@Data DATE,
@idTowar INTEGER,
@Granica INTEGER,
@idSpedytor nvarchar(50),
@idZamawiajacy nvarchar(50),
@DistanceInKilometers varchar(100) output,
@TimeinHours varchar(100) output
)
AS

     Declare @Object as Int;
Declare @ResponseText as Varchar(8000);
Declare @serviceUrl as varchar(500)
  set @serviceUrl = 'http://maps.googleapis.com/maps/api/distancematrix/xml?origins=' +@ToCity+ '&destinations=' +@FromCity+'&mode=driving&language=en-EN&units=metric;'
Exec sp_OACreate 'MSXML2.XMLHTTP', @Object OUT;
Exec sp_OAMethod @Object, 'open', NULL, 'get',
                @serviceUrl, --Your Web Service Url (invoked)
                 'false'
Exec sp_OAMethod @Object, 'send'
Exec sp_OAMethod @Object, 'responseText', @ResponseText OUTPUT

Declare @Response as XML

Select @ResponseText as XMLList

SET @Response = CAST(@ResponseText AS XML);

  Declare @Status as varchar(20)
   Declare @Distance as varchar(20)
   Declare @Time as varchar(20)
DECLARE @kierowca as INTEGER 
DECLARE @koszt as FLOAT

  set @Status= @Response.value('(DistanceMatrixResponse/row/element/status)[1]', 'varchar(20)') 
  print @Status
  if(@Status='ZERO_RESULTS')

   Begin

                     set @Distance=@Status
					 set @Time=@Status
   End
   else

   Begin
   set @Distance=@Response.value('(DistanceMatrixResponse/row/element/distance/text)[1]', 'varchar(20)')
   set @Time=@Response.value('(DistanceMatrixResponse/row/element/duration/value)[1]', 'varchar(20)') 
   End
  --Select @Response.value('(DistanceMatrixResponse/row/element/distance/text)[1]', 'varchar(10)') as Distance 
  select @Distance as Odleglosc
  DECLARE @liczba_km AS INTEGER
  IF (SUBSTRING(@Distance, 2, 1)=',')
	BEGIN
  SET @liczba_km=CAST(((SUBSTRING(@Distance, 1, 1))+(SUBSTRING(@Distance, 3, 3))) as INTEGER)
	END
  ELSE
	BEGIN
  SET @liczba_km=CAST((SUBSTRING(@Distance, 1, 4)) as INTEGER)
	END

SET @koszt=(SELECT dodatkowa.koszt
FROM 
(SELECT TOP 1 MALPA.id_kierowca as id_kierowca, MALPA.KOSZT as koszt
from
(SELECT [KOSZT]=((@liczba_km*LIPA.cena_km+@Granica*LIPA.granica+LIPA.niebezpieczne*LIPA.szkodliwe)*LIPA.wspolczynnik),LIPA.id_kierowca as id_kierowca--, LIPA.cena_id,LIPA.cena_km,LIPA.granica,LIPA.niebezpieczne,LIPA.szkodliwe,LIPA.wspolczynnik
FROM
(SELECT RO.nazwa as nazwa, RO.ladownosc_w_tonach AS ladownosc,S.vin as vin,K.id_kierowca as id_kierowca,K.imie as imie, K.nazwisko as nazwisko, F.id_firma as firma_id,U.niebezpieczne as niebezpieczne ,C.id AS cena_id,C.cena_km as cena_km,C.granica as granica,C.szkodliwe as szkodliwe,C.wspolczynnik as wspolczynnik
FROM tRodzaj_Samochodu as RO
join tSamochod AS S
on S.id_rodzaj_samochodu=RO.id_rodzaj_samochodu
join tKierowca AS K
on K.vin=S.vin
join tFirma AS F
on K.id_firma=F.id_firma
join tUslugi AS U
on U.id_usluga=S.id_usluga
join tCennik AS C
on C.id=F.id
WHERE RO.ladownosc_w_tonach>
((SELECT LOL.ladownosc from
(SELECT T.id_towar,T.nazwa, T.ilosc,T.masa_jednostki_miary,R.czy_niebezpieczny,T.ilosc*T.masa_jednostki_miary as ladownosc
FROM tTowar AS T
join tRodzaj_Towaru AS R
on R.id_rodzaj_towaru=T.id_rodzaj_towaru
WHERE T.id_towar=@idTowar) AS LOL)/1000)) AS LIPA
GROUP BY LIPA.id_kierowca ,LIPA.cena_km, LIPA.granica,LIPA.niebezpieczne,LIPA.szkodliwe,LIPA.wspolczynnik) AS MALPA
GROUP BY MALPA.id_kierowca,MALPA.KOSZT
ORDER BY KOSZT) AS dodatkowa)

SET @kierowca=(SELECT dodatkowa.id_kierowca
FROM 
(SELECT TOP 1 MALPA.id_kierowca as id_kierowca, MALPA.KOSZT as koszt
from
(SELECT [KOSZT]=((@liczba_km*LIPA.cena_km+@Granica*LIPA.granica+LIPA.niebezpieczne*LIPA.szkodliwe)*LIPA.wspolczynnik),LIPA.id_kierowca as id_kierowca--, LIPA.cena_id,LIPA.cena_km,LIPA.granica,LIPA.niebezpieczne,LIPA.szkodliwe,LIPA.wspolczynnik
FROM
(SELECT RO.nazwa as nazwa, RO.ladownosc_w_tonach AS ladownosc,S.vin as vin,K.id_kierowca as id_kierowca,K.imie as imie, K.nazwisko as nazwisko, F.id_firma as firma_id,U.niebezpieczne as niebezpieczne ,C.id AS cena_id,C.cena_km as cena_km,C.granica as granica,C.szkodliwe as szkodliwe,C.wspolczynnik as wspolczynnik
FROM tRodzaj_Samochodu as RO
join tSamochod AS S
on S.id_rodzaj_samochodu=RO.id_rodzaj_samochodu
join tKierowca AS K
on K.vin=S.vin
join tFirma AS F
on K.id_firma=F.id_firma
join tUslugi AS U
on U.id_usluga=S.id_usluga
join tCennik AS C
on C.id=F.id
WHERE RO.ladownosc_w_tonach>
((SELECT LOL.ladownosc from
(SELECT T.id_towar,T.nazwa, T.ilosc,T.masa_jednostki_miary,R.czy_niebezpieczny,T.ilosc*T.masa_jednostki_miary as ladownosc
FROM tTowar AS T
join tRodzaj_Towaru AS R
on R.id_rodzaj_towaru=T.id_rodzaj_towaru
WHERE T.id_towar=@idTowar) AS LOL)/1000)) AS LIPA
GROUP BY LIPA.id_kierowca ,LIPA.cena_km, LIPA.granica,LIPA.niebezpieczne,LIPA.szkodliwe,LIPA.wspolczynnik) AS MALPA
GROUP BY MALPA.id_kierowca,MALPA.KOSZT
ORDER BY KOSZT) AS dodatkowa)

  select @Time/3600 as CzasGodziny
  --select (@Time-(@Time/3600)*3600)/60 as CzasMinuty

BEGIN TRANSACTION [Tran1]

BEGIN TRY

INSERT INTO tTransport

VALUES (@idTowar,@kierowca,@idSpedytor,@idZamawiajacy,@koszt, @FromCity, @ToCity,@liczba_km, @Data )

COMMIT TRANSACTION [Tran1]

END TRY
BEGIN CATCH
  ROLLBACK TRANSACTION [Tran1]
END CATCH  


