#include "Structures.h"
#include "PersonsTable.h"
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PersonsDoc.h"
#include "PersonsView.h"
#include "PersonsDialog.h"
#include "DocumentDataOperation.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsView

// Constants
// ----------------
#define ALL_ITEMS_NUMBER 1000000

/// <summary>
/// enum отговарящ на колона от Cities ListView
/// </summary>
enum PersonsViewColumn
{
	PersonsViewColumnFirstName = 0,
	PersonsViewColumnMiddleName,
	PersonsViewColumnLastName,
	PersonsViewColumnUCN,
	PersonsViewColumnCityName,
	PersonsViewColumnDistrict,
	PersonsViewColumnAddress,
	PersonsViewColumnCompany,
	PersonsViewColumnPosition
};

#define PERSON_FIRST_NAME_COLUMN_WIDTH 150
#define PERSON_MIDDLE_NAME_COLUMN_WIDTH 150
#define PERSON_LAST_NAME_COLUMN_WIDTH 150
#define PERSON_UCN_COLUMN_WIDTH 80
#define PERSON_CITY_NAME_COLUMN_WIDTH 150
#define PERSON_DISTRICT_COLUMN_WIDTH 150
#define PERSON_ADDRESS_COLUMN_WIDTH 220
#define PERSON_COMPANY_COLUMN_WIDTH 150
#define PERSON_POSITION_COLUMN_WIDTH 150


#define PERSON_FIRST_NAME_COLUMN_NAME _T("Име")
#define PERSON_MIDDLE_NAME_COLUMN_NAME _T("Презиме")
#define PERSON_LAST_NAME_COLUMN_NAME _T("Фамилия")
#define PERSON_UCN_COLUMN_NAME _T("ЕГН")
#define PERSON_CITY_NAME_COLUMN_NAME  _T("Град")
#define PERSON_DISTRICT_COLUMN_NAME _T("Област")
#define PERSON_ADDRESS_COLUMN_NAME _T("Адрес")
#define PERSON_COMPANY_COLUMN_NAME _T("Компания")
#define PERSON_POSITION_COLUMN_NAME _T("Позиция")


#define UPDATE_ERROR_MESSAGE _T("Грешка при редактиране на данните. Моля рестартирайте приложението.")
#define INSERT_ERROR_MESSAGE _T("Грешка при въвеждане на данните. Моля рестартирайте приложението.")
#define DELETE_ERROR_MESSAGE _T("Грешка при изтриване на данните. Моля рестартирайте приложението.")
#define DELETE_CONFIRM_MESSAGE _T("Потвърдете изтриването на данните.")

#define SETTING_ITEM_TEXT_ERROR_MESSAGE _T("Грешка при въвеждането на текста във View.")
#define REMOVE_ITEM_ERROR_MESSAGE _T("Грешка при премахване на ред от View.")
#define OPERATION_NOT_RECOGNISED_ERROR_MESSAGE _T("Не е разпозната операцията.")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CPersonsView, CPhonebookListView)

BEGIN_MESSAGE_MAP(CPersonsView, CPhonebookListView)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CPersonsView::OnNMCustomdraw)
	ON_COMMAND(ID_POPUP_EDIT, &CPersonsView::OnContextEdit)
	ON_COMMAND(ID_POPUP_ADD, &CPersonsView::OnContextAdd)
	ON_COMMAND(ID_POPUP_DELETE, &CPersonsView::OnContextDelete)
	ON_COMMAND(ID_POPUP_VIEW, &CPersonsView::OnContextView)
END_MESSAGE_MAP()




// Constructor / Destructor
// ----------------

CPersonsView::CPersonsView() noexcept
{
}

CPersonsView::~CPersonsView()
{
}

// Methods
// ----------------

BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

CPerson* CPersonsView::GetSelectedPerson() const
{
	const CListCtrl& oListCtrl = GetListCtrl();
	POSITION oPosition = oListCtrl.GetFirstSelectedItemPosition();
	if (oPosition == NULL)
		return NULL;

	const int nItem = oListCtrl.GetNextSelectedItem(oPosition);
	const long lID = oListCtrl.GetItemData(nItem);

	return GetDocument()->GetRowByID(lID);
}

