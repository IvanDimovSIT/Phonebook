#include "pch.h"
#include "InputValidator.h"

/////////////////////////////////////////////////////////////////////////////
// CInputValidator

// Constants
// ----------------

// Constructor / Destructor
// ----------------

CInputValidator::CInputValidator()
{
}

CInputValidator::~CInputValidator()
{
}

// Methods
// ----------------

BOOL CInputValidator::ValidateNumber(const CEdit& edbField, const int nMaxLength, const int nMinLength) const
{
	CString strField = _T("");
	const int nLength = edbField.GetWindowTextLengthW();
	if (nLength > nMaxLength ||
		nLength < nMinLength)
	{
		return FALSE;
	}

	edbField.GetWindowTextW(strField);

	for (int i = 0; i < nLength; i++)
	{

		if (strField[i] < _T('0') || strField[i] > _T('9'))
			return FALSE;
	}

	return TRUE;
}


BOOL CInputValidator::ValidateTextField(const CEdit& edbField, const int nMaxLength, const int nMinLength) const
{
	CString strField = _T("");
	const int nLength = edbField.GetWindowTextLengthW();
	if (nLength > nMaxLength ||
		nLength < nMinLength)
	{
		return FALSE;
	}

	edbField.GetWindowTextW(strField);

	for (int i = 0; i < nLength; i++)
	{

		if (strField[i] != _T(' ') &&
			strField[i] != _T('\t') &&
			strField[i] != _T('\n'))
			return TRUE;
	}

	return FALSE;
}


BOOL CInputValidator::ValidateComboBox(const CComboBox& cmbComboBox) const
{
	return cmbComboBox.GetCurSel() != CB_ERR;
}



// Overrides
// ----------------