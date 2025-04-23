#include <memory>
#include <iostream>

#include <atlbase.h>
#include <atlcom.h>

#include "ComComponentFactory.h"

typedef HRESULT (STDAPICALLTYPE* PFNDllGetClassObject)(
    REFCLSID rclsid, REFIID riid, LPVOID* ppv);

HRESULT Run() {
	try {
		auto spObj = ComFactory::Create<ITestDept>();

		spObj->TestSomething();

		CComPtr<IAtlCom> spObj2;
		spObj.QueryInterface(&spObj2);
		spObj2->Info();}
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