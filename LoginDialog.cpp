// LoginDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "LoginDialog.h"
#include "afxdialogex.h"
#include "InputValidator.h"

// CLoginDialog dialog

#define MIN_FIELD_LENGTH 1
#define MAX_FIELD_LENGTH 30


IMPLEMENT_DYNAMIC(CLoginDialog, CDialogEx)

CLoginDialog::CLoginDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

}

CLoginDialog::~CLoginDialog()
{
}

/// <summary> Проверява дали са зададени стойностите на контролите </summary>
BOOL CLoginDialog::ValidateUserInput() const
{
	CInputValidator oInputValidator;
	if (!oInputValidator.ValidateTextField(m_edbName, MAX_FIELD_LENGTH, MIN_FIELD_LENGTH))
	{
		AfxMessageBox(_T("Въведете име."));
		return FALSE;
	}

	if (!oInputValidator.ValidateTextField(m_edbPassword, MAX_FIELD_LENGTH, MIN_FIELD_LENGTH))
	{
		AfxMessageBox(_T("Въведете парола."));
		return FALSE;
	}

	return TRUE;
}

void CLoginDialog::GetData(CString& strName, CString& strPassword) const
{
	strName = m_strUsername;
	strPassword = m_strPassword;
}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_LOGIN_NAME, m_edbName);
	DDX_Control(pDX, IDC_EDB_LOGIN_PASSWORD, m_edbPassword);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLoginDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLoginDialog message handlers


void CLoginDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (!ValidateUserInput())
		return;

	TCHAR szTextBuffer[MAX_FIELD_LENGTH + 1];
	m_edbName.GetWindowTextW(szTextBuffer, MAX_FIELD_LENGTH);
	m_strUsername.Format(_T("%s"), szTextBuffer);

	m_edbPassword.GetWindowTextW(szTextBuffer, MAX_FIELD_LENGTH);
	m_strPassword.Format(_T("%s"), szTextBuffer);


	CDialogEx::OnOK();
}


void CLoginDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CLoginDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
