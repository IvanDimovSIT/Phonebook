#include "pch.h"
#include "PersonsFileConverter.h"
#include <fstream>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <cwchar>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CPersonsFileConverter

// Constants
// ----------------

// Constructor / Destructor
// ----------------
CPersonsFileConverter::CPersonsFileConverter()
{
}

CPersonsFileConverter::~CPersonsFileConverter()
{
}

// Methods
// ----------------



BOOL CPersonsFileConverter::Convert(const CString& strFilepath, CPtrAutoArray<CPerson>& oPersonArray, CPersonDisplay& oPersonDisplay) const
{
    std::ofstream oFile;
    oFile.open(strFilepath + _T(".html"), std::ios::out | std::ios::binary | std::ios::trunc | std::ios::ate);
    if (!oFile.is_open())
    {
        return FALSE;
    }
    CString strData = _T("<!DOCTYPE HTML><html><head><meta http-equiv=\"Content - Type\" content=\"text / html; charset = utf - 8\"></head><body><table style=\"border-spacing: 20px;\"><tr><th>Име</th><th>ЕГН</th><th>Град</th><th>Област</th><th>Адрес</th><th>Компания</th><th>Позиция</th><th>Тел. номера</th></tr>");


    for (int i = 0; i < oPersonArray.GetCount(); i++)
    {
        CPerson* pPerson = oPersonArray.GetAt(i);
        CITIES recCity;
        COMPANIES recCompany;
        POSITIONS recPosition;
        if (!oPersonDisplay.GetCityByID(pPerson->m_recPerson.lCityID, recCity) ||
        !oPersonDisplay.GetCompanyByID(pPerson->m_recPerson.lCompanyID, recCompany) ||
        !oPersonDisplay.GetPositionByID(pPerson->m_recPerson.lPositionID, recPosition))
            return FALSE;

       
        strData += CString(_T("<tr><td>"));
        strData += pPerson->m_recPerson.szFirstName;
        strData += CString(_T(" "));
        strData += pPerson->m_recPerson.szMiddleName;
        strData += CString(_T(" "));
        strData += pPerson->m_recPerson.szLastName;

        strData += CString(_T("</td><td>"));
        strData += pPerson->m_recPerson.szUCN;

        strData += CString(_T("</td><td>"));
        strData += recCity.szCityName;

        strData += CString(_T("</td><td>"));
        strData += recCity.szDistrict;

        strData += CString(_T("</td><td>"));
        strData += pPerson->m_recPerson.szAddress;

        strData += CString(_T("</td><td>"));
        strData += recCompany.szCompanyName;


        strData += CString(_T("</td><td>"));
        strData += recPosition.szPositionName;

        strData += CString(_T("</td><td><ul>"));
        

        for (int j = 0; j < pPerson->m_oPhoneNumbers.GetCount(); j++)
        {
            
            strData += CString(_T("<li>"));
            strData += pPerson->m_oPhoneNumbers.GetAt(j)->szPhoneNumber;
            strData += CString(_T(" - "));
            
            PHONE_TYPES recPhoneType;
            if(!oPersonDisplay.GetPhoneTypeByID(pPerson->m_oPhoneNumbers.GetAt(j)->lPhoneTypeID, recPhoneType))
                return FALSE;

            strData += recPhoneType.szType;

            strData += CString(_T("</li>"));
            
        }


        strData += CString(_T("</ul></td></tr>"));
    }

    
    strData += CString(_T("</table></body></html>"));
    
    std::wstring wstr = CW2CT(strData);
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string str = converter.to_bytes(wstr);
    
    oFile << str;
    oFile.flush();
    oFile.close(); 
    return TRUE;
}

// Overrides
// ----------------