
// CitiesView.h : interface of the CCitiesView class
//

#pragma once
#include "PhonebookListView.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

/// <summary>
/// View клас за таблицата CITIES
/// </summary>
class CCitiesView : public CPhonebookListView
{
private:
	CPtrAutoArray<CITIES> m_oAutoArray;
	CString m_strSearch;
	BOOL m_bIsSearch = FALSE;

protected: // create from serialization only
	CCitiesView() noexcept;
	DECLARE_DYNCREATE(CCitiesView)

// Attributes
public:
	CCitiesDoc* GetDocument() const;

// Operations
public:

private:

	void ShowSearch(CListCtrl& oListCtrl);

	/// <summary> Задава стойностите на елемент от ListCtrl </summary>
	void SetListViewItem(CListCtrl& oListCtrl, const CITIES& recCity, int nIndex);

	/// <summary> Намиране на селектирания град, NULL ако няма селектиран </summary>
	const CITIES* GetSelectedCity() const;

	/// <summary> Промяна на запис </summary>
	void OperationUpdate(CListCtrl& oListCtrl, const CITIES& recCity);

	/// <summary> Въвеждане на нов запис </summary>
	void OperationInsert(CListCtrl& oListCtrl, const CITIES& recCity);

	/// <summary> Изтриване на запис </summary>
	void OperationDelete(CListCtrl& oListCtrl, const CITIES& recCity);


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
	virtual ~CCitiesView();
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
	afx_msg void OnContextSearch();
	afx_msg void OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG  // debug version in CitiesView.cpp
inline CCitiesDoc* CCitiesView::GetDocument() const
   { return reinterpret_cast<CCitiesDoc*>(m_pDocument); }
#endif

