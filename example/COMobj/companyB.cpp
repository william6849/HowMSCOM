#include "companyB.h"

#include <new>

#include <winerror.h>

STDMETHODIMP CompanyB::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == IID_CompanyB) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<ICompany*>(this)), ppvObject);
	}
	else if (iid == IID_CatMeme) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<IStorageDept*>(m_cat)), ppvObject);
	}
	else if (iid == IID_DogeMeme) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<IStorageDept*>(m_doge)), ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CompanyB::Get() {
	return S_OK;
}

HRESULT CompanyB::Init() {
	this->m_cat = static_cast<PUNKNOWN>(new (std::nothrow) CCatMeme(GetOwner()));
	this->m_doge = static_cast<PUNKNOWN>(new (std::nothrow) CDogeMeme(GetOwner()));
	return (this->m_cat || this->m_doge) ? E_POINTER : S_OK;
}

STDMETHODIMP CCatMeme::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == IID_DogeMeme) {
		return GetInterface(this, ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CCatMeme::Oiiaioiiiai() {
	return S_OK;
}

STDMETHODIMP CDogeMeme::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == IID_CatMeme) {
		return GetInterface(this, ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CDogeMeme::Wow() {
	return S_OK;
}