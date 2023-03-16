#pragma once
#pragma once
#include "framework.h"

const int CITIES_CITY_NAME_LENGTH = 64;
const int CITIES_DISTRICT_LENGTH = 64;

const int PERSONS_NAME_LENGTH = 32;
const int PERSONS_UCN_LENGTH = 32;
const int PERSONS_ADDRESS_LENGTH = 64;

const int PHONE_TYPES_TYPE_LENGTH = 16;

const int PHONE_NUMBERS_NUMBER_LENGTH = 15;

const int USERS_USERNAME_LENGTH = 128;
const int USERS_PASSWORD_LENGTH = 128;

const int COMPANIES_COMPANY_NAME_LENGTH = 64;

const int POSITIONS_POSITION_NAME_LENGTH = 64;


/// <summary>
/// Дискова структура за таблицата USERS
/// </summary>
struct USERS
{
	long lID;
	long lUpdateCounter;
	TCHAR szUsername[USERS_USERNAME_LENGTH];
	TCHAR szPassword[USERS_PASSWORD_LENGTH];

	USERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};


/// <summary>
/// Дискова структура за таблицата CITIES
/// </summary>
struct CITIES
{
	long lID;
	long lUpdateCounter;
	TCHAR szCityName[CITIES_CITY_NAME_LENGTH];
	TCHAR szDistrict[CITIES_DISTRICT_LENGTH];

	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};

/// <summary>
/// Дискова структура за таблицата PERSONS
/// </summary>
struct PERSONS
{
	long lID;
	long lUpdateCounter;
	TCHAR szFirstName[PERSONS_NAME_LENGTH];
	TCHAR szMiddleName[PERSONS_NAME_LENGTH];
	TCHAR szLastName[PERSONS_NAME_LENGTH];
	TCHAR szUCN[PERSONS_UCN_LENGTH];
	long lCityID;
	TCHAR szAddress[PERSONS_ADDRESS_LENGTH];
	long lCompanyID;
	long lPositionID;


	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};

/// <summary>
/// Дискова структура за таблицата PHONE_TYPES
/// </summary>
struct PHONE_TYPES
{
	long lID;
	long lUpdateCounter;
	TCHAR szType[PHONE_TYPES_TYPE_LENGTH];

	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};

/// <summary>
///  Дискова структура за таблицата PHONE_NUMBERS
/// </summary>
struct PHONE_NUMBERS
{
	long lID;
	long lUpdateCounter;
	long lPersonID;
	long lPhoneTypeID;
	TCHAR szPhoneNumber[PHONE_NUMBERS_NUMBER_LENGTH];

	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

	bool PHONE_NUMBERS::operator==(PHONE_NUMBERS& recPhoneNumber)
	{
		return (lID == recPhoneNumber.lID) &&
			(lUpdateCounter == recPhoneNumber.lUpdateCounter) &&
			(lPersonID == recPhoneNumber.lPersonID) &&
			(lPhoneTypeID == recPhoneNumber.lPhoneTypeID) &&
			(!StrCmpW(szPhoneNumber, recPhoneNumber.szPhoneNumber));
	}

};

/// <summary>
/// Дискова структура за таблицата COMPANIES
/// </summary>
struct COMPANIES
{
	long lID;
	long lUpdateCounter;
	TCHAR szCompanyName[COMPANIES_COMPANY_NAME_LENGTH];

	COMPANIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};

/// <summary>
/// Дискова структура за таблицата POSITIONS
/// </summary>
struct POSITIONS
{
	long lID;
	long lUpdateCounter;
	TCHAR szPositionName[POSITIONS_POSITION_NAME_LENGTH];

	POSITIONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};


typedef CTypedPtrArray<CPtrArray, CITIES*> CCitiesPtrArray;
typedef CTypedPtrArray<CPtrArray, PERSONS*> CPersonsPtrArray;
typedef CTypedPtrArray<CPtrArray, PHONE_TYPES*> CPhoneTypesPtrArray;
typedef CTypedPtrArray<CPtrArray, PHONE_NUMBERS*> CPhoneNumbersPtrArray;