#include "pch.h"
#include "ErrorLogger.h"
#include <iostream>
#include <fstream>


/////////////////////////////////////////////////////////////////////////////
// CErrorLogger

// Constants
// ----------------

const char* CErrorLogger::_szFilepath = "logfile.txt";

// Constructor / Destructor
// ----------------

// Methods
// ----------------

void CErrorLogger::LogErrorToFile(const CString& strError)
{
	const CTime oTime = CTime::GetCurrentTime();
	std::wofstream oLogfile;

	oLogfile.open(_szFilepath, std::ios_base::app);
	oLogfile << oTime.Format(_T("[%D %T] : ")).GetString() << strError.GetString() << _T("\n");
	oLogfile.close();
}

void CErrorLogger::LogErrorAsMessage(const CString& strError)
{
	AfxMessageBox(strError.GetString());
}

void CErrorLogger::LogMessage(const CString& strError, const BOOL bToFile, const BOOL bAsMessage)
{
	if (bToFile)
		LogErrorToFile(strError);
	
	if (bAsMessage)
		LogErrorAsMessage(strError);
}

// Overrides
// ----------------