#pragma once
#include <atldbcli.h>
#include "DBTable.h"
#include "PhoneTypesAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

/// <summary>
/// Клас за работа с таблицата PHONE_TYPES
/// </summary>
class CPhoneTypesTable : public
	CDBTable<CPhoneTypesAccessor, PHONE_TYPES>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CPhoneTypesTable(CSession& oSession);
	~CPhoneTypesTable();

	// Methods
	// ----------------

	// Overrides
	// ----------------

	// Members
	// ----------------
};

