# Report
**Topic:** Text Editor with Typed Rows and Encryption Feature (Object-Oriented Programming).

**Cours:** Programming Languages: Principles and Paradigms

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
* Cryptography Layer (`Cipher`, `CaesarCipher`, `VigenereCipher`): Provides encryption and decryption algorithms.
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
 - 
  

## 4. Bug Fixing & Lessons Learned:

## 5. Test Plan & Execution Results:

## 6. Conclusion:
