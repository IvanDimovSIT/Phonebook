#pragma once
#include "pch.h"
#include <atldbcli.h>
#include "ErrorLogger.h"
#include "PtrAutoArray.h"
#include "DataSourceSingleton.h"

#define DB_TABLE_OPEN_CONNECTION_ERROR_MESSAGE _T("Unable to open session")
#define DB_TABLE_QUERY_ERROR_MESSAGE _T("Error when executing query.\n Error: %#lx.\nQuery: \"%s\"")
#define DB_TABLE_ERROR_CODE_MESSAGE _T("\nError: %#lx")

#define DB_TABLE_SELECT_ALL_QUERY  _T("SELECT * FROM %s")
#define DB_TABLE_SELECT_BY_ID_QUERY  _T("SELECT * FROM %s WHERE [ID] = %d")
#define DB_TABLE_SELECT_BY_ID_WITH_LOCK_QUERY _T("SELECT * FROM %s WITH(UPDLOCK) WHERE ID = %d")
#define DB_TABLE_SELECT_NOTHING_QUERY _T("SELECT TOP 0 * FROM %s")

#define DB_TABLE_NO_RESULTS_ERROR_MESSAGE _T("Error no results found.")
#define DB_TABLE_UPDATE_ERROR_MESSAGE _T("Error when updating.")
#define DB_TABLE_UPDATE_COUNTER_ERROR_MESSAGE _T("Error when updating. Update counter doesn't match.")
#define DB_TABLE_INSERT_ERROR_MESSAGE _T("Error when inserting.")
#define DB_TABLE_SELECT_ROW_TO_DELETE_ERROR_MESSAGE _T("Error when selecting the row to delete")
#define DB_TABLE_DELETE_ERROR_MESSAGE  _T("Error when deleting.")


/////////////////////////////////////////////////////////////////////////////
// CDBTable

/// <summary>
/// Базов клас за работа с таблица от БД.
/// </summary>
/// <typeparam name="C"> Аксесор съответстващ на таблицата </typeparam>
template <class C, class R>
class CDBTable:protected
	CCommand<CAccessor<C>>
{
// Constants
// ----------------
private:
    /// <summary> Името на таблицата </summary>
    const TCHAR* m_szTableName;
// Constructor / Destructor
// ----------------
public:
    CDBTable(R& recRecord, const TCHAR* szTableName, CSession& oSession);
    CDBTable(R& recRecord, const TCHAR* szTableName);
    ~CDBTable();

// Methods
// ----------------
private:
    /// <summary> Задава стойностите на m_oDBPropSet </summary>
    void AddPropSetProperties();

protected:
	/// <summary> Отваря нова сесия </summary>
	BOOL OpenConnection();

    /// <summary> Започва транзакция </summary>
    BOOL StartTransaction();

    /// <summary> Спира транзакция </summary>
    BOOL Abort();

    /// <summary> Завършва транзакция </summary>
    BOOL Commit();

	/// <summary> Затваря сесията </summary>
	void CloseConnection();

	/// <summary> Показва съобщение за грешка </summary>
	void ShowErrorMessage(const HRESULT hResult, const CString& strError) const;

    /// <summary> Показва съобщение за грешка </summary>
    void ShowErrorMessage(const CString& strError) const;

	/// <summary> Показва съобщение за грешка </summary>
	void ShowErrorMessageQuery(const HRESULT hResult, const CString& strQuery) const;

	/// <summary> Изпълнява заявка </summary>
	BOOL ExecuteQuery(const CString& strQuery);

    /// <summary> Намира запис по зададено ID, изпълнява се в текущата сесия </summary>
    BOOL SelectWhereIDInSession(const long lID, const BOOL bWithLock);
public:
    /// <summary> Получава всички записи и пълни масива </summary>
    BOOL SelectAll(CPtrAutoArray<R>& oAutoArray);

    /// <summary> Намира запис по зададено ID </summary>
    BOOL SelectWhereID(const long lID, R& recRecord);

    /// <summary> Променя запис по ID </summary>
    BOOL UpdateWhereID(const long lID, const R& recRecord);

    /// <summary> Създава нов запис </summary>
    BOOL InsertRecord(R& recCity);

    /// <summary> Изтрива запис по ID </summary>
    BOOL DeleteWhereID(const long lID);


// Overrides
// ----------------

// Members
// ----------------
private:
    /// <summary> Указател към записа </summary>
    R* m_pRecord;
protected:
    BOOL m_bExternalConnection;

	/// <summary> Указател към връзката за БД </summary>
	CDataSource* m_pDataSource;
	/// <summary> Текущата сесия </summary>
	CSession* m_pSession;
	/// <summary> DBPropSet за заявките </summary>
	CDBPropSet m_oDBPropSet;
};


