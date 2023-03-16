#include "pch.h"
#include "CitiesAutoArray.h"

CCitiesAutoArray::CCitiesAutoArray()
{
}

CCitiesAutoArray::~CCitiesAutoArray()
{
	for (int i = 0; i < m_oCitiesPtrArray.GetCount(); i++)
	{
		delete m_oCitiesPtrArray.GetAt(i);
	}
	m_oCitiesPtrArray.RemoveAll();
}

void CCitiesAutoArray::Add(CITIES* pCity)
{
	m_oCitiesPtrArray.Add(pCity);
}

CITIES* CCitiesAutoArray::GetAt(int nIndex)
{
	return m_oCitiesPtrArray.GetAt(nIndex);
}

void CCitiesAutoArray::RemoveAll()
{
	for (int i = 0; i < m_oCitiesPtrArray.GetCount(); i++)
	{
		delete m_oCitiesPtrArray.GetAt(i);
	}
	m_oCitiesPtrArray.RemoveAll();
}

int CCitiesAutoArray::GetCount()
{
	return m_oCitiesPtrArray.GetCount();
}