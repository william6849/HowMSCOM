#//////////////////WIP//////////////////

# Understanding Microsoft Component Object Model (COM)

## Introduction
[Microsoft Component Object Model (COM)](https://learn.microsoft.com/en-us/windows/win32/com/component-object-model--com--portal) is a standard provided by Microsoft to handle the [Application Binary Interface (ABI)](https://en.wikipedia.org/wiki/Application_binary_interface).

COM has been around for over 20 years and remains a critical component in building the Windows kernel and many foundational applications. The [windows-rs](https://github.com/microsoft/windows-rs) project also supports COM to facilitate interaction with the Windows OS. Despite its age, COM is expected to persist in lower-level systems.

Due to its low-level nature and legacy status, Microsoft provides libraries such as the [Active Template Library (ATL)](https://learn.microsoft.com/zh-tw/cpp/atl/introduction-to-atl) and the [Windows Implementation Libraries (WIL)](https://github.com/microsoft/wil) to simplify working with COM objects. Although Microsoft aims to abstract native COM operations, the underlying design and implementation remain unchanged.

In this repository, I will provide a native COM implementation and explain how it works step-by-step. Additionally, I will demonstrate how the Windows-provided headers in kernel mode assist in building a COM-based interface.