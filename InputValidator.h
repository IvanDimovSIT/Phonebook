#pragma once

/////////////////////////////////////////////////////////////////////////////
// CInputValidator

/// <summary>
/// Проверява дали са въведени данни
/// </summary>
class CInputValidator
{
// Constants
// ----------------

// Constructor / Destructor
// ----------------
public:
	CInputValidator();

	~CInputValidator();

// Methods
// ----------------

	/// <summary> Проверява дали е въведен номер </summary>
	BOOL ValidateNumber(const CEdit& edbField, const int nMaxLength, const int nMinLength) const;

	/// <summary> Проверява дали са зададени стойностите на полетата </summary>
	BOOL ValidateTextField(const CEdit& edbField, const int nMaxLength, const int nMinLength) const;

	/// <summary> Проверява дали са зададени стойностите на полетата </summary>
	BOOL ValidateComboBox(const CComboBox& cmbComboBox) const;

// Overrides
// ----------------



// Members
// ----------------

};

