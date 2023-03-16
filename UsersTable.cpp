#include "pch.h"
#include "UsersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CUsersTable

// Constants
// ----------------

#define USERS_TABLE_NAME _T("USERS")
#define USERS_QUERY _T("SELECT * FROM [USERS] WHERE [USERNAME] LIKE '%s'")

// Constructor / Destructor
// ----------------

CUsersTable::CUsersTable(CSession& oSession) :
    CDBTable(m_recUser, USERS_TABLE_NAME, oSession)
{
}

CUsersTable::CUsersTable() :
    CDBTable(m_recUser, USERS_TABLE_NAME)
{
}

CUsersTable::~CUsersTable()
{
}

// Methods
// ----------------

BOOL CUsersTable::SelectByUsername(const CString& strUsername, USERS& recUser)
{
    if (!OpenConnection())
        return FALSE;

    CString strQuery;
    strQuery.Format(USERS_QUERY, strUsername);

    if (!ExecuteQuery(strQuery))
    {
        CloseConnection();
        return FALSE;
    }

    if (MoveNext() != S_OK)
    {
        Close();
        CloseConnection();
        return FALSE;
    }

    recUser = m_recUser;

    Close();
    CloseConnection();
    return TRUE;

}

