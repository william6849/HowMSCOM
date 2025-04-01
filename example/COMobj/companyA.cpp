#include "companyA.h"

#include <new>

#include <winerror.h>

STDMETHODIMP CompanyA::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == IID_CompanyA) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<ICompany*>(this)), ppvObject);
	}
	else if (iid == IID_StorageDept) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<IStorageDept*>(m_cst)), ppvObject);
	}
	else if (iid == IID_SecurityDept) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<IStorageDept*>(m_cse)), ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CompanyA::Get() {
	return S_OK;
}

HRESULT CompanyA::Init() {
	this->m_cst = static_cast<PUNKNOWN>(new (std::nothrow) CStorageDept(GetOwner()));
	this->m_cse = static_cast<PUNKNOWN>(new (std::nothrow) CSecurityDept(GetOwner()));
	return (this->m_cst || this->m_cse) ? E_POINTER : S_OK;
}

STDMETHODIMP CStorageDept::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == IID_StorageDept) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<IStorageDept*>(this)), ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CStorageDept::ReadData() {
	return S_OK;
}

STDMETHODIMP CSecurityDept::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == IID_SecurityDept) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<ISecurityDept*>(this)), ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CSecurityDept::HackAWebsite() {
	return S_OK;
}