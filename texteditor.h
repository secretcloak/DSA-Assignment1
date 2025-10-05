#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>

class TextEditor {
public:
    virtual ~TextEditor() = default;

    // Insert character at cursor
    virtual void insertChar(char c);

    // Delete character before cursor
    virtual void deleteChar();

    // Move cursor one position left
    virtual void moveLeft();

    // Move cursor one position right
    virtual void moveRight();

    // Return string with cursor position
    virtual std::string getTextWithCursor() const;
};

#endif
