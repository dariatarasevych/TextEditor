#ifndef ASSIGNMENT_4_TEXTEDITOR_H
#define ASSIGNMENT_4_TEXTEDITOR_H

#include "Line.h"
#include <stack>

class TextEditor {
private:
    Line** lines;
    int line_counter;

    std::string clipboard;

    std::stack<std::string> undo_stack;
    std::stack<std::string> redo_stack;

    void saveSnapshot();
    void clearLines();

public:
    TextEditor();
    ~TextEditor();

    void appendLine(Line* newLine);
    void appendTextToLastLine(const std::string& text) ;
    void printAll() const;

    void insertText(int lineIndex, int charIndex, const std::string& text);
    void insertWithReplacement(int lineIndex, int charIndex, const std::string& text);
    void deleteText(int lineIndex, int charIndex, int count);
    void searchInText(const std::string& inputToSearch) const;

    //clipboard
    void copyText(int lineIndex, int charIndex, int count);
    void pasteText(int lineIndex, int charIndex);
    void cutText(int lineIndex, int charIndex, int count);

    void undo();
    void redo();

    std::string serializeAll() const;
    void deserializeAll(const std::string& sourceText);

    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);
};

#endif //ASSIGNMENT_4_TEXTEDITOR_H