BOOL CPersonsView::IsSelectedRow()
{
	return GetSelectedPerson() != NULL;
}

void CPersonsView::SetListViewItem(CListCtrl& oListCtrl, const CPerson& oPerson, const CPersonDisplay& oPersonDisplay, int nItemIndex)
{
	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnFirstName, oPerson.m_recPerson.szFirstName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnMiddleName, oPerson.m_recPerson.szMiddleName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnLastName, oPerson.m_recPerson.szLastName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnUCN, oPerson.m_recPerson.szUCN))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	CITIES recCity;
	if (!oPersonDisplay.GetCityByID(oPerson.m_recPerson.lCityID, recCity))
	{
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);
		return;
	}

	COMPANIES recCompany;
	if (!oPersonDisplay.GetCompanyByID(oPerson.m_recPerson.lCompanyID, recCompany))
	{
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);
		return;
	}

	POSITIONS recPosition;
	if (!oPersonDisplay.GetPositionByID(oPerson.m_recPerson.lPositionID, recPosition))
	{
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);
		return;
	}

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnCityName, recCity.szCityName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnDistrict, recCity.szDistrict))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnAddress, oPerson.m_recPerson.szAddress))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnCompany, recCompany.szCompanyName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if (!oListCtrl.SetItemText(nItemIndex, PersonsViewColumnPosition, recPosition.szPositionName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

}


void CPersonsView::SetColumns(CListCtrl& oListCtrl)
{
	oListCtrl.InsertColumn(PersonsViewColumnFirstName, PERSON_FIRST_NAME_COLUMN_NAME, LVCFMT_LEFT, PERSON_FIRST_NAME_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnMiddleName, PERSON_MIDDLE_NAME_COLUMN_NAME, LVCFMT_LEFT, PERSON_MIDDLE_NAME_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnLastName, PERSON_LAST_NAME_COLUMN_NAME, LVCFMT_LEFT, PERSON_LAST_NAME_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnUCN, PERSON_UCN_COLUMN_NAME, LVCFMT_LEFT, PERSON_UCN_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnCityName, PERSON_CITY_NAME_COLUMN_NAME, LVCFMT_LEFT, PERSON_CITY_NAME_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnDistrict, PERSON_DISTRICT_COLUMN_NAME, LVCFMT_LEFT, PERSON_DISTRICT_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnAddress, PERSON_ADDRESS_COLUMN_NAME, LVCFMT_LEFT, PERSON_ADDRESS_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnCompany, PERSON_COMPANY_COLUMN_NAME, LVCFMT_LEFT, PERSON_COMPANY_COLUMN_WIDTH);
	oListCtrl.InsertColumn(PersonsViewColumnPosition, PERSON_POSITION_COLUMN_NAME, LVCFMT_LEFT, PERSON_POSITION_COLUMN_WIDTH);

}


void CPersonsView::SetInitialData(CListCtrl& oListCtrl)
{
	const CPtrAutoArray<CPerson>* pPersonsArray = GetDocument()->GetData();
	if (pPersonsArray == NULL)
	{
		CErrorLogger::LogMessage(_T("Error setting inital data"), TRUE, TRUE);
		return;
	}

	for (INT_PTR i = 0; i < pPersonsArray->GetCount(); i++)
	{
		CPerson* pPerson = pPersonsArray->GetAt(i);

		OperationInsert(oListCtrl, *pPerson);
	}

}

void CPersonsView::OperationUpdate(CListCtrl& oListCtrl, const CPerson& oPerson)
{
	const int nIndex = GetIndexByID(oListCtrl ,oPerson.m_recPerson.lID);

	if (nIndex == INDEX_BY_ID_ERROR)
		return;

	CPersonDisplay* pPersonDisplay = GetDocument()->GetDisplayInformation();
	if (pPersonDisplay == NULL)
	{
		CErrorLogger::LogMessage(UPDATE_ERROR_MESSAGE, TRUE, TRUE);
		return;
	}

	SetListViewItem(oListCtrl, oPerson, *pPersonDisplay, nIndex);
}


void CPersonsView::OperationInsert(CListCtrl& oListCtrl, const CPerson& oPerson)
{
	const int nIndex = oListCtrl.InsertItem(LVIF_PARAM, 0, oPerson.m_recPerson.szFirstName, 0, 0, 0, oPerson.m_recPerson.lID);

	CPersonDisplay* pPersonDisplay = GetDocument()->GetDisplayInformation();
	if (pPersonDisplay == NULL)
	{
		CErrorLogger::LogMessage(INSERT_ERROR_MESSAGE, TRUE, TRUE);
		return;
	}

	SetListViewItem(oListCtrl, oPerson, *pPersonDisplay, nIndex);
}

void CPersonsView::OperationDelete(CListCtrl& oListCtrl, const CPerson& oPerson)
{
	const int nIndex = GetIndexByID(oListCtrl ,oPerson.m_recPerson.lID);
	if (!oListCtrl.DeleteItem(nIndex))
		CErrorLogger::LogMessage(REMOVE_ITEM_ERROR_MESSAGE, TRUE, TRUE);
}

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListCtrl& oListCtrl = GetListCtrl();

	switch ((DocumentDataOperation)lHint)
	{
	case DocumentDataOperationUpdate:
		OperationUpdate(oListCtrl, *(CPerson*)pHint);
		break;
	case DocumentDataOperationInsert:
		OperationInsert(oListCtrl, *(CPerson*)pHint);
		break;
	case DocumentDataOperationDelete:
		OperationDelete(oListCtrl, *(CPerson*)pHint);
		break;
	default:
		CErrorLogger::LogMessage(OPERATION_NOT_RECOGNISED_ERROR_MESSAGE, TRUE, TRUE);
		break;
	}
	oListCtrl.RedrawItems(0, ALL_ITEMS_NUMBER);
}

