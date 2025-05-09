#include "MyLegacyCom.h"

#include <new>
#include <cstdio>

#include <winerror.h>

CLegacyCom::~CLegacyCom() {
	if (m_storage_dept) {
		delete m_storage_dept;
	}
	if (m_secure_dept) {
		delete m_secure_dept;
	}
}

STDMETHODIMP CLegacyCom::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == __uuidof(ILegacyCom)) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<ILegacyCom*>(this)), ppvObject);
	}
	else if (iid == __uuidof(IStorageDept)) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<IStorageDept*>(m_storage_dept)), ppvObject);
	}
	else if (iid == __uuidof(ISecurityDept)) {
		return GetInterface(static_cast<PUNKNOWN>(static_cast<ISecurityDept*>(m_secure_dept)), ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CLegacyCom::Info() {
	printf("CLegacyCom::Info()\n");
	return S_OK;
}

HRESULT CLegacyCom::Init() {
	this->m_storage_dept = static_cast<PUNKNOWN>(new (std::nothrow) CStorageDept(GetOwner()));
	this->m_secure_dept = static_cast<PUNKNOWN>(new (std::nothrow) CSecurityDept(GetOwner()));
	return (this->m_storage_dept || this->m_secure_dept) ? E_POINTER : S_OK;
}

STDMETHODIMP CStorageDept::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == __uuidof(IStorageDept)) {
		return GetInterface(this, ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CStorageDept::ReadData() {
	printf("CStorageDept::ReadData()\n");
	return S_OK;
}

STDMETHODIMP CSecurityDept::NonDelegatingQueryInterface(_In_ REFIID iid, _COM_Outptr_ PVOID* ppvObject) {
	if (iid == __uuidof(ISecurityDept)) {
		return GetInterface(this, ppvObject);
	}
	return CUnknown::NonDelegatingQueryInterface(iid, ppvObject);
}

STDMETHODIMP CSecurityDept::HackAWebsite() {
	printf("CSecurityDept::HackAWebsite()\n");
	return S_OK;
}