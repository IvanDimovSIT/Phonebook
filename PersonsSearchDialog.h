#pragma once


// CPersonsSearchDialog dialog

class CPersonsSearchDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonsSearchDialog)

public:
	CPersonsSearchDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsSearchDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edbName;
	CEdit m_edbUCN;
	CEdit m_edbAddress;
	CString m_strName;
	CString m_strUCN;
	CString m_strAddress;
	afx_msg void OnBnClickedOk();
};
