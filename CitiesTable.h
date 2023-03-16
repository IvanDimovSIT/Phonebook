#pragma once
#include <atldbcli.h>
#include "DBTable.h"
#include "CitiesAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>
/// Клас за работа с таблицата CITIES
/// </summary>
class CCitiesTable : public
CDBTable<CCitiesAccessor, CITIES>
{
// Constants
// ----------------

// Constructor / Destructor
// ----------------
public:
	CCitiesTable(CSession& oSession);
	CCitiesTable();
	~CCitiesTable();

// Methods
// ----------------

// Overrides
// ----------------

// Members
// ----------------
};

