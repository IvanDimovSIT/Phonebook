#pragma once
#include "PhonebookListView.h"

/////////////////////////////////////////////////////////////////////////////
// CPositionsView

/// <summary>
/// View клас за таблицата POSITIONS
/// </summary>
class CPositionsView : public CPhonebookListView
{
protected: // create from serialization only
	CPositionsView() noexcept;
	DECLARE_DYNCREATE(CPositionsView)

	// Attributes
public:
	CPositionsDoc* GetDocument() const;

	// Operations
public:

private:

	/// <summary> Задава стойностите на елемент от ListCtrl </summary>
	void SetListViewItem(CListCtrl& oListCtrl, const POSITIONS& recPosition, int nIndex);

	/// <summary> Намиране на селектирания град, NULL ако няма селектиран </summary>
	const POSITIONS* GetSelectedPosition() const;

	/// <summary> Промяна на запис </summary>
	void OperationUpdate(CListCtrl& oListCtrl, const POSITIONS& recPosition);

	/// <summary> Въвеждане на нов запис </summary>
	void OperationInsert(CListCtrl& oListCtrl, const POSITIONS& recPosition);

	/// <summary> Изтриване на запис </summary>
	void OperationDelete(CListCtrl& oListCtrl, const POSITIONS& recPosition);

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
protected:
	BOOL IsSelectedRow() override;

	/// <summary> Задаване на колоните </summary>
	void SetColumns(CListCtrl& oListCtrl) override;

	/// <summary> Задаване на първоначлните данни </summary>
	void SetInitialData(CListCtrl& oListCtrl) override;

	virtual void OnInitialUpdate(); // called first time after construct

	virtual BOOL CanSearch() override;

	virtual BOOL CanConvert() override;

// Implementation
public:
	virtual ~CPositionsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextEdit();
	afx_msg void OnContextAdd();
	afx_msg void OnContextDelete() override;
	afx_msg void OnContextView() override;
	afx_msg void OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG 
inline CPositionsDoc* CPositionView::GetDocument() const
{
	return reinterpret_cast<CPositionsDoc*>(m_pDocument);
}
#endif

