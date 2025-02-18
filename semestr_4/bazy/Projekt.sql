USE [master]
GO
/****** Object:  Database [Projekt]    Script Date: 2016-01-25 13:00:49 ******/
CREATE DATABASE [Projekt]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Projekt', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\Projekt.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'Projekt_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\Projekt_log.ldf' , SIZE = 1024KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [Projekt] SET COMPATIBILITY_LEVEL = 120
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Projekt].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Projekt] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Projekt] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Projekt] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Projekt] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Projekt] SET ARITHABORT OFF 
GO
ALTER DATABASE [Projekt] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [Projekt] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Projekt] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Projekt] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Projekt] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Projekt] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Projekt] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Projekt] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Projekt] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Projekt] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Projekt] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Projekt] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Projekt] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Projekt] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Projekt] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Projekt] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Projekt] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Projekt] SET RECOVERY FULL 
GO
ALTER DATABASE [Projekt] SET  MULTI_USER 
GO
ALTER DATABASE [Projekt] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Projekt] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Projekt] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Projekt] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
ALTER DATABASE [Projekt] SET DELAYED_DURABILITY = DISABLED 
GO
USE [Projekt]
GO
/****** Object:  User [spedytor]    Script Date: 2016-01-25 13:00:49 ******/
CREATE USER [spedytor] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  User [Analityk]    Script Date: 2016-01-25 13:00:49 ******/
CREATE USER [Analityk] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  User [Admin]    Script Date: 2016-01-25 13:00:49 ******/
CREATE USER [Admin] WITHOUT LOGIN WITH DEFAULT_SCHEMA=[dbo]
GO
ALTER ROLE [db_owner] ADD MEMBER [Admin]
GO
ALTER ROLE [db_accessadmin] ADD MEMBER [Admin]
GO
ALTER ROLE [db_securityadmin] ADD MEMBER [Admin]
GO
ALTER ROLE [db_ddladmin] ADD MEMBER [Admin]
GO
ALTER ROLE [db_backupoperator] ADD MEMBER [Admin]
GO
ALTER ROLE [db_datareader] ADD MEMBER [Admin]
GO
ALTER ROLE [db_datawriter] ADD MEMBER [Admin]
GO
ALTER ROLE [db_denydatareader] ADD MEMBER [Admin]
GO
ALTER ROLE [db_denydatawriter] ADD MEMBER [Admin]
GO
USE [Projekt]
GO
/****** Object:  Sequence [dbo].[licz]    Script Date: 2016-01-25 13:00:50 ******/
CREATE SEQUENCE [dbo].[licz] 
 AS [bigint]
 START WITH 1
 INCREMENT BY 1
 MINVALUE -9223372036854775808
 MAXVALUE 9223372036854775807
 CACHE 
GO
USE [Projekt]
GO
/****** Object:  Sequence [dbo].[licznik]    Script Date: 2016-01-25 13:00:50 ******/
CREATE SEQUENCE [dbo].[licznik] 
 AS [bigint]
 START WITH -9223372036854775808
 INCREMENT BY 1
 MINVALUE -9223372036854775808
 MAXVALUE 9223372036854775807
 CACHE 
GO
USE [Projekt]
GO
/****** Object:  Sequence [dbo].[licznik1]    Script Date: 2016-01-25 13:00:50 ******/
CREATE SEQUENCE [dbo].[licznik1] 
 AS [bigint]
 START WITH 1
 INCREMENT BY 1
 MINVALUE -9223372036854775808
 MAXVALUE 9223372036854775807
 CACHE 
GO
USE [Projekt]
GO
/****** Object:  Sequence [dbo].[numer]    Script Date: 2016-01-25 13:00:50 ******/
CREATE SEQUENCE [dbo].[numer] 
 AS [bigint]
 START WITH 1
 INCREMENT BY 1
 MINVALUE -9223372036854775808
 MAXVALUE 9223372036854775807
 CACHE 
