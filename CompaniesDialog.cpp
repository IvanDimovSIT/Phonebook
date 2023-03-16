
#include "pch.h"
#include "Phonebook.h"
#include "CompaniesDialog.h"
#include "afxdialogex.h"
#include "ErrorLogger.h"
#include "InputValidator.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog

// Constants
// ----------------

#define DIALOG_ADD_NAME _T("Добавяне")
#define DIALOG_EDIT_NAME _T("Редактиране")
#define DIALOG_VIEW_NAME _T("Преглед")

#define EMPTY_FIELD_MESSAGE _T("Попълнете всички полетата за данни.")
#define MIN_COMPANIES_FIELD_LENGTH 1

IMPLEMENT_DYNAMIC(CCompaniesDialog, CDialogEx)

// Constructor / Destructor
// ----------------

CCompaniesDialog::CCompaniesDialog(const COMPANIES* pCompany, const CompaniesDialogType eCompanyDialogType, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMPANIES_DIALOG, pParent),
	m_pCompany(pCompany),
	m_eCompaniesDialogType(eCompanyDialogType)
{
}

CCompaniesDialog::~CCompaniesDialog()
{
}

// Methods
// ----------------

const COMPANIES* CCompaniesDialog::GetCompany() const
{
	return &m_recCompany;
}

BOOL CCompaniesDialog::SetDialogName()
{
	switch (m_eCompaniesDialogType)
	{
	case CompaniesDialogTypeAdd:
		SetWindowText(DIALOG_ADD_NAME);
		break;
	case CompaniesDialogTypeEdit:
		SetWindowText(DIALOG_EDIT_NAME);
		break;
	case CompaniesDialogTypeView:
		SetWindowText(DIALOG_VIEW_NAME);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}


void CCompaniesDialog::SetReadOnly()
{
	m_edbName.SetReadOnly(TRUE);
}


BOOL CCompaniesDialog::SetDialogFields()
{
	switch (m_eCompaniesDialogType)
	{
	case CompaniesDialogTypeAdd:
		break;
	case CompaniesDialogTypeEdit:
	case CompaniesDialogTypeView:
		m_edbName.SetWindowTextW(m_recCompany.szCompanyName);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}

void CCompaniesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edbName);
}


BEGIN_MESSAGE_MAP(CCompaniesDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCompaniesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCompaniesDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CCompaniesDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
	{
		CErrorLogger::LogMessage(_T("Error initalising dialog."), TRUE, TRUE);
		return FALSE;
	}

	if (m_pCompany != NULL)
	{
		m_recCompany = *m_pCompany;
	}

	if (!SetDialogName())
		CErrorLogger::LogMessage(_T("Error when setting Cities dialog name"), TRUE, TRUE);

	if (!SetDialogFields())
		CErrorLogger::LogMessage(_T("Error when setting Cities dialog fields"), TRUE, TRUE);

	if (m_eCompaniesDialogType != CompaniesDialogTypeView)
		return TRUE;

	SetReadOnly();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CCompaniesDialog::OnBnClickedOk()
{

	//Проверка за въведени полета
	CInputValidator oInputValidator;

	if (m_eCompaniesDialogType != CompaniesDialogTypeView &&
		!(oInputValidator.ValidateTextField(m_edbName, COMPANIES_COMPANY_NAME_LENGTH, MIN_COMPANIES_FIELD_LENGTH)))
	{
		AfxMessageBox(EMPTY_FIELD_MESSAGE, MB_OK, MB_ICONEXCLAMATION);
		return;
	}


	m_edbName.GetWindowTextW(m_recCompany.szCompanyName, COMPANIES_COMPANY_NAME_LENGTH);

	__super::OnOK();
}


void CCompaniesDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	__super::OnCancel();
}

// Overrides
// ----------------
