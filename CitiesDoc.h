
// CitiesDoc.h : interface of the CCitiesDoc class
//


#pragma once
#include "CitiesData.h"
#include "PtrAutoArray.h"
#include "Structures.h"
#include "PhonebookDoc.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesDoc

/// <summary>
/// Document клас за таблицата CITIES
/// </summary>
class CCitiesDoc : public CPhonebookDoc<CITIES>
{
public: // create from serialization only
	CCitiesDoc() noexcept;
	DECLARE_DYNCREATE(CCitiesDoc)

// Attributes
private:

	/// <summary> Обект за достъп до данните на БД </summary>
	CCitiesData m_oCitiesData;

public:

// Operations
private:
public:

	/// <summary> Промяна на запис по ID </summary>
	BOOL SetCityByID(const long lID, const CITIES& recCity);

	/// <summary> Добавяне на запис </summary>
	BOOL AddCity(const CITIES& recCity);

	/// <summary> Изтриване на запис </summary>
	BOOL RemoveCity(const long lID);

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
	virtual ~CCitiesDoc();
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
