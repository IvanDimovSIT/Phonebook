#pragma once
#include "PhoneNumbersEditDialogType.h"
#include "Structures.h"
#include "PersonDisplay.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersEditDialog

/// <summary>
/// Диалог за редктиране на телефонен номер, извикван от CPhoneNumbersDialog
/// </summary>
class CPhoneNumbersEditDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPhoneNumbersEditDialog)


// Constants
// ----------------


// Constructor / Destructor
// ----------------

public:
	CPhoneNumbersEditDialog(
		const PHONE_NUMBERS* pPhoneNumber,
		PhoneNumbersEditDialogType ePhoneNumbersEditDialogType,
		CPersonDisplay& oPersonDisplay,
		CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersEditDialog();

// Methods
// ----------------
private:
	/// <summary> Инициализира combo box-a </summary>
	void SetComboBox();
	/// <summary> Задава заглавието на диалога </summary>
	BOOL SetDialogName();
	/// <summary> Проверява за коректно въведени полета </summary>
	BOOL ValidateUserInput() const;
public:
	/// <summary> Връща новите стойности на телефонния номер </summary>
	void GetPhoneNumber(PHONE_NUMBERS& recPhoneNumber);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONE_NUMBERS_EDIT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// Overrides
// ----------------

// Members
// ----------------
private:
	/// <summary> Типа на диалога </summary>
	const PhoneNumbersEditDialogType m_ePhoneNumbersEditDialogType;
	/// <summary> Допълнителна информация за представяне на номера (типа) </summary>
	CPersonDisplay* m_pPersonDisplay;
	/// <summary> Допълнителна информация за представяне на номера </summary>
	const PHONE_NUMBERS* m_pPhoneNumber;
	/// <summary> Новополучения телефонен номер </summary>
	PHONE_NUMBERS m_recPhoneNumber;
public:
	//контроли на диалога
	CEdit m_edbPhoneNumber;
	CComboBox m_cmbPhoneType;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
