#include "pch.h"
#include "PhoneNumbersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

// Constants
// ----------------

#define PHONE_NUMBERS_TABLE_NAME _T("PHONE_NUMBERS")
#define SELECT_WHERE_PERSON_ID_QUERY _T("SELECT * FROM PHONE_NUMBERS WHERE [PERSON_ID] = %d")

// Constructor / Destructor
// ----------------

CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSession) :
    CDBTable(m_recPhoneNumber, PHONE_NUMBERS_TABLE_NAME, oSession)
{
}

CPhoneNumbersTable::~CPhoneNumbersTable()
{
}

// Methods
// ----------------

BOOL CPhoneNumbersTable::SelectWherePersonID(const long lPersonID)
{
    CString strQuery;
    strQuery.Format(SELECT_WHERE_PERSON_ID_QUERY, lPersonID);
    return ExecuteQuery(strQuery.GetString());
}


BOOL CPhoneNumbersTable::SelectWherePersonID(const long lPersonID, CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers)
{
    oPhoneNumbers.RemoveAll();
    if (!OpenConnection())
        return FALSE;

    if (!SelectWherePersonID(lPersonID))
    {
        CloseConnection();
        return FALSE;
    }

    while (MoveNext() == S_OK)
    {
        PHONE_NUMBERS* pPhoneNumberToAdd = new PHONE_NUMBERS(m_recPhoneNumber);

        oPhoneNumbers.Add(pPhoneNumberToAdd);
    }

    Close();
    CloseConnection();
    return TRUE;

}

BOOL CPhoneNumbersTable::DeleteWherePersonID(const long lPersonID)
{
    if (!OpenConnection())
        return FALSE;

    if (!m_bExternalConnection)
    {
        if (FAILED(m_pSession->StartTransaction())) //грешка
        {
            CloseConnection();
            return FALSE;
        }
    }

    if (!SelectWherePersonID(lPersonID))
    {
        if (!m_bExternalConnection)
            m_pSession->Abort();
        CloseConnection();
        return FALSE;
    }

    while (MoveNext() == S_OK)
    {
        HRESULT hResult = Delete();
        if (FAILED(hResult))
        {
            if (!m_bExternalConnection)
                m_pSession->Abort();
            Close();
            CloseConnection();
            ShowErrorMessage(_T("Error when deleting."));
            return FALSE;
        }
    }

    if (!m_bExternalConnection) {
        if (FAILED(m_pSession->Commit()))
        {
            Close();
            CloseConnection();
            return FALSE;
        }
    }


    Close();
    CloseConnection();
    return TRUE;
}

// Overrides
// ----------------
