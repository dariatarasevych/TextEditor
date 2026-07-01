#include "CLI.h"
#include <iostream>
#include <string>
#include <limits>
#include "Cipher.h"

CLI::CLI(TextEditor &text_editor) : editor(text_editor) {}

void CLI::printMenu() const {
    std::cout << "\n------------------ TEXT EDITOR MENU ------------------\n";
    std::cout << "1 - Print all lines (printAll)\n";
    std::cout << "2 - Append new line (appendLine)\n";
    std::cout << "3 - Append text to the last line (appendTextToLastLine)\n";
    std::cout << "4 - Insert text (insertText)\n";
    std::cout << "5 - Insert text with replacement (insertWithReplacement)\n";
    std::cout << "6 - Delete text (deleteText)\n";
    std::cout << "7 - Copy text to clipboard (copyText)\n";
    std::cout << "8 - Cut text to clipboard (cutText)\n";
    std::cout << "9 - Paste text from clipboard (pasteText)\n";
    std::cout << "10 - Search in text (searchInText)\n";
    std::cout << "11 - Undo\n";
    std::cout << "12 - Redo\n";
    std::cout << "13 - Save to file(Usual text)\n";
    std::cout << "14 - Load from file (Usual text)\n";
    std::cout << "15 - Save to file (Encrypted text)\n";
    std::cout << "16 - Load from file (Decrypted text)\n";
    std::cout << "0 - Exit\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Enter your choice: ";
}

