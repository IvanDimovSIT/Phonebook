#pragma once
#include "Structures.h"
#include "CompaniesDialogType.h"

// CCompaniesDialog dialog

class CCompaniesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCompaniesDialog)

public:
	CCompaniesDialog(const COMPANIES* pCompany, const CompaniesDialogType eCompaniesDialogType, CWnd* pParent = nullptr);
	virtual ~CCompaniesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPANIES_DIALOG };
#endif


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
	/// <summary> Връща указател към реда, създаден/редактиран от диалога </summary>
	const COMPANIES* GetCompany() const;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edbName;
private:
	/// <summary> Данните във вид на запис </summary>
	COMPANIES m_recCompany;
	/// <summary> Името на диалога </summary>
	const CString m_strDialogName;

	/// <summary> Указател към записа, който зареждаме в диалога </summary>
	const COMPANIES* m_pCompany;

	/// <summary> Роля на диалога </summary>
	const CompaniesDialogType m_eCompaniesDialogType;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


};
