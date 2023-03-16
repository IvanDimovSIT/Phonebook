#pragma once
#include "CompaniesData.h"
#include "PtrAutoArray.h"
#include "Structures.h"
#include "PhonebookDoc.h"


/////////////////////////////////////////////////////////////////////////////
// CCompaniesDoc

/// <summary>
/// Document клас за таблицата COMPANIES
/// </summary>
class CCompaniesDoc : public CPhonebookDoc<COMPANIES>
{
public: // create from serialization only
	CCompaniesDoc() noexcept;
	DECLARE_DYNCREATE(CCompaniesDoc)

	// Attributes
private:

	/// <summary> Обект за достъп до данните на БД </summary>
	CCompaniesData m_oCompaniesData;

public:

	// Operations
private:
public:

	/// <summary> Промяна на запис по ID </summary>
	BOOL SetCompanyByID(const long lID, const COMPANIES& recCompany);

	/// <summary> Добавяне на запис </summary>
	BOOL AddCompany(const COMPANIES& recCompany);

	/// <summary> Изтриване на запис </summary>
	BOOL RemoveCompany(const long lID);

	// Overrides
public:
	virtual BOOL OnNewDocument() override;
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

private:
	/// <summary> Намира индекса на записа по ID </summary>
	INT_PTR GetRowIndexByID(const long lID) const override;

	/// <summary> Зарежда запис от Data класа </summary>
	BOOL LoadFromData(const long lID) override;

	// Implementation
public:
	virtual ~CCompaniesDoc();
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
