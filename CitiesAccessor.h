#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define CITIES_ACCESSOR_MAP_VALUE 2

enum CitiesAccessorValues
{
	CitiesAccessorValuesFirst = 0,
	CitiesAccessorValuesSecond
};

enum CitiesAccessorColumnEntries
{
	CitiesAccessorColumnEntriesID = 1,
	CitiesAccessorColumnEntriesUpdateCounter,
	CitiesAccessorColumnEntriesName,
	CitiesAccessorColumnEntriesDistrict
};

/////////////////////////////////////////////////////////////////////////////
// CCitiesAccessor


/// <summary>
/// Accessor за таблицата CITIES
/// </summary>
class CCitiesAccessor
{
protected:
	CITIES m_recCity;
	BEGIN_ACCESSOR_MAP(CCitiesAccessor, CITIES_ACCESSOR_MAP_VALUE)
		BEGIN_ACCESSOR(CitiesAccessorValuesFirst, true)
			COLUMN_ENTRY(CitiesAccessorColumnEntriesID, m_recCity.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(CitiesAccessorValuesSecond, true)
			COLUMN_ENTRY(CitiesAccessorColumnEntriesUpdateCounter, m_recCity.lUpdateCounter)
			COLUMN_ENTRY(CitiesAccessorColumnEntriesName, m_recCity.szCityName)
			COLUMN_ENTRY(CitiesAccessorColumnEntriesDistrict, m_recCity.szDistrict)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};

