// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Card.h"

using namespace std;

class Simple : public Player {
public:
    Simple(const string& name_in)
        : name(name_in) {}

    const string& get_name() const {
        return name;
    }

    void add_card(const Card& c) {
        if (cards.size() < MAX_HAND_SIZE) {
            cards.push_back(c);
        }

    }

    bool make_trump(const Card& upcard, bool is_dealer,
            int round, std::string& order_up_suit) const {
        
        bool makesTrump = true;
        
        if (round == 1) {
            int num = 0;
            string upcard_suit = upcard.get_suit();
            
            for (int i = 0; i < MAX_HAND_SIZE; ++i) {
                if (cards[i].is_face() && cards[i].is_trump(upcard_suit)) {
                    ++num;
                }
            }
            
            if (num <= 1) {
                makesTrump = false;
            }
            else {
                order_up_suit = upcard.get_suit();
                makesTrump = true;
            }
        }
        else if (round == 2 && !is_dealer) {
                int temp = 0;
                string next = Suit_next(upcard.get_suit());
                
                for (int i = 0; i < MAX_HAND_SIZE; ++i) {
                    if (cards[i].is_face() && cards[i].is_trump(next)) {
                        ++temp;
                    }
                }
                if (0 < temp) {
                    order_up_suit = next;
                    makesTrump = true;
                }
                else {
                    makesTrump = false;
                }
            }
        else {
            string next = Suit_next(upcard.get_suit());
            order_up_suit = next;
            makesTrump = true;
        }
        
        return makesTrump;
    }

    void add_and_discard(const Card& upcard) {
        cards.push_back(upcard);
        int min = 0;
        
        for (int i = 1; i < cards.size(); ++i) {
            if (Card_less(cards[i], cards[min], upcard.get_suit())) {
                min = i;
            }
        }
        cards.erase(cards.begin() + min);
    }

    Card lead_card(const string& trump) {
        bool temp = false;
        for (auto &index : cards) {
            if (!index.is_trump(trump)) {
                temp = true;
            }
        }
            if (temp == true) {
              int max = 0;
              for (int i = 1; i < cards.size(); ++i) {
                if ((!Card_less(cards[i], cards[max], trump) &&
                     !cards[i].is_trump(trump)) ||
                    (cards[max].is_trump(trump) && !cards[i].is_trump(trump))) {
                  max = i;
                }
              }
                Card card = cards[max];
                cards.erase(cards.begin() + max);
                return card;
            }
            else {
              int max = 0;
              for (int i = 1; i < cards.size(); i++) {
                  if (!Card_less(cards[i], cards[max], trump)) {
                  max = i;
                }
              }
                Card card = cards[max];
                cards.erase(cards.begin() + max);
                return card;
            }
    }

    Card play_card(const Card& led_card, const string& trump) {
        int num = 0;
        string led_suit = led_card.get_suit();
        
        if (led_card.is_left_bower(trump) || led_card.is_trump(trump)) {
            for (int i = 0; i < cards.size(); ++i) {
                if (cards[i].is_trump(trump)) {
                    ++num;
                }
            }
        }
        else {
            for (int i = 0; i < cards.size(); ++i) {
                if (!(cards[i].is_left_bower(trump)) &&
                    cards[i].get_suit() == led_suit) {
                    ++num;
                }
            }
        }
        if (num > 0) {
            int max = 0;
            for (int i = 1; i < cards.size(); i++) {
                if ((Card_less(cards[max], cards[i], led_card, trump) &&
                    cards[i].get_suit(trump) == led_card.get_suit(trump)) ||
                    (cards[max].get_suit(trump) != led_card.get_suit(trump) &&
                    cards[i].get_suit(trump) == led_card.get_suit(trump))) {
                        max = i;
                }
            }
            
            Card card = cards[max];
            cards.erase(cards.begin() + max);
            return card;
        }
        else {
            int min = 0;
            for (int i = 1; i < cards.size(); i++) {
                if (Card_less(cards[i], cards[min], led_card, trump)) {
                    min = i;
                }
            }
            Card card = cards[min];
            cards.erase(cards.begin() + min);
            return card;
        }
    }

private:
    string name;
    vector<Card> cards;
};

class Human : public Player {
public:
    Human(const string& name_in)
        : name(name_in) {}

    const string& get_name() const {
        return name;
    }

    void add_card(const Card& c) {
        cards.push_back(c);
        sort(cards.begin(), cards.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const {
        int size = cards.size();
        string option;

        for (int i = 0; i < size; i++) {
            cout << "Human player" << " " << name << "'s hand: [" << i << "] " <<
                cards[i] << endl;
        }
        cout << "Human player" << " " << name << ", please enter a suit, or \"pass\":"
            << endl;
        cin >> option;

        if (option.compare("pass") == 0) {
            return false;
        }
        else {
            order_up_suit = option;
            return true;
        }
    }

    void add_and_discard(const Card& upcard) {
        int size = cards.size();
        int garbage;
        cards.push_back(upcard);

        for (int i = 0; i < size; i++) {
            cout << "Human player" << " " << name << "'s hand: [" << i << "] " <<
                cards[i] << endl;
        }
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player" << " " << name << ", please select a card to discard:"
            << endl;
        cin >> garbage;

        if (garbage != -1) {
            Card index = cards[garbage];
            cards[garbage] = upcard;
            sort(cards.begin(), cards.begin() + size);
            cards.pop_back();
        }
    }

    Card lead_card(const string& trump) {
        int size = cards.size();
        int game;
        sort(cards.begin(), cards.end());

        for (int i = 0; i < size; i++) {
            cout << "Human player" << " " << name << "'s hand: [" << i << "] " <<
                cards[i] << endl;
        }
        cout << "Human player" << " " << name << ", please select a card:" << endl;
        cin >> game;


        Card index = cards[game];
        cards[game] = cards[size - 1];
        cards[size - 1] = index;
        cards.pop_back();
        return index;
    }

    Card play_card(const Card& led_card, const std::string& trump) {
        int sizes = cards.size();
        int games;
        sort(cards.begin(), cards.end());

        for (int j = 0; j < sizes; j++) {
            cout << "Human player" << " " << name << "'s hand: [" << j << "] " <<
                cards[j] << endl;
        }
        cout << "Human player" << " " << name << ", please select a card:" << endl;
        cin >> games;

        Card index = cards[games];
        cards[games] = cards[sizes - 1];
        cards[sizes - 1] = index;
        cards.pop_back();
        return index;
    }
private:
    string name;
    vector<Card> cards;
};

Player* Player_factory(const std::string& name, const std::string& strategy) {
    if (strategy.compare("Human") == 0) {
        return new Human(name);
    }
    if (strategy.compare("Simple") == 0) {
        return new Simple(name);
    }
    cout << "Invalid strategy" << endl;
    assert(false);
    return nullptr;
}

ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.get_name();
    return os;
}
