
// CitiesView.cpp : implementation of the CCitiesView class
//
#include "pch.h"
#include "Structures.h"
#include "CitiesTable.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CitiesDoc.h"
#include "CitiesView.h"
#include "CitiesDialog.h"
#include "CitiesDialogType.h"
#include "DocumentDataOperation.h"
#include "CitiesSearchDialog.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesView

// Constants
// ----------------

/// <summary>
/// enum отговарящ на колона от Cities ListView
/// </summary>
enum CitiesViewColumn
{
	CitiesViewColumnName = 0,
	CitiesViewColumnDistrict
};

#define CITY_NAME_COLUMN_WIDTH 200
#define CITY_DISTRICT_COLUMN_WIDTH 200

#define ALL_ITEMS_NUMBER 1000000

#define CITY_NAME_COLUMN_NAME _T("Град")
#define CITY_DISTRICT_COLUMN_NAME _T("Област")

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


IMPLEMENT_DYNCREATE(CCitiesView, CPhonebookListView)

BEGIN_MESSAGE_MAP(CCitiesView, CPhonebookListView)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CCitiesView::OnNMCustomdraw)
	ON_COMMAND(ID_POPUP_EDIT, &CCitiesView::OnContextEdit)
	ON_COMMAND(ID_POPUP_ADD, &CCitiesView::OnContextAdd)
	ON_COMMAND(ID_POPUP_DELETE, &CCitiesView::OnContextDelete)
	ON_COMMAND(ID_POPUP_VIEW, &CCitiesView::OnContextView)
	ON_COMMAND(ID_POPUP_SEARCH, &CCitiesView::OnContextSearch)
END_MESSAGE_MAP()




// Constructor / Destructor
// ----------------

CCitiesView::CCitiesView() noexcept
{

}

CCitiesView::~CCitiesView()
{
}

// Methods
// ----------------

BOOL CCitiesView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

const CITIES* CCitiesView::GetSelectedCity() const
{
	const CListCtrl& oListCtrl = GetListCtrl();
	POSITION oPosition = oListCtrl.GetFirstSelectedItemPosition();
	if (oPosition == NULL)
		return NULL;

	const int nItem = oListCtrl.GetNextSelectedItem(oPosition);
	const long lID = oListCtrl.GetItemData(nItem);

	return GetDocument()->GetRowByID(lID);
}

BOOL CCitiesView::IsSelectedRow()
{
	return GetSelectedCity() != NULL;
}

void CCitiesView::ShowSearch(CListCtrl& oListCtrl)
{
	if (!m_bIsSearch)
		return;

	SetRedraw(FALSE);
	oListCtrl.DeleteAllItems();
	SetRedraw(TRUE);

	GetDocument()->SelectByName(m_oAutoArray, m_strSearch);
	for (INT_PTR i = 0; i < m_oAutoArray.GetCount(); i++)
	{
		CITIES* pCity = m_oAutoArray.GetAt(i);

		OperationInsert(oListCtrl, *pCity);
	}
}


void CCitiesView::SetListViewItem(CListCtrl& oListCtrl, const CITIES& recCity, int nItemIndex)
{
	if(!oListCtrl.SetItemText(nItemIndex, CitiesViewColumnName, recCity.szCityName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);

	if(!oListCtrl.SetItemText(nItemIndex, CitiesViewColumnDistrict, recCity.szDistrict))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);
}


void CCitiesView::SetColumns(CListCtrl& oListCtrl)
{
	oListCtrl.InsertColumn(CitiesViewColumnName, CITY_NAME_COLUMN_NAME, LVCFMT_LEFT, CITY_NAME_COLUMN_WIDTH);
	oListCtrl.InsertColumn(CitiesViewColumnDistrict, CITY_DISTRICT_COLUMN_NAME, LVCFMT_LEFT, CITY_DISTRICT_COLUMN_WIDTH);	
}


void CCitiesView::SetInitialData(CListCtrl& oListCtrl)
{
	const CPtrAutoArray<CITIES>* pCitiesArray = GetDocument()->GetData();

	for (INT_PTR i = 0; i < pCitiesArray->GetCount(); i++)
	{
		CITIES* pCity = pCitiesArray->GetAt(i);

		OperationInsert(oListCtrl, *pCity);
	}

}

void CCitiesView::OperationUpdate(CListCtrl& oListCtrl, const CITIES& recCity)
{
	const int nIndex = GetIndexByID(oListCtrl, recCity.lID);
	if (nIndex == INDEX_BY_ID_ERROR)
		return;

	SetListViewItem(oListCtrl, recCity, nIndex);
}


