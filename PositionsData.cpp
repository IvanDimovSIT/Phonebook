#include "pch.h"
#include "PositionsData.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionsData

// Constants
// ----------------

// Constructor / Destructor
// ----------------

CPositionsData::CPositionsData()
{
}

CPositionsData::~CPositionsData()
{
}

// Methods
// ----------------

BOOL CPositionsData::SelectAll(CPtrAutoArray<POSITIONS>& oPositionsAutoArray)
{
	//CSession oSession;
	CPositionsTable oPositionsTable;
	return oPositionsTable.SelectAll(oPositionsAutoArray);
}


BOOL CPositionsData::SelectWhereID(const long lID, POSITIONS& recPosition)
{
	//CSession oSession;
	CPositionsTable oPositionsTable;
	return oPositionsTable.SelectWhereID(lID, recPosition);
}


BOOL CPositionsData::UpdateWhereID(const long lID, const POSITIONS& recPosition)
{
	//CSession oSession;
	CPositionsTable oPositionsTable;
	return oPositionsTable.UpdateWhereID(lID, recPosition);
}


BOOL CPositionsData::InsertPosition(POSITIONS& recPosition)
{
	//CSession oSession;
	CPositionsTable oPositionsTable;
	return oPositionsTable.InsertRecord(recPosition);
}


BOOL CPositionsData::DeleteWhereID(const long lID)
{
	//CSession oSession;
	CPositionsTable oPositionsTable;
	return oPositionsTable.DeleteWhereID(lID);
}

// Overrides
// ----------------
