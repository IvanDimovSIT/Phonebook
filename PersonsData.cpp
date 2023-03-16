#include "pch.h"
#include "PersonsData.h"
#include "PersonsTable.h"
#include "PersonDisplay.h"
#include "PhoneNumbersTable.h"
#include "CitiesTable.h"
#include "CompaniesTable.h"
#include "PositionsTable.h"
#include "PhoneTypesTable.h"
#include "ErrorLogger.h"
#include "DataSourceSingleton.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsData

// Constants
// ----------------

#define DATA_ERROR_MESSAGE _T("Error in PersonsData. Error %#lx")

// Constructor / Destructor
// ----------------
CPersonsData::CPersonsData()
{
}

CPersonsData::~CPersonsData() 
{
}

// Methods
// ----------------

void CPersonsData::LogError(const HRESULT hResult) const
{
	CString strError;
	strError.Format(DATA_ERROR_MESSAGE, hResult);
	CErrorLogger::LogMessage(strError, TRUE, TRUE);
}


BOOL CPersonsData::SelectPhoneNumbersForPerson(
	CPtrAutoArray<CPerson>& oPersonsArrayComplete,
	const CPtrAutoArray<PERSONS>& oPersonsArray,
	CPhoneNumbersTable& oPhoneNumbersTable) const
{
	for (INT_PTR i = 0; i < oPersonsArray.GetCount(); i++)
	{
		CPerson* pPersonToAdd = new CPerson;
		pPersonToAdd->m_recPerson = *oPersonsArray.GetAt(i);

		if (!oPhoneNumbersTable.SelectWherePersonID(pPersonToAdd->m_recPerson.lID, pPersonToAdd->m_oPhoneNumbers))
		{
			delete pPersonToAdd;
			oPersonsArrayComplete.RemoveAll();
			return FALSE;
		}

		oPersonsArrayComplete.Add(pPersonToAdd);
	}

	return TRUE;
}

