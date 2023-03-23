#include "pch.h"
#include "CitiesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constants
// ----------------

#define CITIES_TABLE_NAME _T("CITIES")
#define SELECT_BY_NAME _T("SELECT * FROM CITIES WHERE UPPER([CITY_NAME]) LIKE UPPER(N'%%%s%%') OR UPPER([DISTRICT]) LIKE UPPER(N'%%%s%%')")

// Constructor / Destructor
// ----------------

CCitiesTable::CCitiesTable(CSession& oSession) :
    CDBTable(m_recCity, CITIES_TABLE_NAME, oSession)
{
}

CCitiesTable::CCitiesTable() :
    CDBTable(m_recCity, CITIES_TABLE_NAME)
{
}

CCitiesTable::~CCitiesTable() 
{
}

// Methods
// ----------------

	/// <summary> Получава всички записи по име </summary>
BOOL CCitiesTable::SelectByName(CPtrAutoArray<CITIES>& oAutoArray, const CString& strName)
{
    if (!OpenConnection())
        return FALSE;


    CString strQuery;
    strQuery.Format(SELECT_BY_NAME, strName, strName);
    if (!ExecuteQuery(strQuery.GetString()))
    {
        CloseConnection();
        return FALSE;
    }

    while (MoveNext() == S_OK)
    {
        CITIES* pRecordToAdd = new CITIES(m_recCity);

        oAutoArray.Add(pRecordToAdd);
    }

    Close();
    CloseConnection();
    return TRUE;
}



// Overrides
// ----------------
