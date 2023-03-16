#pragma once

#include "UsersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CUsersData

/// <summary>
/// Клас за достъп до потребителските данни
/// </summary>
class CUsersData
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CUsersData();
	~CUsersData();

	// Methods
	// ----------------
	/// <summary> За автентикация </summary>
	BOOL LogIn(const CString& strUsername, const CString& strPassword) const;

	// Overrides
	// ----------------


	// Members
	// ----------------
private:
};

