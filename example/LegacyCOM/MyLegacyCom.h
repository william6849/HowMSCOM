#pragma once

#include "interfaces.h"

class CLegacyCom : public ILegacyCom, public CUnknown {
public:
	DEFINE_STD_CONSTRUCTOR(CLegacyCom);
	~CLegacyCom();

	DECLARE_STD_UNKNOWN();

	IFACEMETHOD(Info)();

	// For Standard COM Aggregation
	HRESULT Init();

private:
	IUnknown* m_storage_dept;
	IUnknown* m_secure_dept;
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