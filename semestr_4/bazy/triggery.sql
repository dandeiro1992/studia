USE [Projekt]
GO
/****** Object:  Trigger [dbo].[DodajKierowce]    Script Date: 2016-01-25 12:11:33 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER TRIGGER [dbo].[DodajKierowce]
	on [dbo].[tKierowca]
FOR INSERT 
AS
BEGIN

DECLARE @idkierowca INTEGER
	SET NOCOUNT ON;
SET @idkierowca=(SELECT MAX(id_kierowca) FROM tKierowca)
DECLARE @vin nvarchar(17)
SET @vin=(SELECT vin as samochod from tKierowca where id_kierowca=@idkierowca)

IF ((SELECT vin as samochod from tKierowca where id_kierowca=@idkierowca) IN (SELECT vin from tSamochod))
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Samochod o podanym numerze vin '+@vin+' ma juz wlasciciela'

	END

IF ((SELECT DateDIFF(year, cast('19'+SUBSTRING(pesel,1,2)+'-05-06' as date), Cast(getdate() as date))  wiek 
from tKierowca where id_kierowca=@idkierowca) >67)
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Ta osoba powinna ju¿ byæ na emeryturze'
	END

IF ((SELECT DateDIFF(year, data_otrzymania_uprawnien, Cast(getdate() as date)) as kiedy
	from tKierowca where id_kierowca=@idkierowca) IS NULL)
	BEGIN 
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Ta osoba nie ma uprawnien'
	END
ELSE IF ((SELECT DateDIFF(year, data_otrzymania_uprawnien, Cast(getdate() as date)) as kiedy
	from tKierowca where id_kierowca=@idkierowca)<0 )
		BEGIN 
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Ta osoba nie ma jeszcze uprawnien'
	END

IF ((SELECT DateDIFF(day, data_badan_lekarskich, Cast(getdate() as date)) as badania
	from tKierowca where id_kierowca=@idkierowca) >0)
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Ta osoba nie ma badañ lekarskich'
	END

END





USE [Projekt]
GO
/****** Object:  Trigger [dbo].[DodajTransport]    Script Date: 2016-01-25 12:40:54 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER TRIGGER [dbo].[DodajTransport]
	on [dbo].[tTransport]
FOR INSERT 
AS
BEGIN
DECLARE @idtransport integer
	SET NOCOUNT ON;
SET @idtransport=(SELECT MAX(id_transport) FROM tTransport)

IF ((SELECT koszt as koszt from tTransport where id_transport=@idtransport)<0) 
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Przejazd nie moze kosztowac mniej niz 0 zl'
	END

IF ((SELECT kilometry as kilometry from tTransport where id_transport=@idtransport)<0) 
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Przejazd nie moze miec mniej niz 0 km'
	END

IF (DATEDIFF(day,Cast(getdate() as date),(SELECT kiedy as data from tTransport where id_transport=@idtransport))>20)
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Nie mozna zaplanowac trasy z takim wyprzedzeniem'
	END
IF (DATEDIFF(day,Cast(getdate() as date),(SELECT kiedy as data from tTransport where id_transport=@idtransport))<0)
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'podales zla date'
	END
END




USE [Projekt]
GO
/****** Object:  Trigger [dbo].[Kursy]    Script Date: 2016-01-25 12:42:43 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER TRIGGER [dbo].[Kursy]
	on [dbo].[tTransport]
FOR INSERT 
AS
BEGIN
DECLARE @idkierowca integer

set @idkierowca=(SELECT id_kierowca from inserted)

	SET NOCOUNT ON;
IF ((SELECT COUNT(id_transport) as liczba from tTransport where id_kierowca=@idkierowca AND DATEDIFF(d, kiedy, Cast(getdate() as date)) < 30) > 20)
	BEGIN
			RAISERROR('"%d rows have been modified"' , 0, 1, @@rowcount)
			PRINT 'Za duzo tras dla tego kierowcy w ciagu ostatnich 30 dni'
	END

END
