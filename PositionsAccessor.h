#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define POSITIONS_ACCESSOR_MAP_VALUE 2

enum PositionsAccessorValues
{
	PositionsAccessorValuesFirst = 0,
	PositionsAccessorValuesSecond
};

enum PositionsAccessorColumnEntries
{
	PositionsAccessorColumnEntriesID = 1,
	PositionsAccessorColumnEntriesUpdateCounter,
	PositionsAccessorColumnEntriesPositionName
};

/////////////////////////////////////////////////////////////////////////////
// CPositionsAccessor


/// <summary>
/// Accessor за таблицата POSITIONS
/// </summary>
class CPositionsAccessor
{
protected:
	POSITIONS m_recPosition;
	BEGIN_ACCESSOR_MAP(CPositionsAccessor, POSITIONS_ACCESSOR_MAP_VALUE)
		BEGIN_ACCESSOR(PositionsAccessorValuesFirst, true)
			COLUMN_ENTRY(PositionsAccessorColumnEntriesID, m_recPosition.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(PositionsAccessorValuesSecond, true)
			COLUMN_ENTRY(PositionsAccessorColumnEntriesUpdateCounter, m_recPosition.lUpdateCounter)
			COLUMN_ENTRY(PositionsAccessorColumnEntriesPositionName, m_recPosition.szPositionName)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};
