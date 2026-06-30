#include <iostream>

#include "CLI.h"
#include "TextEditor.h"

int main() {
    TextEditor editor;
    CLI cli(editor);
    cli.Run();
    return 0;
}
