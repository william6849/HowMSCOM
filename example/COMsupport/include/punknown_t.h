/*****************************************************************************
 * punknown.h - IUnknown definitions (modfied)
 *****************************************************************************
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */

#pragma once

#include <basetypes.h>

DEFINE_GUID(IID_IUnknown,
	0x00000000, 0x0000, 0x0000, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x46);

/*****************************************************************************
 * IUnknown
 *****************************************************************************
 * Base interface for otherwise unknown objects.
 */
DECLARE_INTERFACE(IUnknown)
{
	/*
	The COM interfaces use stdcall as standard C call.
	virtual __declspec(nothrow) NTSTATUS __stdcall QueryInterface // STDMETHOD_
	(   THIS_
		_In_            REFIID,
		_COM_Outptr_    PVOID *
	)   PURE;

	virtual __declspec(nothrow) ULONG __stdcall AddRef
	(   THIS
	)   PURE;

	virtual __declspec(nothrow) ULONG __stdcall Release
	(   THIS
	)   PURE;
	*/
	STDMETHOD_(HRESULT, QueryInterface)
		(THIS_
			_In_            REFIID,
			_COM_Outptr_    PVOID*
			)   PURE;

	STDMETHOD_(ULONG, AddRef)
		(THIS
			)PURE;

	STDMETHOD_(ULONG, Release)
		(THIS
			)PURE;
};
#undef INTERFACE

typedef IUnknown* PUNKNOWN;

/*****************************************************************************
 * PFNCREATEINSTANCE
 *****************************************************************************
 * Type for object create function.
 */
typedef
HRESULT
(*PFNCREATEINSTANCE)
(
	_Out_ PUNKNOWN* Unknown,
	_In_  REFCLSID    ClassId,
	_In_  PUNKNOWN    OuterUnknown
	// _In_  POOL_TYPE   PoolType // There's no pool tag in user space
	);