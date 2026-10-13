/**
 * Purpose: Capture and restore an object's internal state without exposing its implementation unnecessarily.
    
    Typical participants:
    - Originator — owns the state.
    - Memento — stores a snapshot.
    - Caretaker — manages saved snapshots.
*/

// Memento pattern: a text editor with undo.
//
// Three roles:
//   Editor   (originator)  - the object whose state we want to save/restore
//   Memento  (snapshot)    - a stored copy of the editor's state
//   History  (caretaker)   - keeps the snapshots, but never looks inside them

#include <iostream>
#include <string>
#include <vector>

class Editor;  // forward declaration so Memento can name it as a friend

// The snapshot. Its contents are private, so only the Editor can read them.
class Memento {
    friend class Editor;  // only the Editor may create and read a Memento

    Memento(const std::string &text, int cursor) : text(text), cursor(cursor) {}

    std::string text;
    int cursor;
};

// The originator: it creates snapshots of itself and can restore from them.
class Editor {
public:
    void type(const std::string &s) {
        text += s;
        cursor = static_cast<int>(text.size());
    }

    Memento save() const { return Memento(text, cursor); }  // take a snapshot

    void restore(const Memento &m) {                        // go back to a snapshot
        text = m.text;
        cursor = m.cursor;
    }

    void print() const { std::cout << "\"" << text << "\" (cursor at " << cursor << ")\n"; }

private:
    std::string text;
    int cursor = 0;
};

// The caretaker: stores snapshots in a stack and hands the latest one back on undo.
class History {
public:
    void push(const Memento &m) { snapshots.push_back(m); }

    bool undo(Editor &editor) {
        if (snapshots.empty())
            return false;                  // nothing left to undo
        editor.restore(snapshots.back());  // restore the most recent snapshot
        snapshots.pop_back();
        return true;
    }

private:
    std::vector<Memento> snapshots;
};

    Editor editor;
    History history;

    history.push(editor.save());  // snapshot BEFORE each change
    editor.type("Hello");
    editor.print();               // "Hello"

    history.push(editor.save());
    editor.type(", world");
    editor.print();               // "Hello, world"

    history.push(editor.save());
    editor.type("!!!");
    editor.print();               // "Hello, world!!!"

    std::cout << "--- undo ---\n";
    history.undo(editor);
    editor.print();               // "Hello, world"

    history.undo(editor);
    editor.print();               // "Hello"

    history.undo(editor);
    editor.print();               // "" (back to the start)

    if (!history.undo(editor))
        std::cout << "Nothing left to undo\n";
}