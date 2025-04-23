#include <atlbase.h>

#include "resource.h"
#include "Interfaces_h.h"

class CMyAtlModule : public CAtlDllModuleT<CMyAtlModule>
{
public:
    DECLARE_LIBID(LIBID_AtlComLib)
};

CMyAtlModule _AtlModule;

STDAPI_(BOOL) DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
    return _AtlModule.DllMain(dwReason, lpReserved);
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID FAR* ppv) {
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow() {
    return _AtlModule.DllCanUnloadNow();
}

STDAPI DllRegisterServer() {
	return _AtlModule.DllRegisterServer(0);
}

STDAPI DllUnregisterServer() {
	return _AtlModule.UnregisterServer(FALSE);
}