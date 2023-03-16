// PersonsDialog.cpp : implementation file
//

#include "pch.h"
#include "Phonebook.h"
#include "PersonsDialog.h"
#include "afxdialogex.h"
#include "ErrorLogger.h"
#include "PhoneNumbersEditDialog.h"
#include "InputValidator.h"



/// <summary>
/// enum отговарящ на колона от PHONE_NUMBERS ListView
/// </summary>
enum PhoneNumbersColumn
{
	PhoneNumbersColumnPhoneType = 0,
	PhoneNumbersColumnPhoneNumber
};


/////////////////////////////////////////////////////////////////////////////
// CPersonsDialog

	// Constants
	// ----------------
#define DIALOG_ADD_NAME _T("Добавяне")
#define DIALOG_EDIT_NAME _T("Редактиране")
#define DIALOG_VIEW_NAME _T("Преглед")

#define PHONE_NUMBERS_TYPE_COLUMN_WIDTH 90
#define PHONE_NUMBERS_NUMBER_COLUMN_WIDTH 120

#define PHONE_NUMBERS_TYPE_COLUMN_NAME _T("Тип")
#define PHONE_NUMBERS_NUMBER_COLUMN_NAME _T("Номер")


#define NAME_MIN_FIELD_LENGTH 2
#define ADDRESS_MIN_FIELD_LENGTH 4
#define UCN_MIN_FIELD_LENGTH 10

#define TEMPORARY_ID_INITIAL_VALUE -1
#define INDEX_NOT_FOUND -1

#define SETTING_ITEM_TEXT_ERROR_MESSAGE _T("Грешка при въвеждането на текста във ListCtrl.")
#define CONFIRM_DELETE_MESSAGE _T("Сигурни ли сте, че искате да изтриете селектирания запис?")
#define VALIDATE_FIRST_NAME_MESSAGE _T("Моля въведете име.")
#define VALIDATE_MIDDLE_NAME_MESSAGE _T("Моля въведете презиме")
#define VALIDATE_LAST_NAME_MESSAGE _T("Моля въведете фамилия")
#define VALIDATE_UCN_MESSAGE _T("Моля въведете правилно ЕГН (10 цифри).")
#define VALIDATE_ADDRESS_MESSAGE _T("Моля въведете адрес")
#define VALIDATE_CITY_MESSAGE _T("Моля въведете град")
#define VALIDATE_COMPANY_MESSAGE _T("Моля въведете компания")
#define VALIDATE_POSITION_MESSAGE _T("Моля въведете позиция")


IMPLEMENT_DYNAMIC(CPersonsDialog, CDialogEx)


// Constructor / Destructor
// ----------------

CPersonsDialog::CPersonsDialog(CPerson* pPerson, CPersonDisplay& oPersonDisplay, const PersonsDialogType ePersonsDialogType, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PERSONS_DIALOG, pParent),
	m_pPerson(pPerson),
	m_pPersonDisplay(&oPersonDisplay),
	m_ePersonsDialogType(ePersonsDialogType),
	m_lTemporaryID(TEMPORARY_ID_INITIAL_VALUE)
{
	if (pPerson == NULL)
		return;
	
	m_oNewPerson.m_oPhoneNumbers = pPerson->m_oPhoneNumbers;
}

CPersonsDialog::~CPersonsDialog()
{
}

