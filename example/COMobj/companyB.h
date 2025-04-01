#pragma once

#include "building_interface.h"

class CompanyB : public ICompany, public CUnknown {
public:
	DEFINE_STD_CONSTRUCTOR(CompanyB);
	DECLARE_STD_UNKNOWN();

	IFACEMETHOD(Get)();

	// For Standard COM Aggregation
	HRESULT Init();

private:
	IUnknown* m_cat;
	IUnknown* m_doge;
};

class CCatMeme : public ICatMeme, public CUnknown {
public:
	DEFINE_STD_CONSTRUCTOR(CCatMeme);
	DECLARE_STD_UNKNOWN();

	IFACEMETHOD(Oiiaioiiiai)();
};

class CDogeMeme : public IDogeMeme, public CUnknown {
public:
	DEFINE_STD_CONSTRUCTOR(CDogeMeme);
	DECLARE_STD_UNKNOWN();

	IFACEMETHOD(Wow)();
};