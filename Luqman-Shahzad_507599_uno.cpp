#include "UNO.h"
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <sstream>
#include <map>

struct CardInternal {
    std::string color;
    std::string value;
    CardInternal() : color(""), value("") {}
    CardInternal(const std::string &c, const std::string &v) : color(c), value(v) {}
};

class UNOGameInternal {
public:
    std::vector<CardInternal> deck;
    std::vector<std::vector<CardInternal>> players;
    std::vector<CardInternal> discardPile;
    int currentPlayer = 0;
    bool clockwise = true;
    int numPlayers;
    int winner = -1;
    std::mt19937 rng;

    UNOGameInternal(int n) : numPlayers(n), rng(1234) {}

    void buildDeck() {
        deck.clear();
        std::vector<std::string> colors = {"Red", "Green", "Blue", "Yellow"};
        std::vector<std::string> values = {"0","1","2","3","4","5","6","7","8","9"};
        std::vector<std::string> actions = {"Skip","Reverse","Draw Two"};

        for (const auto &c : colors) {
            deck.emplace_back(c, "0");
            for (int i = 1; i <= 9; ++i) {
                deck.emplace_back(c, values[i]);
                deck.emplace_back(c, values[i]);
            }
            for (const auto &a : actions) {
                deck.emplace_back(c, a);
                deck.emplace_back(c, a);
            }
        }
    }

    void shuffleDeck() {
        std::shuffle(deck.begin(), deck.end(), rng);
    }

    void dealCards() {
        players.assign(numPlayers, {});
        for (int i = 0; i < 7; ++i) {
            for (int p = 0; p < numPlayers; ++p) {
                if (deck.empty()) break;
                players[p].push_back(deck.back());
                deck.pop_back();
            }
        }
        if (!deck.empty()) {
            discardPile.push_back(deck.back());
            deck.pop_back();
        }
    }

    bool isPlayable(const CardInternal &top, const CardInternal &card) const {
        return (card.color == top.color || card.value == top.value);
    }

    bool isAction(const CardInternal &c) const {
        return c.value == "Skip" || c.value == "Reverse" || c.value == "Draw Two";
    }

    int nextIndex(int step = 1) const {
        int dir = clockwise ? 1 : -1;
        int next = (currentPlayer + dir * step + numPlayers) % numPlayers;
        return next;
    }

    void applyAction(const CardInternal &c) {
        if (c.value == "Reverse") {
            clockwise = !clockwise;
            currentPlayer = nextIndex(1);
        } else if (c.value == "Skip") {
            currentPlayer = nextIndex(2);
        } else if (c.value == "Draw Two") {
            int target = nextIndex(1);
            for (int i = 0; i < 2 && !deck.empty(); ++i) {
                players[target].push_back(deck.back());
                deck.pop_back();
            }
            currentPlayer = nextIndex(2);
        } else {
            currentPlayer = nextIndex(1);
        }
    }

    bool checkGameOver() {
        for (int i = 0; i < numPlayers; ++i) {
            if (players[i].empty()) {
                winner = i;
                return true;
            }
        }
        return false;
    }

    std::string getState() const {
        std::ostringstream out;
        out << "Player " << currentPlayer
            << "'s turn, Direction: " << (clockwise ? "Clockwise" : "Counter-clockwise")
            << ", Top: ";
        if (!discardPile.empty())
            out << discardPile.back().color << " " << discardPile.back().value;
        else
            out << "None";

        out << ", Players cards: ";
        for (int i = 0; i < numPlayers; ++i) {
            if (i > 0) out << ", ";
            out << "P" << i << ":" << players[i].size();
        }
        return out.str();
    }

    void playTurn() {
        if (winner != -1) return;
        auto &hand = players[currentPlayer];
        if (hand.empty()) return;

        CardInternal top = discardPile.back();
        bool played = false;
        size_t idx = 0;

        // Try to find a playable card (color or value match)
        for (size_t i = 0; i < hand.size(); ++i) {
            if (isPlayable(top, hand[i])) {
                idx = i;
                played = true;
                break;
            }
        }

        // If none playable, draw one
        if (!played && !deck.empty()) {
            hand.push_back(deck.back());
            deck.pop_back();
            for (size_t i = 0; i < hand.size(); ++i) {
                if (isPlayable(top, hand[i])) {
                    idx = i;
                    played = true;
                    break;
                }
            }
        }

        if (played) {
            CardInternal playedCard = hand[idx];
            hand.erase(hand.begin() + idx);
            discardPile.push_back(playedCard);
            applyAction(playedCard);
        } else {
            currentPlayer = nextIndex(1);
        }

        checkGameOver();
    }
};

// Map UNOGame* → UNOGameInternal*
static std::map<const UNOGame*, UNOGameInternal*> unoRepo;

UNOGame::UNOGame(int numPlayers) {
    unoRepo[this] = new UNOGameInternal(numPlayers);
}

void UNOGame::initialize() {
    auto g = unoRepo[this];
    g->buildDeck();
    g->shuffleDeck();
    g->dealCards();
}

void UNOGame::playTurn() {
    unoRepo[this]->playTurn();
}

bool UNOGame::isGameOver() const {
    return unoRepo.at(this)->checkGameOver();
}

int UNOGame::getWinner() const {
    return unoRepo.at(this)->winner;
}

std::string UNOGame::getState() const {
    return unoRepo.at(this)->getState();
}
