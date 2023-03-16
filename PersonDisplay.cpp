#include "pch.h"
#include "PersonDisplay.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonDisplay

// Constructor / Destructor
// ----------------

CPersonDisplay::CPersonDisplay()
{
}

CPersonDisplay::~CPersonDisplay()
{
}


// Methods
// ----------------

BOOL CPersonDisplay::GetCityByID(const long lID, CITIES& recCity) const
{
	for (INT_PTR i = 0; i < m_oCities.GetCount(); i++)
	{
		if (m_oCities.GetAt(i)->lID != lID)
			continue;

		recCity = *(m_oCities.GetAt(i));
		return TRUE;
	}

	return FALSE;
}

BOOL CPersonDisplay::GetPhoneTypeByID(const long lID, PHONE_TYPES& recPhoneType) const
{
	for (INT_PTR i = 0; i < m_oPhoneTypes.GetCount(); i++)
	{
		if (m_oPhoneTypes.GetAt(i)->lID != lID)
			continue;

		recPhoneType = *(m_oPhoneTypes.GetAt(i));
		return TRUE;
	}

	return FALSE;
}

CPtrAutoArray<CITIES>* CPersonDisplay::GetCities()
{
	return &m_oCities;
}

CPtrAutoArray<PHONE_TYPES>* CPersonDisplay::GetPhoneTypes()
{
	return &m_oPhoneTypes;
}


// Overrides
// ----------------

