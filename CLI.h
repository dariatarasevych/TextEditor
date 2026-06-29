#ifndef ASSIGNMENT_4_CLI_H
#define ASSIGNMENT_4_CLI_H

#include "TextEditor.h"

class CLI {
private:
    TextEditor& editor;
    void printMenu() const;
public:
    CLI(TextEditor& textEditor);
    void Run();
};

#endif //ASSIGNMENT_4_CLI_H
