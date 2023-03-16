#pragma once



/////////////////////////////////////////////////////////////////////////////
// CLoginDialog

/// <summary>
/// Диалогов прозорец за автентикация
/// </summary>
class CLoginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDialog)

private:
	/// <summary> Проверява дали са зададени стойностите на контролите </summary>
	BOOL ValidateUserInput() const;

public:
	CLoginDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CLoginDialog();


	/// <summary> Връща въведените данни </summary>
	void GetData(CString& strName, CString& strPassword) const;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CString m_strUsername;
	CString m_strPassword;
public:
	CEdit m_edbName;
	CEdit m_edbPassword;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
