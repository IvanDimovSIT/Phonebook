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

	/// <summary> Връща компания по ID </summary>
	BOOL GetCompanyByID(const long lID, COMPANIES& recCompany) const;

	/// <summary> Връща позиция по ID </summary>
	BOOL GetPositionByID(const long lID, POSITIONS& recPositon) const;

	/// <summary> Връща всички градове </summary>
	CPtrAutoArray<COMPANIES>* GetCompanies();

	/// <summary> Връща всички позиции </summary>
	CPtrAutoArray<POSITIONS>* GetPositions();

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
	CPtrAutoArray<COMPANIES> m_oCompanies;
	CPtrAutoArray<POSITIONS> m_oPositions;
};