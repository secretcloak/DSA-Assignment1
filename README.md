# DSA-Assignment1

Name: Luqman Shahzad
CMS : 507599
Course: Data Structures & Algorithms
Assignment: #1

 Overview

This project implements three independent modules that demonstrate the use of dynamic data structures (mainly linked lists and maps) in C++ through object-oriented programming principles.

The three main components are:

Polynomial

Text Editor

UNO Game Simulation

Each component uses an internal data structure to manage its state efficiently, focusing on operations that require dynamic insertion, deletion, and traversal.

 Approach
1. Polynomial

Implemented using a std::map<int, int>, where the key is the exponent and the value is the coefficient.

Supports:

Insertion of new terms

Addition and multiplication of polynomials

Derivative calculation

String conversion for display

Using std::map ensures terms remain sorted and easy to merge or iterate over.

2. Text Editor

Uses a std::list<char> to represent text, allowing efficient character insertion and deletion in O(1) time.

A cursor is maintained using a list iterator, simulating editor movement (moveLeft, moveRight).

The internal logic allows printing text with the cursor symbol (|) to visualize editing behavior.

Mimics a simple text editing buffer, demonstrating linked list operations.

3. UNO Game

Implements a simplified UNO game simulation.

Uses vectors for deck management and per-player hands.

Handles action cards (Skip, Reverse, Draw Two) and turn order logic (clockwise or counter-clockwise).

Shuffling is done using a fixed seed (1234) for deterministic, testable results.

Tracks player states, top card, and winner status.

Each class is defined in its .h header and implemented in a separate .cpp file.
Since constructors could not be modified, internal states are managed via static maps that associate each class instance with its internal data.

 Sample Output
Polynomial
p1.toString(): 3x^4 + 2x^2 - x + 5
sum.toString(): 4x^4 + 2x^2 - x + 6
prod.toString(): 8x^5 + 4x^3 - 2x^2 + 12x
deriv.toString(): 12x^3 + 4x - 1

Text Editor
After insert 'a': a|
After insert 'b': ab|
After move left: a|b
After insert 'c': ac|b
After delete: a|
After move left twice: |a
After move right twice: a|

UNO Game

(Output may vary due to randomness, but simulates real UNO logic)

Player 0's turn, Direction: Clockwise, Top: Blue 3, Players cards: P0:7, P1:7
Player 1's turn, Direction: Clockwise, Top: Blue 8, Players cards: P0:7, P1:6
Player 0's turn, Direction: Clockwise, Top: Yellow 8, Players cards: P0:6, P1:6
Player 0's turn, Direction: Clockwise, Top: Yellow Skip, Players cards: P0:5, P1:6

 Challenges Faced

Could not modify constructors — solved by using static repository patterns (std::unordered_map) to store per-instance data.

Handling cursor movement and deletion correctly in the TextEditor required precise iterator logic.

UNO’s random shuffle and action card logic required multiple iterations to simulate realistic gameplay.

Ensuring all modules are independent yet behave consistently under strict constraints.

 How to Compile & Run

Compile:

g++ main.cpp Polynomial.cpp TextEditor.cpp UNO.cpp -o Assignment1


Run:

./Assignment1

GitHub Repository:

https://github.com/secretcloak/DSA-Assignment1