// Constants
// ----------------

// Constructor / Destructor
// ----------------

template<class C, class R>
CDBTable<C, R>::CDBTable(R& recRecord, const TCHAR* szTableName, CSession& oSession) :
    m_oDBPropSet(DBPROPSET_ROWSET)
{
    m_bExternalConnection = TRUE;

    m_pSession = &oSession;
    m_pDataSource = CDataSourceSingleton::GetInstance()->GetDataSource();
    m_szTableName = szTableName;
    m_pRecord = &recRecord;

    AddPropSetProperties();
}

template<class C, class R>
CDBTable<C, R>::CDBTable(R& recRecord, const TCHAR* szTableName) :
    m_oDBPropSet(DBPROPSET_ROWSET)
{
    m_bExternalConnection = FALSE;
    m_pSession = new CSession;

    m_pDataSource = CDataSourceSingleton::GetInstance()->GetDataSource();
    m_szTableName = szTableName;
    m_pRecord = &recRecord;

    AddPropSetProperties();
}

template<class C, class R>
CDBTable<C, R>::~CDBTable()
{
    if (!m_bExternalConnection)
        delete m_pSession;
}

// Methods
// ----------------

template<class C, class R>
void CDBTable<C, R>::AddPropSetProperties()
{
    m_oDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
    m_oDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
    m_oDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
    m_oDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
}

template<class C, class R>
BOOL CDBTable<C, R>::OpenConnection()
{
    if (m_bExternalConnection)
        return TRUE;

    const HRESULT hResult = m_pSession->Open(*m_pDataSource);
    if (FAILED(hResult))
    {
        ShowErrorMessage(hResult, DB_TABLE_OPEN_CONNECTION_ERROR_MESSAGE);
        return FALSE;
    }

    return TRUE;
}

template<class C, class R>
BOOL CDBTable<C, R>::StartTransaction()
{
    if (m_bExternalConnection)
        return TRUE;

    return !FAILED(m_pSession->StartTransaction());
}

template<class C, class R>
BOOL  CDBTable<C, R>::Abort()
{
    if (m_bExternalConnection)
        return TRUE;

    return !FAILED(m_pSession->Abort());
}

template<class C, class R>
BOOL  CDBTable<C, R>::Commit()
{
    if (m_bExternalConnection)
        return TRUE;

    return !FAILED(m_pSession->Commit());
}

template<class C, class R>
void CDBTable<C, R>::CloseConnection()
{
    if (m_bExternalConnection)
        return;

    m_pSession->Close();
}

template<class C, class R>
void CDBTable<C, R>::ShowErrorMessageQuery(const HRESULT hResult, const CString& strQuery) const
{
    CString strError;
    strError.Format(DB_TABLE_QUERY_ERROR_MESSAGE, hResult, strQuery);

    CErrorLogger::LogMessage(strError, TRUE, FALSE);
}

template<class C, class R>
void CDBTable<C, R>::ShowErrorMessage(const HRESULT hResult, const CString& strError) const
{
    CString strMessage;
    strMessage.Format(DB_TABLE_ERROR_CODE_MESSAGE, hResult);
    strMessage = strError + strMessage;

    CErrorLogger::LogMessage(strMessage, TRUE, FALSE);
}

template<class C, class R>
void CDBTable<C, R>::ShowErrorMessage(const CString& strError) const
{
    CErrorLogger::LogMessage(strError, TRUE, FALSE);
}

template<class C, class R>
BOOL CDBTable<C, R>::ExecuteQuery(const CString& strQuery)
{
    const HRESULT hResult = Open(*m_pSession, strQuery, &m_oDBPropSet);
    if (FAILED(hResult))
    {
        ShowErrorMessageQuery(hResult, strQuery);
        return FALSE;
    }

    return TRUE;
}

template<class C, class R>
BOOL CDBTable<C, R>::SelectWhereIDInSession(const long lID, const BOOL bWithLock)
{
    CString strQuery;
    if (bWithLock)
    {
        strQuery.Format(DB_TABLE_SELECT_BY_ID_WITH_LOCK_QUERY, m_szTableName, lID);
    }
    else
    {
        strQuery.Format(DB_TABLE_SELECT_BY_ID_QUERY, m_szTableName, lID);
    }

    return ExecuteQuery(strQuery.GetString());
}

