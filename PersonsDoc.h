
// CitiesDoc.h : interface of the CCitiesDoc class
//


#pragma once
#include "PersonsData.h"
#include "PersonDisplay.h"
#include "PtrAutoArray.h"
#include "Structures.h"
#include "Person.h"
#include "PhonebookDoc.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc

/// <summary>
/// Document клас за таблицата PERSONS
/// </summary>
class CPersonsDoc : public CPhonebookDoc<CPerson>
{
protected: // create from serialization only
	CPersonsDoc() noexcept;
	DECLARE_DYNCREATE(CPersonsDoc)

	// Attributes
private:
	/// <summary> Допълнителни данни за хората </summary>
	CPersonDisplay m_oPersonDisplay;

	/// <summary> Обект за достъп до данните на БД </summary>
	CPersonsData m_oPersonsData;

public:

	// Operations
private:

	void SetPhoneNumberFK(CPerson& oPerson);

	/// <summary> Намира индекса на записа по ID </summary>
	INT_PTR GetRowIndexByID(const long lID) const override;

	/// <summary> Зарежда запис от Data класа </summary>
	BOOL LoadFromData(const long lID) override;
public:

	/// <summary> Получаване на допълнителни данни за представяне </summary>
	CPersonDisplay* GetDisplayInformation();

	/// <summary> Промяна на запис по ID </summary>
	BOOL SetPersonByID(const long lID, CPerson& oPerson);

	/// <summary> Добавяне на запис </summary>
	BOOL AddPerson(const CPerson& oPerson);

	/// <summary> Изтриване на запис </summary>
	BOOL RemovePerson(const long lID);

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CPersonsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
