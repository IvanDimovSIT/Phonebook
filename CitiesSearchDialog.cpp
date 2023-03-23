// CitiesSearchDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "CitiesSearchDialog.h"
#include "afxdialogex.h"


// CCitiesSearchDialog dialog

IMPLEMENT_DYNAMIC(CCitiesSearchDialog, CDialogEx)

CCitiesSearchDialog::CCitiesSearchDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CITIES_SEARCH_DIALOG, pParent)
{

}

CCitiesSearchDialog::~CCitiesSearchDialog()
{
}

void CCitiesSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edbName);
}


BEGIN_MESSAGE_MAP(CCitiesSearchDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCitiesSearchDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCitiesSearchDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCitiesSearchDialog message handlers


void CCitiesSearchDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_edbName.GetWindowTextW(m_strName);
	CDialogEx::OnOK();
}


void CCitiesSearchDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
