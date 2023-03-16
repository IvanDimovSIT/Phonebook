
// CitiesDoc.cpp : implementation of the CCitiesDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CitiesDoc.h"
#include "DocumentDataOperation.h"
#include "ErrorLogger.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCitiesDoc

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()


// Constants
// ----------------

// Constructor / Destructor
// ----------------

CCitiesDoc::CCitiesDoc() noexcept : CPhonebookDoc()
{

}

CCitiesDoc::~CCitiesDoc()
{
}

// Methods
// ----------------
INT_PTR CCitiesDoc::GetRowIndexByID(const long lID) const
{
	for (INT_PTR i = 0; i < m_oArray.GetCount(); i++)
	{
		if (lID == m_oArray.GetAt(i)->lID)
		{
			return i;
		}
	}

	return ROW_INDEX_NOT_FOUND;
}

BOOL CCitiesDoc::LoadFromData(const long lID)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex != ROW_INDEX_NOT_FOUND)
	{
		return m_oCitiesData.SelectWhereID(lID, *(m_oArray.GetAt(nIndex)));
	}

	CITIES* pCity = new CITIES;
	if (!m_oCitiesData.SelectWhereID(lID, (*pCity)))
	{
		delete pCity;
		return FALSE;
	}
	m_oArray.Add(pCity);
	
	return TRUE;
}

BOOL CCitiesDoc::SetCityByID(const long lID, const CITIES& recCity)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return FALSE;

	if (!m_oCitiesData.UpdateWhereID(lID, recCity))
		return FALSE;

	if (!LoadFromData(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationUpdate, (CObject*)m_oArray.GetAt(nIndex));

	return TRUE;
}

BOOL CCitiesDoc::AddCity(const CITIES& recCity)
{
	CITIES* pAddedCity = new CITIES(recCity);

	if (!m_oCitiesData.InsertCity(*pAddedCity))
	{
		delete pAddedCity;
		return FALSE;
	}

	m_oArray.Add(pAddedCity);
	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationInsert, (CObject*)pAddedCity);
	return TRUE;
}

BOOL CCitiesDoc::RemoveCity(const long lID)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return FALSE;

	const CITIES* pDeletedCity = m_oArray.GetAt(nIndex);
	if (pDeletedCity == NULL)
		return FALSE;

	if (!m_oCitiesData.DeleteWhereID(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationDelete, (CObject*)pDeletedCity);
	m_oArray.RemoveAt(nIndex);

	return TRUE;
}

BOOL CCitiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return m_oCitiesData.SelectAll(m_oArray);
}



// CCitiesDoc serialization

void CCitiesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCitiesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCitiesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCitiesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCitiesDoc diagnostics

#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCitiesDoc commands
