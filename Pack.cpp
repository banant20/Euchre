// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <cmath>
#include "Pack.h"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    next = 0;
    int count = 0;
    
    for (int i = 0; i < NUM_SUITS; ++i) {
        for (int j = 0; j < 6; ++j) {
            const char *rank = RANK_NAMES_BY_WEIGHT[7 + j];
            const char *suit = SUIT_NAMES_BY_WEIGHT[i];
            cards[count] = Card(rank, suit);
            ++count;
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    next = 0;
    std::string garbage;
    std::string rank;
    std::string suit;
    
    for (int i = 0; pack_input >> rank; ++i) {
        pack_input >> garbage;
        pack_input >> suit;
        cards[i] = Card(rank, suit);
    }
    reset();
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    int temp = next;
    next++;
    return cards[temp];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    Card top[12];
    Card bot[12];
    
    
    for (int i = 0; i < 7; ++i) {
        for (int x = 0; x < 12; ++x) {
            bot[x] = cards[x];
        }
        for (int y = 12; y < 24; ++y) {
            top[y - 12] = cards[y];
        }
        for (int j = 0; j < PACK_SIZE; ++j) {
            if (j % 2 == 0) {
                cards[j] = top[(j / 2)];
            }
            else {
                cards[j] = bot[(j / 2)];
            }
        }
    }
    reset();
}


// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next > 23) {
        return true;
    }
    else {
        return false;
    }
}
