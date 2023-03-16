#pragma once
#include "Structures.h"
#include "PtrAutoArray.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonDisplay

/// <summary>
/// Клас съдържащ допълнителните данни за PERSONS
/// </summary>
class CPersonDisplay
{
public:
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
	CPersonDisplay();
	~CPersonDisplay();

	// Methods
	// ----------------

	/// <summary> Връща град по ID </summary>
	BOOL GetCityByID(const long lID, CITIES& recCity) const;

	/// <summary> Връща типа на телефона по ID </summary>
	BOOL GetPhoneTypeByID(const long lID, PHONE_TYPES& recPhoneType) const;

	/// <summary> Връща всички градове </summary>
	CPtrAutoArray<CITIES>* GetCities();

	/// <summary> Връща всички видове телефони </summary>
	CPtrAutoArray<PHONE_TYPES>* GetPhoneTypes();

	// Overrides
	// ----------------

	// Members
	// ----------------
private:
	CPtrAutoArray<CITIES> m_oCities;
	CPtrAutoArray<PHONE_TYPES> m_oPhoneTypes;
};