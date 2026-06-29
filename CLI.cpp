#include "CLI.h"
#include <iostream>
#include <string>

CLI::CLI(TextEditor &text_editor) : editor(text_editor) {}

void CLI::printMenu() const {
    std::cout << "\n================= TEXT EDITOR MENU =================\n";
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
    std::cout << "========================================================\n";
    std::cout << "Enter your choice: ";
}

void CLI::Run() {
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;
    }
}