// Methods
// ----------------
BOOL CPersonsDialog::ValidateUserInput() const
{
	CInputValidator oInputValidator;

	if (!oInputValidator.ValidateTextField(m_edbFirstName, PERSONS_NAME_LENGTH, NAME_MIN_FIELD_LENGTH))
	{
		AfxMessageBox(VALIDATE_FIRST_NAME_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if(!oInputValidator.ValidateTextField(m_edbMiddleName, PERSONS_NAME_LENGTH, NAME_MIN_FIELD_LENGTH))
	{
		AfxMessageBox(VALIDATE_MIDDLE_NAME_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if(!oInputValidator.ValidateTextField(m_edbLastName, PERSONS_NAME_LENGTH, NAME_MIN_FIELD_LENGTH))
	{
		AfxMessageBox(VALIDATE_LAST_NAME_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if(!oInputValidator.ValidateTextField(m_edbAddress, PERSONS_ADDRESS_LENGTH, ADDRESS_MIN_FIELD_LENGTH))
	{
		AfxMessageBox(VALIDATE_ADDRESS_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if(!oInputValidator.ValidateNumber(m_edbUCN, UCN_MIN_FIELD_LENGTH, UCN_MIN_FIELD_LENGTH))
	{
		AfxMessageBox(VALIDATE_UCN_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if(!oInputValidator.ValidateComboBox(m_cmbCity))
	{
		AfxMessageBox(VALIDATE_CITY_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if (!oInputValidator.ValidateComboBox(m_cmbCompany))
	{
		AfxMessageBox(VALIDATE_COMPANY_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}

	if (!oInputValidator.ValidateComboBox(m_cmbPosition))
	{
		AfxMessageBox(VALIDATE_POSITION_MESSAGE, MB_OK, MB_ICONERROR);
		return FALSE;
	}


	return TRUE;
}


CPerson* CPersonsDialog::GetPerson()
{
	return &m_oNewPerson;
}


BOOL CPersonsDialog::SetDialogName()
{
	switch (m_ePersonsDialogType)
	{
	case PersonsDialogTypeAdd:
		SetWindowText(DIALOG_ADD_NAME);
		break;
	case PersonsDialogTypeEdit:
		SetWindowText(DIALOG_EDIT_NAME);
		break;
	case PersonsDialogTypeView:
		SetWindowText(DIALOG_VIEW_NAME);
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

CString CPersonsDialog::CityToString(const CITIES& recCity) const
{
	CString strCity = recCity.szCityName;
	strCity += _T(" - ");
	strCity += recCity.szDistrict;
	return strCity;
}


void CPersonsDialog::SetCitiesComboBox()
{
	CPtrAutoArray<CITIES>* oCitiesArray = m_pPersonDisplay->GetCities();

	for (INT_PTR i = 0; i < oCitiesArray->GetCount(); i++)
	{
		CITIES* pCurrentCity = oCitiesArray->GetAt(i);

		int nIndex = m_cmbCity.AddString(CityToString(*pCurrentCity).GetString());
		m_cmbCity.SetItemData(nIndex, (DWORD_PTR)pCurrentCity->lID);

		if (m_pPerson != NULL && pCurrentCity->lID == m_pPerson->m_recPerson.lCityID)
			m_cmbCity.SetCurSel(nIndex);
	}
	
}

void CPersonsDialog::SetCompaniesComboBox()
{
	CPtrAutoArray<COMPANIES>* oCompaniesArray = m_pPersonDisplay->GetCompanies();

	for (INT_PTR i = 0; i < oCompaniesArray->GetCount(); i++)
	{
		COMPANIES* pCurrent = oCompaniesArray->GetAt(i);

		int nIndex = m_cmbCompany.AddString(pCurrent->szCompanyName);
		m_cmbCompany.SetItemData(nIndex, (DWORD_PTR)pCurrent->lID);

		if (m_pPerson != NULL && pCurrent->lID == m_pPerson->m_recPerson.lCompanyID)
			m_cmbCompany.SetCurSel(nIndex);
	}

}

void CPersonsDialog::SetPositionsComboBox()
{
	CPtrAutoArray<POSITIONS>* oPositionsArray = m_pPersonDisplay->GetPositions();

	for (INT_PTR i = 0; i < oPositionsArray->GetCount(); i++)
	{
		POSITIONS* pCurrent = oPositionsArray->GetAt(i);

		int nIndex = m_cmbPosition.AddString(pCurrent->szPositionName);
		m_cmbPosition.SetItemData(nIndex, (DWORD_PTR)pCurrent->lID);

		if (m_pPerson != NULL && pCurrent->lID == m_pPerson->m_recPerson.lPositionID)
			m_cmbPosition.SetCurSel(nIndex);
	}


}


BOOL CPersonsDialog::SetDialogFields()
{
	switch (m_ePersonsDialogType)
	{
	case PersonsDialogTypeAdd:
		break;
	case PersonsDialogTypeEdit:
	case PersonsDialogTypeView:
		m_edbFirstName.SetWindowTextW(m_pPerson->m_recPerson.szFirstName);
		m_edbMiddleName.SetWindowTextW(m_pPerson->m_recPerson.szMiddleName);
		m_edbLastName.SetWindowTextW(m_pPerson->m_recPerson.szLastName);
		m_edbUCN.SetWindowTextW(m_pPerson->m_recPerson.szUCN);
		m_edbAddress.SetWindowTextW(m_pPerson->m_recPerson.szAddress);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}

INT_PTR CPersonsDialog::FindArrayIndexByID(const long lID)
{
	for (INT_PTR i = 0; i < m_oNewPerson.m_oPhoneNumbers.GetCount(); i++)
	{
		if (m_oNewPerson.m_oPhoneNumbers.GetAt(i)->lID != lID)
			continue;
		return i;
	}

	return INDEX_NOT_FOUND;
}

int CPersonsDialog::FindListIndexByID(const long lID)
{
	LVFINDINFOW oFindInfo;
	oFindInfo.flags = LVFI_PARAM;
	oFindInfo.lParam = lID;

	return m_lscPhoneNumbers.FindItem(&oFindInfo);
}


BOOL CPersonsDialog::SetItemText(const PHONE_NUMBERS& recPhoneNumber, const int nIndexList)
{
	PHONE_TYPES recPhoneType;
	if (!m_pPersonDisplay->GetPhoneTypeByID(recPhoneNumber.lPhoneTypeID, recPhoneType))
		return FALSE;

	if (!m_lscPhoneNumbers.SetItemText(nIndexList, PhoneNumbersColumnPhoneType, recPhoneType.szType))
		return FALSE;

	if (!m_lscPhoneNumbers.SetItemText(nIndexList, PhoneNumbersColumnPhoneNumber, recPhoneNumber.szPhoneNumber))
		return FALSE;

	return TRUE;
}


BOOL CPersonsDialog::AddItem(const PHONE_NUMBERS& recPhoneNumber)
{
	PHONE_TYPES recPhoneType;
	if (!m_pPersonDisplay->GetPhoneTypeByID(recPhoneNumber.lPhoneTypeID, recPhoneType))
		return FALSE;

	const int nIndex = m_lscPhoneNumbers.InsertItem(LVIF_PARAM, 0, recPhoneType.szType, 0, 0, 0, recPhoneNumber.lID);


	return SetItemText(recPhoneNumber, nIndex);
}


void CPersonsDialog::SetColumns()
{
	m_lscPhoneNumbers.InsertColumn(PhoneNumbersColumnPhoneType, PHONE_NUMBERS_TYPE_COLUMN_NAME, LVCFMT_LEFT, PHONE_NUMBERS_TYPE_COLUMN_WIDTH);
	m_lscPhoneNumbers.InsertColumn(PhoneNumbersColumnPhoneNumber, PHONE_NUMBERS_NUMBER_COLUMN_NAME, LVCFMT_LEFT, PHONE_NUMBERS_NUMBER_COLUMN_WIDTH);
	m_lscPhoneNumbers.SetExtendedStyle(m_lscPhoneNumbers.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}


void CPersonsDialog::SetInitalData()
{
	for (INT_PTR i = 0; i < m_oNewPerson.m_oPhoneNumbers.GetCount(); i++)
	{
		if (!AddItem(*m_oNewPerson.m_oPhoneNumbers.GetAt(i)))
			CErrorLogger::LogMessage(_T("Error adding item to PHONE_NUMBERS ListCtrl"), TRUE, TRUE);
	}
}


BOOL CPersonsDialog::UpdateItem(const PHONE_NUMBERS& recPhoneNumber, const int nIndexArray)
{
	if (nIndexArray < 0 || nIndexArray >= m_oNewPerson.m_oPhoneNumbers.GetCount())
		return FALSE;

	*m_oNewPerson.m_oPhoneNumbers.GetAt(nIndexArray) = recPhoneNumber;
	int nIndexList = FindListIndexByID(m_oNewPerson.m_oPhoneNumbers.GetAt(nIndexArray)->lID);

	return SetItemText(recPhoneNumber, nIndexList);
}


const PHONE_NUMBERS* CPersonsDialog::GetSelectedPhoneNumber()
{
	POSITION oPosition = m_lscPhoneNumbers.GetFirstSelectedItemPosition();
	if (oPosition == NULL)
		return NULL;

	const int nItem = m_lscPhoneNumbers.GetNextSelectedItem(oPosition);
	const long lID = m_lscPhoneNumbers.GetItemData(nItem);

	for (INT_PTR i = 0; i < m_oNewPerson.m_oPhoneNumbers.GetCount(); i++)
	{
		if (m_oNewPerson.m_oPhoneNumbers.GetAt(i)->lID == lID)
			return m_oNewPerson.m_oPhoneNumbers.GetAt(i);
	}

	return NULL;

}

void CPersonsDialog::SetReadOnly()
{
	m_edbFirstName.SetReadOnly(TRUE);
	m_edbMiddleName.SetReadOnly(TRUE);
	m_edbLastName.SetReadOnly(TRUE);
	m_edbUCN.SetReadOnly(TRUE);
	m_edbAddress.SetReadOnly(TRUE);
}


void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRST_NAME, m_edbFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_MIDDLE_NAME, m_edbMiddleName);
	DDX_Control(pDX, IDC_EDB_PERSONS_LAST_NAME, m_edbLastName);
	DDX_Control(pDX, IDC_EDB_PERSONS_UCN, m_edbUCN);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITY, m_cmbCity);
	DDX_Control(pDX, IDC_EDB_PERSONS_ADDRESS, m_edbAddress);
	DDX_Control(pDX, IDC_LSC_PERSONS_PHONE_NUMBERS, m_lscPhoneNumbers);
	DDX_Control(pDX, IDC_COMBO1, m_cmbCompany);
	DDX_Control(pDX, IDC_COMBO2, m_cmbPosition);
}


BEGIN_MESSAGE_MAP(CPersonsDialog, CDialogEx)
	//ON_BN_CLICKED(IDC_BTN_PERSONS_PHONE_NUMBERS, &CPersonsDialog::OnBnClickedBtnPersonsPhoneNumbers)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_POPUP_ADD, &CPersonsDialog::OnPopupAdd)
	ON_COMMAND(ID_POPUP_DELETE, &CPersonsDialog::OnPopupDelete)
	ON_COMMAND(ID_POPUP_EDIT, &CPersonsDialog::OnPopupEdit)
	ON_COMMAND(ID_POPUP_VIEW, &CPersonsDialog::OnPopupView)

END_MESSAGE_MAP()


// CPersonsDialog message handlers


BOOL CPersonsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDialogName();
	SetCitiesComboBox();
	SetCompaniesComboBox();
	SetPositionsComboBox();
	SetColumns();
	if (m_pPerson == NULL)
		return TRUE;

	SetDialogFields();
	SetInitalData();

	if (m_ePersonsDialogType != PersonsDialogTypeView)
		return TRUE;

	SetReadOnly();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CPersonsDialog::OnOK()
{
	if (m_ePersonsDialogType == PersonsDialogTypeView)
	{
		CDialogEx::OnOK();
		return;
	}

	if (!ValidateUserInput())
		return;

	if (m_ePersonsDialogType == PersonsDialogTypeEdit && m_pPerson != NULL)
		m_oNewPerson.m_recPerson = m_pPerson->m_recPerson;

	m_edbFirstName.GetWindowTextW(m_oNewPerson.m_recPerson.szFirstName, PERSONS_NAME_LENGTH);
	m_edbMiddleName.GetWindowTextW(m_oNewPerson.m_recPerson.szMiddleName, PERSONS_NAME_LENGTH);
	m_edbLastName.GetWindowTextW(m_oNewPerson.m_recPerson.szLastName, PERSONS_NAME_LENGTH);
	m_edbUCN.GetWindowTextW(m_oNewPerson.m_recPerson.szUCN, PERSONS_UCN_LENGTH);
	m_edbAddress.GetWindowTextW(m_oNewPerson.m_recPerson.szAddress, PERSONS_ADDRESS_LENGTH);
	m_oNewPerson.m_recPerson.lCityID = m_cmbCity.GetItemData(m_cmbCity.GetCurSel());
	m_oNewPerson.m_recPerson.lCompanyID = m_cmbCompany.GetItemData(m_cmbCompany.GetCurSel());
	m_oNewPerson.m_recPerson.lPositionID = m_cmbPosition.GetItemData(m_cmbPosition.GetCurSel());


	CDialogEx::OnOK();
}


void CPersonsDialog::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}


void CPersonsDialog::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: Add your message handler code here
#ifndef SHARED_HANDLERS
	CMenu oContextMenu;
	oContextMenu.LoadMenu(IDR_POPUP);
	CMenu* oPopupMenu = oContextMenu.GetSubMenu(0);

	if (m_ePersonsDialogType == PersonsDialogTypeView)
	{
		oPopupMenu->EnableMenuItem(ID_POPUP_ADD, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		oPopupMenu->EnableMenuItem(ID_POPUP_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		oPopupMenu->EnableMenuItem(ID_POPUP_EDIT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		oPopupMenu->EnableMenuItem(ID_POPUP_VIEW, MF_BYCOMMAND | MF_ENABLED);
	}

	if (GetSelectedPhoneNumber() == NULL)
	{
		oPopupMenu->EnableMenuItem(ID_POPUP_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		oPopupMenu->EnableMenuItem(ID_POPUP_EDIT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		oPopupMenu->EnableMenuItem(ID_POPUP_VIEW, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	oPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP, point.x, point.y, this, TRUE);
#endif
}


void CPersonsDialog::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ClientToScreen(&point);
	OnContextMenu(this, point);

	CDialogEx::OnRButtonUp(nFlags, point);
}


void CPersonsDialog::OnPopupAdd()
{
	CPhoneNumbersEditDialog oPhoneNumbersEditDialog(NULL, PhoneNumbersEditDialogTypeAdd, *m_pPersonDisplay);
	if (oPhoneNumbersEditDialog.DoModal() != IDOK)
		return;

	PHONE_NUMBERS* pPhoneNumber = new PHONE_NUMBERS;
	oPhoneNumbersEditDialog.GetPhoneNumber(*pPhoneNumber);
	pPhoneNumber->lID = m_lTemporaryID--;

	m_oNewPerson.m_oPhoneNumbers.Add(pPhoneNumber);
	if (!AddItem(*pPhoneNumber))
		CErrorLogger::LogMessage(_T("Error adding item to ListCtrl."), TRUE, TRUE);
}


void CPersonsDialog::OnPopupDelete()
{

	const PHONE_NUMBERS* pSelectedPhoneNumber = GetSelectedPhoneNumber();
	if (pSelectedPhoneNumber == NULL)
		return;

	if (AfxMessageBox(CONFIRM_DELETE_MESSAGE, MB_OKCANCEL, MB_ICONINFORMATION) != IDOK)
		return;

	INT_PTR nIndex = FindArrayIndexByID(pSelectedPhoneNumber->lID);
	if (nIndex == INDEX_NOT_FOUND)
	{
		CErrorLogger::LogMessage(_T("Error index not found."), TRUE, TRUE);
		return;
	}

	if (!m_lscPhoneNumbers.DeleteItem(FindListIndexByID(pSelectedPhoneNumber->lID)))
	{
		CErrorLogger::LogMessage(_T("Error removing item from ListCtrl."), TRUE, TRUE);
		return;
	}

	m_oNewPerson.m_oPhoneNumbers.RemoveAt(nIndex);
}


void CPersonsDialog::OnPopupEdit()
{
	// TODO: Add your command handler code here
	const PHONE_NUMBERS* pSelectedPhoneNumber = GetSelectedPhoneNumber();
	if (pSelectedPhoneNumber == NULL)
		return;

	CPhoneNumbersEditDialog oPhoneNumbersEditDialog(pSelectedPhoneNumber, PhoneNumbersEditDialogTypeEdit, *m_pPersonDisplay);
	if (oPhoneNumbersEditDialog.DoModal() != IDOK)
		return;

	const INT_PTR nIndex = FindArrayIndexByID(pSelectedPhoneNumber->lID);
	if (nIndex == INDEX_NOT_FOUND)
	{
		CErrorLogger::LogMessage(_T("Error phone number not found."), TRUE, TRUE);
		return;
	}

	oPhoneNumbersEditDialog.GetPhoneNumber(*m_oNewPerson.m_oPhoneNumbers.GetAt(nIndex));

	SetItemText(*m_oNewPerson.m_oPhoneNumbers.GetAt(nIndex), FindListIndexByID(pSelectedPhoneNumber->lID));
}


void CPersonsDialog::OnPopupView()
{
	// TODO: Add your command handler code here
	const PHONE_NUMBERS* pSelectedPhoneNumber = GetSelectedPhoneNumber();
	if (pSelectedPhoneNumber == NULL)
		return;

	CPhoneNumbersEditDialog oPhoneNumbersEditDialog(pSelectedPhoneNumber, PhoneNumbersEditDialogTypeView, *m_pPersonDisplay);
	oPhoneNumbersEditDialog.DoModal();
}
