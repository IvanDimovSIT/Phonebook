#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PositionsDoc.h"
#include "DocumentDataOperation.h"
#include "ErrorLogger.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCitiesDoc

IMPLEMENT_DYNCREATE(CPositionsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPositionsDoc, CDocument)
END_MESSAGE_MAP()


// Constants
// ----------------

// Constructor / Destructor
// ----------------

CPositionsDoc::CPositionsDoc() noexcept
{

}

CPositionsDoc::~CPositionsDoc()
{
}

// Methods
// ----------------
INT_PTR CPositionsDoc::GetRowIndexByID(const long lID) const
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

BOOL CPositionsDoc::LoadFromData(const long lID)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex != ROW_INDEX_NOT_FOUND)
	{
		return m_oPositionsData.SelectWhereID(lID, *(m_oArray.GetAt(nIndex)));
	}

	POSITIONS* pPosition = new POSITIONS;
	if (!m_oPositionsData.SelectWhereID(lID, (*pPosition)))
	{
		delete pPosition;
		return FALSE;
	}
	m_oArray.Add(pPosition);

	return TRUE;
}

BOOL CPositionsDoc::SetPositionByID(const long lID, const POSITIONS& recPosition)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return FALSE;

	if (!m_oPositionsData.UpdateWhereID(lID, recPosition))
		return FALSE;

	if (!LoadFromData(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationUpdate, (CObject*)m_oArray.GetAt(nIndex));

	return TRUE;
}

BOOL CPositionsDoc::AddPosition(const POSITIONS& recPosition)
{
	POSITIONS* pAddedPosition = new POSITIONS(recPosition);

	if (!m_oPositionsData.InsertPosition(*pAddedPosition))
	{
		delete pAddedPosition;
		return FALSE;
	}

	m_oArray.Add(pAddedPosition);
	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationInsert, (CObject*)pAddedPosition);
	return TRUE;
}

BOOL CPositionsDoc::RemovePosition(const long lID)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return FALSE;

	const POSITIONS* pDeletedPosition = m_oArray.GetAt(nIndex);
	if (pDeletedPosition == NULL)
		return FALSE;

	if (!m_oPositionsData.DeleteWhereID(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationDelete, (CObject*)pDeletedPosition);
	m_oArray.RemoveAt(nIndex);

	return TRUE;
}

BOOL CPositionsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return m_oPositionsData.SelectAll(m_oArray);
}



// CCitiesDoc serialization

void CPositionsDoc::Serialize(CArchive& ar)
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
void CPositionsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPositionsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPositionsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
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
void CPositionsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPositionsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCitiesDoc commands
