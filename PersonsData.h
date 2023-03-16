#pragma once
#include "Person.h"
#include "PersonDisplay.h"
#include "PhoneNumbersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

/// <summary>
/// Клас съдържащ бизнес логиката за PERSONS
/// </summary>
class CPersonsData
{
	// Constants
	// ----------------

	// Constructor / Destructor
	// ----------------
public:
	CPersonsData();
	~CPersonsData();

	// Methods
	// ----------------
private:
	/// <summary> Записва и показва грешка </summary>
	void LogError(const HRESULT hResult) const;

	/// <summary> Намира съответстващите телефонни номера </summary>
	BOOL SelectPhoneNumbersForPerson(
		CPtrAutoArray<CPerson>& oPersonsArrayComplete,
		const CPtrAutoArray<PERSONS>& oPersonsArray,
		CPhoneNumbersTable& oPhoneNumbersTable) const;

	/// <summary> Намира запис по ID </summary>
	BOOL PhoneNumberInArray(const CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers,
		const PHONE_NUMBERS& recSearched,
		PHONE_NUMBERS& recFound) const;

	/// <summary> Проверява за изтрити записи </summary>
	BOOL DeleteCheck(const long lPersonID,
		const CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers,
		const CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbersDB,
		CPhoneNumbersTable& oPhoneNumbersTable) const;

	/// <summary> Извършва съответната операция на телефонните номера според състоянието им </summary>
	BOOL UpdatePersonsPhoneNumbers(const long lPersonID, CPtrAutoArray<PHONE_NUMBERS>& oPhoneNumbers, CPhoneNumbersTable& oPhoneNumbersTable) const;

public:
	/// <summary> Получава всички записи за PERSONS и пълни масива </summary>
	BOOL SelectAll(CPtrAutoArray<CPerson>& oPersonAutoArray) const;

	/// <summary> Намира запис по зададено ID </summary>
	BOOL SelectWhereID(const long lID, CPerson& oPerson) const;

	/// <summary> Променя запис по ID </summary>
	BOOL UpdateWhereID(const long lID, CPerson& oPerson) const;

	/// <summary> Създава нов запис </summary>
	BOOL InsertPerson(CPerson& oPerson) const;

	/// <summary> Изтрива запис по ID </summary>
	BOOL DeleteWhereID(const long lID) const;

	/// <summary> Намира допълнителна информацията, нужна за визуализиране на PERSONS </summary>
	BOOL SelectDislpayInformation(CPersonDisplay& oPersonDisplay);
	// Overrides
	// ----------------


	// Members
	// ----------------
private:
};