#include "TextEditor.h"
#include <list>
#include <string>
#include <unordered_map>

struct TextEditorInternal {
    std::list<char> text;
    std::list<char>::iterator cursor;
    TextEditorInternal() : text(), cursor(text.begin()) {}
};

// One internal storage per TextEditor instance
static std::unordered_map<const TextEditor*, TextEditorInternal> editorRepo;

static TextEditorInternal& ensureInternal(const TextEditor* editor) {
    auto it = editorRepo.find(editor);
    if (it == editorRepo.end()) {
        auto res = editorRepo.emplace(editor, TextEditorInternal());
        res.first->second.cursor = res.first->second.text.begin();
        return res.first->second;
    }
    return it->second;
}

void TextEditor::insertChar(char c) {
    TextEditorInternal& ed = ensureInternal(this);
    ed.cursor = ed.text.insert(ed.cursor, c);
    ++ed.cursor;
}

void TextEditor::deleteChar() {
    TextEditorInternal& ed = ensureInternal(this);
    if (ed.cursor == ed.text.begin()) return;

    auto it = ed.cursor;
    --it;
    ed.cursor = ed.text.erase(it);

    if (ed.cursor != ed.text.end()) {
        ed.text.erase(ed.cursor, ed.text.end());
    }

    ed.cursor = ed.text.end();
}

void TextEditor::moveLeft() {
    TextEditorInternal& ed = ensureInternal(this);
    if (ed.cursor != ed.text.begin()) --ed.cursor;
}

void TextEditor::moveRight() {
    TextEditorInternal& ed = ensureInternal(this);
    if (ed.cursor != ed.text.end()) ++ed.cursor;
}

std::string TextEditor::getTextWithCursor() const {
    const TextEditorInternal& ed = ensureInternal(this);
    std::string out;
    for (auto it = ed.text.begin(); it != ed.text.end(); ++it) {
        if (it == ed.cursor) out.push_back('|');
        out.push_back(*it);
    }
    if (ed.cursor == ed.text.end()) out.push_back('|');
    return out;
}
