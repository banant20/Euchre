// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player* alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;

    Player* anant = Player_factory("Anant", "Human");
    Player* meehir = Player_factory("Meehir", "Simple");
    ASSERT_EQUAL("Anant", anant->get_name());
    ASSERT_EQUAL("Meehir", meehir->get_name());

    delete anant;
    delete meehir;
}

TEST(test_player_insertion) {
    Player* human = Player_factory("Anant", "Human");
    ostringstream oss;
    oss << *human;
    ASSERT_EQUAL(oss.str(), "Anant");
    oss.str("");
    Player* alice = Player_factory("Meehir", "Simple");
    oss << *alice;
    ASSERT_EQUAL(oss.str(), "Meehir");
    delete alice;
    delete human;
}

static void add_cards(Player* player) {
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    for (int i = 0; i < 5; ++i) {
        player->add_card(two_spades);
    }
}

TEST(test_simple_make_trump) {
    Player* Meehir = Player_factory("Meehir", "Simple");
    add_cards(Meehir);

    Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
    string trump = Card::SUIT_SPADES;
    bool orderup = Meehir->make_trump(jack_spades, true, 1, trump);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, Card::SUIT_SPADES);

    delete Meehir;
}

TEST(test_simple_make_trump2) {
    Player* Meehir = Player_factory("Meehir", "Simple");
    Meehir->add_card(Card("Nine", "Clubs"));
    Meehir->add_card(Card("Nine", "Hearts"));
    Meehir->add_card(Card("Nine", "Diamonds"));
    Meehir->add_card(Card("Ten", "Diamonds"));
    Meehir->add_card(Card("Nine", "Spades"));
    Card one("Ace", "Diamonds");
    string suit = "Diamonds";
    bool orderup = Meehir->make_trump(one, false, 2, suit);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(suit, "Diamonds");
    delete Meehir;
}

TEST(test_simple_make_trump3) {
    Player* Meehir = Player_factory("Meehir", "Simple");
    Meehir->add_card(Card("Nine", "Clubs"));
    Meehir->add_card(Card("Queen", "Hearts"));
    Meehir->add_card(Card("Nine", "Diamonds"));
    Meehir->add_card(Card("Queen", "Diamonds"));
    Meehir->add_card(Card("Jack", "Spades"));
    Card one("Ace", "Diamonds");
    string suit = "Diamonds";
    bool orderup = Meehir->make_trump(one, false, 2, suit);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(suit, "Hearts");
    delete Meehir;
}

TEST(test_simple_make_trump4) {
    Player* Meehir = Player_factory("Meehir", "Simple");
    Meehir->add_card(Card("Jack", "Clubs"));
    Meehir->add_card(Card("Ten", "Hearts"));
    Meehir->add_card(Card("Nine", "Diamonds"));
    Meehir->add_card(Card("Ace", "Diamonds"));
    Meehir->add_card(Card("Jack", "Spades"));
    Card one("Nine", "Spades");
    string suit = "Hearts";
    bool orderup = Meehir->make_trump(one, false, 1, suit);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(suit, "Spades");
    delete Meehir;
}

TEST(test_simple_make_trump5) {
    Player* Meehir = Player_factory("Meehir", "Simple");
    Meehir->add_card(Card("King", "Clubs"));
    Meehir->add_card(Card("Ten", "Hearts"));
    Meehir->add_card(Card("Ace", "Clubs"));
    Meehir->add_card(Card("Ace", "Diamonds"));
    Meehir->add_card(Card("Jack", "Spades"));
    Card one("Nine", "Clubs");
    string suit = "Diamonds";
    bool orderup = Meehir->make_trump(one, false, 1, suit);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(suit, "Clubs");
    delete Meehir;
}

TEST(test_simple_make_trump6) {
    Player* Meehir = Player_factory("Meehir", "Simple");
    Meehir->add_card(Card("Nine", "Clubs"));
    Meehir->add_card(Card("Ten", "Hearts"));
    Meehir->add_card(Card("Nine", "Diamonds"));
    Meehir->add_card(Card("Queen", "Diamonds"));
    Meehir->add_card(Card("Jack", "Spades"));
    Card one("Ace", "Hearts");
    string suit = "Diamonds";
    bool orderup = Meehir->make_trump(one, true, 1, suit);
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(suit, "Diamonds");
    delete Meehir;
}