void CCitiesView::OperationInsert(CListCtrl& oListCtrl, const CITIES& recCity)
{
	const int nIndex = oListCtrl.InsertItem(LVIF_PARAM, 0, recCity.szCityName, 0, 0, 0, recCity.lID);
	SetListViewItem(oListCtrl, recCity, nIndex);
}

void CCitiesView::OperationDelete(CListCtrl& oListCtrl, const CITIES& recCity)
{
	const int nIndex = GetIndexByID(oListCtrl, recCity.lID);
	if (!oListCtrl.DeleteItem(nIndex))
		CErrorLogger::LogMessage(REMOVE_ITEM_ERROR_MESSAGE, TRUE, TRUE);
}

void CCitiesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListCtrl& oListCtrl = GetListCtrl();

	switch ((DocumentDataOperation)lHint)
	{
	case DocumentDataOperationUpdate:
		OperationUpdate(oListCtrl, *(CITIES*)pHint);
		break;
	case DocumentDataOperationInsert:
		OperationInsert(oListCtrl, *(CITIES*)pHint);
		break;
	case DocumentDataOperationDelete:
		OperationDelete(oListCtrl, *(CITIES*)pHint);
		break;
	default:
		CErrorLogger::LogMessage(OPERATION_NOT_RECOGNISED_ERROR_MESSAGE, TRUE, TRUE);
		break;
	}

	if (m_bIsSearch)
		ShowSearch(oListCtrl);
	oListCtrl.RedrawItems(0, ALL_ITEMS_NUMBER);
}

void CCitiesView::OnInitialUpdate()
{
	//CListView::OnInitialUpdate();

	CListCtrl& oListCtrl = GetListCtrl();
	Initialize(oListCtrl);
}

// CCitiesView diagnostics

#ifdef _DEBUG
void CCitiesView::AssertValid() const
{
	__super::AssertValid();
}

void CCitiesView::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}

CCitiesDoc* CCitiesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers


void CCitiesView::OnContextEdit()
{
	const CITIES* pSelectedCity = GetSelectedCity();
	if (pSelectedCity == NULL)
		return;

	CCitiesDialog oCitiesDialog(pSelectedCity, CitiesDialogTypeEdit);
	if (oCitiesDialog.DoModal() != IDOK)
		return;

	const BOOL bResult = GetDocument()->SetCityByID(oCitiesDialog.GetCity()->lID, *(oCitiesDialog.GetCity()));
	if (!bResult)
		CErrorLogger::LogMessage(UPDATE_ERROR_MESSAGE, TRUE, TRUE);
}


void CCitiesView::OnContextAdd()
{
	CCitiesDialog oCitiesDialog(NULL, CitiesDialogTypeAdd);
	if (oCitiesDialog.DoModal() != IDOK)
		return;

	const BOOL bResult = GetDocument()->AddCity(*(oCitiesDialog.GetCity()));
	if (!bResult)
		CErrorLogger::LogMessage(INSERT_ERROR_MESSAGE, TRUE, TRUE);

}


void CCitiesView::OnContextDelete()
{
	const CListCtrl& oListCtrl = GetListCtrl();
	POSITION oPosition = oListCtrl.GetFirstSelectedItemPosition();
	if (oPosition == NULL)
		return;

	const int nResult = AfxMessageBox(DELETE_CONFIRM_MESSAGE, MB_YESNO, MB_ICONINFORMATION);

	if (nResult != IDYES)
		return;

	const int nItem = oListCtrl.GetNextSelectedItem(oPosition);
	const long lID = oListCtrl.GetItemData(nItem);

	if (!GetDocument()->RemoveCity(lID))
		CErrorLogger::LogMessage(DELETE_ERROR_MESSAGE, FALSE, TRUE);
}


void CCitiesView::OnContextView()
{
	const CITIES* pSelectedCity = GetSelectedCity();
	if (pSelectedCity == NULL)
		return;

	CCitiesDialog oCitiesDialog(pSelectedCity, CitiesDialogTypeView);
	oCitiesDialog.DoModal();
}


void CCitiesView::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetRowColors(pNMHDR, pResult);
}

void CCitiesView::OnContextSearch()
{
	CListCtrl& oListCtrl = GetListCtrl();
	CCitiesSearchDialog oDialog;
	if (oDialog.DoModal() != IDOK)
	{
		SetRedraw(FALSE);
		oListCtrl.DeleteAllItems();
		SetRedraw(TRUE);

		m_bIsSearch = FALSE;
		SetInitialData(oListCtrl);
		return;
	}
	m_bIsSearch = TRUE;
	m_strSearch = oDialog.m_strName;
	ShowSearch(oListCtrl);
}
