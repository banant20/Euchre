// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card() : rank(RANK_TWO), suit(SUIT_SPADES) {}

Card::Card(const std::string& rank_in, const std::string& suit_in) {
    assert(rank_in == RANK_TWO || rank_in == RANK_THREE ||
        rank_in == RANK_FOUR || rank_in == RANK_FIVE ||
        rank_in == RANK_SIX || rank_in == RANK_SEVEN ||
        rank_in == RANK_EIGHT || rank_in == RANK_NINE ||
        rank_in == RANK_TEN || rank_in == RANK_JACK ||
        rank_in == RANK_QUEEN || rank_in == RANK_KING ||
        rank_in == RANK_ACE);
    assert(suit_in == SUIT_SPADES || suit_in == SUIT_HEARTS ||
        suit_in == SUIT_CLUBS || suit_in == SUIT_DIAMONDS);

    rank = rank_in;
    suit = suit_in;

}

std::string Card::get_rank() const {
    return rank;
}

std::string Card::get_suit() const {
    return suit;
}

std::string Card::get_suit(const std::string& trump) const {
    if (get_rank() == RANK_JACK && get_suit() == Suit_next(trump)) {
        return trump;
    }
    else {
        return suit;
    }
}

bool Card::is_face() const {
    if (get_rank() == RANK_JACK || get_rank() == RANK_QUEEN ||
        get_rank() == RANK_KING || get_rank() == RANK_ACE) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string& trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS || trump == SUIT_SPADES
        || trump == SUIT_DIAMONDS);

    if (get_rank() == RANK_JACK && get_suit() == trump) {
        return true;
    }
    else {
        return false;
    }

}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string& trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS || trump == SUIT_SPADES
        || trump == SUIT_DIAMONDS);

    if (get_rank() == RANK_JACK && get_suit() == Suit_next(trump)) {
        return true;
    }
    else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string& trump) const {
    assert(trump == SUIT_CLUBS || trump == SUIT_HEARTS || trump == SUIT_SPADES
        || trump == SUIT_DIAMONDS);

    if (get_suit(trump) == trump || is_left_bower(trump)) {
        return true;
    }
    else {
        return false;
    }
}


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


bool operator<(const Card& lhs, const Card& rhs) {
    int lval = 0;
    int rval = 0;
    int rsuit = 0;
    int lsuit = 0;

    for (int i = 0; i < NUM_SUITS; ++i) {
        if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
            lsuit = i;
        }
        if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) {
            rsuit = i;
        }
    }
    for (int i = 0; i < NUM_RANKS; i++) {
        if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            lval = i;
        }
        if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) {
            rval = i;
        }
    }
    if (lval == rval) {
        if (lsuit < rsuit) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (lval < rval) {
        return true;
    }
    else {
        return false;
    }
}




bool operator==(const Card& lhs, const Card& rhs) {
    return ((lhs.get_rank() == rhs.get_rank() &&
        lhs.get_suit() == rhs.get_suit()));
}

bool operator<=(const Card& lhs, const Card& rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Card& lhs, const Card& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Card& lhs, const Card& rhs) {
    return ((lhs > rhs) || (lhs == rhs));
}

bool operator!=(const Card& lhs, const Card& rhs) {
    return !(lhs == rhs);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string& suit) {
    assert(suit == Card::SUIT_CLUBS || suit == Card::SUIT_HEARTS ||
        suit == Card::SUIT_SPADES || suit == Card::SUIT_DIAMONDS);

    if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    }
    else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    }
    else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    }
    else {
        return Card::SUIT_CLUBS;
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const std::string& trump) {
    assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_HEARTS ||
        trump == Card::SUIT_SPADES || trump == Card::SUIT_DIAMONDS);

    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (a.is_right_bower(trump)) {
            return false;
        }
        else if (b.is_right_bower(trump)) {
            return true;
        }
        else if (a.is_left_bower(trump)) {
            return false;
        }
        else if (b.is_left_bower(trump)) {
            return true;
        }
        else {
            return a < b;
        }
    }
    else if (!(a.is_trump(trump)) && b.is_trump(trump)) {
        return true;
    }
    else if (a.is_trump(trump) && !(b.is_trump(trump))) {
        return false;
    }
    else {
        return a < b;
    }
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const Card& led_card,
    const std::string& trump) {
    
    if (a.is_right_bower(trump)) {
            return false;
        }
    else if (b.is_right_bower(trump)) {
            return true;
        }
    else if (a.is_left_bower(trump)) {
            return false;
        }
    else if (b.is_left_bower(trump)) {
            return true;
        }
    
    else if (a.is_trump(trump) && !b.is_trump(trump)) {
        return false;
    }
    else if (!a.is_trump(trump) && b.is_trump(trump)) {
        return true;
    }
    else if (a.get_suit() == led_card.get_suit() &&
             b.get_suit() != led_card.get_suit()) {
        return false;
    }
    else if (a.get_suit() != led_card.get_suit() &&
             b.get_suit() == led_card.get_suit()) {
        return true;
    }
    else {
        if (a.get_suit() == led_card.get_suit() &&
            b.get_suit() == led_card.get_suit()) {
            
            if (a < b) {
                return true;
            }
            return false;
        }
        else if (a.get_suit() == led_card.get_suit() &&
                 b.get_suit() != led_card.get_suit()) {
            return false;
        }
        else if (a.get_suit() != led_card.get_suit() &&
                 b.get_suit() == led_card.get_suit()) {
            return true;
        }
        else {
            if (a < b) {
                return true;
            }
            return false;
        }
    }
}
    
