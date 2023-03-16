USE Phonebook
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[PHONE_NUMBERS]') AND type IN (N'U'))
	DROP TABLE [PHONE_NUMBERS]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[PHONE_TYPES]') AND type IN (N'U'))
	DROP TABLE [PHONE_TYPES]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[PERSONS]') AND type IN (N'U'))
	DROP TABLE [PERSONS]
GO

IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[CITIES]') AND type IN (N'U'))
	DROP TABLE [CITIES]
GO

	-- Create City Table
CREATE TABLE [CITIES](
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[CITY_NAME] [NVARCHAR](64) NOT NULL,
	[DISTRICT] [NVARCHAR](64) NOT NULL,
	
	CONSTRAINT PK_CITIES_ID PRIMARY KEY(ID),
)
GO

	-- Create Company Table
CREATE TABLE [COMPANIES](
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[COMPANY_NAME] [NVARCHAR](64) NOT NULL,
	
	CONSTRAINT PK_COMPANIES_ID PRIMARY KEY(ID),
)
GO

	-- Create Position Table
CREATE TABLE [POSITIONS](
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[POSITION_NAME] [NVARCHAR](64) NOT NULL,
	
	CONSTRAINT PK_POSITIONS_ID PRIMARY KEY(ID),
)
GO



	-- Create Phone types Table

CREATE TABLE [PHONE_TYPES](
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[TYPE] [NVARCHAR](16) NOT NULL,

	CONSTRAINT PK_PHONE_TYPES_ID PRIMARY KEY(ID),
)
GO

	-- Create Phone types unique index

CREATE UNIQUE INDEX UX_PHONE_TYPES_TYPE
ON PHONE_TYPES([TYPE]);

	-- Create Persons Table

CREATE TABLE [PERSONS](
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[FIRST_NAME] [NVARCHAR](32) NOT NULL,
	[MIDDLE_NAME] [NVARCHAR](32) NOT NULL,
	[LAST_NAME] [NVARCHAR](32) NOT NULL,
	[UCN] [NVARCHAR](32) NOT NULL,
	[CITY_ID] [INT] NOT NULL,
	[ADDRESS] [NVARCHAR](64) NOT NULL,
	[COMPANY_ID] [INT] NOT NULL,
	[POSITION_ID] [INT] NOT NULL,

	CONSTRAINT PK_PERSONS_ID PRIMARY KEY(ID),
	CONSTRAINT FK_PERSONS_CITY_ID FOREIGN KEY(CITY_ID) REFERENCES CITIES(ID),
	CONSTRAINT FK_PERSONS_COMPANY_ID FOREIGN KEY(COMPANY_ID) REFERENCES COMPANIES(ID),
	CONSTRAINT FK_PERSONS_POSITION_ID FOREIGN KEY(POSITION_ID) REFERENCES POSITIONS(ID),
)
GO


	-- Create Persons indexes
CREATE UNIQUE INDEX UX_PERSONS_UCN ON PERSONS(UCN)
GO

CREATE INDEX IX_PERSONS_CITY_ID ON PERSONS(CITY_ID)
GO

	-- Create Phone numbers Table

CREATE TABLE [PHONE_NUMBERS](
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[PERSON_ID] [INT] NOT NULL,
	[PHONE_TYPE_ID] [INT] NOT NULL,
	[PHONE_NUMBER] [VARCHAR](15) NOT NULL,

	CONSTRAINT PK_PHONE_NUMBERS_ID PRIMARY KEY(ID),
	CONSTRAINT FK_PHONE_NUMBERS_PERSON_ID FOREIGN KEY(PERSON_ID) REFERENCES PERSONS(ID),
	CONSTRAINT FK_PHONE_NUMBERS_PHONE_TYPE_ID FOREIGN KEY(PHONE_TYPE_ID) REFERENCES PHONE_TYPES(ID),
)
GO

	-- Create Phone numbers indexes
CREATE UNIQUE INDEX UX_PHONE_NUMBERS_PERSON_ID_PHONE_TYPE_ID_PHONE_NUMBER on PHONE_NUMBERS(PERSON_ID, PHONE_TYPE_ID, PHONE_NUMBER)
GO


	-- Create Users Table
CREATE TABLE [USERS](
	[ID] [INT] IDENTITY(1,1) NOT NULL,
	[UPDATE_COUNTER] [INT] NOT NULL,
	[USERNAME] [NVARCHAR](128) NOT NULL,
	[PASSWORD] [NVARCHAR](128) NOT NULL,
	
	CONSTRAINT PK_USERS_ID PRIMARY KEY(ID),
)
GO

-- username = 'ivan' password = '1234'
INSERT INTO [USERS] VALUES(0 ,'ivan', '4f37c061f1854f9682f543fecb5ee9d652c803235970202de97c6e40c8361766')
GO