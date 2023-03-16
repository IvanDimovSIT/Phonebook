#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define PHONE_TYPES_ACCESSOR_MAP_VALUE 2

enum PhoneTypesAccessorValues
{
	PhoneTypesAccessorValuesFirst = 0,
	PhoneTypesAccessorValuesSecond
};

enum PhoneTypesAccessorColumnEntries
{
	PhoneTypesAccessorColumnEntriesID = 1,
	PhoneTypesAccessorColumnEntriesUpdateCounter,
	PhoneTypesAccessorColumnEntriesType
};

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesAccessor


/// <summary>
/// Accessor за таблицата PHONE_TYPES
/// </summary>
class CPhoneTypesAccessor
{
protected:
	PHONE_TYPES m_recPhoneType;
	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, PHONE_TYPES_ACCESSOR_MAP_VALUE)
		BEGIN_ACCESSOR(PhoneTypesAccessorValuesFirst, true)
			COLUMN_ENTRY(PhoneTypesAccessorColumnEntriesID, m_recPhoneType.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(PhoneTypesAccessorValuesSecond, true)
			COLUMN_ENTRY(PhoneTypesAccessorColumnEntriesUpdateCounter, m_recPhoneType.lUpdateCounter)
			COLUMN_ENTRY(PhoneTypesAccessorColumnEntriesType, m_recPhoneType.szType)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};