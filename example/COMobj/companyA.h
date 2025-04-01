#pragma once

#include "building_interface.h"

class CompanyA : public ICompany, public CUnknown {
public:
	DEFINE_STD_CONSTRUCTOR(CompanyA);
	DECLARE_STD_UNKNOWN();

	IFACEMETHOD(Get)();
	
	 // For Standard COM Aggregation
	HRESULT Init();

private:
	IUnknown* m_cst;
	IUnknown* m_cse;
};

class CStorageDept : public IStorageDept, public CUnknown {
public:
	DEFINE_STD_CONSTRUCTOR(CStorageDept);
	DECLARE_STD_UNKNOWN();

	IFACEMETHOD(ReadData)();
};

class CSecurityDept : public ISecurityDept, public CUnknown {
public:
	DEFINE_STD_CONSTRUCTOR(CSecurityDept);
	DECLARE_STD_UNKNOWN();

	IFACEMETHOD(HackAWebsite)();
};