#pragma once
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CPtrAutoArray

/// <summary>
/// Template клас за автоматично освобождаване на паметта на CTypedPtrArray
/// </summary>
template <class T>
class CPtrAutoArray
{
// Constants
// ----------------

// Constructor / Destructor
// ----------------
public:
	CPtrAutoArray();

	CPtrAutoArray(const CPtrAutoArray<T> &oPtrAutoArray);

	~CPtrAutoArray();

// Methods
// ----------------

	CPtrAutoArray<T>& operator=(const CPtrAutoArray<T>& oPtrAutoArray);

	/// <summary> Добавя елемент в масива </summary>
	/// <param name="pToAdd"> Елемента който се добавя </param>
	void Add(T* pToAdd);

	/// <summary> Намира и връща елемент от масива по зададен индекс </summary>
	/// <param name="nIndex"> Индекс на елемента </param>
	/// <returns> Указател към елемента </returns>
	T* GetAt(const INT_PTR nIndex) const;

	/// <summary> Премахва всички елементи от масива и освобождава паметта </summary>
	void RemoveAll();

	/// <summary> Премахва елемент по индекс </summary>
	void RemoveAt(const INT_PTR nIndex);

	/// <summary>  Връща броя на елементите от масива </summary>
	int GetCount() const;

// Overrides
// ----------------

// Members
// ----------------
private:
	/// <summary> Масива от елементите </summary>
	CTypedPtrArray<CPtrArray, T*> m_oCTypedPtrArray;
};



// Constants
// ----------------

// Constructor / Destructor
// ----------------

template<class T> 
CPtrAutoArray<T>::CPtrAutoArray()
{
}

template<class T>
CPtrAutoArray<T>::CPtrAutoArray(const CPtrAutoArray<T>& oPtrAutoArray)
{
	for (INT_PTR i = 0; i < oPtrAutoArray.GetCount(); i++)
	{
		m_oCTypedPtrArray.Add(new T(*oPtrAutoArray.GetAt(i)));
	}
}

template<class T> 
CPtrAutoArray<T>::~CPtrAutoArray()
{
	RemoveAll();
}

// Methods
// ----------------
template<class T>
CPtrAutoArray<T>& CPtrAutoArray<T>::operator=(const CPtrAutoArray<T>& oPtrAutoArray)
{
	if (this == &oPtrAutoArray)
		return *this;

	RemoveAll();
	for (INT_PTR i = 0; i < oPtrAutoArray.GetCount(); i++)
		Add(new T(*oPtrAutoArray.GetAt(i)));

	return *this;
}

template<class T>
void CPtrAutoArray<T>::Add(T* pToAdd)
{
	m_oCTypedPtrArray.Add(pToAdd);
}

template<class T>
T* CPtrAutoArray<T>::GetAt(const INT_PTR nIndex) const
{
	return m_oCTypedPtrArray.GetAt(nIndex);
}

template<class T>
void CPtrAutoArray<T>::RemoveAt(const INT_PTR nIndex)
{
	const T* pToDelete = GetAt(nIndex);
	if (pToDelete != NULL)
	{
		delete pToDelete;
	}

	m_oCTypedPtrArray.RemoveAt(nIndex);
}

template<class T>
void CPtrAutoArray<T>::RemoveAll()
{
	for (INT_PTR i = 0; i < m_oCTypedPtrArray.GetCount(); i++)
	{
		delete m_oCTypedPtrArray.GetAt(i);
	}
	m_oCTypedPtrArray.RemoveAll();
}

template<class T>
int CPtrAutoArray<T>::GetCount() const
{
	return m_oCTypedPtrArray.GetCount();
}

// Overrides
// ----------------