void CPersonsView::OnInitialUpdate()
{
	//CListView::OnInitialUpdate();

	CListCtrl& oListCtrl = GetListCtrl();
	Initialize(oListCtrl);
}


// CCitiesView diagnostics

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	__super::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}

CPersonsDoc* CPersonsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDoc)));
	return (CPersonsDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers


void CPersonsView::OnContextEdit()
{
	CPerson* pSelectedPerson = GetSelectedPerson();
	if (pSelectedPerson == NULL)
		return;

	CPersonsDialog oPersonsDialog(pSelectedPerson, *GetDocument()->GetDisplayInformation() , PersonsDialogTypeEdit);
	if (oPersonsDialog.DoModal() != IDOK)
		return;

	CPerson* pPerson = oPersonsDialog.GetPerson();

	const BOOL bResult = GetDocument()->SetPersonByID(pPerson->m_recPerson.lID, *(pPerson));
	if (!bResult)
		CErrorLogger::LogMessage(UPDATE_ERROR_MESSAGE, TRUE, TRUE);
}


void CPersonsView::OnContextAdd()
{
	CPersonsDialog oPersonsDialog(NULL, *GetDocument()->GetDisplayInformation(), PersonsDialogTypeAdd);
	if (oPersonsDialog.DoModal() != IDOK)
		return;

	if (!GetDocument()->AddPerson(*oPersonsDialog.GetPerson()))
		CErrorLogger::LogMessage(INSERT_ERROR_MESSAGE, TRUE, TRUE);

}


void CPersonsView::OnContextDelete()
{
	const CPerson* pSelectedPerson = GetSelectedPerson();
	if (pSelectedPerson == NULL)
		return;

	const int nResult = AfxMessageBox(DELETE_CONFIRM_MESSAGE, MB_YESNO, MB_ICONINFORMATION);

	if (nResult != IDYES)
		return;

	if (!GetDocument()->RemovePerson(pSelectedPerson->m_recPerson.lID))
		CErrorLogger::LogMessage(DELETE_ERROR_MESSAGE, FALSE, TRUE);

}


void CPersonsView::OnContextView()
{
	CPerson* pSelectedPerson = GetSelectedPerson();
	if (pSelectedPerson == NULL)
		return;

	CPersonDisplay* oPersonDisplay = GetDocument()->GetDisplayInformation();
	
	CPersonsDialog oPersonsDialog(pSelectedPerson, *oPersonDisplay, PersonsDialogTypeView);
	oPersonsDialog.DoModal();
}


void CPersonsView::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetRowColors(pNMHDR, pResult);
}
