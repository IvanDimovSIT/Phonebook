#include "pch.h"
#include "PersonsTable.h"



/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

// Constants
// ----------------

#define PERSONS_TABLE_NAME _T("PERSONS")
#define PERSON_TABLE_SELECT_ALL_SORTED_QUERY _T("SELECT * FROM PERSONS ORDER BY [FIRST_NAME] DESC, [MIDDLE_NAME] DESC, [LAST_NAME] DESC")

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


// Overrides
// ----------------
