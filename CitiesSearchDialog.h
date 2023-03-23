#pragma once


// CCitiesSearchDialog dialog

class CCitiesSearchDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesSearchDialog)

public:
	CCitiesSearchDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCitiesSearchDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITIES_SEARCH_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edbName;
	CString m_strName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
