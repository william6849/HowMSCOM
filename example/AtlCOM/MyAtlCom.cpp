#include "MyAtlCom.h"

#include <new>
#include <cstdio>
#include <combaseapi.h>

OBJECT_ENTRY_AUTO(CLSID_AtlComClass, CAtlCom)

STDMETHODIMP CDevelopDept::CreateSomething() {
	printf("CDevelopDept::CreateSomething()\n");
	return S_OK;
}

STDMETHODIMP CTestDept::TestSomething() {
	printf("CTestDept::TestSomething()\n");
	return S_OK;
}

namespace {
	template<class T>
	auto CreateAggObject = [](IUnknown* outer, CComPtr<IUnknown>& pComPtr) {
		HRESULT hr = E_UNEXPECTED;
		CComAggObject<T>* pInner = nullptr;
		__try {
			hr = CComAggObject<T>::CreateInstance(outer, &pInner);
			if (FAILED(hr)) {
				__leave;
			}
			pInner->AddRef();
			hr = pInner->QueryInterface(&pComPtr);
			if (FAILED(hr)) {
				__leave;
			}
		}
		__finally {
			if (pInner) {
				pInner->Release();
			}
		}
		return hr;
	};
};

HRESULT CAtlCom::FinalConstruct() {
	HRESULT hr = ::CreateAggObject<CDevelopDept>(static_cast<IUnknown*>(this), m_InnerDev);
	if (FAILED(hr)) {
		return hr;
	}
    
	hr = ::CreateAggObject<CTestDept>(static_cast<IUnknown*>(this), m_InnerTest);
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;
}

void CAtlCom::FinalRelease() {}

STDMETHODIMP CAtlCom::Info() {
	printf("CAtlCom::Info()\n");
	return S_OK;
}