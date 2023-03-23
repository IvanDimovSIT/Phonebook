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
	/// <summary> Получава всички записи по име </summary>
	BOOL SelectByName(CPtrAutoArray<CITIES>& oAutoArray, const CString& strName);

// Overrides
// ----------------

// Members
// ----------------
};