template<class C, class R>
BOOL CDBTable<C, R>::SelectAll(CPtrAutoArray<R>& oAutoArray)
{
    if (!OpenConnection())
        return FALSE;


    CString strQuery;
    strQuery.Format(DB_TABLE_SELECT_ALL_QUERY, m_szTableName);
    if (!ExecuteQuery(strQuery.GetString()))
    {
        CloseConnection();
        return FALSE;
    }

    while (MoveNext() == S_OK)
    {
        R* pRecordToAdd = new R((*m_pRecord));

        oAutoArray.Add(pRecordToAdd);
    }

    Close();
    CloseConnection();
    return TRUE;
}

template<class C, class R>
BOOL CDBTable<C, R>::SelectWhereID(const long lID, R& recRecord)
{
    if (!OpenConnection())
        return FALSE;

    if (!SelectWhereIDInSession(lID, FALSE))
    {
        CloseConnection();
        return FALSE;
    }

    if (MoveNext() != S_OK)
    {
        ShowErrorMessage(DB_TABLE_NO_RESULTS_ERROR_MESSAGE);
        Close();
        CloseConnection();
        return FALSE;
    }

    recRecord = (*m_pRecord);

    Close();
    CloseConnection();

    return TRUE;
}

template<class C, class R>
BOOL CDBTable<C, R>::UpdateWhereID(const long lID, const R& recRecord)
{
    if (!OpenConnection())
        return FALSE;
    StartTransaction();

    // Начало на транзакцията

    if (!SelectWhereIDInSession(lID, TRUE))
    {
        Abort();
        CloseConnection();

        return FALSE;
    }

    HRESULT hResult = MoveFirst();
    if (FAILED(hResult))
    {
        ShowErrorMessage(hResult, DB_TABLE_NO_RESULTS_ERROR_MESSAGE);

        Abort();
        Close();
        CloseConnection();

        return FALSE;
    }

    // Проверка на Update counter
    if (recRecord.lUpdateCounter != (*m_pRecord).lUpdateCounter)
    {
        ShowErrorMessage(DB_TABLE_UPDATE_COUNTER_ERROR_MESSAGE);

        Abort();
        Close();
        CloseConnection();
        return FALSE;
    }

    (*m_pRecord) = recRecord;
    (*m_pRecord).lUpdateCounter++;

    hResult = SetData(1);
    if (FAILED(hResult))
    {
        // Неуспешно приключване на транзакцията
        Abort();
        ShowErrorMessage(hResult, DB_TABLE_UPDATE_ERROR_MESSAGE);
        Close();
        CloseConnection();

        return FALSE;
    }

    // Успешно приключване на транзакцията
    Commit();
    Close();
    CloseConnection();
    return TRUE;
}

template<class C, class R>
BOOL CDBTable<C, R>::InsertRecord(R& recRecord)
{
    if (!OpenConnection())
        return FALSE;

    // изпълняване на фиктивна команда за настройване на PropSet
    CString strQuery;
    strQuery.Format(DB_TABLE_SELECT_NOTHING_QUERY, m_szTableName);
    if (!ExecuteQuery(strQuery.GetString()))
    {
        CloseConnection();

        return FALSE;
    }

    (*m_pRecord) = recRecord;

    HRESULT hResult = Insert(1, false);

    if (FAILED(hResult))
    {
        Close();
        ShowErrorMessage(hResult, DB_TABLE_INSERT_ERROR_MESSAGE);
        CloseConnection();

        return FALSE;
    }

    hResult = MoveFirst();
    if (FAILED(hResult))
    {
        Close();
        ShowErrorMessage(hResult, DB_TABLE_INSERT_ERROR_MESSAGE);
        CloseConnection();

        return FALSE;
    }

    recRecord = (*m_pRecord);

    Close();
    CloseConnection();
    return TRUE;
}

template<class C, class R>
BOOL CDBTable<C, R>::DeleteWhereID(const long lID)
{

    if (!OpenConnection())
        return FALSE;


    CString strQuery;
    strQuery.Format(DB_TABLE_SELECT_BY_ID_QUERY, m_szTableName, lID);

    // Селектираме записа за изтриване
    if (!ExecuteQuery(strQuery))
    {
        CloseConnection();

        return FALSE;
    }

    HRESULT hResult = MoveFirst();
    if (FAILED(hResult))
    {
        ShowErrorMessage(hResult, DB_TABLE_SELECT_ROW_TO_DELETE_ERROR_MESSAGE);
        Close();
        CloseConnection();

        return FALSE;
    }

    // Изтриваме селектирания запис
    hResult = Delete();

    if (FAILED(hResult))
    {
        ShowErrorMessage(hResult, DB_TABLE_DELETE_ERROR_MESSAGE);
        Close();
        CloseConnection();

        return FALSE;
    }

    Close();
    CloseConnection();
    return TRUE;
}


// Overrides
// ----------------
