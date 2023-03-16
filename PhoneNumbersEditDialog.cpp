// PhoneNumbersEditDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PhoneNumbersEditDialog.h"
#include "ErrorLogger.h"
#include "InputValidator.h"
#include "afxdialogex.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersEditDialog


// Constants
// ----------------

#define DIALOG_ADD_NAME _T("Добавяне")
#define DIALOG_EDIT_NAME _T("Редактиране")
#define DIALOG_VIEW_NAME _T("Преглед")

#define MIN_PHONE_NUMBER_LENGTH 4

#define VALIDATE_PHONE_NUMBER_MESSAGE _T("Моля въведете телефонен номер.")
#define VALIDATE_PHONE_TYPE_MESSAGE _T("Моля въведете типа на телефонния номер.")


IMPLEMENT_DYNAMIC(CPhoneNumbersEditDialog, CDialogEx)

// Constructor / Destructor
// ----------------

CPhoneNumbersEditDialog::CPhoneNumbersEditDialog(
	const PHONE_NUMBERS* pPhoneNumber,
	PhoneNumbersEditDialogType ePhoneNumbersEditDialogType,
	CPersonDisplay& oPersonDisplay,
	CWnd* pParent)
	: CDialogEx(IDD_PHONE_NUMBERS_EDIT_DIALOG, pParent),
	m_ePhoneNumbersEditDialogType(ePhoneNumbersEditDialogType),
	m_pPersonDisplay(&oPersonDisplay),
	m_pPhoneNumber(pPhoneNumber)
{

}

CPhoneNumbersEditDialog::~CPhoneNumbersEditDialog()
{
}

// Methods
// ----------------

BOOL CPhoneNumbersEditDialog::ValidateUserInput() const
{
	CInputValidator oInputValidator;

	if (!oInputValidator.ValidateNumber(m_edbPhoneNumber, PHONE_NUMBERS_NUMBER_LENGTH, MIN_PHONE_NUMBER_LENGTH))
	{
		AfxMessageBox(VALIDATE_PHONE_NUMBER_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if (!oInputValidator.ValidateComboBox(m_cmbPhoneType))
	{
		AfxMessageBox(VALIDATE_PHONE_TYPE_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

void CPhoneNumbersEditDialog::SetComboBox()
{
	const CPtrAutoArray<PHONE_TYPES>* oPhoneTypesArray = m_pPersonDisplay->GetPhoneTypes();
	for (INT_PTR i = 0; i < oPhoneTypesArray->GetCount(); i++)
	{
		PHONE_TYPES* pCurrentType = oPhoneTypesArray->GetAt(i);

		int nIndex = m_cmbPhoneType.AddString(pCurrentType->szType);
		m_cmbPhoneType.SetItemData(nIndex, (DWORD_PTR)pCurrentType->lID);


		if (m_pPhoneNumber == NULL ||
			pCurrentType->lID != m_pPhoneNumber->lPhoneTypeID)
			continue;

		m_cmbPhoneType.SetCurSel(nIndex);
	}
}

void CPhoneNumbersEditDialog::GetPhoneNumber(PHONE_NUMBERS& recPhoneNumber)
{
	recPhoneNumber = m_recPhoneNumber;
}

BOOL CPhoneNumbersEditDialog::SetDialogName()
{
	switch (m_ePhoneNumbersEditDialogType)
	{
	case PhoneNumbersEditDialogTypeAdd:
		SetWindowText(DIALOG_ADD_NAME);
		break;
	case PhoneNumbersEditDialogTypeEdit:
		SetWindowText(DIALOG_EDIT_NAME);
		break;
	case PhoneNumbersEditDialogTypeView:
		SetWindowText(DIALOG_VIEW_NAME);
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;

}

void CPhoneNumbersEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBERS_EDIT_PHONE_NUMBER, m_edbPhoneNumber);
	DDX_Control(pDX, IDC_CMB_PHONE_NUMBERS_EDIT_TYPE, m_cmbPhoneType);
}


BEGIN_MESSAGE_MAP(CPhoneNumbersEditDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPhoneNumbersEditDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPhoneNumbersEditDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPhoneNumbersEditDialog message handlers


void CPhoneNumbersEditDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (m_ePhoneNumbersEditDialogType == PhoneNumbersEditDialogTypeView)
	{
		CDialogEx::OnOK();
		return;
	}

	if (!ValidateUserInput())
	{
		return;
	}

	if(m_ePhoneNumbersEditDialogType != PhoneNumbersEditDialogTypeAdd)
		m_recPhoneNumber = *m_pPhoneNumber;

	m_recPhoneNumber.lPhoneTypeID = m_cmbPhoneType.GetItemData(m_cmbPhoneType.GetCurSel());
	m_edbPhoneNumber.GetWindowTextW(m_recPhoneNumber.szPhoneNumber, PHONE_NUMBERS_NUMBER_LENGTH);

	CDialogEx::OnOK();
}


void CPhoneNumbersEditDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CPhoneNumbersEditDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!SetDialogName())
		CErrorLogger::LogMessage(_T("Error setting dialog name."), TRUE, TRUE);

	SetComboBox();

	if (m_ePhoneNumbersEditDialogType != PhoneNumbersEditDialogTypeAdd &&
		m_pPhoneNumber == NULL)
		return FALSE;

	if (m_ePhoneNumbersEditDialogType == PhoneNumbersEditDialogTypeAdd)
		return TRUE;

	m_edbPhoneNumber.SetWindowTextW(m_pPhoneNumber->szPhoneNumber);
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// Overrides
// ----------------
