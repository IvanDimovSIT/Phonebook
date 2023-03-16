#pragma once
#include "pch.h"

#include "UsersData.h"
#include "UsersTable.h"
#include "SHA256.h"

/////////////////////////////////////////////////////////////////////////////
// CUsersData


// Constants
// ----------------

// Constructor / Destructor
// ----------------

CUsersData::CUsersData() 
{
}

CUsersData::~CUsersData()
{
}

// Methods
// ----------------
	

BOOL CUsersData::LogIn(const CString& strUsername, const CString& strPassword) const
{
	CUsersTable oUsersTable;
	USERS recUser;

	if (!oUsersTable.SelectByUsername(strUsername, recUser))
		return FALSE;

	SHA256 oSHA256;
	
	oSHA256.update((uint8_t*) strPassword.GetString(), sizeof(*strPassword.GetString())*strPassword.GetLength());
	uint8_t* pDigest = oSHA256.digest();

	CString strHash = CString(SHA256::toString(pDigest).c_str());

	delete[] pDigest;

	return wcscmp(strHash, recUser.szPassword) == 0;
}

// Overrides
// ----------------

