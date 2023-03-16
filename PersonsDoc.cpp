
// CitiesDoc.cpp : implementation of the CCitiesDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Phonebook.h"
#endif

#include "PersonsDoc.h"
#include "DocumentDataOperation.h"
#include "ErrorLogger.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc


IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()


// Constants
// ----------------

// Constructor / Destructor
// ----------------

CPersonsDoc::CPersonsDoc() noexcept
{
	// TODO: add one-time construction code here

}

CPersonsDoc::~CPersonsDoc()
{
}

// Methods
// ----------------
INT_PTR CPersonsDoc::GetRowIndexByID(const long lID) const
{
	for (INT_PTR i = 0; i < m_oArray.GetCount(); i++)
	{
		if (lID == m_oArray.GetAt(i)->m_recPerson.lID)
		{
			return i;
		}
	}

	return ROW_INDEX_NOT_FOUND;
}

BOOL CPersonsDoc::LoadFromData(const long lID)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex != ROW_INDEX_NOT_FOUND)
	{
		return m_oPersonsData.SelectWhereID(lID, *(m_oArray.GetAt(nIndex)));
	}

	CPerson* pPerson = new CPerson;
	if (!m_oPersonsData.SelectWhereID(lID, (*pPerson)))
	{
		delete pPerson;
		return FALSE;
	}
	m_oArray.Add(pPerson);

	return TRUE;
}

CPersonDisplay* CPersonsDoc::GetDisplayInformation()
{
	return &m_oPersonDisplay;
}

void CPersonsDoc::SetPhoneNumberFK(CPerson& oPerson)
{
	for (INT_PTR i = 0; i < oPerson.m_oPhoneNumbers.GetCount(); i++)
	{
		oPerson.m_oPhoneNumbers.GetAt(i)->lPersonID = oPerson.m_recPerson.lID;
	}
}

BOOL CPersonsDoc::SetPersonByID(const long lID, CPerson& oPerson)
{
	const INT_PTR nIndex = GetRowIndexByID(lID);
	if (nIndex == ROW_INDEX_NOT_FOUND)
		return FALSE;

	SetPhoneNumberFK(oPerson);

	if (!m_oPersonsData.UpdateWhereID(lID, oPerson))
		return FALSE;

	if (!LoadFromData(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationUpdate, (CObject*)m_oArray.GetAt(nIndex));

	return TRUE;
}

BOOL CPersonsDoc::AddPerson(const CPerson& oPerson)
{

	CPerson* pAddedPerson = new CPerson(oPerson);

	if (!m_oPersonsData.InsertPerson(*pAddedPerson))
	{
		delete pAddedPerson;
		return FALSE;
	}

	m_oArray.Add(pAddedPerson);
	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationInsert, (CObject*)pAddedPerson);
	return TRUE;
}

BOOL CPersonsDoc::RemovePerson(const long lID)
{
	CPerson* pPerson = GetRowByID(lID);

	if (pPerson == NULL)
		return FALSE;

	const INT_PTR nIndex = GetRowIndexByID(lID);

	if (!m_oPersonsData.DeleteWhereID(lID))
		return FALSE;

	UpdateAllViews(NULL, (LPARAM)DocumentDataOperationDelete, (CObject*)pPerson);

	m_oArray.RemoveAt(nIndex);

	return TRUE;
}

BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;



	return m_oPersonsData.SelectAll(m_oArray) &&
		m_oPersonsData.SelectDislpayInformation(m_oPersonDisplay);
}



// CCitiesDoc serialization

void CPersonsDoc::Serialize(CArchive& ar)
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
void CPersonsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCitiesDoc commands
