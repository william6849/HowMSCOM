#//////////////////WIP//////////////////

# Understanding legacy Microsoft Component Object Model (COM) developement

## Introduction
[Microsoft Component Object Model (COM)](https://learn.microsoft.com/en-us/windows/win32/com/component-object-model--com--portal) is a standard provided by Microsoft to handle the [Application Binary Interface (ABI)](https://en.wikipedia.org/wiki/Application_binary_interface).

COM has been around for over 20 years and remains a critical component in building the Windows kernel and many foundational applications. The [windows-rs](https://github.com/microsoft/windows-rs) project also supports COM to facilitate interaction with the Windows OS. Despite its age, COM is expected to persist in lower-level systems.

Due to its low-level nature and legacy status, Microsoft provides libraries such as the [Active Template Library (ATL)](https://learn.microsoft.com/zh-tw/cpp/atl/introduction-to-atl) and the [Windows Implementation Libraries (WIL)](https://github.com/microsoft/wil) to simplify working with COM objects. Although Microsoft aims to abstract native COM operations, the underlying design and implementation remain unchanged.

In this repository, I will provide a native COM implementation and explain how it works step-by-step. Additionally, I will demonstrate how the Windows-provided headers in kernel mode assist in building a COM-based interface.

## COM Interface

## Vtable
To understand COM, you need to know how virtual tables are created in C++. If you just want a quick understanding of COM, consider the example below:
```cpp
#include <iostream>

class Human {
 public:
  virtual void Eat() = 0;
  virtual void WakeUp() { 
    std::cout << "WakeUp!\n";
  };
};

class MySon : public Human {
  void Eat() {
    std::cout << "MySon Eat.\n";
  };
};

class Dog {
 public:
  virtual void Jump() = 0;
};

int main(){ 
	MySon son;
	auto dog = (Dog*)(void*)&son;
    dog->Jump(); // Call MySon::Eat()
	return 0; 
}
```

This will compiles and prints `"MySon Eat."` in the terminal. The key to this behavior lies in how virtual functions are called. Unlike regular(non-virtual) member functions, which are called by name, virtual functions are called based on their position in the vtable. This means the order of virtual functions affects the result. Since both `Eat()` and `Jump()` are the first virtual functions in their respective classes, they occupy the same vtable slot. If you swap `Eat()` and `WakeUp()` in Human, then `WakeUp()` will be called instead.

The vtable of `MySon` looks like this:  
```
vtable for MySon:
        .quad   0 // offset for adjust "this" pointer
        .quad   typeinfo for MySon // typeinfo for RTTI usage
        .quad   MySon::Eat() // virtual function 1
        .quad   Human::WakeUp() // virtual function 2
```

The `Dog` class is not related to `Human` or `MySon` through inheritance. However, if we forcefully cast an instance of `MySon` to `Dog`, calling `Jump()` will actually call `MySon::Eat()`. This happens because both functions are the first virtual function in their respective classes and occupy the same position in the vtable.  

This idea is a key part of how COM was implemented to support objects with multiple interfaces or aggregated interfaces. It also explains why Microsoft named one of its core interfaces `INonDelegatingUnknown`. The **"NonDelegating"** part means that the class does **not** inherit directly from `IUnknown`, but can still be cast and called through an interface with a different name.  

I recommend reading `Inside the C++ Object Model` if you want to go deeper into how C++ works at a lower level. It's an amazing resource.

## MACROS
Microsoft provided several macros for us, primarily used to simplify the definition of COM interfaces, ensuring compliance with the standard ABI (Application Binary Interface) while improving readability and portability.
The detail are explained in header files of this repo. Check our example.

## CUknown