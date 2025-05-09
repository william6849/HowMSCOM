#pragma once

#include "..\COMsupport\include\my_stdunk.h"

// {BF9454D9-F47C-4273-9272-A13A8FEB8B9E}
static const CLSID CLSID_LegacyComClass = 
{ 0xbf9454d9, 0xf47c, 0x4273, { 0x92, 0x72, 0xa1, 0x3a, 0x8f, 0xeb, 0x8b, 0x9e } };

// {D984BB08-635E-4B6E-BE1F-AE798682BE81}
__interface __declspec(uuid("D984BB07-635E-4B6E-BE1F-AE798682BE81"))
ILegacyCom : IUnknown {
	STDMETHOD(Info) () PURE;
};

// {D984BB08-635E-4B6E-BE1F-AE798682BE81}
__interface __declspec(uuid("D984BB08-635E-4B6E-BE1F-AE798682BE81"))
IStorageDept : IUnknown {
	STDMETHOD(ReadData) () PURE;
};

// {D984BB09-635E-4B6E-BE1F-AE798682BE81}
__interface __declspec(uuid("D984BB09-635E-4B6E-BE1F-AE798682BE81"))
ISecurityDept : IUnknown {
	STDMETHOD(HackAWebsite) () PURE;
};

/*
Below is older way to define GUID. 

// {D984BB09-635E-4B6E-BE1F-AE798682BE81}
static const GUID IID_SecurityDept = 
{ 0xd984bb09, 0x635e, 0x4b6e, { 0xbe, 0x1f, 0xae, 0x79, 0x86, 0x82, 0xbe, 0x81 } };

DECLARE_INTERFACE_(ISecurityDept, IUnknown) {
	STDMETHOD(HackAWebsite) () PURE;
};
*/