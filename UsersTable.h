#pragma once
#include <atldbcli.h>
#include "DBTable.h"
#include "UsersAccessor.h"

/////////////////////////////////////////////////////////////////////////////
// CUsersTable

/// <summary>
/// Клас за работа с таблицата USERS
/// </summary>
class CUsersTable : public
	CDBTable<CUsersAccessor, USERS>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CUsersTable(CSession& oSession);
	CUsersTable();
	~CUsersTable();

	// Methods
	// ----------------
	BOOL SelectByUsername(const CString& strUsername, USERS& recUser);

	// Overrides
	// ----------------

	// Members
	// ----------------
};