TEST(test_simple_make_trump7) {
    Player* Meehir = Player_factory("Meehir", "Simple");
    Meehir->add_card(Card("Nine", "Clubs"));
    Meehir->add_card(Card("Nine", "Hearts"));
    Meehir->add_card(Card("Nine", "Diamonds"));
    Meehir->add_card(Card("Ten", "Diamonds"));
    Meehir->add_card(Card("Nine", "Spades"));
    Card one("Ace", "Diamonds");
    string suit = "Diamonds";
    bool orderup = Meehir->make_trump(one, true, 2, suit);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(suit, "Hearts");
    delete Meehir;
}

TEST(test_simple_add_discard) {
    Card twocl("Two", "Clubs");
    Card twodi("Two", "Diamonds");
    Card twosp("Two", "Spades");
    Card twohe("Two", "Hearts");
    string di = "Diamonds";
    string cl = "Clubs";
    string sp = "Spades";
    string he = "Hearts";
    Card ten_clubs("Ten", "Clubs");
    Card queen_diamonds("Queen", "Diamonds");
    Card jack_clubs("Jack", "Clubs");

    Player* Anant = Player_factory("Anant", "Simple");
    Anant->add_card(queen_diamonds);
    Anant->add_card(jack_clubs);
    Anant->add_and_discard(ten_clubs);
    Card next = Anant->play_card(twohe, he);

    ASSERT_EQUAL(next, ten_clubs);

    next = Anant->play_card(twohe, he);

    ASSERT_EQUAL(next, jack_clubs);

    delete Anant;
}

TEST(test_simple_play_card) {
    Card twocl("Two", "Clubs");
    Card twodi("Two", "Diamonds");
    Card twosp("Two", "Spades");
    Card twohe("Two", "Hearts");
    string di = "Diamonds";
    string cl = "Clubs";
    string sp = "Spades";
    string he = "Hearts";
    Card jack_diamonds("Jack", "Diamonds");
    Card nine_spades("Nine", "Spades");
    Card jack_hearts("Jack", "Hearts");
    Card ace_diamonds("Ace", "Diamonds");
    Card ten_spades("Ten", "Spades");

    Player* Meehir = Player_factory("Meehir", "Simple");
    Meehir->add_card(ten_spades);
    Meehir->add_card(jack_diamonds);
    Meehir->add_card(jack_hearts);
    Meehir->add_card(nine_spades);
    Meehir->add_card(ace_diamonds);
    Card next = Meehir->play_card(twosp, di);

    ASSERT_EQUAL(next, ten_spades);

    next = Meehir->play_card(twodi, di);

    ASSERT_EQUAL(next, jack_diamonds);

    next = Meehir->play_card(twosp, di);

    ASSERT_EQUAL(next, nine_spades);

    Meehir->add_card(ace_diamonds);
    next = Meehir->play_card(twosp, sp);

    ASSERT_EQUAL(next, jack_hearts);

    next = Meehir->play_card(twosp, he);

    ASSERT_EQUAL(next, ace_diamonds);

    delete Meehir;
}

TEST(test_simple_lead_card) {
    Card twocl("Two", "Clubs");
    Card twodi("Two", "Diamonds");
    Card twosp("Two", "Spades");
    Card twohe("Two", "Hearts");
    string di = "Diamonds";
    string cl = "Clubs";
    string sp = "Spades";
    string he = "Hearts";
    Player* Meehir = Player_factory("Meehir", "Simple");
    Card three_clubs("Three", "Clubs");
    Card ten_hearts("Ten", "Hearts");
    Card jack_clubs("Jack", "Clubs");
    Meehir->add_card(three_clubs);
    Meehir->add_card(ten_hearts);
    Meehir->add_card(jack_clubs);

    Card next = Meehir->lead_card(cl);

    ASSERT_EQUAL(next, ten_hearts);

    Meehir->add_card(ten_hearts);
    next = Meehir->lead_card(di);

    ASSERT_EQUAL(next, jack_clubs);

    next = Meehir->lead_card(di);

    ASSERT_EQUAL(next, ten_hearts);

    Meehir->add_card(jack_clubs);
    Meehir->add_card(ten_hearts);
    next = Meehir->lead_card(cl);

    ASSERT_EQUAL(next, ten_hearts);

    next = Meehir->lead_card(he);

    ASSERT_EQUAL(next, jack_clubs);

    next = Meehir->lead_card(cl);

    ASSERT_EQUAL(next, three_clubs);

    delete Meehir;
}


// Add more tests here

TEST_MAIN()
