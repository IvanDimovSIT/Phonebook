#include "pch.h"
#include "CompaniesData.h"

/////////////////////////////////////////////////////////////////////////////
// CCompaniesData

// Constants
// ----------------

// Constructor / Destructor
// ----------------

CCompaniesData::CCompaniesData()
{
}

CCompaniesData::~CCompaniesData()
{
}

// Methods
// ----------------

BOOL CCompaniesData::SelectAll(CPtrAutoArray<COMPANIES>& oCitiesAutoArray)
{
	//CSession oSession;
	CCompaniesTable oCompaniesTable;
	return oCompaniesTable.SelectAll(oCitiesAutoArray);
}


BOOL CCompaniesData::SelectWhereID(const long lID, COMPANIES& recCompany)
{
	//CSession oSession;
	CCompaniesTable oCompaniesTable;
	return oCompaniesTable.SelectWhereID(lID, recCompany);
}


BOOL CCompaniesData::UpdateWhereID(const long lID, const COMPANIES& recCompany)
{
	//CSession oSession;
	CCompaniesTable oCompaniesTable;
	return oCompaniesTable.UpdateWhereID(lID, recCompany);
}


BOOL CCompaniesData::InsertCompany(COMPANIES& recCompany)
{
	//CSession oSession;
	CCompaniesTable oCompaniesTable;
	return oCompaniesTable.InsertRecord(recCompany);
}


BOOL CCompaniesData::DeleteWhereID(const long lID)
{
	//CSession oSession;
	CCompaniesTable oCompaniesTable;
	return oCompaniesTable.DeleteWhereID(lID);
}

// Overrides
// ----------------
