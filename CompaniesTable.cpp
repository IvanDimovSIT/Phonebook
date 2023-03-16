#include "pch.h"
#include "CompaniesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCompaniesTable

// Constants
// ----------------

#define COMPANIES_TABLE_NAME _T("COMPANIES")

// Constructor / Destructor
// ----------------

CCompaniesTable::CCompaniesTable(CSession& oSession) :
    CDBTable(m_recCompany, COMPANIES_TABLE_NAME, oSession)
{
}

CCompaniesTable::CCompaniesTable() :
    CDBTable(m_recCompany, COMPANIES_TABLE_NAME)
{
}

CCompaniesTable::~CCompaniesTable()
{
}

// Methods
// ----------------


// Overrides
// ----------------
