#include "TextEditor.h"

#include <iostream>
#include <sstream>
#include <fstream>

TextEditor::TextEditor() {
    lines = nullptr;
    line_counter = 0;
    clipboard = "";

    appendLine(new TextLine(""));
}
TextEditor::~TextEditor() {
    clearLines();
}

void TextEditor::clearLines() {
    if (lines != nullptr) {
        for (int i = 0; i < line_counter; i++) {
            delete lines[i];
        }
        free(lines);
        lines = nullptr;
        line_counter = 0;
    }
}

//Add new object (TextLine, ChecklistLine or ContactLine)
void TextEditor::appendLine(Line *newLine) {
    line_counter++;

    Line** temp_lines = (Line**) realloc(lines, (line_counter) * sizeof(Line*));

    if (temp_lines == nullptr) {
        std::cout << "Error! Memory allocation failed." << std::endl;
        delete newLine;
        exit(1);
    }
    lines = temp_lines;
    lines[line_counter - 1] = newLine;
}

//Print whole text
void TextEditor::printAll() const {
    if (line_counter == 0) {
        std::cout << "Text is empty." << std::endl;
        return;
    }

    for (int i = 0; i < line_counter; i++) {
        lines[i] -> print();
    }
}

void TextEditor::appendTextToLastLine(const std::string &text) {
    if (line_counter == 0) {
        std::cout << "Text is empty." << std::endl;
        return;
    }

    Line* last_line = lines[line_counter - 1];
    TextLine* textLine = dynamic_cast<TextLine *>( last_line); //check if line type is TextLine

    if (textLine != nullptr) {
        std::string current_text = textLine -> getText();
        textLine -> setText(current_text + text);
    } else {
        std::cout << "Error! Cannot append text because this line type is CheckListLine or ContactLine" << std::endl;
    }
}

void TextEditor::searchInText(const std::string &inputToSearch) const {
    if (line_counter == 0) {
        std::cout << "Text is empty." << std::endl;
        return;
    }

    bool is_in_text = false;

    for (int i = 0; i < line_counter; i++) {
        std::string current_text = lines[i] -> serialize();

        size_t foundSymbol_s = current_text.find(inputToSearch);

        while (foundSymbol_s != std::string::npos) {
            std::cout << "Text is present in position: " << i << " " << foundSymbol_s << std::endl;
            is_in_text = true;

            foundSymbol_s = current_text.find(inputToSearch, foundSymbol_s + 1);
        }
    }

    if (!is_in_text) {
        std::cout << "Text/symbol not found." << std::endl;
    }
}

void TextEditor::insertText(int lineIndex, int charIndex, const std::string &text) {
    if (lineIndex < 0 || lineIndex >= line_counter) {
        std::cout << "Invalid line index." << std::endl;
        return;
    }

    Line* baseLine = lines[lineIndex];
    TextLine* textLine = dynamic_cast<TextLine *> (baseLine);

    if (textLine == nullptr) {
        std::cout << "Error. This type does not have insertion function" << std::endl;
        return;
    }

    std::string s = textLine ->getText();

    if (charIndex < 0 || charIndex > s.length()) {
        std::cout << "Invalid char index." << std::endl;
        return;
    }

    s.insert(charIndex, text);

    textLine -> setText(s);
    std::cout << "Text inserted!" << std::endl;
}

void TextEditor::insertWithReplacement(int lineIndex, int charIndex, const std::string &text) {
    if (lineIndex < 0 || lineIndex >= line_counter) {
        std::cout << "Invalid line index." << std::endl;
        return;
    }

    Line* baseLine = lines[lineIndex];
    TextLine* textLine = dynamic_cast<TextLine *> (baseLine);

    if (textLine == nullptr) {
        std::cout << "Error. This type does not have insertion function" << std::endl;
        return;
    }

    std::string s = textLine ->getText();

    if (charIndex < 0 || charIndex > s.length()) {
        std::cout << "Invalid char index." << std::endl;
        return;
    }

    int countToReplace = text.length();

    if ((charIndex + countToReplace) > s.length()) {
        countToReplace = s.length() - charIndex;
    }

    s.replace(charIndex, countToReplace, text);

    textLine -> setText(s);

    std::cout << "Text inserted with replacement!" << std::endl;
}

void TextEditor::deleteText(int lineIndex, int charIndex, int count) {
    if (lineIndex < 0 || lineIndex >= line_counter) {
        std::cout << "Invalid line index." << std::endl;
        return;
    }

    Line* baseLine = lines[lineIndex];
    TextLine* textLine = dynamic_cast<TextLine *> (baseLine);

    if (textLine == nullptr) {
        std::cout << "Error. This type does not have delete function" << std::endl;
        return;
    }

    std::string s = textLine ->getText();

    if (charIndex < 0 || charIndex > s.length()) {
        std::cout << "Invalid char index." << std::endl;
        return;
    }

    if (count < 0) {
        std::cout << "Number of symbols to delete must be more then 0." << std::endl;
        return;
    }

    if ((charIndex + count) > s.length()) {
        count = s.length() - charIndex;
    }

    s.erase(charIndex, count);

    textLine -> setText(s);

    std::cout << "Deleted successfully!" << std::endl;
}

