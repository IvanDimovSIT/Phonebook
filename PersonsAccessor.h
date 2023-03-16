#pragma once

#include <atldbcli.h>
#include "Structures.h"

#define PERSONS_ACCESSOR_MAP_VALUE 2

enum PersonsAccessorValues
{
	PersonsAccessorValuesFirst = 0,
	PersonsAccessorValuesSecond
};

enum PersonsAccessorColumnEntries
{
	PersonsAccessorColumnEntriesID = 1,
	PersonsAccessorColumnEntriesUpdateCounter,
	PersonsAccessorColumnEntriesFirstName,
	PersonsAccessorColumnEntriesMiddleName,
	PersonsAccessorColumnEntriesLastName,
	PersonsAccessorColumnEntriesUCN,
	PersonsAccessorColumnEntriesCityID,
	PersonsAccessorColumnEntriesAddress,
	PersonsAccessorColumnEntriesCompanyID,
	PersonsAccessorColumnEntriesPositionID

};

/////////////////////////////////////////////////////////////////////////////
// CPersonsAccessor


/// <summary>
/// Accessor за таблицата PERSONS
/// </summary>
class CPersonsAccessor
{
protected:
	PERSONS m_recPerson;
	BEGIN_ACCESSOR_MAP(CPersonsAccessor, PERSONS_ACCESSOR_MAP_VALUE)
		BEGIN_ACCESSOR(PersonsAccessorValuesFirst, true)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesID, m_recPerson.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(PersonsAccessorValuesSecond, true)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesUpdateCounter, m_recPerson.lUpdateCounter)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesFirstName, m_recPerson.szFirstName)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesMiddleName, m_recPerson.szMiddleName)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesLastName, m_recPerson.szLastName)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesUCN, m_recPerson.szUCN)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesCityID, m_recPerson.lCityID)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesAddress, m_recPerson.szAddress)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesCompanyID, m_recPerson.lCompanyID)
			COLUMN_ENTRY(PersonsAccessorColumnEntriesPositionID, m_recPerson.lPositionID)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};