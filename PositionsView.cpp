#include "pch.h"
#include "Structures.h"
#include "PositionsTable.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PositionsDoc.h"
#include "PositionsView.h"
#include "PositionsDialog.h"
#include "PositionsDialogType.h"
#include "DocumentDataOperation.h"


/////////////////////////////////////////////////////////////////////////////
// CPositionsView

// Constants
// ----------------

/// <summary>
/// enum отговарящ на колона от Positions ListView
/// </summary>
enum PositionsViewColumn
{
	PositionsViewColumnName = 0,
};

#define POSITION_NAME_COLUMN_WIDTH 400

#define ALL_ITEMS_NUMBER 1000000

#define POSITION_NAME_COLUMN_NAME _T("Позиция")

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


IMPLEMENT_DYNCREATE(CPositionsView, CPhonebookListView)

BEGIN_MESSAGE_MAP(CPositionsView, CPhonebookListView)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CPositionsView::OnNMCustomdraw)
	ON_COMMAND(ID_POPUP_EDIT, &CPositionsView::OnContextEdit)
	ON_COMMAND(ID_POPUP_ADD, &CPositionsView::OnContextAdd)
	ON_COMMAND(ID_POPUP_DELETE, &CPositionsView::OnContextDelete)
	ON_COMMAND(ID_POPUP_VIEW, &CPositionsView::OnContextView)
END_MESSAGE_MAP()




// Constructor / Destructor
// ----------------

CPositionsView::CPositionsView() noexcept
{

}

CPositionsView::~CPositionsView()
{
}

// Methods
// ----------------

BOOL CPositionsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

const POSITIONS* CPositionsView::GetSelectedPosition() const
{
	const CListCtrl& oListCtrl = GetListCtrl();
	POSITION oPosition = oListCtrl.GetFirstSelectedItemPosition();
	if (oPosition == NULL)
		return NULL;

	const int nItem = oListCtrl.GetNextSelectedItem(oPosition);
	const long lID = oListCtrl.GetItemData(nItem);

	return GetDocument()->GetRowByID(lID);
}

BOOL CPositionsView::IsSelectedRow()
{
	return GetSelectedPosition() != NULL;
}

void CPositionsView::SetListViewItem(CListCtrl& oListCtrl, const POSITIONS& recPosition, int nItemIndex)
{
	if (!oListCtrl.SetItemText(nItemIndex, PositionsViewColumnName, recPosition.szPositionName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);
}


void CPositionsView::SetColumns(CListCtrl& oListCtrl)
{
	oListCtrl.InsertColumn(PositionsViewColumnName, POSITION_NAME_COLUMN_NAME, LVCFMT_LEFT, POSITION_NAME_COLUMN_WIDTH);
}


void CPositionsView::SetInitialData(CListCtrl& oListCtrl)
{
	const CPtrAutoArray<POSITIONS>* pPosiotionsArray = GetDocument()->GetData();

	for (INT_PTR i = 0; i < pPosiotionsArray->GetCount(); i++)
	{
		POSITIONS* pPosition = pPosiotionsArray->GetAt(i);

		OperationInsert(oListCtrl, *pPosition);
	}

}

void CPositionsView::OperationUpdate(CListCtrl& oListCtrl, const POSITIONS& recPosition)
{
	const int nIndex = GetIndexByID(oListCtrl, recPosition.lID);
	if (nIndex == INDEX_BY_ID_ERROR)
		return;

	SetListViewItem(oListCtrl, recPosition, nIndex);
}


void CPositionsView::OperationInsert(CListCtrl& oListCtrl, const POSITIONS& recPosition)
{
	const int nIndex = oListCtrl.InsertItem(LVIF_PARAM, 0, recPosition.szPositionName, 0, 0, 0, recPosition.lID);
	SetListViewItem(oListCtrl, recPosition, nIndex);
}

void CPositionsView::OperationDelete(CListCtrl& oListCtrl, const POSITIONS& recPosition)
{
	const int nIndex = GetIndexByID(oListCtrl, recPosition.lID);
	if (!oListCtrl.DeleteItem(nIndex))
		CErrorLogger::LogMessage(REMOVE_ITEM_ERROR_MESSAGE, TRUE, TRUE);
}

void CPositionsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListCtrl& oListCtrl = GetListCtrl();

	switch ((DocumentDataOperation)lHint)
	{
	case DocumentDataOperationUpdate:
		OperationUpdate(oListCtrl, *(POSITIONS*)pHint);
		break;
	case DocumentDataOperationInsert:
		OperationInsert(oListCtrl, *(POSITIONS*)pHint);
		break;
	case DocumentDataOperationDelete:
		OperationDelete(oListCtrl, *(POSITIONS*)pHint);
		break;
	default:
		CErrorLogger::LogMessage(OPERATION_NOT_RECOGNISED_ERROR_MESSAGE, TRUE, TRUE);
		break;
	}
	oListCtrl.RedrawItems(0, ALL_ITEMS_NUMBER);
}

void CPositionsView::OnInitialUpdate()
{
	//CListView::OnInitialUpdate();

	CListCtrl& oListCtrl = GetListCtrl();
	Initialize(oListCtrl);
}

// CCitiesView diagnostics

#ifdef _DEBUG
void CPositionsView::AssertValid() const
{
	__super::AssertValid();
}

void CPositionsView::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}

CPositionsDoc* CPositionsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPositionsDoc)));
	return (CPositionsDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers


void CPositionsView::OnContextEdit()
{
	const POSITIONS* pSelectedPosition = GetSelectedPosition();
	if (pSelectedPosition == NULL)
		return;

	CPositionsDialog oPositionsDialog(pSelectedPosition, PositionsDialogTypeEdit);
	if (oPositionsDialog.DoModal() != IDOK)
		return;

	const BOOL bResult = GetDocument()->SetPositionByID(oPositionsDialog.GetPosition()->lID, *(oPositionsDialog.GetPosition()));
	if (!bResult)
		CErrorLogger::LogMessage(UPDATE_ERROR_MESSAGE, TRUE, TRUE);
}


void CPositionsView::OnContextAdd()
{
	CPositionsDialog oPositionsDialog(NULL, PositionsDialogTypeAdd);
	if (oPositionsDialog.DoModal() != IDOK)
		return;

	const BOOL bResult = GetDocument()->AddPosition(*(oPositionsDialog.GetPosition()));
	if (!bResult)
		CErrorLogger::LogMessage(INSERT_ERROR_MESSAGE, TRUE, TRUE);

}


void CPositionsView::OnContextDelete()
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

	if (!GetDocument()->RemovePosition(lID))
		CErrorLogger::LogMessage(DELETE_ERROR_MESSAGE, FALSE, TRUE);
}


void CPositionsView::OnContextView()
{
	const POSITIONS* pSelectedPosition = GetSelectedPosition();
	if (pSelectedPosition == NULL)
		return;

	CPositionsDialog oPositionsDialog(pSelectedPosition, PositionsDialogTypeView);
	oPositionsDialog.DoModal();
}


void CPositionsView::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetRowColors(pNMHDR, pResult);
}


BOOL CPositionsView::CanSearch()
{
	return FALSE;
}

BOOL CPositionsView::CanConvert()
{
	return FALSE;
}