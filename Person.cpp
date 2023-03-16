#include "pch.h"
#include "Person.h"

/////////////////////////////////////////////////////////////////////////////
// CPerson

// Constructor / Destructor
// ----------------

CPerson::CPerson()
{
}

CPerson::CPerson(const CPerson& oPerson):
	m_oPhoneNumbers(oPerson.m_oPhoneNumbers)
{
	m_recPerson = oPerson.m_recPerson;
}

CPerson::~CPerson()
{
}


// Methods
// ----------------


// Overrides
// ----------------

