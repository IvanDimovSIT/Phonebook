#include "pch.h"
#include "PhoneTypesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

// Constants
// ----------------

#define PHONE_TYPES_TABLE_NAME _T("PHONE_TYPES")

// Constructor / Destructor
// ----------------

CPhoneTypesTable::CPhoneTypesTable(CSession& oSession) :
    CDBTable(m_recPhoneType, PHONE_TYPES_TABLE_NAME, oSession)
{
}

CPhoneTypesTable::~CPhoneTypesTable()
{
}

// Methods
// ----------------


// Overrides
// ----------------