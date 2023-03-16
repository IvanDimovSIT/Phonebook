#pragma once
#include <atldbcli.h>
#include "DBTable.h"
#include "PositionsAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionsTable

/// <summary>
/// Клас за работа с таблицата POSITIONS
/// </summary>
class CPositionsTable : public
	CDBTable<CPositionsAccessor, POSITIONS>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CPositionsTable(CSession& oSession);
	CPositionsTable();
	~CPositionsTable();

	// Methods
	// ----------------

	// Overrides
	// ----------------

	// Members
	// ----------------
};
