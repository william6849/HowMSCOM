#include "my_stdunk.h"

#include <winerror.h>

#define ASSERT(_x_)

namespace {
	inline BOOL IsEqualObject(IUnknown* pFirst, IUnknown* pSecond)
	{

		if (pFirst == pSecond) {
			return TRUE;
		}

		PUNKNOWN pUnknown1;
		PUNKNOWN pUnknown2;
		HRESULT hr;

		ASSERT(pFirst);
		ASSERT(pSecond);

		hr = pFirst->QueryInterface(IID_IUnknown, (void**)&pUnknown1);
		ASSERT(SUCCEEDED(hr));
		ASSERT(pUnknown1);

		hr = pSecond->QueryInterface(IID_IUnknown, (void**)&pUnknown2);
		ASSERT(SUCCEEDED(hr));
		ASSERT(pUnknown2);

		pUnknown1->Release();
		pUnknown2->Release();
		return (pUnknown1 == pUnknown2);
	}
};

ULONG CBaseObject::m_ulObjects = 0;

CBaseObject::CBaseObject() {
	InterlockedIncrement(&m_ulObjects);
}

CBaseObject::~CBaseObject()
{
	InterlockedDecrement(&m_ulObjects);
}

// *** ***
CUnknown::CUnknown(PUNKNOWN pUnk) : CBaseObject(), m_lRef(0), m_pUnknown(pUnk != nullptr ? pUnk : reinterpret_cast<PUNKNOWN>(static_cast<PNDUNKNOWN>(this)))
{

}

STDMETHODIMP CUnknown::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	if (ppv == nullptr) {
		return E_POINTER;
	}

	if (riid == IID_IUnknown) {
		GetInterface(reinterpret_cast<PUNKNOWN>(static_cast<PNDUNKNOWN>(this)), ppv);
		return S_OK;
	}
	else {
		*ppv = nullptr;
		return E_NOINTERFACE;
	}
}

STDMETHODIMP_(ULONG) CUnknown::NonDelegatingAddRef()
{
	LONG lRef = InterlockedIncrement(&m_lRef);
	ASSERT(lRef > 0);
	return max(static_cast<ULONG>(m_lRef), 1ul);
}

STDMETHODIMP_(ULONG) CUnknown::NonDelegatingRelease()
{
	// If the reference count drops to zero delete ourselves 
	LONG lRef = InterlockedDecrement(&m_lRef);

	if (lRef == 0) {

		// COM rules say we must protect against re-entrancy.
		// If we are an aggregator and we hold our own interfaces
		// on the aggregatee, the QI for these interfaces will
		// addref ourselves. So after doing the QI we must release
		// a ref count on ourselves. Then, before releasing the
		// private interface, we must addref ourselves. When we do
		// this from the destructor here it will result in the ref
		// count going to 1 and then back to 0 causing us to
		// re-enter the destructor. Hence we add an extra refcount here
		// once we know we will delete the object.

		m_lRef++;

		delete this;
		return static_cast<ULONG>(0);
	}
	else {
		return max(static_cast<ULONG>(m_lRef), 1ul);
	}
}

PUNKNOWN CUnknown::GetOwner() 
{
	return m_pUnknown;
}

inline HRESULT CUnknown::GetInterface(PUNKNOWN pUnk, void** ppv) {
	if (ppv == nullptr) {
		return E_POINTER;
	}
	*ppv = pUnk;
	pUnk->AddRef();
	return S_OK;
};