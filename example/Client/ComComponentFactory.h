#pragma once

#include <variant>
#include <stdexcept>

#include <atlbase.h>
#include <atlcom.h>

#include "../AtlCOM/Interfaces_h.h"
#include "../LegacyCOM/interfaces.h"

using ATLComs = std::variant<IAtlCom, IDevelopDept, ITestDept>;
using LegacyComs = std::variant<ILegacyCom, IStorageDept, ISecurityDept>;

class ComFactory {
public:
    template <typename T>
    static CComPtr<T> Create() {
        CComPtr<T> ptr;
        auto hr = ptr.CoCreateInstance(ClsidOf<T>(), nullptr, CLSCTX_INPROC_SERVER);
        if (FAILED(hr)) {
            throw std::runtime_error("");
        }
        return ptr;
    }

private:
    template <typename T>
    static constexpr  CLSID ClsidOf() {
        static_assert(sizeof(T) == 0, "No CLSID mapping for this interface type");
    };
};

template <> inline CLSID ComFactory::ClsidOf<IAtlCom>() { return CLSID_AtlComClass; }
template <> inline CLSID ComFactory::ClsidOf<IDevelopDept>() { return CLSID_AtlComClass; }
template <> inline CLSID ComFactory::ClsidOf<ITestDept>() { return CLSID_AtlComClass; }

template <> inline CLSID ComFactory::ClsidOf<ILegacyCom>() { return CLSID_LegacyComClass; }
template <> inline CLSID ComFactory::ClsidOf<IStorageDept>() { return CLSID_LegacyComClass; }
template <> inline CLSID ComFactory::ClsidOf<ISecurityDept>() { return CLSID_LegacyComClass; }