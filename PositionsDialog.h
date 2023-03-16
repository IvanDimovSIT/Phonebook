#pragma once
#include "Structures.h"
#include "PositionsDialogType.h"


// CPositionsDialog dialog

class CPositionsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPositionsDialog)

public:
	CPositionsDialog(const POSITIONS* pPosition, const PositionsDialogType ePositionsDialogType, CWnd* pParent = nullptr);
	virtual ~CPositionsDialog();


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
	const POSITIONS* GetPosition() const;


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POSITIONS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	/// <summary> Данните във вид на запис </summary>
	POSITIONS m_recPosition;
	/// <summary> Името на диалога </summary>
	const CString m_strDialogName;

	/// <summary> Указател към записа, който зареждаме в диалога </summary>
	const POSITIONS* m_pPosition;

	/// <summary> Роля на диалога </summary>
	const PositionsDialogType m_ePositionsDialogType;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_edbName;
};
