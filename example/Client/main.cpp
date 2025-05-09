#include <memory>
#include <iostream>

#include <atlbase.h>
#include <atlcom.h>

#include "ComComponentFactory.h"
#include "../LegacyCOM/interfaces.h"

typedef HRESULT (STDAPICALLTYPE* PFNDllGetClassObject)(
    REFCLSID rclsid, REFIID riid, LPVOID* ppv);

HRESULT Run() {
	try {
		auto spObj = ComFactory::Create<ITestDept>();

		spObj->TestSomething();

		CComPtr<IAtlCom> spObj2;
		auto ret = spObj.QueryInterface(&spObj2);
		if (FAILED(ret)) {
			return ret;
		}
		spObj2->Info();

		auto legcy = ComFactory::Create<ILegacyCom>();
		legcy->Info();
	
	}
	catch (...) {
		return E_UNEXPECTED;
	}
	
	return S_OK;
}

int main(int argc, void** argv) {
	auto hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::cout << "CoInitialize failed\n";
        return 1;
    }
	
	hr = Run();
	
	CoUninitialize();
	return hr;
}