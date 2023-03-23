#include "pch.h"
#include "PersonsTable.h"



/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

// Constants
// ----------------

#define PERSONS_TABLE_NAME _T("PERSONS")
#define PERSON_TABLE_SELECT_ALL_SORTED_QUERY _T("SELECT * FROM PERSONS ORDER BY [FIRST_NAME] DESC, [MIDDLE_NAME] DESC, [LAST_NAME] DESC")
#define SELECT_BY_NAME _T("SELECT * FROM PERSONS WHERE (UPPER([FIRST_NAME]) LIKE UPPER(N'%%%s%%') AND '%s' != '' ) OR \
                           (UPPER([MIDDLE_NAME]) LIKE UPPER(N'%%%s%%') AND '%s' != '' ) OR \
                           (UPPER([LAST_NAME]) LIKE UPPER(N'%%%s%%') AND '%s' != '' ) OR \
                           (UPPER([UCN]) LIKE UPPER(N'%%%s%%') AND '%s' != '' ) OR \
                           (UPPER([ADDRESS]) LIKE UPPER(N'%%%s%%') AND '%s' != '' ) \
                           ORDER BY \
                           [FIRST_NAME] DESC, \
                           [MIDDLE_NAME] DESC, \
                           [LAST_NAME] DESC")

// Constructor / Destructor
// ----------------

CPersonsTable::CPersonsTable(CSession& oSession) :
    CDBTable(m_recPerson, PERSONS_TABLE_NAME, oSession)
{
}

CPersonsTable::~CPersonsTable()
{
}

// Methods
// ----------------

BOOL CPersonsTable::SelectAllSorted(CPtrAutoArray<PERSONS>& oAutoArray)
{
    if (!OpenConnection())
        return FALSE;

    if (!ExecuteQuery(PERSON_TABLE_SELECT_ALL_SORTED_QUERY))
    {
        CloseConnection();
        return FALSE;
    }

    while (MoveNext() == S_OK)
    {
        PERSONS* pRecordToAdd = new PERSONS(m_recPerson);

        oAutoArray.Add(pRecordToAdd);
    }


    Close();
    CloseConnection();
    return TRUE;
}

BOOL CPersonsTable::SelectByNameUCNAddress(CPtrAutoArray<PERSONS>& oAutoArray, const CString& strName, const CString& strUCN, const CString& strAddress)
{
    if (!OpenConnection())
        return FALSE;

    CString strQuery;
    strQuery.Format(SELECT_BY_NAME, strName, strName, strName, strName, strName, strName, strUCN, strUCN, strAddress, strAddress);
    if (!ExecuteQuery(strQuery))
    {
        CloseConnection();
        return FALSE;
    }

    while (MoveNext() == S_OK)
    {
        PERSONS* pRecordToAdd = new PERSONS(m_recPerson);

        oAutoArray.Add(pRecordToAdd);
    }


    Close();
    CloseConnection();
    return TRUE;
}



// Overrides
// ----------------
