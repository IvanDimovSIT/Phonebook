#include "pch.h"
#include "resource.h"
#include "PhonebookListView.h"
#include "ErrorLogger.h"

/////////////////////////////////////////////////////////////////////////////
// CPhonebookListView

// Constants
// ----------------

#define COLOR_TEXT RGB(0, 0, 0)
#define COLOR_BACKGROUND_LIGHT RGB(240, 240, 255)
#define COLOR_BACKGROUND_DARK RGB(220, 220, 240)

#define STYLE_ERROR_MESSAGE _T("Грешка при настройката на стила.")

// Constructor / Destructor
// ----------------

CPhonebookListView::CPhonebookListView()
{
}

CPhonebookListView::~CPhonebookListView()
{
}

// Methods
// ----------------

BEGIN_MESSAGE_MAP(CPhonebookListView, CListView)
	ON_WM_LBUTTONDBLCLK()//LMB double click
	ON_WM_KEYUP()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


int CPhonebookListView::GetIndexByID(CListCtrl& oListCtrl, const long lID) const
{
	for (int i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (oListCtrl.GetItemData(i) == lID)
		{
			return i;
		}
	}

	return INDEX_BY_ID_ERROR;
}


void CPhonebookListView::SetStyle(CListCtrl& oListCtrl)
{
	if (!oListCtrl.ModifyStyle(LVS_TYPEMASK, LVS_REPORT))
		CErrorLogger::LogMessage(STYLE_ERROR_MESSAGE, TRUE, TRUE);

	oListCtrl.SetExtendedStyle(oListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	oListCtrl.SetBkColor(COLOR_BACKGROUND_LIGHT);

}

void CPhonebookListView::Initialize(CListCtrl& oListCtrl)
{
	SetColumns(oListCtrl);
	SetInitialData(oListCtrl);
	SetStyle(oListCtrl);
}


void CPhonebookListView::SetRowColors(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW pLVCDCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	*pResult = CDRF_DODEFAULT;

	switch (pLVCDCustomDraw->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_PREPAINT | CDDS_ITEM:
	{
		COLORREF dwEven = COLOR_BACKGROUND_LIGHT;
		COLORREF dwOdd = COLOR_BACKGROUND_DARK;
		COLORREF dwText = COLOR_TEXT;

		if ((pLVCDCustomDraw->nmcd.dwItemSpec % 2) == 0)
			pLVCDCustomDraw->clrTextBk = dwEven;
		else
			pLVCDCustomDraw->clrTextBk = dwOdd;
		pLVCDCustomDraw->clrText = dwText;
	}
	break;
	default:
		break;

	}
}

void CPhonebookListView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhonebookListView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	CMenu oContextMenu;
	oContextMenu.LoadMenu(IDR_POPUP);
	CMenu* oPopupMenu = oContextMenu.GetSubMenu(0);

	if (!IsSelectedRow())
	{
		oPopupMenu->EnableMenuItem(ID_POPUP_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		oPopupMenu->EnableMenuItem(ID_POPUP_EDIT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		oPopupMenu->EnableMenuItem(ID_POPUP_VIEW, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	if (!CanSearch()) 
	{
		oPopupMenu->EnableMenuItem(ID_POPUP_SEARCH, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	oPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

#endif
}

afx_msg void CPhonebookListView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)
	{
		OnContextDelete();
	}
}

void CPhonebookListView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnContextView();

	__super::OnLButtonDblClk(nFlags, point);
}


// Overrides
// ----------------
