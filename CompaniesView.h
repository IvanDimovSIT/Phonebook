#pragma once
#include "PhonebookListView.h"

/////////////////////////////////////////////////////////////////////////////
// CCompaniesView

/// <summary>
/// View клас за таблицата COMPANIES
/// </summary>
class CCompaniesView : public CPhonebookListView
{
protected: // create from serialization only
	CCompaniesView() noexcept;
	DECLARE_DYNCREATE(CCompaniesView)

	// Attributes
public:
	CCompaniesDoc* GetDocument() const;

	// Operations
public:

private:

	/// <summary> Задава стойностите на елемент от ListCtrl </summary>
	void SetListViewItem(CListCtrl& oListCtrl, const COMPANIES& recCompany, int nIndex);

	/// <summary> Намиране на селектирания град, NULL ако няма селектиран </summary>
	const COMPANIES* GetSelectedCompany() const;

	/// <summary> Промяна на запис </summary>
	void OperationUpdate(CListCtrl& oListCtrl, const COMPANIES& recCompany);

	/// <summary> Въвеждане на нов запис </summary>
	void OperationInsert(CListCtrl& oListCtrl, const COMPANIES& recCompany);

	/// <summary> Изтриване на запис </summary>
	void OperationDelete(CListCtrl& oListCtrl, const COMPANIES& recCompany);

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

// Implementation
public:
	virtual ~CCompaniesView();
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

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCompaniesDoc* CCompaniesView::GetDocument() const
{
	return reinterpret_cast<CCompaniesDoc*>(m_pDocument);
}
#endif

