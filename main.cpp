#include <iostream>
#include "Polynomial.h"
#include "TextEditor.h"
#include "UNO.h"

int main() {
    // ---------------- POLYNOMIAL ----------------
    Polynomial p1;
    p1.insertTerm(3, 4);
    p1.insertTerm(2, 2);
    p1.insertTerm(-1, 1);
    p1.insertTerm(5, 0);

    Polynomial p2;
    p2.insertTerm(1, 4);
    p2.insertTerm(1, 0);

    Polynomial sum = p1.add(p2);

    Polynomial p3;
    p3.insertTerm(2, 1);

    Polynomial prod = sum.multiply(p3);
    Polynomial deriv = p1.derivative();

    std::cout << "p1.toString(): " << p1.toString() << std::endl;
    std::cout << "sum.toString(): " << sum.toString() << std::endl;
    std::cout << "prod.toString(): " << prod.toString() << std::endl;
    std::cout << "deriv.toString(): " << deriv.toString() << std::endl << std::endl;

    // ---------------- TEXT EDITOR ----------------
    TextEditor ed;
    ed.insertChar('a');
    std::cout << "After insert 'a': " << ed.getTextWithCursor() << std::endl;
    ed.insertChar('b');
    std::cout << "After insert 'b': " << ed.getTextWithCursor() << std::endl;
    ed.moveLeft();
    std::cout << "After move left: " << ed.getTextWithCursor() << std::endl;
    ed.insertChar('c');
    std::cout << "After insert 'c': " << ed.getTextWithCursor() << std::endl;
    ed.deleteChar();
    std::cout << "After delete: " << ed.getTextWithCursor() << std::endl;
    ed.moveLeft();
    ed.moveLeft();
    std::cout << "After move left twice: " << ed.getTextWithCursor() << std::endl;
    ed.moveRight();
    ed.moveRight();
    std::cout << "After move right twice: " << ed.getTextWithCursor() << std::endl << std::endl;

    // ---------------- UNO GAME ----------------
    UNOGame game(2);
    game.initialize();  // fixed seed inside implementation

    std::cout << game.getState() << std::endl;
    game.playTurn();
    std::cout << game.getState() << std::endl;
    game.playTurn();
    std::cout << game.getState() << std::endl;
    game.playTurn();
    std::cout << game.getState() << std::endl;

    return 0;
}
