#include "pch.h"
#include "CitiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

// Constants
// ----------------

// Constructor / Destructor
// ----------------

CCitiesData::CCitiesData()
{
}

CCitiesData::~CCitiesData()
{
}

// Methods
// ----------------
BOOL CCitiesData::SelectByName(CPtrAutoArray<CITIES>& oAutoArray, const CString& strName)
{
	CCitiesTable oCitiesTable;
	return oCitiesTable.SelectByName(oAutoArray, strName);
}


BOOL CCitiesData::SelectAll(CPtrAutoArray<CITIES>& oCitiesAutoArray)
{
	//CSession oSession;
	CCitiesTable oCitiesTable;
	return oCitiesTable.SelectAll(oCitiesAutoArray);
}


BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCity)
{
	//CSession oSession;
	CCitiesTable oCitiesTable;
	return oCitiesTable.SelectWhereID(lID, recCity);
}


BOOL CCitiesData::UpdateWhereID(const long lID, const CITIES& recCity)
{
	//CSession oSession;
	CCitiesTable oCitiesTable;
	return oCitiesTable.UpdateWhereID(lID, recCity);
}


BOOL CCitiesData::InsertCity(CITIES& recCity)
{
	//CSession oSession;
	CCitiesTable oCitiesTable;
	return oCitiesTable.InsertRecord(recCity);
}


BOOL CCitiesData::DeleteWhereID(const long lID)
{
	//CSession oSession;
	CCitiesTable oCitiesTable;
	return oCitiesTable.DeleteWhereID(lID);
}

// Overrides
// ----------------
