#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define COMPANIES_ACCESSOR_MAP_VALUE 2

enum CompaniesAccessorValues
{
	CompaniesAccessorValuesFirst = 0,
	CompaniesAccessorValuesSecond
};

enum CompaniesAccessorColumnEntries
{
	CompaniesAccessorColumnEntriesID = 1,
	CompaniesAccessorColumnEntriesUpdateCounter,
	CompaniesAccessorColumnEntriesCompanyName
};

/////////////////////////////////////////////////////////////////////////////
// CCompaniesAccessor


/// <summary>
/// Accessor за таблицата COMPANIES
/// </summary>
class CCompaniesAccessor
{
protected:
	COMPANIES m_recCompany;
	BEGIN_ACCESSOR_MAP(CCompaniesAccessor, COMPANIES_ACCESSOR_MAP_VALUE)
		BEGIN_ACCESSOR(CompaniesAccessorValuesFirst, true)
			COLUMN_ENTRY(CompaniesAccessorColumnEntriesID, m_recCompany.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(CompaniesAccessorValuesSecond, true)
			COLUMN_ENTRY(CompaniesAccessorColumnEntriesUpdateCounter, m_recCompany.lUpdateCounter)
			COLUMN_ENTRY(CompaniesAccessorColumnEntriesCompanyName, m_recCompany.szCompanyName)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};
