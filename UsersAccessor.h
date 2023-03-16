#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define USERS_ACCESSOR_MAP_VALUE 2

enum UsersAccessorValues
{
	UsersAccessorValuesFirst = 0,
	UsersAccessorValuesSecond
};

enum UsersAccessorColumnEntries
{
	UsersAccessorColumnEntriesID = 1,
	UsersAccessorColumnEntriesUpdateCounter,
	UsersAccessorColumnEntriesName,
	UsersAccessorColumnEntriesDistrict
};

/////////////////////////////////////////////////////////////////////////////
// CUsersAccessor


/// <summary>
/// Accessor за таблицата USERS
/// </summary>
class CUsersAccessor
{
protected:
	USERS m_recUser;
	BEGIN_ACCESSOR_MAP(CUsersAccessor, USERS_ACCESSOR_MAP_VALUE)
		BEGIN_ACCESSOR(UsersAccessorValuesFirst, true)
			COLUMN_ENTRY(UsersAccessorColumnEntriesID, m_recUser.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(UsersAccessorValuesSecond, true)
			COLUMN_ENTRY(UsersAccessorColumnEntriesUpdateCounter, m_recUser.lUpdateCounter)
			COLUMN_ENTRY(UsersAccessorColumnEntriesName, m_recUser.szUsername)
			COLUMN_ENTRY(UsersAccessorColumnEntriesDistrict, m_recUser.szPassword)
		END_ACCESSOR()

	END_ACCESSOR_MAP()
};

