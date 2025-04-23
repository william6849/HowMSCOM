#pragma once

#include <atlbase.h>
#include <atlcom.h>

#include "resource.h"
#include "Interfaces_h.h"

// Be aggregated but has own interface.
class ATL_NO_VTABLE CDevelopDept :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDevelopDept
{
public:
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CDevelopDept)
        COM_INTERFACE_ENTRY(IDevelopDept)
    END_COM_MAP()

	IFACEMETHOD(CreateSomething)();

private:
};

class ATL_NO_VTABLE CTestDept :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ITestDept
{
public:
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CTestDept)
        COM_INTERFACE_ENTRY(ITestDept)
    END_COM_MAP()

	IFACEMETHOD(TestSomething)();
};

class ATL_NO_VTABLE CAtlCom :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAtlCom, &CLSID_AtlComClass>,
	public IAtlCom
{
public:
	CAtlCom() :m_InnerDev(nullptr), m_InnerTest(nullptr) {};

	DECLARE_REGISTRY_RESOURCEID(IDR_REGISTRY1)

	BEGIN_COM_MAP(CAtlCom)
		COM_INTERFACE_ENTRY(IAtlCom)
		COM_INTERFACE_ENTRY_AGGREGATE(__uuidof(IDevelopDept), m_InnerDev)
		COM_INTERFACE_ENTRY_AGGREGATE(__uuidof(ITestDept), m_InnerTest)
    END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

    // override for initialize
	HRESULT FinalConstruct();
	void FinalRelease();

	IFACEMETHOD(Info)();
	
private:
	CComPtr<IUnknown> m_InnerDev;
	CComPtr<IUnknown> m_InnerTest;
};