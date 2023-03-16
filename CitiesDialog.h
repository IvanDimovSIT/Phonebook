#pragma once
#include "Structures.h"
#include "CitiesDialogType.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog

/// <summary>
/// Диалогов прозорец за работа с град
/// </summary>
class CCitiesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesDialog)

// Constants
// ----------------
private:
	/// <summary> Името на диалога </summary>
	const CString m_strDialogName;

	/// <summary> Указател към града, който зареждаме в диалога </summary>
	const CITIES* m_pCity;

	/// <summary> Роля на диалога </summary>
	const CitiesDialogType m_eCitiesDialogType;

// Constructor / Destructor
// ----------------
public:
	CCitiesDialog(const CITIES* pCity, const CitiesDialogType eCitiesDialogType, CWnd* pParent = nullptr); 
	virtual ~CCitiesDialog();

// Methods
// ----------------
private:
	/// <summary> Задава заглавието на диалога </summary>
	BOOL SetDialogName();
	/// <summary> Задава стойностите на полетата </summary>
	BOOL SetDialogFields();

	/// <summary> Задаване полетата да са само за четене </summary>
	void SetReadOnly();

public:
	/// <summary> Връща указател към града, създаден/редактиран от диалога </summary>
	const CITIES* GetCity() const;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// Overrides
// ----------------

// Members
// ----------------
private:
	/// <summary> Данните във вид на запис </summary>
	CITIES m_recCity;
public:
	/// <summary> Името на града </summary>
	CEdit m_edbCityName;
	/// <summary> Името на областта </summary>
	CEdit m_edbDistrict;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
