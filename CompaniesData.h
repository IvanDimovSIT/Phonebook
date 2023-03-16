#pragma once
#include "CompaniesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCompaniesData

/// <summary>
/// Клас съдържащ бизнес логиката за COMPANIES
/// </summary>
class CCompaniesData
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CCompaniesData();
	~CCompaniesData();

	// Methods
	// ----------------
	/// <summary> Получава всички записи за COMPANIES и пълни масива </summary>
	BOOL SelectAll(CPtrAutoArray<COMPANIES>& oCompaniesAutoArray);

	/// <summary> Намира запис по зададено ID </summary>
	BOOL SelectWhereID(const long lID, COMPANIES& recCompany);

	/// <summary> Променя запис по ID </summary>
	BOOL UpdateWhereID(const long lID, const COMPANIES& recCompany);

	/// <summary> Създава нов запис </summary>
	BOOL InsertCompany(COMPANIES& recCompany);

	/// <summary> Изтрива запис по ID </summary>
	BOOL DeleteWhereID(const long lID);

	// Overrides
	// ----------------


	// Members
	// ----------------
private:
};

