#pragma once

#include <my_stdunk.h>

// {D984BB07-635E-4B6E-BE1F-AE798682BE81}
static const GUID IID_CompanyA = 
{ 0xd984bb07, 0x635e, 0x4b6e, { 0xbe, 0x1f, 0xae, 0x79, 0x86, 0x82, 0xbe, 0x81 } };


// {D984BB0A-635E-4B6E-BE1F-AE798682BE81}
static const GUID IID_CompanyB = 
{ 0xd984bb0A, 0x635e, 0x4b6e, { 0xbe, 0x1f, 0xae, 0x79, 0x86, 0x82, 0xbe, 0x81 } };

DECLARE_INTERFACE_(ICompany, IUnknown) {
	STDMETHOD(Get) () PURE;
};

// {D984BB08-635E-4B6E-BE1F-AE798682BE81}
static const GUID IID_StorageDept = 
{ 0xd984bb08, 0x635e, 0x4b6e, { 0xbe, 0x1f, 0xae, 0x79, 0x86, 0x82, 0xbe, 0x81 } };

DECLARE_INTERFACE_(IStorageDept, IUnknown) {
	STDMETHOD(ReadData) () PURE;
};

// {D984BB09-635E-4B6E-BE1F-AE798682BE81}
static const GUID IID_SecurityDept = 
{ 0xd984bb09, 0x635e, 0x4b6e, { 0xbe, 0x1f, 0xae, 0x79, 0x86, 0x82, 0xbe, 0x81 } };

DECLARE_INTERFACE_(ISecurityDept, IUnknown) {
	STDMETHOD(HackAWebsite) () PURE;
};

// {D984BB0B-635E-4B6E-BE1F-AE798682BE81}
static const GUID IID_CatMeme = 
{ 0xd984bb0B, 0x635e, 0x4b6e, { 0xbe, 0x1f, 0xae, 0x79, 0x86, 0x82, 0xbe, 0x81 } };

DECLARE_INTERFACE_(ICatMeme, IUnknown) {
	STDMETHOD(Oiiaioiiiai) () PURE;
};

// {D984BB0C-635E-4B6E-BE1F-AE798682BE81}
static const GUID IID_DogeMeme = 
{ 0xd984bb0C, 0x635e, 0x4b6e, { 0xbe, 0x1f, 0xae, 0x79, 0x86, 0x82, 0xbe, 0x81 } };

DECLARE_INTERFACE_(IDogeMeme, IUnknown) {
	STDMETHOD(Wow) () PURE;
};