// CitiesDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "CitiesDialog.h"
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
#define MIN_CITIES_FIELD_LENGTH 1
#define MIN_DISTRICT_FIELD_LENGTH 1

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialogEx)

// Constructor / Destructor
// ----------------

CCitiesDialog::CCitiesDialog(const CITIES* pCity, const CitiesDialogType eCitiesDialogType, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CITIES_DIALOG, pParent),
	m_pCity(pCity),
	m_eCitiesDialogType(eCitiesDialogType)
{
}

CCitiesDialog::~CCitiesDialog()
{
}

// Methods
// ----------------

const CITIES* CCitiesDialog::GetCity() const
{
	return &m_recCity;
}

BOOL CCitiesDialog::SetDialogName()
{
	switch (m_eCitiesDialogType)
	{
	case CitiesDialogTypeAdd:
		SetWindowText(DIALOG_ADD_NAME);
		break;
	case CitiesDialogTypeEdit:
		SetWindowText(DIALOG_EDIT_NAME);
		break;
	case CitiesDialogTypeView:
		SetWindowText(DIALOG_VIEW_NAME);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}


void CCitiesDialog::SetReadOnly()
{
	m_edbCityName.SetReadOnly(TRUE);
	m_edbDistrict.SetReadOnly(TRUE);
}


BOOL CCitiesDialog::SetDialogFields()
{
	switch (m_eCitiesDialogType)
	{
	case CitiesDialogTypeAdd:
		break;
	case CitiesDialogTypeEdit:
	case CitiesDialogTypeView:
		m_edbCityName.SetWindowTextW(m_recCity.szCityName);
		m_edbDistrict.SetWindowTextW(m_recCity.szDistrict);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_DIALOG_NAME, m_edbCityName);
	DDX_Control(pDX, IDC_EDB_CITIES_DIALOG_DISTRICT, m_edbDistrict);
}


BEGIN_MESSAGE_MAP(CCitiesDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCitiesDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCitiesDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCitiesDialog message handlers


BOOL CCitiesDialog::OnInitDialog()
{
	if (!CDialogEx::OnInitDialog())
	{
		CErrorLogger::LogMessage(_T("Error initalising dialog."), TRUE, TRUE);
		return FALSE;
	}

	if (m_pCity != NULL)
	{
		m_recCity = *m_pCity;
	}

	if (!SetDialogName())
		CErrorLogger::LogMessage(_T("Error when setting Cities dialog name"), TRUE, TRUE);

	if(!SetDialogFields())
		CErrorLogger::LogMessage(_T("Error when setting Cities dialog fields"), TRUE, TRUE);

	if (m_eCitiesDialogType != CitiesDialogTypeView)
		return TRUE;

	SetReadOnly();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CCitiesDialog::OnBnClickedOk()
{
	
	//Проверка за въведени полета
	CInputValidator oInputValidator;

	if (m_eCitiesDialogType != CitiesDialogTypeView &&
		!(oInputValidator.ValidateTextField(m_edbCityName, CITIES_CITY_NAME_LENGTH, MIN_CITIES_FIELD_LENGTH) &&
		oInputValidator.ValidateTextField(m_edbDistrict, CITIES_DISTRICT_LENGTH, MIN_DISTRICT_FIELD_LENGTH)))
	{
		AfxMessageBox(EMPTY_FIELD_MESSAGE, MB_OK, MB_ICONEXCLAMATION);
		return;
	}


	m_edbCityName.GetWindowTextW(m_recCity.szCityName, CITIES_CITY_NAME_LENGTH);
	m_edbDistrict.GetWindowTextW(m_recCity.szDistrict, CITIES_DISTRICT_LENGTH);

	__super::OnOK();
}


void CCitiesDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	__super::OnCancel();
}

// Overrides
// ----------------
