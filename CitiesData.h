#pragma once
#include "CitiesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary>
/// Клас съдържащ бизнес логиката за CITIES
/// </summary>
class CCitiesData
{
// Constants
// ----------------

// Constructor / Destructor
// ----------------
public:
	CCitiesData();
	~CCitiesData();

// Methods
// ----------------
	/// <summary> Получава всички записи за CITIES и пълни масива </summary>
	BOOL SelectAll(CPtrAutoArray<CITIES>& oCitiesAutoArray);

	/// <summary> Намира запис по зададено ID </summary>
	BOOL SelectWhereID(const long lID, CITIES& recCity);

	/// <summary> Променя запис по ID </summary>
	BOOL UpdateWhereID(const long lID, const CITIES& recCity);

	/// <summary> Създава нов запис </summary>
	BOOL InsertCity(CITIES& recCity);

	/// <summary> Изтрива запис по ID </summary>
	BOOL DeleteWhereID(const long lID);

// Overrides
// ----------------


// Members
// ----------------
private:
};