void TextEditor::copyText(int lineIndex, int charIndex, int count) {
    if (lineIndex < 0 || lineIndex >= line_counter) {
        std::cout << "Invalid line index." << std::endl;
        return;
    }

    Line* baseLine = lines[lineIndex];
    TextLine* textLine = dynamic_cast<TextLine *> (baseLine);

    if (textLine == nullptr) {
        std::cout << "Error. This type does not have copy function" << std::endl;
        return;
    }

    std::string s = textLine -> getText();

    if (charIndex < 0 || charIndex > s.length()) {
        std::cout << "Invalid char index." << std::endl;
        return;
    }

    if (count < 0) {
        std::cout << "Number of symbols to copy must be more then 0." << std::endl;
        return;
    }

    if ((charIndex + count) > s.length()) {
        count = s.length() - charIndex;
    }

    clipboard = s.substr(charIndex, count); //substr() бере копію шматка довжиною count, починаючи з charIndex

    textLine -> setText(s);

    std::cout << "Copied successfully!" << std::endl;
}

void TextEditor::pasteText(int lineIndex, int charIndex) {
    if (clipboard.empty()) {
        std::cout << "Clipboard is empty!" << std::endl;
        return;
    }

    if (lineIndex < 0 || lineIndex >= line_counter) {
        std::cout << "Invalid line index." << std::endl;
        return;
    }

    Line* baseLine = lines[lineIndex];
    TextLine* textLine = dynamic_cast<TextLine *> (baseLine);

    if (textLine == nullptr) {
        std::cout << "Error. This type does not have paste function" << std::endl;
        return;
    }

    std::string s = textLine -> getText();

    if (charIndex < 0 || charIndex > s.length()) {
        std::cout << "Invalid char index." << std::endl;
        return;
    }

    s.insert(charIndex, clipboard);

    textLine ->setText(s);

    std::cout << "Pasted successfully!" << std::endl;
}

void TextEditor::cutText(int lineIndex, int charIndex, int count) {
    copyText(lineIndex, charIndex, count);
    deleteText(lineIndex, charIndex, count);
}

std::string TextEditor::serializeAll() const {
    std::string result = "";

    for (int i = 0; i < line_counter; i++) {
        result += lines[i] ->serialize() + '\n';
    }
    return result;
}

void TextEditor::deserializeAll(const std::string &sourceText) {
    std::stringstream sT(sourceText);
    std::string tempLine;

    while (std::getline(sT, tempLine)) {
        if (tempLine[0] == 'T') {
            std::string pureText = tempLine.substr(2);
            Line* newLine = new TextLine(pureText);
            appendLine(newLine);
        }

        else if (tempLine[0] == 'C') {
            std::string body = tempLine.substr(2);
            bool is_checked = (body[0] == '1');
            std::string bodyTaskText = body.substr(2);
            Line* newLine = new CheckListLine(bodyTaskText, is_checked);
            appendLine(newLine);
        }

        else if (tempLine[0] == 'I') {
            std::string body = tempLine.substr(2);
            std::stringstream contactStream(body);
            std::string firstName, lastName, email;

            std::getline(contactStream, firstName, ':');
            std::getline(contactStream, lastName, ':');
            std::getline(contactStream, email);

            Line* newLine = new ContactLine(firstName, lastName, email);
            appendLine(newLine);
        }
    }
}

void TextEditor::saveSnapshot() {
    std::string currentText = serializeAll();
    undo_stack.push(currentText);
    redo_stack = std::stack<std::string>();
}

void TextEditor::undo() {
    if (undo_stack.empty()) {
        std::cout << "Nothing to undo." << std::endl;
        return;
    }

    redo_stack.push(serializeAll());

    std::string oldState = undo_stack.top();
    undo_stack.pop();

    clearLines();

    deserializeAll(oldState);

    std::cout << "Undo successfully!" << std::endl;
}

void TextEditor::redo() {
    if (redo_stack.empty()) {
        std::cout << "Nothing to redo." << std::endl;
        return;
    }

    undo_stack.push(serializeAll());

    std::string oldState = redo_stack.top();
    redo_stack.pop();

    clearLines();

    deserializeAll(oldState);

    std::cout << "Redo successfully!" << std::endl;
}

void TextEditor::saveToFile(const std::string &fileName) {
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
        std::cout << "Error! Cannot open file to save: " << fileName << std::endl;
        return;
    }

    outFile << serializeAll();

    outFile.close();
}

void TextEditor::loadFromFile(const std::string &fileName) {
    std::ifstream inFile(fileName);

    if (!inFile.is_open()) {
        std::cout << "Error! Cannot open file to load: " << fileName << std::endl;
        return;
    }

    clearLines();

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();

    inFile.close();
    deserializeAll(fileContent);
}

void TextEditor::saveToFileEncrypted(const std::string &fileName, Cipher *cipher) {
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
        std::cout << "Error! Cannot open file to save: " << fileName << std::endl;
        return;
    }

    std::string encrypted = cipher -> encrypt(serializeAll());

    outFile << encrypted;

    outFile.close();
}

void TextEditor::loadFromFileDecrypted(const std::string &fileName, Cipher *cipher) {
    std::ifstream inFile(fileName);

    if (!inFile.is_open()) {
        std::cout << "Error! Cannot open file to load: " << fileName << std::endl;
        return;
    }

    clearLines();

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();

    std::string decrypted = cipher -> decrypt(fileContent);

    inFile.close();

    deserializeAll(decrypted);
}