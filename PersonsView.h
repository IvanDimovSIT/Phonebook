#pragma once
#include "PersonDisplay.h"
#include "PhonebookListView.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsView

/// <summary>
/// View клас за таблицата CITIES
/// </summary>
class CPersonsView : public CPhonebookListView
{
private:
	CPtrAutoArray<CPerson> m_oAutoArray;
	CString m_strSearchName;
	CString m_strSearchUCN;
	CString m_strSearchAddress;
	BOOL m_bIsSearch = FALSE;

protected: // create from serialization only
	CPersonsView() noexcept;
	DECLARE_DYNCREATE(CPersonsView)

	// Attributes
public:
	CPersonsDoc* GetDocument() const;

	// Operations
public:

private:
	void ShowSearch(CListCtrl& oListCtrl);

	/// <summary> Задава стойностите на елемент от ListCtrl </summary>
	void SetListViewItem(CListCtrl& oListCtrl, const CPerson& oPerson, const CPersonDisplay& oPersonDisplay, int nIndex);

	/// <summary> Намиране на селектирания град, NULL ако няма селектиран </summary>
	CPerson* GetSelectedPerson() const;

	/// <summary> Промяна на запис </summary>
	void OperationUpdate(CListCtrl& oListCtrl, const CPerson& oPerson);

	/// <summary> Въвеждане на нов запис </summary>
	void OperationInsert(CListCtrl& oListCtrl, const CPerson& oPerson);

	/// <summary> Изтриване на запис </summary>
	void OperationDelete(CListCtrl& oListCtrl, const CPerson& oPerson);

	// Overrides
public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;
protected:
	/// <summary> Задаване на колоните </summary>
	void SetColumns(CListCtrl& oListCtrl) override;

	/// <summary> Задаване на първоначлните данни </summary>
	void SetInitialData(CListCtrl& oListCtrl) override;

	virtual void OnInitialUpdate(); // called first time after construct

	virtual BOOL CanSearch() override;

// Implementation
public:
	virtual ~CPersonsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL IsSelectedRow() override;

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
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
inline CPersonsDoc* CPersonsView::GetDocument() const
{
	return reinterpret_cast<CPesonsDoc*>(m_pDocument);
}
#endif

