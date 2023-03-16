#pragma once

#include "pch.h"
#include "PtrAutoArray.h"
#include "ErrorLogger.h"


#define ROW_INDEX_NOT_FOUND -1

/////////////////////////////////////////////////////////////////////////////
// CPhonebookDoc

/// <summary>
/// Базов Document клас
/// </summary>

template<class T>
class CPhonebookDoc : public CDocument
{
protected: // create from serialization only
	CPhonebookDoc() noexcept;

	// Attributes
protected:
	/// <summary> Масив с данните </summary>
	CPtrAutoArray<T> m_oArray;
public:

	// Operations
protected:

	/// <summary> Намира индекса на записа по ID </summary>
	virtual INT_PTR GetRowIndexByID(const long lID) const = 0;

	/// <summary> Зарежда запис от Data класа </summary>
	virtual BOOL LoadFromData(const long lID) = 0;
public:
	/// <summary> Получаване на данни за четене </summary>
	const CPtrAutoArray<T>* GetData() const;

	/// <summary> Получаване на запис по ID </summary>
	T* GetRowByID(const long lID);


	// Overrides
public:
	virtual BOOL OnNewDocument() = 0;
public:
	virtual ~CPhonebookDoc();

};

template<class T>
CPhonebookDoc<T>::CPhonebookDoc() noexcept
{
	theApp.CloseAllDocuments(TRUE);
}

template<class T>
CPhonebookDoc<T>::~CPhonebookDoc()
{
}

template<class T>
const CPtrAutoArray<T>* CPhonebookDoc<T>::GetData() const
{
	return &m_oArray;
}

template<class T>
T* CPhonebookDoc<T>::GetRowByID(const long lID)
{
	if (!LoadFromData(lID))
		CErrorLogger::LogMessage(_T("Error loading row from Database"), TRUE, TRUE);

	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return NULL;

	return m_oArray.GetAt(nIndex);

}
