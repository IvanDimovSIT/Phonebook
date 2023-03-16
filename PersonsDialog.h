#pragma once
#include "Person.h"
#include "PersonDisplay.h"
#include "PersonsDialogType.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsDialog

/// <summary>
/// Диалог за редактиране, преглеждане и добавяне на PERSONS
/// </summary>
class CPersonsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonsDialog)

	// Constants
	// ----------------
private:
	/// <summary> Тип на диалога </summary>
	const PersonsDialogType m_ePersonsDialogType;

	// Constructor / Destructor
	// ----------------
public:
	CPersonsDialog(CPerson* pPerson, CPersonDisplay& oPersonDisplay, const PersonsDialogType ePersonsDialogType, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsDialog();

	/// <summary> Достъп до новополучения запис </summary>
	CPerson* GetPerson();

	// Methods
	// ----------------
private:
	/// <summary> Задаване полетата да са само за четене </summary>
	void SetReadOnly();

	/// <summary> Задаване на колоните </summary>
	void SetColumns();

	/// <summary> Задаване на първоначлните данни </summary>
	void SetInitalData();

	/// <summary> Намира индекса на записа в масива по зададено ID </summary>
	INT_PTR FindArrayIndexByID(const long lID);

	/// <summary> Намира индекса на записа в CListCtrl по зададено ID </summary>
	int FindListIndexByID(const long lID);

	/// <summary> Намира селектирания запис </summary>
	const PHONE_NUMBERS* GetSelectedPhoneNumber();

	/// <summary> Редактиране на PHONE_NUMBERS </summary>
	BOOL UpdateItem(const PHONE_NUMBERS& recPhoneNumber, const int nIndexArray);

	/// <summary> Задава ред от CListCtrl </summary>
	BOOL SetItemText(const PHONE_NUMBERS& recPhoneNumber, const int nIndexList);

	/// <summary> Добавя ред от CListCtrl </summary>
	BOOL AddItem(const PHONE_NUMBERS& recPhoneNumber);

	/// <summary> Проверява дали са зададени стойностите на контролите </summary>
	BOOL ValidateUserInput() const;

	/// <summary> Задава заглавието на диалога </summary>
	BOOL SetDialogName();

	/// <summary> Задава стойностите на полетата </summary>
	BOOL SetDialogFields();

	/// <summary> Представя CITIES като низ </summary>
	CString CityToString(const CITIES& recCity) const;

	/// <summary> Задава CITIES в комбо-бокс </summary>
	void SetCitiesComboBox();

	/// <summary> Задава COMPANIES в комбо-бокс </summary>
	void SetCompaniesComboBox();

	/// <summary> Задава POSITIONS в комбо-бокс </summary>
	void SetPositionsComboBox();


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPopupAdd();
	afx_msg void OnPopupDelete();
	afx_msg void OnPopupEdit();
	afx_msg void OnPopupView();
	virtual void OnOK();
	virtual void OnCancel();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	/// <summary> Указател към човека, когото редактираме. Има стойност NULL при добавяне </summary>
	CPerson* m_pPerson;
	/// <summary> Указател към допълнителна информация за представяне </summary>
	CPersonDisplay* m_pPersonDisplay;
	/// <summary> Новополучения запис </summary>
	CPerson m_oNewPerson;
	/// <summary> Временно ID на телефоннния номер </summary>
	long m_lTemporaryID;
public:
	//Полетата на диалога:
	CEdit m_edbFirstName;
	CEdit m_edbMiddleName;
	CEdit m_edbLastName;
	CEdit m_edbUCN;
	CComboBox m_cmbCity;
	CEdit m_edbAddress;
	CListCtrl m_lscPhoneNumbers;
	CComboBox m_cmbCompany;
	CComboBox m_cmbPosition;
};
