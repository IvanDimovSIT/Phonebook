#include "pch.h"
#include "UserLogin.h"
#include "LoginDialog.h"
#include "ErrorLogger.h"
#include "UsersData.h"

// Constants
// ----------------
#define INCORRECT_AUTH_MESSAGE _T("Неправилно име или парола. Моля опитайте отново.")

// Constructor / Destructor
// ----------------
CUserLogin::CUserLogin()
{
}

CUserLogin::~CUserLogin()
{
}

// Methods
// ----------------



BOOL CUserLogin::LogIn() const
{
	CLoginDialog oLoginDialog;
	CUsersData oUsersData;

	do 
	{
		if (oLoginDialog.DoModal() != IDOK)
			return FALSE;

		CString strUsername;
		CString strPassword;

		oLoginDialog.GetData(strUsername, strPassword);

		if (oUsersData.LogIn(strUsername, strPassword))
			return TRUE;

		AfxMessageBox(INCORRECT_AUTH_MESSAGE, MB_OK, MB_ICONASTERISK);
	} while (TRUE);
}



// Overrides
// ----------------