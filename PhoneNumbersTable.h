#pragma once
#include <atldbcli.h>
#include "DBTable.h"
#include "PhoneNumbersAccessor.h"
#include "PtrAutoArray.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>
/// Клас за работа с таблицата PHONE_NUMBERS
/// </summary>
class CPhoneNumbersTable : public
	CDBTable<CPhoneNumbersAccessor, PHONE_NUMBERS>
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CPhoneNumbersTable(CSession& oSession);
	~CPhoneNumbersTable();

	// Methods
	// ----------------
private:
	BOOL SelectWherePersonID(const long lPersonID);

public:
	/// <summary> Намира всички PHONE_NUMBERS със съответния PERSON_ID </summary>
	BOOL SelectWherePersonID(const long lPersonID, CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers);

	/// <summary> Изтрива всички PHONE_NUMBERS със съответния PERSON_ID </summary>
	BOOL DeleteWherePersonID(const long lPersonID);
	// Overrides
	// ----------------

	// Members
	// ----------------
};

