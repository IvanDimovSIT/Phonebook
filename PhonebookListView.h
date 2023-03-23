#pragma once

/////////////////////////////////////////////////////////////////////////////
// CPhonebookListView

#define INDEX_BY_ID_ERROR -1

/// <summary>
/// Помощен клас за ListView
/// </summary>
class CPhonebookListView : public CListView
{
// Constants
// ----------------

// Constructor / Destructor
// ----------------
public:
CPhonebookListView();
~CPhonebookListView();

// Methods
// ----------------
private:
	/// <summary> Задава стила на таблицата </summary>
	void SetStyle(CListCtrl& oListCtrl);

protected:
	/// <summary> Проверява дали е селектиран ред </summary>
	virtual BOOL IsSelectedRow() = 0;

	/// <summary> Намиране на ред по ID </summary>
	int GetIndexByID(CListCtrl& oListCtrl, const long lID) const;

	/// <summary> Задава колоните на таблицата </summary>
	virtual void SetColumns(CListCtrl& oListCtrl) = 0;

	/// <summary> Задава началнните стойности </summary>
	virtual void SetInitialData(CListCtrl& oListCtrl) = 0;

	virtual BOOL CanSearch() = 0;

	/// <summary> Инитиализира контролата </summary>
	void Initialize(CListCtrl& oListCtrl);

	/// <summary> Задава цветовете </summary>
	void SetRowColors(NMHDR* pNMHDR, LRESULT* pResult);

	virtual afx_msg void OnContextDelete() = 0;
	virtual afx_msg void OnContextView() = 0;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);//double click

// Overrides
// ----------------

// Members
// ----------------
};

