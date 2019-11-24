
USE [Projekt]
GO
/****** Object:  UserDefinedFunction [dbo].[funkcja2]    Script Date: 2016-01-20 13:43:06 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER FUNCTION [dbo].[funkcja2]
(@id_kierowcy INTEGER)
RETURNS @ret table
( [ID] int primary key NOT NULL,
	[IMIE] nvarchar(50) NOT NULL,
	[NAZWISKO] NVARCHAR(50) NOT NULL,
	[ILOSC_DNI] INTEGER )

BEGIN
DECLARE @pomoc DATE
DECLARE @idosoba integer
DECLARE @imie nvarchar(50)
DECLARE @nazwisko nvarchar(50)
DECLARE @liczba_dni INTEGER
SET @idosoba=@id_kierowcy
SET @imie=(SELECT imie from tKierowca where id_kierowca=@id_kierowcy)
SET @nazwisko=(SELECT nazwisko from tKierowca where id_kierowca=@id_kierowcy)
SET @pomoc=(SELECT data_badan_lekarskich from tKierowca where id_kierowca=@id_kierowcy)
SET @liczba_dni=CAST((DATEDIFF(DD,GETDATE(),@pomoc)) AS INTEGER)

INSERT @ret 
SELECT @idosoba, @imie, @nazwisko, @liczba_dni
RETURN 
END




SET ANSI_NULLS ON GO SET QUOTED_IDENTIFIER ON
GO
ALTER FUNCTION [dbo].[funkcja3](
@id_kierowcy INTEGER,
@data_od DATE)
RETURNS FLOAT
BEGIN
DECLARE @pomoc FLOAT
DECLARE @pomoc_dwa FLOAT
DECLARE @pomoc_trzy FLOAT
DECLARE @adr INTEGER
DECLARE @premia FLOAT
SET @pomoc=(
select SUM(T.koszt)
from tKierowca as K
join (
select * from tTransport
union
select * from tHistoria_Transportu) AS T
on K.id_kierowca=T.id_kierowca
where T.kiedy between @data_od AND GETDATE() AND K.id_kierowca=@id_kierowcy)
SET @pomoc_dwa=(
select count(T.koszt)
from tKierowca as K
join (
select * from tTransport
union
select * from tHistoria_Transportu) AS T
on K.id_kierowca=T.id_kierowca
where T.kiedy between @data_od AND GETDATE() AND K.id_kierowca=@id_kierowcy)
SET @pomoc_trzy=(
select SUM(T.kilometry)
from tKierowca as K
join (
select * from tTransport
union
select * from tHistoria_Transportu) AS T
on K.id_kierowca=T.id_kierowca
where T.kiedy between @data_od AND GETDATE() AND K.id_kierowca=@id_kierowcy)
SET @adr=(
SELECT czy_adr from tKierowca 
where id_kierowca=@id_kierowcy)
IF(@pomoc_trzy<1000)
SET @premia=@pomoc*0.05+@pomoc_dwa*50+@adr*200 
ELSE 
SET @premia=@pomoc*0.1+@pomoc_dwa*60+@adr*200 
RETURN @premia
END




USE [Projekt]
GO
/****** Object:  UserDefinedFunction [dbo].[funkcja4]    Script Date: 2016-01-20 14:01:17 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER FUNCTION [dbo].[funkcja4]
()
RETURNS @ret table (
[IMIE] nvarchar(50) NOT NULL,
	[NAZWISKO] NVARCHAR(50) NOT NULL,
	[liczba] FLOAT )
BEGIN

DECLARE kursor CURSOR FOR
select K.imie, K.nazwisko,SUM(T.kilometry)
from tKierowca AS K
join(
select * from tTransport
union
select * from tHistoria_Transportu) AS T
on K.id_kierowca=T.id_kierowca
WHERE DateDIFF(year, cast('19'+SUBSTRING(K.pesel,1,2)+'-05-06' as date), Cast(getdate() as date))<50
GROUP BY K.imie,K.nazwisko

DECLARE @imie nvarchar(50)
DECLARE @nazwisko nvarchar(50)
DECLARE @liczba FLOAT

OPEN kursor 
FETCH NEXT FROM kursor INTO @imie, @nazwisko, @liczba
WHILE @@FETCH_STATUS = 0
	BEGIN
	INSERT @ret 
	SELECT @imie, @nazwisko, @liczba
	FETCH NEXT FROM kursor INTO @imie, @nazwisko, @liczba
	END
CLOSE kursor 
DEALLOCATE kursor
RETURN
END
