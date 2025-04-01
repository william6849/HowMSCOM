/*****************************************************************************
 * stdunk.h - standard IUnknown implementaton definitions (modfied)
 *****************************************************************************
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */

#ifndef _STDUNK_H_
#define _STDUNK_H_

#include "punknown.h"

// VSTS 14847240: Locally suppress individual -Wv:17 compiler warnings.
// For more information, visit https://osgwiki.com/wiki/Windows_C%2B%2B_Toolset_Status.
#pragma warning(push)
#pragma warning(disable:4595) // non-member operator new or delete functions may not be declared inline

#if (NTDDI_VERSION >= NTDDI_WIN2K)
/*****************************************************************************
 * Interfaces
 */

/*****************************************************************************
 * INonDelegatingUnknown
 *****************************************************************************
 * Non-delegating unknown interface.
 */
DECLARE_INTERFACE(INonDelegatingUnknown)
{
    virtual __declspec(nothrow)  NTSTATUS __stdcall NonDelegatingQueryInterface
    (   THIS_
        _In_             REFIID,
        _COM_Outptr_     PVOID *
    ) = 0;

    virtual __declspec(nothrow)  ULONG __stdcall NonDelegatingAddRef
    (   void
    ) = 0;

    virtual __declspec(nothrow)  ULONG __stdcall NonDelegatingRelease
    (   void
    ) = 0;
};

typedef INonDelegatingUnknown *PNONDELEGATINGUNKNOWN;

/*****************************************************************************
 * Classes
 */

/*****************************************************************************
 * CUnknown
 *****************************************************************************
 * Base INonDelegatingUnknown implementation.
 */
class CUnknown : public INonDelegatingUnknown
{
private:

    LONG            m_lRefCount;        // Reference count.
    PUNKNOWN        m_pUnknownOuter;    // Outer IUnknown.

public:

    /*************************************************************************
         * CUnknown methods.
     */
    CUnknown(PUNKNOWN pUnknownOuter);
        virtual ~CUnknown(void);
    PUNKNOWN GetOuterUnknown(void)
    {
        return m_pUnknownOuter;
    }

    /*************************************************************************
         * INonDelegatingUnknown methods.
     */
    ULONG __stdcall NonDelegatingAddRef
    (   void
    );

    ULONG __stdcall NonDelegatingRelease
    (   void
    );

    NTSTATUS __stdcall NonDelegatingQueryInterface
    (   _In_            REFIID      rIID,
        _COM_Outptr_    PVOID *     ppVoid
    );
};

/*****************************************************************************
 * Macros
 */

/*****************************************************************************
 * DECLARE_STD_UNKNOWN
 *****************************************************************************
 * Various declarations for standard objects based on CUnknown.
 */
#define DECLARE_STD_UNKNOWN()                                   \
    STDMETHODIMP_(NTSTATUS) NonDelegatingQueryInterface         \
        (                                                       \
                _In_            REFIID          iid,            \
                _COM_Outptr_    PVOID *     ppvObject           \
        );                                                      \
    STDMETHODIMP_(NTSTATUS) QueryInterface(_In_ REFIID riid, _COM_Outptr_ void **ppv)        \
    {                                                           \
        return GetOuterUnknown()->QueryInterface(riid,ppv);     \
    };                                                          \
    STDMETHODIMP_(ULONG) AddRef()                               \
    {                                                           \
        return GetOuterUnknown()->AddRef();                     \
    };                                                          \
    STDMETHODIMP_(ULONG) Release()                              \
    {                                                           \
        return GetOuterUnknown()->Release();                    \
    };

#define DEFINE_STD_CONSTRUCTOR(Class)                           \
    Class(PUNKNOWN pUnknownOuter)                               \
    :   CUnknown(pUnknownOuter)                                 \
    {                                                           \
    }

#define QICAST(Type)                                            \
    PVOID((Type)(this))

#define QICASTUNKNOWN(Type)                                     \
    PVOID(PUNKNOWN((Type)(this)))

#define STD_CREATE_BODY_(Class,ppUnknown,pUnknownOuter,base)   \
    NTSTATUS ntStatus;                                                  \
    Class *p = new Class(pUnknownOuter);                  \
    if (p)                                                              \
    {                                                                   \
        *ppUnknown = PUNKNOWN((base)(p));                               \
        (*ppUnknown)->AddRef();                                         \
        ntStatus = STATUS_SUCCESS;                                      \
    }                                                                   \
    else                                                                \
    {                                                                   \
        ntStatus = STATUS_INSUFFICIENT_RESOURCES;                       \
    }                                                                   \
    return ntStatus

#define STD_CREATE_BODY(Class,ppUnknown,pUnknownOuter) \
    STD_CREATE_BODY_(Class,ppUnknown,pUnknownOuter,PUNKNOWN)

#endif  // NTDDI

#pragma warning(pop) // Wv:17 Warnings

#endif