GO
/****** Object:  UserDefinedFunction [dbo].[funkcja1]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[funkcja1]
()
RETURNS nvarchar(1000)
AS
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
DECLARE @pomoc nvarchar(1000)
DECLARE @cos nvarchar(1000)

OPEN kursor 
FETCH NEXT FROM kursor INTO @imie, @nazwisko, @liczba
WHILE @@FETCH_STATUS = 0
	BEGIN
	SET @pomoc=@imie + ' '+@nazwisko + ' ' + CAST(@liczba AS nvarchar(50))
	RETURN @pomoc
	FETCH NEXT FROM kursor INTO @imie, @nazwisko, @liczba
	END
CLOSE kursor 
DEALLOCATE kursor
RETURN @cos
END
GO
/****** Object:  UserDefinedFunction [dbo].[funkcja2]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[funkcja2]
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
GO
/****** Object:  UserDefinedFunction [dbo].[funkcja3]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[funkcja3](
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

GO
/****** Object:  UserDefinedFunction [dbo].[funkcja4]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE FUNCTION [dbo].[funkcja4]
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
GO
/****** Object:  Table [dbo].[tCennik]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tCennik](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[szkodliwe] [float] NOT NULL,
	[cena_km] [float] NOT NULL,
	[granica] [float] NOT NULL,
	[wspolczynnik] [float] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tFirma]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[tFirma](
	[id_firma] [int] IDENTITY(1,1) NOT NULL,
	[id] [int] NOT NULL,
	[nazwa] [nvarchar](50) NOT NULL,
	[nip] [nvarchar](15) NULL,
	[regon] [char](15) NULL,
	[kod_pocztowy] [nvarchar](5) NOT NULL,
	[poczta] [nvarchar](50) NOT NULL,
	[ulica] [nvarchar](50) NOT NULL,
	[nr_lokalu] [char](10) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_firma] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[tHistoria_Transportu]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tHistoria_Transportu](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[id_towar] [int] NOT NULL,
	[id_kierowca] [int] NOT NULL,
	[id_spedytor] [int] NOT NULL,
	[id_zamawiajacy] [int] NOT NULL,
	[koszt] [float] NOT NULL,
	[skad] [nvarchar](50) NOT NULL,
	[dokad] [nvarchar](50) NOT NULL,
	[kilometry] [float] NOT NULL,
	[kiedy] [date] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tJednostka]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tJednostka](
	[id_jednostka] [int] IDENTITY(1,1) NOT NULL,
	[nazwa] [nvarchar](50) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_jednostka] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tKierowca]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[tKierowca](
	[id_kierowca] [int] IDENTITY(1,1) NOT NULL,
	[vin] [char](17) NOT NULL,
	[id_firma] [int] NOT NULL,
	[imie] [nvarchar](50) NOT NULL,
	[nazwisko] [nvarchar](50) NOT NULL,
	[pesel] [nvarchar](11) NOT NULL,
	[miejsce_urodzenia] [nvarchar](50) NOT NULL,
	[data_otrzymania_uprawnien] [date] NOT NULL,
	[data_badan_lekarskich] [date] NOT NULL,
	[kod_pocztowy] [nvarchar](5) NOT NULL,
	[poczta] [nvarchar](50) NOT NULL,
	[ulica] [nvarchar](50) NOT NULL,
	[nr_lokalu] [nvarchar](10) NOT NULL,
	[czy_adr] [bit] NOT NULL,
	[czy_dostepny] [bit] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_kierowca] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[tOleje]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tOleje](
	[id] [int] NOT NULL,
	[nazwa] [nvarchar](50) NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tOleje1]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tOleje1](
	[id] [int] NOT NULL DEFAULT (NEXT VALUE FOR [licznik1]),
	[nazwa] [nvarchar](50) NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tPodatek]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tPodatek](
	[id_podatek] [int] IDENTITY(1,1) NOT NULL,
	[nazwa] [nvarchar](50) NOT NULL,
	[stawka] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_podatek] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tRodzaj_Samochodu]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tRodzaj_Samochodu](
	[id_rodzaj_samochodu] [int] IDENTITY(1,1) NOT NULL,
	[nazwa] [nvarchar](50) NOT NULL,
	[dlugosc] [float] NOT NULL,
	[wysokosc] [float] NOT NULL,
	[szerokosc] [float] NOT NULL,
	[objetosc] [float] NOT NULL,
	[ladownosc_w_tonach] [float] NOT NULL,
	[liczba_miejsc] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_rodzaj_samochodu] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tRodzaj_Towaru]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tRodzaj_Towaru](
	[id_rodzaj_towaru] [int] IDENTITY(1,1) NOT NULL,
	[id_podatek] [int] NOT NULL,
	[nazwa] [nvarchar](50) NOT NULL,
	[czy_niebezpieczny] [bit] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_rodzaj_towaru] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tSamochod]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[tSamochod](
	[vin] [char](17) NOT NULL,
	[id_usluga] [int] NOT NULL,
	[id_rodzaj_samochodu] [int] NOT NULL,
	[nr_rej] [char](8) NOT NULL,
	[marka] [nvarchar](50) NOT NULL,
	[model] [nvarchar](50) NOT NULL,
	[poj_silnika] [float] NOT NULL,
	[rok_produkcji] [int] NOT NULL,
	[moc_silnika] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[vin] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[tSpedytor]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[tSpedytor](
	[id_spedytor] [int] IDENTITY(1,1) NOT NULL,
	[imie] [nvarchar](50) NOT NULL,
	[nazwisko] [nvarchar](50) NOT NULL,
	[pesel] [nvarchar](11) NOT NULL,
	[miejsce_urodzenia] [nvarchar](50) NOT NULL,
	[kod_pocztowy] [char](5) NOT NULL,
	[poczta] [nvarchar](50) NOT NULL,
	[ulica] [nvarchar](50) NOT NULL,
	[nr_lokalu] [nvarchar](10) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_spedytor] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[tTowar]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tTowar](
	[id_towar] [int] IDENTITY(1,1) NOT NULL,
	[id_rodzaj_towaru] [int] NOT NULL,
	[id_jednostka] [int] NOT NULL,
	[nazwa] [nvarchar](50) NOT NULL,
	[ilosc] [int] NOT NULL,
	[zajmowana_objetosc_przez_jednostke] [float] NOT NULL,
	[masa_jednostki_miary] [float] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_towar] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tTransport]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tTransport](
	[id_transport] [int] IDENTITY(1,1) NOT NULL,
	[id_towar] [int] NOT NULL,
	[id_kierowca] [int] NOT NULL,
	[id_spedytor] [int] NOT NULL,
	[id_zamawiajacy] [int] NOT NULL,
	[koszt] [float] NOT NULL,
	[skad] [nvarchar](50) NOT NULL,
	[dokad] [nvarchar](50) NOT NULL,
	[kilometry] [float] NOT NULL,
	[kiedy] [date] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_transport] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tUslugi]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[tUslugi](
	[id_usluga] [int] IDENTITY(1,1) NOT NULL,
	[nazwa] [nvarchar](80) NOT NULL,
	[przewoz_osob] [bit] NOT NULL,
	[osoby_niepelnosprawne] [bit] NOT NULL,
	[przewoz_towaru] [bit] NOT NULL,
	[niebezpieczne] [bit] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_usluga] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[tZamawiajacy]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[tZamawiajacy](
	[id_zamawiajacy] [int] IDENTITY(1,1) NOT NULL,
	[nazwa_firmy] [nvarchar](50) NULL,
	[nip] [nvarchar](15) NULL,
	[regon] [char](15) NULL,
	[imie] [nvarchar](50) NULL,
	[nazwisko] [nvarchar](50) NULL,
	[pesel] [char](11) NULL,
	[kod_pocztowy] [char](5) NOT NULL,
	[poczta] [nvarchar](50) NOT NULL,
	[ulica] [nvarchar](50) NOT NULL,
	[nr_lokalu] [nvarchar](10) NOT NULL,
	[czy_firma] [bit] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[id_zamawiajacy] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  View [dbo].[widok_drugi]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

CREATE VIEW [dbo].[widok_drugi]
AS
SELECT        imie, nazwisko, wiek, SUM(liczba_przyjetych_zlecen) AS liczba_zlecen, SUM(suma_zlecen) AS suma, ROUND(SUM(suma_zlecen) / SUM(liczba_przyjetych_zlecen), 
                         2) AS srednia
FROM            (SELECT DISTINCT 
                                                    S.imie, S.nazwisko, DATEDIFF(year, CAST('19' + SUBSTRING(S.pesel, 1, 2) + '-05-06' AS date), CAST(GETDATE() AS date)) AS wiek, 
                                                    COUNT(TRANS.id_spedytor) AS liczba_przyjetych_zlecen, SUM(TRANS.koszt) AS suma_zlecen, AVG(TRANS.koszt) AS srednia
                          FROM            dbo.tTowar AS T INNER JOIN
                                                    dbo.tTransport AS TRANS ON TRANS.id_towar = T.id_towar INNER JOIN
                                                    dbo.tSpedytor AS S ON S.id_spedytor = TRANS.id_spedytor INNER JOIN
                                                    dbo.tKierowca AS K ON K.id_kierowca = TRANS.id_kierowca INNER JOIN
                                                    dbo.tFirma AS F ON F.id_firma = K.id_firma
                          GROUP BY S.imie, S.nazwisko, S.pesel) AS jakies
GROUP BY imie, nazwisko, wiek
GO
/****** Object:  View [dbo].[widok_pierwszy]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[widok_pierwszy]
AS
SELECT DISTINCT 
                         K.imie, K.nazwisko, K.id_kierowca, DATEDIFF(year, CAST('19' + SUBSTRING(K.pesel, 1, 2) + '-05-06' AS date), CAST(GETDATE() AS date)) AS wiek, SUM(T.kilometry) 
                         AS kilometraz, YEAR(GETDATE()) - YEAR(K.data_otrzymania_uprawnien) AS ile_lat_uprawnienia, COUNT(T.id_transport) AS ile_razy, 
                         CASE WHEN (K.czy_dostepny = 0) THEN 'W TRASIE' ELSE 'GOTOWY DO PRACY' END AS CzyDostepny, CASE WHEN (K.czy_adr = 0) 
                         THEN 'NIE' ELSE 'TAK' END AS [czy moze niebezpieczne], CASE WHEN (datediff(day, CAST(getdate() AS date), K.data_badan_lekarskich) < 100) 
                         THEN 'SKIERUJ PRACOWNIKA NA BADANIA' ELSE 'WSZYSTKO OK' END AS [CZY WAZNE BADANIA]
FROM            dbo.tKierowca AS K INNER JOIN
                         dbo.tTransport AS T ON T.id_kierowca = K.id_kierowca INNER JOIN
                         dbo.tTowar AS Towar ON T.id_towar = Towar.id_towar
GROUP BY K.imie, K.nazwisko, K.id_kierowca, K.pesel, K.data_otrzymania_uprawnien, K.czy_dostepny, K.czy_adr, K.data_badan_lekarskich
GO
/****** Object:  View [dbo].[widok_trzeci]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[widok_trzeci]  AS
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
GROUP BY S.imie, S.nazwisko,S.pesel,TRANS.koszt) jakies
GROUP BY imie,nazwisko,wiek
GO
/****** Object:  View [dbo].[widokC]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE VIEW [dbo].[widokC]
AS
SELECT        SUM(T.kilometry) AS liczba_przejechanych_km, MAX(K.imie) as imie, MAX(K.nazwisko) as nazwisko, COUNT_BIG(*) AS tmp
FROM            dbo.tTransport AS T INNER JOIN
                         dbo.tKierowca AS K ON T.id_kierowca = K.id_kierowca
GROUP BY K.pesel
GO
ALTER TABLE [dbo].[tOleje] ADD  DEFAULT (NEXT VALUE FOR [licznik]) FOR [id]
GO
ALTER TABLE [dbo].[tFirma]  WITH CHECK ADD FOREIGN KEY([id])
REFERENCES [dbo].[tCennik] ([id])
GO
ALTER TABLE [dbo].[tHistoria_Transportu]  WITH CHECK ADD FOREIGN KEY([id_kierowca])
REFERENCES [dbo].[tKierowca] ([id_kierowca])
GO
ALTER TABLE [dbo].[tHistoria_Transportu]  WITH CHECK ADD FOREIGN KEY([id_spedytor])
REFERENCES [dbo].[tSpedytor] ([id_spedytor])
GO
ALTER TABLE [dbo].[tHistoria_Transportu]  WITH CHECK ADD FOREIGN KEY([id_towar])
REFERENCES [dbo].[tTowar] ([id_towar])
GO
ALTER TABLE [dbo].[tHistoria_Transportu]  WITH CHECK ADD FOREIGN KEY([id_zamawiajacy])
REFERENCES [dbo].[tZamawiajacy] ([id_zamawiajacy])
GO
ALTER TABLE [dbo].[tKierowca]  WITH CHECK ADD FOREIGN KEY([id_firma])
REFERENCES [dbo].[tFirma] ([id_firma])
GO
ALTER TABLE [dbo].[tKierowca]  WITH CHECK ADD FOREIGN KEY([vin])
REFERENCES [dbo].[tSamochod] ([vin])
GO
ALTER TABLE [dbo].[tRodzaj_Towaru]  WITH CHECK ADD FOREIGN KEY([id_podatek])
REFERENCES [dbo].[tPodatek] ([id_podatek])
GO
ALTER TABLE [dbo].[tSamochod]  WITH CHECK ADD FOREIGN KEY([id_rodzaj_samochodu])
REFERENCES [dbo].[tRodzaj_Samochodu] ([id_rodzaj_samochodu])
GO
ALTER TABLE [dbo].[tSamochod]  WITH CHECK ADD FOREIGN KEY([id_usluga])
REFERENCES [dbo].[tUslugi] ([id_usluga])
GO
ALTER TABLE [dbo].[tTowar]  WITH CHECK ADD FOREIGN KEY([id_jednostka])
REFERENCES [dbo].[tJednostka] ([id_jednostka])
GO
ALTER TABLE [dbo].[tTowar]  WITH CHECK ADD FOREIGN KEY([id_rodzaj_towaru])
REFERENCES [dbo].[tRodzaj_Towaru] ([id_rodzaj_towaru])
GO
ALTER TABLE [dbo].[tTransport]  WITH CHECK ADD FOREIGN KEY([id_kierowca])
REFERENCES [dbo].[tKierowca] ([id_kierowca])
GO
ALTER TABLE [dbo].[tTransport]  WITH CHECK ADD FOREIGN KEY([id_spedytor])
REFERENCES [dbo].[tSpedytor] ([id_spedytor])
GO
ALTER TABLE [dbo].[tTransport]  WITH CHECK ADD FOREIGN KEY([id_towar])
REFERENCES [dbo].[tTowar] ([id_towar])
GO
ALTER TABLE [dbo].[tTransport]  WITH CHECK ADD FOREIGN KEY([id_zamawiajacy])
REFERENCES [dbo].[tZamawiajacy] ([id_zamawiajacy])
GO
/****** Object:  StoredProcedure [dbo].[dystans]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[dystans] --exec dystans 'Widawa','Warszawa','',''
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

BEGIN TRANSACTION

INSERT INTO tTransport

VALUES (@idTowar,@kierowca,@idSpedytor,@idZamawiajacy,@koszt, @FromCity, @ToCity,@liczba_km, @Data )

COMMIT 
GO
/****** Object:  StoredProcedure [dbo].[mis]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[mis]
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
	FETCH NEXT FROM kursor INTO @id_transport, @id_towar, @id_kierowca,@id_spedytor,@id_zamawiajacy,@koszt,@skad,@dokad,@kilometry,@kiedy
	SET IDENTITY_INSERT tHistoria_Transportu OFF
	END
CLOSE kursor 
DEALLOCATE kursor

								


GO
/****** Object:  StoredProcedure [dbo].[zarobek]    Script Date: 2016-01-25 13:00:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[zarobek]
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
PRINT 'Zarobione dla firmy pieniadze przez kierowcow poniżej 50 roku zycia:'

OPEN kursor 
FETCH NEXT FROM kursor INTO @imie, @nazwisko, @zarobek, @nazwafirmy
WHILE @@FETCH_STATUS = 0
	BEGIN
	PRINT @imie + ' '+@nazwisko + ' ' + CAST(@zarobek AS nvarchar(50)) +' '+@nazwafirmy
      FETCH NEXT FROM kursor INTO @imie, @nazwisko, @zarobek, @nazwafirmy
   END 
CLOSE kursor 
DEALLOCATE kursor

GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPane1', @value=N'[0E232FF0-B466-11cf-A24F-00AA00A3EFFF, 1.00]
Begin DesignProperties = 
   Begin PaneConfigurations = 
      Begin PaneConfiguration = 0
         NumPanes = 4
         Configuration = "(H (1[40] 4[20] 2[20] 3) )"
      End
      Begin PaneConfiguration = 1
         NumPanes = 3
         Configuration = "(H (1 [50] 4 [25] 3))"
      End
      Begin PaneConfiguration = 2
         NumPanes = 3
         Configuration = "(H (1 [50] 2 [25] 3))"
      End
      Begin PaneConfiguration = 3
         NumPanes = 3
         Configuration = "(H (4 [30] 2 [40] 3))"
      End
      Begin PaneConfiguration = 4
         NumPanes = 2
         Configuration = "(H (1 [56] 3))"
      End
      Begin PaneConfiguration = 5
         NumPanes = 2
         Configuration = "(H (2 [66] 3))"
      End
      Begin PaneConfiguration = 6
         NumPanes = 2
         Configuration = "(H (4 [50] 3))"
      End
      Begin PaneConfiguration = 7
         NumPanes = 1
         Configuration = "(V (3))"
      End
      Begin PaneConfiguration = 8
         NumPanes = 3
         Configuration = "(H (1[56] 4[18] 2) )"
      End
      Begin PaneConfiguration = 9
         NumPanes = 2
         Configuration = "(H (1 [75] 4))"
      End
      Begin PaneConfiguration = 10
         NumPanes = 2
         Configuration = "(H (1[66] 2) )"
      End
      Begin PaneConfiguration = 11
         NumPanes = 2
         Configuration = "(H (4 [60] 2))"
      End
      Begin PaneConfiguration = 12
         NumPanes = 1
         Configuration = "(H (1) )"
      End
      Begin PaneConfiguration = 13
         NumPanes = 1
         Configuration = "(V (4))"
      End
      Begin PaneConfiguration = 14
         NumPanes = 1
         Configuration = "(V (2))"
      End
      ActivePaneConfig = 0
   End
   Begin DiagramPane = 
      Begin Origin = 
         Top = -96
         Left = 0
      End
      Begin Tables = 
         Begin Table = "K"
            Begin Extent = 
               Top = 6
               Left = 38
               Bottom = 135
               Right = 291
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "T"
            Begin Extent = 
               Top = 138
               Left = 38
               Bottom = 267
               Right = 225
            End
            DisplayFlags = 280
            TopColumn = 0
         End
         Begin Table = "Towar"
            Begin Extent = 
               Top = 270
               Left = 38
               Bottom = 399
               Right = 341
            End
            DisplayFlags = 280
            TopColumn = 0
         End
      End
   End
   Begin SQLPane = 
   End
   Begin DataPane = 
      Begin ParameterDefaults = ""
      End
   End
   Begin CriteriaPane = 
      Begin ColumnWidths = 12
         Column = 1440
         Alias = 900
         Table = 1170
         Output = 720
         Append = 1400
         NewValue = 1170
         SortType = 1350
         SortOrder = 1410
         GroupBy = 1350
         Filter = 1350
         Or = 1350
         Or = 1350
         Or = 1350
      End
   End
End
' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'widok_pierwszy'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_DiagramPaneCount', @value=1 , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'VIEW',@level1name=N'widok_pierwszy'
GO
USE [master]
GO
ALTER DATABASE [Projekt] SET  READ_WRITE 
GO