BOOL CPersonsData::PhoneNumberInArray(const CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers,
	const PHONE_NUMBERS& recSearched,
	PHONE_NUMBERS& recFound) const
{
	for (INT_PTR i = 0; i < oPhoneNumbers.GetCount(); i++)
	{
		if (oPhoneNumbers.GetAt(i)->lID == recSearched.lID)
		{
			recFound = *oPhoneNumbers.GetAt(i);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CPersonsData::DeleteCheck(const long lPersonID, 
	const CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers,
	const CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbersDB,
	CPhoneNumbersTable& oPhoneNumbersTable) const
{
	PHONE_NUMBERS recFound;

	for (INT_PTR i = 0; i < oPhoneNumbersDB.GetCount(); i++)
	{
		if (oPhoneNumbersDB.GetAt(i)->lPersonID != lPersonID)
			continue;

		if (PhoneNumberInArray(oPhoneNumbers, *oPhoneNumbersDB.GetAt(i), recFound))
			continue;

		if (!oPhoneNumbersTable.DeleteWhereID(oPhoneNumbersDB.GetAt(i)->lID))
			return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::UpdatePersonsPhoneNumbers(const long lPersonID,
	CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers,
	CPhoneNumbersTable& oPhoneNumbersTable) const
{
	CPtrAutoArray<PHONE_NUMBERS> oPhoneNumbersDB;
	if (!oPhoneNumbersTable.SelectWherePersonID(lPersonID, oPhoneNumbersDB))
		return FALSE;

	PHONE_NUMBERS recFound;
	for (INT_PTR i = 0; i < oPhoneNumbers.GetCount(); i++)
	{
		PHONE_NUMBERS* pCurrent = oPhoneNumbers.GetAt(i);


		if (!PhoneNumberInArray(oPhoneNumbersDB, *pCurrent, recFound)) //за insert
		{
			if (!oPhoneNumbersTable.InsertRecord(*pCurrent))
				return FALSE;
		}
		else //за update
		{
			if (recFound == (*pCurrent))
				continue;

			if (!oPhoneNumbersTable.UpdateWhereID(pCurrent->lID, *pCurrent))
				return FALSE;
		}
	}

	return DeleteCheck(lPersonID, oPhoneNumbers, oPhoneNumbersDB, oPhoneNumbersTable);
}

BOOL CPersonsData::SelectAll(CPtrAutoArray<CPerson>& oPersonAutoArray) const
{
	CSession oSession;
	CPersonsTable oPersonsTable(oSession);
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	oSession.Open(*CDataSourceSingleton::GetInstance()->GetDataSource());


	CPtrAutoArray<PERSONS> oPersonsPartialArray;
	if (!oPersonsTable.SelectAllSorted(oPersonsPartialArray))
	{
		oSession.Close();
		return FALSE;
	}
	

	BOOL bResult = SelectPhoneNumbersForPerson(oPersonAutoArray, oPersonsPartialArray, oPhoneNumbersTable);
	oSession.Close();
	return bResult;
}

BOOL CPersonsData::SelectWhereID(const long lID, CPerson& oPerson) const
{
	CSession oSession;
	CPersonsTable oPersonsTable(oSession);
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	oSession.Open(*CDataSourceSingleton::GetInstance()->GetDataSource());


	if (!oPersonsTable.SelectWhereID(lID, oPerson.m_recPerson)) 
	{ 
		oSession.Close(); 
		return FALSE; 
	}

	BOOL bResult = oPhoneNumbersTable.SelectWherePersonID(lID, oPerson.m_oPhoneNumbers);
	oSession.Close();
	return bResult;
}

BOOL CPersonsData::UpdateWhereID(const long lID, CPerson& oPerson) const
{
	CSession oSession;
	CPersonsTable oPersonsTable(oSession);
	CPhoneNumbersTable oPhoneNumbersTable(oSession);

	oSession.Open(*CDataSourceSingleton::GetInstance()->GetDataSource());

	HRESULT hResult = oSession.StartTransaction();
	if (FAILED(hResult))
	{
		LogError(hResult);
		oSession.Close();
		return FALSE;
	}

	if (!oPersonsTable.UpdateWhereID(lID, oPerson.m_recPerson))
	{
		oSession.Abort();
		oSession.Close();
		return FALSE;
	}

	if (!UpdatePersonsPhoneNumbers(oPerson.m_recPerson.lID, oPerson.m_oPhoneNumbers, oPhoneNumbersTable))
	{
		oSession.Abort();
		oSession.Close();
		return FALSE;
	}

	hResult = oSession.Commit(); 
	if (FAILED(hResult))
	{
		LogError(hResult);
		oSession.Close();
		return FALSE;
	}

	oSession.Close();
	return TRUE;
}

BOOL CPersonsData::InsertPerson(CPerson& oPerson) const
{
	CSession oSession;
	CPersonsTable oPersonsTable(oSession);
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	oSession.Open(*CDataSourceSingleton::GetInstance()->GetDataSource());


	HRESULT hResult = oSession.StartTransaction();
	if (FAILED(hResult))
	{
		LogError(hResult);
		oSession.Close();
		return FALSE;
	}

	if (!oPersonsTable.InsertRecord(oPerson.m_recPerson))
	{
		oSession.Abort();
		oSession.Close();
		return FALSE;
	}

	// Задаваме ID-то на собственика на телефоните номера
	for (INT_PTR i = 0; i < oPerson.m_oPhoneNumbers.GetCount(); i++)
	{
		oPerson.m_oPhoneNumbers.GetAt(i)->lPersonID = oPerson.m_recPerson.lID;
	}

	for (INT_PTR i = 0; i < oPerson.m_oPhoneNumbers.GetCount(); i++)
	{
		if (!oPhoneNumbersTable.InsertRecord(*oPerson.m_oPhoneNumbers.GetAt(i)))
		{
			oSession.Abort();
			oSession.Close();
			return FALSE;
		}
	}

	hResult = oSession.Commit();
	if (FAILED(hResult))
	{
		LogError(hResult);
		oSession.Close();
		return FALSE;
	}

	oSession.Close();
	return TRUE;
}

BOOL CPersonsData::DeleteWhereID(const long lID) const
{
	CSession oSession;
	CPersonsTable oPersonsTable(oSession);
	CPhoneNumbersTable oPhoneNumbersTable(oSession);
	oSession.Open(*CDataSourceSingleton::GetInstance()->GetDataSource());

	HRESULT hResult = oSession.StartTransaction();
	if (FAILED(hResult))
	{
		LogError(hResult);
		oSession.Close();
		return FALSE;
	}

	if (!oPhoneNumbersTable.DeleteWherePersonID(lID))
	{
		oSession.Abort();
		oSession.Close();
		return FALSE;
	}

	if (!oPersonsTable.DeleteWhereID(lID))
	{
		oSession.Abort();
		oSession.Close();
		return FALSE;
	}

	hResult = oSession.Commit();
	if (FAILED(hResult))
	{
		LogError(hResult);
		oSession.Close();
		return FALSE;
	}

	oSession.Close();
	return TRUE;
}

BOOL CPersonsData::SelectDislpayInformation(CPersonDisplay& oPersonDisplay)
{
	CSession oSession;
	CPhoneTypesTable oPhoneTypesTable(oSession);
	CCitiesTable oCitiesTable(oSession);
	CCompaniesTable oCompaniesTable(oSession);
	CPositionsTable oPositionsTable(oSession);
	oSession.Open(*CDataSourceSingleton::GetInstance()->GetDataSource());


	BOOL bResult =
		oPhoneTypesTable.SelectAll(*oPersonDisplay.GetPhoneTypes()) &&
		oCitiesTable.SelectAll(*oPersonDisplay.GetCities()) &&
		oCompaniesTable.SelectAll(*oPersonDisplay.GetCompanies()) &&
		oPositionsTable.SelectAll(*oPersonDisplay.GetPositions());

	oSession.Close();

	return bResult;
}


// Overrides
// ----------------

