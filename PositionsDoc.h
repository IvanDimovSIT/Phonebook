#pragma once
#include "PositionsData.h"
#include "PtrAutoArray.h"
#include "Structures.h"
#include "PhonebookDoc.h"


/////////////////////////////////////////////////////////////////////////////
// CCompaniesDoc

/// <summary>
/// Document клас за таблицата POSITIONS
/// </summary>
class CPositionsDoc : public CPhonebookDoc<POSITIONS>
{
public: // create from serialization only
	CPositionsDoc() noexcept;
	DECLARE_DYNCREATE(CPositionsDoc)

	// Attributes
private:

	/// <summary> Обект за достъп до данните на БД </summary>
	CPositionsData m_oPositionsData;

public:

	// Operations
private:
public:

	/// <summary> Промяна на запис по ID </summary>
	BOOL SetPositionByID(const long lID, const POSITIONS& recPosition);

	/// <summary> Добавяне на запис </summary>
	BOOL AddPosition(const POSITIONS& recPosition);

	/// <summary> Изтриване на запис </summary>
	BOOL RemovePosition(const long lID);

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
	virtual ~CPositionsDoc();
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
