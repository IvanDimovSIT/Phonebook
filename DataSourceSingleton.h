#pragma once
#include <atldbcli.h>

/////////////////////////////////////////////////////////////////////////////
// CDataSourceSingleton

/// <summary>
/// Singleton клас за връзка с базата данни
/// </summary>
class CDataSourceSingleton
{
// Constants
// ----------------


// Constructor / Destructor
// ----------------
private:
	CDataSourceSingleton();


// Methods
// ----------------
public:
    CDataSourceSingleton(CDataSourceSingleton& oDataSourceSingleton) = delete;
    void operator=(const CDataSourceSingleton&) = delete;
private:

	/// <summary> Показва съобщение за грешка </summary>
	void ShowErrorMessage(const HRESULT hResult) const;

	/// <summary> Логване в БД </summary>
	BOOL Login(CDBPropSet& oDBPropSet);

	BOOL ReadConfigFile(const CString& strFilePath);
public:

	/// <summary> Свързване с базата данни чрез Windows Authentication </summary>
	BOOL OpenConnectionWindowsAuthentication();

	/// <summary> Свързване с базата данни чрез име и парола </summary>
	BOOL OpenConnectionLogin(const CString& strUsername, const CString& strPassword);

    /// <summary> Метод за достъп до инстанцията на класа </summary>
    static CDataSourceSingleton* GetInstance();

	/// <summary> Достъп до CDataSource </summary>
	CDataSource* GetDataSource();

	/// <summary> Затваря връзката с базата данни </summary>
	void CloseConnection();

// Overrides
// ----------------

// Members
// ----------------
private:
	/// <summary> Указател към Singleton обекта </summary>
	static CDataSourceSingleton* _pInstance;
	/// <summary> Връзката с БД </summary>
	CDataSource m_oDataSource;
	/// <summary> Името на БД </summary>
	CString m_strDatasourceName;
};

