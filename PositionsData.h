#pragma once
#include "PositionsTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionsData

/// <summary>
/// Клас съдържащ бизнес логиката за POSITIONS
/// </summary>
class CPositionsData
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CPositionsData();
	~CPositionsData();

	// Methods
	// ----------------
	/// <summary> Получава всички записи за POSITIONS и пълни масива </summary>
	BOOL SelectAll(CPtrAutoArray<POSITIONS>& oPositionsAutoArray);

	/// <summary> Намира запис по зададено ID </summary>
	BOOL SelectWhereID(const long lID, POSITIONS& recPosition);

	/// <summary> Променя запис по ID </summary>
	BOOL UpdateWhereID(const long lID, const POSITIONS& recPosition);

	/// <summary> Създава нов запис </summary>
	BOOL InsertPosition(POSITIONS& recPosition);

	/// <summary> Изтрива запис по ID </summary>
	BOOL DeleteWhereID(const long lID);

	// Overrides
	// ----------------


	// Members
	// ----------------
private:
};

