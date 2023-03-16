#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define PHONE_NUMBERS_ACCESSOR_MAP_VALUE 2

enum PhoneNumbersAccessorValues
{
	PhoneNumbersAccessorValuesFirst = 0,
	PhoneNumbersAccessorValuesSecond
};

enum PhoneNumbersAccessorColumnEntries
{
	PhoneNumbersAccessorColumnEntriesID = 1,
	PhoneNumbersAccessorColumnEntriesUpdateCounter,
	PhoneNumbersAccessorColumnEntriesPersonID,
	PhoneNumbersAccessorColumnEntriesPhoneTypeID,
	PhoneNumbersAccessorColumnEntriesPhoneNumber
};

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor


/// <summary>
/// Accessor за таблицата PHONE_NUMBERS
/// </summary>
class CPhoneNumbersAccessor
{
protected:
	PHONE_NUMBERS m_recPhoneNumber;

	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, PHONE_NUMBERS_ACCESSOR_MAP_VALUE)

		BEGIN_ACCESSOR(PhoneNumbersAccessorValuesFirst, true)
			COLUMN_ENTRY(PhoneNumbersAccessorColumnEntriesID, m_recPhoneNumber.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(PhoneNumbersAccessorValuesSecond, true)
			COLUMN_ENTRY(PhoneNumbersAccessorColumnEntriesUpdateCounter, m_recPhoneNumber.lUpdateCounter)
			COLUMN_ENTRY(PhoneNumbersAccessorColumnEntriesPersonID, m_recPhoneNumber.lPersonID)
			COLUMN_ENTRY(PhoneNumbersAccessorColumnEntriesPhoneTypeID, m_recPhoneNumber.lPhoneTypeID)
			COLUMN_ENTRY(PhoneNumbersAccessorColumnEntriesPhoneNumber, m_recPhoneNumber.szPhoneNumber)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};
