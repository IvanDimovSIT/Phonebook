#pragma once
#include "DataSourceSingleton.h"

/////////////////////////////////////////////////////////////////////////////
// CInputValidator

/// <summary>
/// Клас за влизане на потребител
/// </summary>
class CUserLogin
{
public:
// Constants
// ----------------

// Constructor / Destructor
// ----------------
	CUserLogin();
	~CUserLogin();

// Methods
// ----------------

public:
	/// <summary> Влизане на потребител </summary>
	BOOL LogIn() const;

// Overrides
// ----------------


// Members
// ----------------

};

