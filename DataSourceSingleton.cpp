#include "pch.h"
#include "DataSourceSingleton.h"
#include "ErrorLogger.h"
#include "iostream"
#include "fstream"
#include "PtrAutoArray.h"

//#define DATASOURCE_NAME _T("DESKTOP-VQF53N4")
#define DATABASE_AUTHENTIFICATION _T("SSPI")
#define DATABASE_NAME _T("PHONEBOOK")
#define DATABASE_PERSIST_SENSITIVE_AUTHINFO false
#define DATABASE_INIT_LCID 1033L
#define DATABASE_CLSID _T("SQLOLEDB.1")

#define CONFIG_FILE _T("config.txt")
#define LINES_TO_READ 3

enum ConfigLines
{
	ConfigLinesDataSource = 0,
	ConfigLinesUsername,
	ConfigLinesPassword
};

//#define MAX_FILE_LENGTH 100


/////////////////////////////////////////////////////////////////////////////
// CDataSourceSingleton

CDataSourceSingleton* CDataSourceSingleton::_pInstance = NULL;

// Constants
// ----------------


// Constructor / Destructor
// ----------------

CDataSourceSingleton::CDataSourceSingleton()
{
	if(!ReadConfigFile(CONFIG_FILE))
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

// Methods
// ----------------

BOOL CDataSourceSingleton::ReadConfigFile(const CString& strFilePath)
{	
	CString strLines[LINES_TO_READ];
	int nLinesRead;
	CStdioFile oFile(strFilePath, CFile::modeRead);

	for (nLinesRead = 0; nLinesRead < LINES_TO_READ; nLinesRead++)
	{
		if (!oFile.ReadString(strLines[nLinesRead]))
			break;
	}

	if (nLinesRead <= ConfigLinesDataSource)
		return FALSE;

	m_strDatasourceName = strLines[ConfigLinesDataSource];

	if (nLinesRead < ConfigLinesPassword)
	{
		return OpenConnectionWindowsAuthentication();
	}

	if (!OpenConnectionLogin(strLines[ConfigLinesUsername], strLines[ConfigLinesPassword]))
	{
		return OpenConnectionWindowsAuthentication();
	}

	return TRUE;
}


CDataSourceSingleton* CDataSourceSingleton::GetInstance()
{
	if (_pInstance == NULL)
	{
		_pInstance = new CDataSourceSingleton();
	}

	return _pInstance;
}

void CDataSourceSingleton::ShowErrorMessage(const HRESULT hResult) const
{
	CString strError;
	strError.Format(_T(
		"Error connecting to DB. Error: %d\n"
		"DATASOURCE_NAME: %s\n"
		"DATABASE_NAME: %s"
	), hResult, m_strDatasourceName, DATABASE_NAME);
	CErrorLogger::LogMessage(strError, TRUE, FALSE);
}

BOOL CDataSourceSingleton::Login(CDBPropSet& oDBPropSet)
{
	const HRESULT hResult = m_oDataSource.Open(DATABASE_CLSID, &oDBPropSet);
	if (FAILED(hResult))
	{
		ShowErrorMessage(hResult);

		return FALSE;
	}

	return TRUE;
}

BOOL CDataSourceSingleton::OpenConnectionWindowsAuthentication()
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, m_strDatasourceName);
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, DATABASE_AUTHENTIFICATION);
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, DATABASE_NAME);
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, DATABASE_PERSIST_SENSITIVE_AUTHINFO);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, DATABASE_INIT_LCID);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	return Login(oDBPropSet);
}

BOOL CDataSourceSingleton::OpenConnectionLogin(const CString& strUsername, const CString& strPassword)
{
	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, m_strDatasourceName);
	oDBPropSet.AddProperty(DBPROP_AUTH_USERID, strUsername.GetString());                        
	oDBPropSet.AddProperty(DBPROP_AUTH_PASSWORD, strPassword.GetString());                        
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, DATABASE_NAME);
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, DATABASE_PERSIST_SENSITIVE_AUTHINFO);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, DATABASE_INIT_LCID);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	return Login(oDBPropSet);
}


CDataSource* CDataSourceSingleton::GetDataSource()
{
	return &m_oDataSource;
}

void CDataSourceSingleton::CloseConnection()
{
	if (_pInstance == NULL)
	{
		return;
	}

	m_oDataSource.Close();
	delete _pInstance;
	_pInstance = NULL;
}

// Overrides
// ----------------
