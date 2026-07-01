# Report
**Topic:** Text Editor with Typed Rows and Encryption Feature (Object-Oriented Programming).

**Course:** Programming Languages: Principles and Paradigms

**Student:** Tarasevych Daria.

---

## 1. Introduction:
The purpose of this assignment is to gain experience in programming using an object-oriented paradigm by upgrading a text editor program with new functions, 
including one that use a encryption/decryption algorithm. The upgrade contains the code in object-oriented style.

## 2. Architectural Design & Paradigms:
The system is built entirely on the Object-Oriented Programming (OOP) paradigm, decoupling the core data structures, state management, and user interaction layers:

* Data Representation Layer (`Line`, `TextLine`, `CheckListLine`, `ContactLine`): Implements a polymorphic hierarchy to handle different semantic types of text rows.
* Logic Layer (`TextEditor`): This is the core of the app where all the main operations happen. It manages the array of lines, handles clipboard actions (copy, cut, and paste text), and converts the editor's content into a text format for saving to a file and loading it back.
* State & History Management (`Undo` / `Redo`): This module is responsible for reversing and reapplying user actions. Every time a change is made, the program automatically takes a "snapshot" of the current text and pushes it into a history stacks (std::stack). When the user choose Undo or Redo, the editor simply retrieves the correct snapshot from the stack and restores the text to that exact moment.
* Dynamic Cryptography: An isolated bridge class inside the main app that contains no actual encryption logic. Instead, it interacts with the operating system's API (<dlfcn.h>) to load and unload the shared library at runtime.
* Shared Library (libcipher.dylib): A separate build target containing the actual compiled OOP hierarchy for the ciphers, hidden behind an extern "C" binary export layer.
* Presentation Layer (`CLI`): An isolated interactive interface routing user decisions into actions, separating user interaction from core text processing.

## 3. Implementation of OOP:
The project demonstrates the core principles of Object-Oriented Programming:

* Encapsulation: Classes strictly protect their state. For example, `TextLine` hides its `std::string text` under the private modifier, forcing external access through explicit getters and setters (`getText()`, `setText()`).
* **Inheritance:**
  
  - Inheritance is used to establish a clear code hierarchy, promoting reuse and defining common behaviors for specialized sub-types. Instead of creating isolated, redundant classes for different types of text rows and   encryption methods, the architecture relies on base abstract classes that act as strict contracts.
  - Line Hierarchy: The abstract base class `Line` defines a pure virtual interface with `virtual void print() const = 0;` and `virtual std::string serialize() const = 0;`. The concrete classes `TextLine`, `CheckListLine`, and `ContactLine` inherit from `Line`. This ensures that regardless of their internal fields (e.g., CheckListLine tracking a bool checked status, or ContactLine containing three distinct string components), they all strictly conform to the same interface.
  - Cryptography Hierarchy: Similarly, the abstract class `Cipher` defines the pure virtual methods for `encrypt()` and `decrypt()`. The specialized sub-classes `CaesarCipher` (handling integer-shift key logic) and VigenereCipher (handling keyword shift logic) extend `Cipher`. This allows the text editor to encrypt and decrypt files without needing to know how the underlying math or cipher algorithms actually work.

* **Polymorphism:**
 - Polymorphism is the core mechanism that provides the text editor with its dynamic flexibility, allowing the system to treat different object types through a single interface.
 - The TextEditor iterates through a vector of `Line*` pointers. When rendering the document or saving it to disk, it executes `line->print()` or `line->serialize()`, triggering the correct concrete behavior dynamically.
 - When the main text editor passes an opaque pointer `(cipher_t*)` back into the dynamic library, the library's exported C-functions cast it back to the base abstract class `(Cipher*)`. When `obj->encrypt()` is called, C++'s internal vtable automatically routes the execution to either `CaesarCipher::encrypt` or `VigenereCipher::encrypt` based on the underlying object instance allocated in the library's heap space.

## 4. Conclusion:
The developed text editor successfully demonstrates the practical application of the Object-Oriented Programming paradigm to build a flexible and modular system. By designing a strict hierarchy of polymorphic data types (Line, TextLine, CheckListLine, ContactLine), the system achieves a clear separation of concerns, where the core application logic handles document structure uniformly without relying on hardcoded row implementations.

Furthermore, hiding the cryptographic classes (CaesarCipher and VigenereCipher) behind an abstract runtime interface showcases the power of encapsulation and polymorphism. The text editor is completely decoupled from specific mathematical details, interacting only with a generalized contract. Ultimately, this OOP-driven architecture ensures excellent codebase maintainability, enabling developers to scale data formats or add new specialized cipher types seamlessly without modifying the core text processing engine.
