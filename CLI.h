#ifndef ASSIGNMENT_4_CLI_H
#define ASSIGNMENT_4_CLI_H

#include "TextEditor.h"

class CLI {
private:
    TextEditor& text_editor;
    void printMenu() const;
public:
    CLI(TextEditor& text_editor);
    void Run();
};

#endif //ASSIGNMENT_4_CLI_H
