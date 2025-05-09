#include <strsafe.h>
#include <olectl.h>
#include <combaseapi.h>
#include <Unknwn.h>

#include "interfaces.h"
#include "MyLegacyCom.h"

namespace {
	template<typename T>
	struct type_tag { using type = T; };

	template<typename T>
	auto CreateCOMBody = [](auto ClassType, IUnknown** ppUnknown, IUnknown* pUnkOuter) {
		using type = typename decltype(ClassType)::type;
		// Our classes are using default constructor, so that we can use windows helper to help us.
		STD_CREATE_BODY_(type, ppUnknown, pUnkOuter, T*);
		};
}

LONG g_cDllRef = 0;

class LobbyFactory :
	public IClassFactory
{
public:
	LobbyFactory() : m_lRef(1) {};

	IFACEMETHOD(QueryInterface)(REFIID riid, void** ppv) {
		if (riid == IID_IUnknown || riid == IID_IClassFactory) {
			*ppv = static_cast<IClassFactory*>(this);
			AddRef();
			return S_OK;
		}
		*ppv = nullptr;
		return E_NOINTERFACE;
	}

	IFACEMETHOD_(ULONG, AddRef)() {
		return InterlockedIncrement(&m_lRef);
	}

	IFACEMETHOD_(ULONG, Release)() {
		return InterlockedDecrement(&m_lRef);
	}

	IFACEMETHOD(CreateInstance)(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
		if (ppv == nullptr) {
			return E_POINTER;
		}
		*ppv = nullptr;

		// Not allowing aggregation
		if (pUnkOuter != nullptr) {
			return CLASS_E_NOAGGREGATION;
		}
		if (riid == __uuidof(ILegacyCom)) {
			IUnknown* pUnk;
			CreateCOMBody<IUnknown>(type_tag<CLegacyCom>{}, &pUnk, pUnkOuter);
			HRESULT ret = pUnk->QueryInterface(__uuidof(ILegacyCom), ppv);
			pUnk->Release(); // Local reference
			return ret;
		} else {
			return E_NOINTERFACE;
		}
	    return S_OK;
	}

	IFACEMETHOD(LockServer)(BOOL fLock) {
		return CoLockObjectExternal(static_cast<IUnknown*>(this), fLock, FALSE);
	}

private:
	LONG m_lRef;
};

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID FAR* ppv) {
    if (rclsid == CLSID_LegacyComClass) {
	    // static LobbyFactory pFactory; // if you have crt
		LobbyFactory* pFactory = new LobbyFactory();
		if (pFactory == nullptr) {
			return E_OUTOFMEMORY;
		}
		auto ret = pFactory->QueryInterface(riid, ppv);
		pFactory->Release();
		return ret;
	}
	return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow()
{
	return g_cDllRef == 0 ? S_OK : S_FALSE;
}

STDAPI DllRegisterServer() {
	// Get dll path
	auto hMod = GetModuleHandle(L"LegacyCom.dll");
	if (!hMod) {
		return E_FAIL;
	}

	WCHAR szModuleName[MAX_PATH];
	if (!GetModuleFileNameW(hMod, szModuleName, MAX_PATH)) {
		return SELFREG_E_CLASS;
	}
	
	/*
	* HKCR
	* {CLSID}
	*   InprocServer32
	*     default: dllpath
	*     ThreadingModel: Apartment
	*/
	LPOLESTR wszClsidString;
    if (FAILED(StringFromCLSID(CLSID_LegacyComClass, &wszClsidString)))
        return E_FAIL;

	WCHAR keyPath[MAX_PATH];
	StringCchPrintfW(keyPath, MAX_PATH, L"CLSID\\%s", wszClsidString);

	HKEY hKey;
    if (RegCreateKeyExW(
		HKEY_CLASSES_ROOT, 
		keyPath,
		0, nullptr, 0, KEY_WRITE, nullptr, &hKey, nullptr) != ERROR_SUCCESS) {
        CoTaskMemFree(wszClsidString);
        return SELFREG_E_CLASS;
    }

	HKEY hInproc;
    if (RegCreateKeyExW(hKey, L"InprocServer32", 0, nullptr, 0, KEY_WRITE, nullptr, &hInproc, nullptr) == ERROR_SUCCESS) {
        RegSetValueExW(hInproc, nullptr, 0, REG_SZ, (const BYTE*)szModuleName, ((DWORD)wcslen(szModuleName) + 1) * sizeof(wchar_t));
        const WCHAR threadingModel[] = L"Apartment";
        RegSetValueExW(hInproc, L"ThreadingModel", 0, REG_SZ, (const BYTE*)threadingModel, ((DWORD)wcslen(threadingModel) + 1) * sizeof(wchar_t));

        RegCloseKey(hInproc);
    }

	RegCloseKey(hKey);
    CoTaskMemFree(wszClsidString);

    return S_OK;
}

STDAPI DllUnregisterServer() {
    return S_OK;
}