#pragma once

#include <atldbcli.h>
#include "DBTable.h"
#include "PersonsAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

/// <summary>
/// Клас за работа с таблицата PERSONS
/// </summary>
class CPersonsTable : public
	CDBTable<CPersonsAccessor, PERSONS>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CPersonsTable(CSession& oSession);
	~CPersonsTable();

	// Methods
	// ----------------

	/// <summary> Получава всички записи по азбучен ред и пълни масива </summary>
	BOOL SelectAllSorted(CPtrAutoArray<PERSONS>& oAutoArray);


	// Overrides
	// ----------------

	// Members
	// ----------------
};