void CLI::Run() {
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::cout << "Current text:" << std::endl;
                editor.printAll();
                break;
            }

            case 2: {
                std::cout << "Enter line type (1 - Text Line, 2 - Check List Line, 3 - Contact Line): ";
                int type;
                std::cin >> type;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (type == 1) {
                    std::cout << "Enter text: ";
                    std::string text;
                    std::getline(std::cin, text);

                    editor.appendLine(new TextLine(text));
                    std::cout << "Text Line added.\n";
                }

                else if (type == 2) {
                    std::cout << "Enter text: ";
                    std::string text;
                    std::getline(std::cin, text);

                    std::cout << "Is it checked? (1 - yes, 0 - no): ";
                    bool is_checked;
                    std::cin >> is_checked;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    editor.appendLine(new CheckListLine(text, is_checked));
                    std::cout << "Check List Line added.\n";
                }

                else if (type == 3) {
                    std::string firstName, lastName, email;
                    std::cout << "Enter First Name: ";
                    std::getline(std::cin, firstName);
                    std::cout << "Enter Last Name: ";
                    std::getline(std::cin, lastName);
                    std::cout << "Enter email: ";
                    std::getline(std::cin, email);

                    editor.appendLine(new ContactLine(firstName, lastName, email));
                    std::cout << "Contact Line added.\n";
                }
                break;
            }

            case 3: {
                std::cout << "Enter text to append to the last line: ";
                std::string text;
                std::getline(std::cin, text);

                editor.appendTextToLastLine(text);
                break;
            }

            case 4: {
                int lineIndex, charIndex;
                std::string text;
                std::cout << "Enter line index to insert text: ";
                std::cin >> lineIndex;
                std::cout << "Enter char index: ";
                std::cin >> charIndex;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter text to insert: ";
                std::getline(std::cin, text);

                editor.insertText(lineIndex, charIndex, text);
                break;
            }

            case 5: {
                int lineIndex, charIndex;
                std::string text;
                std::cout << "Enter line index to insert text: ";
                std::cin >> lineIndex;
                std::cout << "Enter char index: ";
                std::cin >> charIndex;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter text to replace: ";
                std::getline(std::cin, text);

                editor.insertWithReplacement(lineIndex, charIndex, text);
                break;
            }

            case 6: {
                int lineIndex, charIndex, count;
                std::cout << "Enter line index to delete text: ";
                std::cin >> lineIndex;
                std::cout << "Enter char index: ";
                std::cin >> charIndex;
                std::cout << "Enter number of symbols to delete: ";
                std::cin >> count;

                editor.deleteText(lineIndex, charIndex, count);
                break;
            }

            case 7: {
                int lineIndex, charIndex, count;
                std::cout << "Enter line index to copy text: ";
                std::cin >> lineIndex;
                std::cout << "Enter char index: ";
                std::cin >> charIndex;
                std::cout << "Enter number of symbols to copy: ";
                std::cin >> count;

                editor.copyText(lineIndex, charIndex, count);
                break;
            }

            case 8: {
                int lineIndex, charIndex, count;
                std::cout << "Enter line index to cut text: ";
                std::cin >> lineIndex;
                std::cout << "Enter char index: ";
                std::cin >> charIndex;
                std::cout << "Enter number of symbols to cut: ";
                std::cin >> count;

                editor.cutText(lineIndex, charIndex, count);
                break;
            }

            case 9: {
                int lineIndex, charIndex;
                std::cout << "Enter line index to paste text: ";
                std::cin >> lineIndex;
                std::cout << "Enter char index: ";
                std::cin >> charIndex;

                editor.pasteText(lineIndex, charIndex);
                break;
            }

            case 10: {
                std::cout << "Enter text to search: ";
                std::string text;
                std::getline(std::cin, text);

                editor.searchInText(text);
                break;
            }

            case 11: {
                editor.undo();
                break;
            }

            case 12: {
                editor.redo();
                break;
            }

            case 13: {
                std::string fileName;
                std::cout << "Enter file name to save to: ";
                std::getline(std::cin, fileName);

                editor.saveToFile(fileName);
                std::cout << "Saved successfully.\n";
                break;
            }

            case 14: {
                std::string fileName;
                std::cout << "Enter file name to load from: ";
                std::getline(std::cin, fileName);

                editor.loadFromFile(fileName);
                std::cout << "Load successfully.\n";
                break;
            }

            case 15: {
                std::string fileName;
                std::cout << "Enter file name to save (encrypted): ";
                std::getline(std::cin, fileName);

                std::cout << "Enter cipher type (1 - Caesar, 2 - Vigenere): ";
                int type;
                std::cin >> type;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Cipher* cipher = nullptr;

                if (type == 1) {
                    int key;
                    std::cout << "Enter Caesar key: ";
                    std::cin >> key;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    Cipher cipher(1, key, "");
                }
                else if (type == 2) {
                    std::string key;
                    std::cout << "Enter Vigenere key word: ";
                    std::getline(std::cin, key);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    Cipher cipher(2, 0, key);
                }

                if (cipher != nullptr) {
                    editor.saveToFileEncrypted(fileName, cipher);
                    delete cipher;
                    std::cout << "File was saved and encrypted.\n";
                }else {
                    std::cout << "Invalid selection of cipher type.\n";
                }
                break;
            }

            case 16: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string fileName;
                std::cout << "Enter file name to load (decrypted): ";
                std::getline(std::cin, fileName);

                std::cout << "Enter cipher type (1 - Caesar, 2 - Vigenere): ";
                int type;
                std::cin >> type;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Cipher* cipher = nullptr;

                if (type == 1) {
                    int key;
                    std::cout << "Enter Caesar key: ";
                    std::cin >> key;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    cipher = new Cipher(1, key, "");
                }

                else if (type == 2) {
                    std::string key;
                    std::cout << "Enter Vigenere key word: ";
                    std::getline(std::cin, key);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    cipher = new Cipher(2, 0, key);
                }

                if (cipher != nullptr) {
                    editor.loadFromFileDecrypted(fileName, cipher);
                    delete cipher;

                    std::cout << "File was loaded and decrypted.\n";
                }else {
                    std::cout <<"Invalid selection of cipher type.\n";
                }
                break;
            }

            case 0: {
                std::cout << "Exiting TextEditor. Goodbye!\n";
                return;
            }

            default:
                std::cout << "Unknown command. Try again.\n";
                break;
        }
    }
}

