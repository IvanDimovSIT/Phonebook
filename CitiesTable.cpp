#include "pch.h"
#include "CitiesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

// Constants
// ----------------

#define CITIES_TABLE_NAME _T("CITIES")

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


// Overrides
// ----------------
