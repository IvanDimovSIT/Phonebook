#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "CompaniesDoc.h"
#include "DocumentDataOperation.h"
#include "ErrorLogger.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCitiesDoc

IMPLEMENT_DYNCREATE(CCompaniesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCompaniesDoc, CDocument)
END_MESSAGE_MAP()


// Constants
// ----------------

// Constructor / Destructor
// ----------------

CCompaniesDoc::CCompaniesDoc() noexcept
{

}

CCompaniesDoc::~CCompaniesDoc()
{
}

// Methods
// ----------------
INT_PTR CCompaniesDoc::GetRowIndexByID(const long lID) const
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

BOOL CCompaniesDoc::LoadFromData(const long lID)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex != ROW_INDEX_NOT_FOUND)
	{
		return m_oCompaniesData.SelectWhereID(lID, *(m_oArray.GetAt(nIndex)));
	}

	COMPANIES* pCompany = new COMPANIES;
	if (!m_oCompaniesData.SelectWhereID(lID, (*pCompany)))
	{
		delete pCompany;
		return FALSE;
	}
	m_oArray.Add(pCompany);

	return TRUE;
}

BOOL CCompaniesDoc::SetCompanyByID(const long lID, const COMPANIES& recCompany)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return FALSE;

	if (!m_oCompaniesData.UpdateWhereID(lID, recCompany))
		return FALSE;

	if (!LoadFromData(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationUpdate, (CObject*)m_oArray.GetAt(nIndex));

	return TRUE;
}

BOOL CCompaniesDoc::AddCompany(const COMPANIES& recCompany)
{
	COMPANIES* pAddedCompany = new COMPANIES(recCompany);

	if (!m_oCompaniesData.InsertCompany(*pAddedCompany))
	{
		delete pAddedCompany;
		return FALSE;
	}

	m_oArray.Add(pAddedCompany);
	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationInsert, (CObject*)pAddedCompany);
	return TRUE;
}

BOOL CCompaniesDoc::RemoveCompany(const long lID)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return FALSE;

	const COMPANIES* pDeletedCompany = m_oArray.GetAt(nIndex);
	if (pDeletedCompany == NULL)
		return FALSE;

	if (!m_oCompaniesData.DeleteWhereID(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationDelete, (CObject*)pDeletedCompany);
	m_oArray.RemoveAt(nIndex);

	return TRUE;
}

BOOL CCompaniesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return m_oCompaniesData.SelectAll(m_oArray);
}



// CCitiesDoc serialization

void CCompaniesDoc::Serialize(CArchive& ar)
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
void CCompaniesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CCompaniesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCompaniesDoc::SetSearchContent(const CString& value)
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
void CCompaniesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCompaniesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCitiesDoc commands
