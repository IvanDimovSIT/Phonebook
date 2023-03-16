
#include "pch.h"
#include "Phonebook.h"
#include "PositionsDialog.h"
#include "afxdialogex.h"
#include "ErrorLogger.h"
#include "InputValidator.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionsDialog

// Constants
// ----------------

#define DIALOG_ADD_NAME _T("Добавяне")
#define DIALOG_EDIT_NAME _T("Редактиране")
#define DIALOG_VIEW_NAME _T("Преглед")

#define EMPTY_FIELD_MESSAGE _T("Попълнете всички полетата за данни.")
#define MIN_POSITIONS_FIELD_LENGTH 1

IMPLEMENT_DYNAMIC(CPositionsDialog, CDialogEx)

// Constructor / Destructor
// ----------------

CPositionsDialog::CPositionsDialog(const POSITIONS* pPosition, const PositionsDialogType ePositionsDialogType, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMPANIES_DIALOG, pParent),
	m_pPosition(pPosition),
	m_ePositionsDialogType(ePositionsDialogType)
{
}

CPositionsDialog::~CPositionsDialog()
{
}

// Methods
// ----------------

const POSITIONS* CPositionsDialog::GetPosition() const
{
	return &m_recPosition;
}

BOOL CPositionsDialog::SetDialogName()
{
	switch (m_ePositionsDialogType)
	{
	case PositionsDialogTypeAdd:
		SetWindowText(DIALOG_ADD_NAME);
		break;
	case PositionsDialogTypeEdit:
		SetWindowText(DIALOG_EDIT_NAME);
		break;
	case PositionsDialogTypeView:
		SetWindowText(DIALOG_VIEW_NAME);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}


void CPositionsDialog::SetReadOnly()
{
	m_edbName.SetReadOnly(TRUE);
}


BOOL CPositionsDialog::SetDialogFields()
{
	switch (m_ePositionsDialogType)
	{
	case PositionsDialogTypeAdd:
		break;
	case PositionsDialogTypeEdit:
	case PositionsDialogTypeView:
		m_edbName.SetWindowTextW(m_recPosition.szPositionName);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}

void CPositionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edbName);
}


BEGIN_MESSAGE_MAP(CPositionsDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPositionsDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPositionsDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CPositionsDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
	{
		CErrorLogger::LogMessage(_T("Error initalising dialog."), TRUE, TRUE);
		return FALSE;
	}

	if (m_pPosition != NULL)
	{
		m_recPosition = *m_pPosition;
	}

	if (!SetDialogName())
		CErrorLogger::LogMessage(_T("Error when setting Cities dialog name"), TRUE, TRUE);

	if (!SetDialogFields())
		CErrorLogger::LogMessage(_T("Error when setting Cities dialog fields"), TRUE, TRUE);

	if (m_ePositionsDialogType != PositionsDialogTypeView)
		return TRUE;

	SetReadOnly();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CPositionsDialog::OnBnClickedOk()
{

	//Проверка за въведени полета
	CInputValidator oInputValidator;

	if (m_ePositionsDialogType != PositionsDialogTypeView &&
		!(oInputValidator.ValidateTextField(m_edbName, POSITIONS_POSITION_NAME_LENGTH, MIN_POSITIONS_FIELD_LENGTH)))
	{
		AfxMessageBox(EMPTY_FIELD_MESSAGE, MB_OK, MB_ICONEXCLAMATION);
		return;
	}


	m_edbName.GetWindowTextW(m_recPosition.szPositionName, POSITIONS_POSITION_NAME_LENGTH);

	__super::OnOK();
}


void CPositionsDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	__super::OnCancel();
}

// Overrides
// ----------------
