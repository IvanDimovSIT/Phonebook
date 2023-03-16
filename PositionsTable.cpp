#include "pch.h"
#include "PositionsTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionsTable

// Constants
// ----------------

#define POSITIONS_TABLE_NAME _T("POSITIONS")

// Constructor / Destructor
// ----------------

CPositionsTable::CPositionsTable(CSession& oSession) :
    CDBTable(m_recPosition, POSITIONS_TABLE_NAME, oSession)
{
}

CPositionsTable::CPositionsTable() :
    CDBTable(m_recPosition, POSITIONS_TABLE_NAME)
{
}

CPositionsTable::~CPositionsTable()
{
}

// Methods
// ----------------


// Overrides
// ----------------
