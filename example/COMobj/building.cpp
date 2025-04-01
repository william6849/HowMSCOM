#include <Unknwn.h>
#include <new>

#include "building_interface.h"
#include "companyA.h"
#include "companyB.h"

namespace {
	constexpr auto CreateCompanyA = [](PUNKNOWN* ppUnknown, PUNKNOWN pUnkOuter) {
		STD_CREATE_BODY_(CompanyA, ppUnknown, pUnkOuter, ICompany*);
		};

	constexpr auto CreateCompanyB = [](PUNKNOWN* ppUnknown, PUNKNOWN pUnkOuter) {
		STD_CREATE_BODY_(CompanyB, ppUnknown, pUnkOuter, ICompany*);
		};

}

class LobbyFactory : public IClassFactory {
public:
	IFACEMETHOD(QueryInterface)(REFIID riid, void** ppv) {
		if (riid == IID_IUnknown || riid == IID_IClassFactory) {
			*ppv = static_cast<IClassFactory*>(this);
			AddRef();
			return S_OK;
		}
		ppv = nullptr;
		return E_NOINTERFACE;
	}

	IFACEMETHOD_(ULONG, AddRef)() {
		return InterlockedIncrement(&m_lRef);
	}

	IFACEMETHOD_(ULONG, Release)() {
		return InterlockedDecrement(&m_lRef);
	}

	IFACEMETHOD(CreateInstance)(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
		try {
			if (ppv == nullptr) {
				return E_POINTER;
			}
			*ppv = nullptr;

			// Not allowing aggregation
			if (pUnkOuter != nullptr) {
				return CLASS_E_NOAGGREGATION;
			}

			if (riid == IID_CompanyA) {
				PUNKNOWN pUnk;
				CreateCompanyA(&pUnk, pUnkOuter);
				return pUnk->QueryInterface(IID_CompanyA, ppv);
			}
			else if (riid == IID_CompanyB) {
				PUNKNOWN pUnk;
				CreateCompanyB(&pUnk, pUnkOuter);
				return pUnk->QueryInterface(IID_CompanyA, ppv);
			}
			else {
				return E_NOINTERFACE;
			}
			return S_OK;
		}
		catch (const std::bad_alloc&) {
			return E_OUTOFMEMORY;
		}
		catch (...) {
			return E_FAIL;
		}
	}

	IFACEMETHOD(LockServer)(BOOL fLock) {
		return CoLockObjectExternal(static_cast<IUnknown*>(this), fLock, FALSE);
	}

private:
	LONG m_lRef;
};

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID clsid, REFIID riid, void** ppv) {
	static LobbyFactory lobby;
	return lobby.QueryInterface(riid, ppv);
}