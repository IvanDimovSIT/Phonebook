#pragma once
#include "PtrAutoArray.h"
#include "Person.h"
#include "PersonDisplay.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsFileConverter

/// <summary>
/// Клас за конвертиране на PERSONS в HTML
/// </summary>
class CPersonsFileConverter
{
public:
// Constants
// ----------------

// Constructor / Destructor
// ----------------
	CPersonsFileConverter();
	~CPersonsFileConverter();
// Methods
// ----------------
	BOOL Convert(const CString& strFilepath, CPtrAutoArray<CPerson>& oPersonArray, CPersonDisplay& oPersonDisplay) const;
// Overrides
// ----------------

// Members
// ----------------
};

