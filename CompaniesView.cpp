#include "pch.h"
#include "Structures.h"
#include "CompaniesTable.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CompaniesDoc.h"
#include "CompaniesView.h"
#include "CompaniesDialog.h"
#include "CompaniesDialogType.h"
#include "DocumentDataOperation.h"


/////////////////////////////////////////////////////////////////////////////
// CCompaniesView

// Constants
// ----------------

/// <summary>
/// enum отговарящ на колона от Companies ListView
/// </summary>
enum CompaniesViewColumn
{
	CompaniesViewColumnName = 0,
};

#define COMPANY_NAME_COLUMN_WIDTH 400

#define ALL_ITEMS_NUMBER 1000000

#define COMPANY_NAME_COLUMN_NAME _T("Комапния")

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


IMPLEMENT_DYNCREATE(CCompaniesView, CPhonebookListView)

BEGIN_MESSAGE_MAP(CCompaniesView, CPhonebookListView)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CCompaniesView::OnNMCustomdraw)
	ON_COMMAND(ID_POPUP_EDIT, &CCompaniesView::OnContextEdit)
	ON_COMMAND(ID_POPUP_ADD, &CCompaniesView::OnContextAdd)
	ON_COMMAND(ID_POPUP_DELETE, &CCompaniesView::OnContextDelete)
	ON_COMMAND(ID_POPUP_VIEW, &CCompaniesView::OnContextView)
END_MESSAGE_MAP()




// Constructor / Destructor
// ----------------

CCompaniesView::CCompaniesView() noexcept
{

}

CCompaniesView::~CCompaniesView()
{
}

// Methods
// ----------------

BOOL CCompaniesView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

const COMPANIES* CCompaniesView::GetSelectedCompany() const
{
	const CListCtrl& oListCtrl = GetListCtrl();
	POSITION oPosition = oListCtrl.GetFirstSelectedItemPosition();
	if (oPosition == NULL)
		return NULL;

	const int nItem = oListCtrl.GetNextSelectedItem(oPosition);
	const long lID = oListCtrl.GetItemData(nItem);

	return GetDocument()->GetRowByID(lID);
}

BOOL CCompaniesView::IsSelectedRow()
{
	return GetSelectedCompany() != NULL;
}

void CCompaniesView::SetListViewItem(CListCtrl& oListCtrl, const COMPANIES& recCompany, int nItemIndex)
{
	if (!oListCtrl.SetItemText(nItemIndex, CompaniesViewColumnName, recCompany.szCompanyName))
		CErrorLogger::LogMessage(SETTING_ITEM_TEXT_ERROR_MESSAGE, TRUE, TRUE);
}


void CCompaniesView::SetColumns(CListCtrl& oListCtrl)
{
	oListCtrl.InsertColumn(CompaniesViewColumnName, COMPANY_NAME_COLUMN_NAME, LVCFMT_LEFT, COMPANY_NAME_COLUMN_WIDTH);
}


void CCompaniesView::SetInitialData(CListCtrl& oListCtrl)
{
	const CPtrAutoArray<COMPANIES>* pCompaniesArray = GetDocument()->GetData();

	for (INT_PTR i = 0; i < pCompaniesArray->GetCount(); i++)
	{
		COMPANIES* pCompany = pCompaniesArray->GetAt(i);

		OperationInsert(oListCtrl, *pCompany);
	}

}

void CCompaniesView::OperationUpdate(CListCtrl& oListCtrl, const COMPANIES& recCompany)
{
	const int nIndex = GetIndexByID(oListCtrl, recCompany.lID);
	if (nIndex == INDEX_BY_ID_ERROR)
		return;

	SetListViewItem(oListCtrl, recCompany, nIndex);
}


void CCompaniesView::OperationInsert(CListCtrl& oListCtrl, const COMPANIES& recCompany)
{
	const int nIndex = oListCtrl.InsertItem(LVIF_PARAM, 0, recCompany.szCompanyName, 0, 0, 0, recCompany.lID);
	SetListViewItem(oListCtrl, recCompany, nIndex);
}

void CCompaniesView::OperationDelete(CListCtrl& oListCtrl, const COMPANIES& recCompany)
{
	const int nIndex = GetIndexByID(oListCtrl, recCompany.lID);
	if (!oListCtrl.DeleteItem(nIndex))
		CErrorLogger::LogMessage(REMOVE_ITEM_ERROR_MESSAGE, TRUE, TRUE);
}

void CCompaniesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListCtrl& oListCtrl = GetListCtrl();

	switch ((DocumentDataOperation)lHint)
	{
	case DocumentDataOperationUpdate:
		OperationUpdate(oListCtrl, *(COMPANIES*)pHint);
		break;
	case DocumentDataOperationInsert:
		OperationInsert(oListCtrl, *(COMPANIES*)pHint);
		break;
	case DocumentDataOperationDelete:
		OperationDelete(oListCtrl, *(COMPANIES*)pHint);
		break;
	default:
		CErrorLogger::LogMessage(OPERATION_NOT_RECOGNISED_ERROR_MESSAGE, TRUE, TRUE);
		break;
	}
	oListCtrl.RedrawItems(0, ALL_ITEMS_NUMBER);
}

void CCompaniesView::OnInitialUpdate()
{
	//CListView::OnInitialUpdate();

	CListCtrl& oListCtrl = GetListCtrl();
	Initialize(oListCtrl);
}

// CCitiesView diagnostics

#ifdef _DEBUG
void CCompaniesView::AssertValid() const
{
	__super::AssertValid();
}

void CCompaniesView::Dump(CDumpContext& dc) const
{
	__super::Dump(dc);
}

CCompaniesDoc* CCompaniesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCompaniesDoc)));
	return (CCompaniesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCitiesView message handlers


void CCompaniesView::OnContextEdit()
{
	const COMPANIES* pSelectedCompany = GetSelectedCompany();
	if (pSelectedCompany == NULL)
		return;

	CCompaniesDialog oCompaniesDialog(pSelectedCompany, CompaniesDialogTypeEdit);
	if (oCompaniesDialog.DoModal() != IDOK)
		return;

	const BOOL bResult = GetDocument()->SetCompanyByID(oCompaniesDialog.GetCompany()->lID, *(oCompaniesDialog.GetCompany()));
	if (!bResult)
		CErrorLogger::LogMessage(UPDATE_ERROR_MESSAGE, TRUE, TRUE);
}


void CCompaniesView::OnContextAdd()
{
	CCompaniesDialog oCompaniesDialog(NULL, CompaniesDialogTypeAdd);
	if (oCompaniesDialog.DoModal() != IDOK)
		return;

	const BOOL bResult = GetDocument()->AddCompany(*(oCompaniesDialog.GetCompany()));
	if (!bResult)
		CErrorLogger::LogMessage(INSERT_ERROR_MESSAGE, TRUE, TRUE);

}


void CCompaniesView::OnContextDelete()
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

	if (!GetDocument()->RemoveCompany(lID))
		CErrorLogger::LogMessage(DELETE_ERROR_MESSAGE, FALSE, TRUE);
}


void CCompaniesView::OnContextView()
{
	const COMPANIES* pSelectedCompany = GetSelectedCompany();
	if (pSelectedCompany == NULL)
		return;

	CCompaniesDialog oCompaniesDialog(pSelectedCompany, CompaniesDialogTypeView);
	oCompaniesDialog.DoModal();
}


void CCompaniesView::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetRowColors(pNMHDR, pResult);
}
