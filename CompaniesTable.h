#pragma once
#include <atldbcli.h>
#include "DBTable.h"
#include "CompaniesAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CCompaniesTable

/// <summary>
/// Клас за работа с таблицата COMPANIES
/// </summary>
class CCompaniesTable : public
	CDBTable<CCompaniesAccessor, COMPANIES>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CCompaniesTable(CSession& oSession);
	CCompaniesTable();
	~CCompaniesTable();

	// Methods
	// ----------------

	// Overrides
	// ----------------

	// Members
	// ----------------
};
