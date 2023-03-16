#pragma once
#include "Structures.h"
#include "PtrAutoArray.h"

/////////////////////////////////////////////////////////////////////////////
// CPerson

/// <summary>
/// Клас съдържащ данните за PERSONS
/// </summary>
class CPerson 
{
// Constants
// ----------------

// Constructor / Destructor
// ----------------
public:
	CPerson();
	CPerson(const CPerson& oPerson);
	~CPerson();

// Methods
// ----------------

// Overrides
// ----------------

// Members
// ----------------
public:
	PERSONS m_recPerson;
	CPtrAutoArray<PHONE_NUMBERS> m_oPhoneNumbers;
};