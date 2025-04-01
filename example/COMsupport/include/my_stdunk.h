// This is a modifyed and own implemented version of stdunk.h for learning, you should include original one in windows sdk.
// Modifyed for userspace usage, so that QueryInterface return with HRESULT, with no poolTag memory allocation.

#pragma once

#include <unknwn.h>

typedef IUnknown* PUNKNOWN;

DECLARE_INTERFACE(INonDelegatingUnknown)
{
	STDMETHOD(NonDelegatingQueryInterface) (THIS_ REFIID, PVOID*) PURE;
	STDMETHOD_(ULONG, NonDelegatingAddRef)(THIS) PURE;
	STDMETHOD_(ULONG, NonDelegatingRelease)(THIS) PURE;
};

typedef INonDelegatingUnknown* PNDUNKNOWN;

class CBaseObject
{
public:
	CBaseObject();
	~CBaseObject();

private:
	CBaseObject(const CBaseObject&) = delete;
	void operator=(const CBaseObject&) = delete;

	static ULONG m_ulObjects;
};

class CUnknown : public INonDelegatingUnknown,
	public CBaseObject
{
public:
	CUnknown(PUNKNOWN pUnk);
	virtual ~CUnknown() {};

	IFACEMETHOD(NonDelegatingQueryInterface)(REFIID, void**);
	IFACEMETHOD_(ULONG, NonDelegatingAddRef)(THIS);
	IFACEMETHOD_(ULONG, NonDelegatingRelease)(THIS);

	PUNKNOWN GetOwner();
	HRESULT GetInterface(PUNKNOWN pUnk, void** ppv);

private:
	const PUNKNOWN m_pUnknown;
	volatile ULONG m_lRef;
};

#define DECLARE_STD_UNKNOWN()                                   \
    STDMETHODIMP_(HRESULT) NonDelegatingQueryInterface         \
        (                                                       \
                _In_            REFIID          iid,            \
                _COM_Outptr_    PVOID *     ppvObject           \
        );                                                      \
    STDMETHODIMP_(HRESULT) QueryInterface(_In_ REFIID riid, _COM_Outptr_ void **ppv)        \
    {                                                           \
        return GetOwner()->QueryInterface(riid,ppv);     \
    };                                                          \
    STDMETHODIMP_(ULONG) AddRef()                               \
    {                                                           \
        return GetOwner()->AddRef();                     \
    };                                                          \
    STDMETHODIMP_(ULONG) Release()                              \
    {                                                           \
        return GetOwner()->Release();                    \
    };

#define DEFINE_STD_CONSTRUCTOR(Class)                           \
    Class(PUNKNOWN pUnknownOuter)                               \
    :   CUnknown(pUnknownOuter)                                 \
    {                                                           \
    }

#define STD_CREATE_BODY_(Class,ppUnknown,pUnknownOuter,base)   \
    HRESULT hrs;                                                  \
    Class *p = new Class(pUnknownOuter);                  \
    if (p)                                                              \
    {                                                                   \
        *ppUnknown = PUNKNOWN((base)(p));                               \
        (*ppUnknown)->AddRef();                                         \
        hrs = S_OK;                                      \
    }                                                                   \
    else                                                                \
    {                                                                   \
        hrs = E_OUTOFMEMORY;                       \
    }                                                                   \
    return hrs

#define STD_CREATE_BODY(Class,ppUnknown,pUnknownOuter) \
    STD_CREATE_BODY_(Class,ppUnknown,pUnknownOuter,PUNKNOWN)