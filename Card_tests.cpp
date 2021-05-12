// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_suit) {
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(nine_spades.get_suit(), Card::SUIT_SPADES);

    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(), Card::SUIT_SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(Card::SUIT_HEARTS), Card::SUIT_SPADES);
}

TEST(test_get_rank) {
    Card two_spades;
    Card ten_diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card queen_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    
    ASSERT_EQUAL(Card::RANK_TWO, two_spades.get_rank());
    ASSERT_EQUAL(Card::RANK_TEN, ten_diamonds.get_rank());
    ASSERT_EQUAL(Card::RANK_QUEEN, queen_clubs.get_rank());
    ASSERT_EQUAL(Card::RANK_JACK, jack_hearts.get_rank());
}

TEST(test_get_suit_with_trump) {
    Card queen_spades(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
    
    ASSERT_EQUAL(Card::SUIT_SPADES, queen_spades.get_suit(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_HEARTS, jack_hearts.get_suit(Card::SUIT_HEARTS));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, jack_hearts.get_suit(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(Card::SUIT_CLUBS, jack_clubs.get_suit(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::SUIT_SPADES, jack_clubs.get_suit(Card::SUIT_SPADES));
    
}

TEST(test_card_is_right_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);

    ASSERT_TRUE(c.is_right_bower(Card::SUIT_CLUBS));
}

TEST(test_card_is_left_bower) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);

    ASSERT_TRUE(c.is_left_bower(Card::SUIT_DIAMONDS));
}

TEST(test_card_is_trump) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);

    ASSERT_TRUE(c.is_trump(Card::SUIT_CLUBS));
    ASSERT_FALSE(c.is_trump(Card::SUIT_HEARTS));
}

TEST(test_card_is_face) {
    Card c(Card::RANK_JACK, Card::SUIT_CLUBS);

    ASSERT_TRUE(c.is_face());
}

TEST(test_Suit_next) {
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS), Card::SUIT_DIAMONDS);
}

TEST(test_card_less1) {
    Card three_spades = Card(Card::RANK_THREE, Card::SUIT_SPADES);
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(three_spades, nine_spades, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(nine_spades, three_spades, three_spades,
        Card::SUIT_CLUBS));
}

TEST(test_card_less2) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(jack_clubs, jack_spades, ace_hearts, Card::SUIT_HEARTS));
}

TEST(test_card_less3) {
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card nine_diamonds = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(nine_spades, nine_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Card_less(nine_diamonds, nine_spades, ace_spades, Card::SUIT_DIAMONDS));
}

TEST(test_card_less4) {
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card ace_diamonds = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ace_diamonds, nine_spades, Card::SUIT_SPADES));
    ASSERT_FALSE(Card_less(nine_spades, ace_diamonds, ace_spades, Card::SUIT_SPADES));
}

TEST(test_card_less5) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, jack_spades, Card::SUIT_SPADES));
}

TEST(test_card_less6) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ace_spades, jack_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(ace_spades, jack_diamonds, jack_spades, Card::SUIT_HEARTS));
}

TEST(test_card_less7) {
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    Card jack_clubs = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card ace_spades = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(ace_spades, jack_clubs, jack_spades, Card::SUIT_SPADES));
}

TEST(test_card_less8) {
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card ace_hearts = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(ace_hearts, jack_hearts, jack_hearts, Card::SUIT_HEARTS));
}

TEST(test_card_less9) {
    Card queen_hearts = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card jack_diamonds = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card jack_hearts = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card two_spades = Card(Card::RANK_TWO, Card::SUIT_SPADES);
    Card two_diamonds(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card two_clubs(Card::RANK_TWO, Card::SUIT_CLUBS);
    Card two_hearts(Card::RANK_TWO, Card::SUIT_HEARTS);

    ASSERT_TRUE(Card_less(jack_diamonds, jack_hearts, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(jack_diamonds, jack_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(jack_diamonds, queen_hearts, Card::SUIT_CLUBS));
    ASSERT_FALSE(Card_less(jack_diamonds, jack_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(jack_diamonds, two_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(queen_hearts, two_spades, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(queen_hearts, jack_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(queen_hearts, jack_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(jack_hearts, jack_diamonds, Card::SUIT_DIAMONDS));
    ASSERT_TRUE(Card_less(two_spades, queen_hearts, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(two_spades, jack_diamonds, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(two_spades, queen_hearts, Card::SUIT_HEARTS));
    ASSERT_FALSE(Card_less(jack_diamonds, queen_hearts, two_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(queen_hearts, jack_diamonds, two_diamonds, Card::SUIT_SPADES));
    ASSERT_TRUE(Card_less(queen_hearts, jack_hearts, two_diamonds, Card::SUIT_HEARTS));
    ASSERT_TRUE(Card_less(jack_hearts, queen_hearts, two_spades, Card::SUIT_CLUBS));
    ASSERT_TRUE(Card_less(jack_hearts, queen_hearts, two_hearts, Card::SUIT_CLUBS));
}

TEST(test_card_insertion) {
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    ostringstream oss;
    oss << nine_spades;
    ASSERT_EQUAL(oss.str(), "Nine of Spades");
}

TEST(test_card_comparison) {
    Card nine_spades = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    Card jack_spades = Card(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_TRUE(nine_spades < jack_spades);
    ASSERT_TRUE(nine_spades <= nine_spades);
    ASSERT_FALSE(nine_spades > jack_spades);
    ASSERT_TRUE(nine_spades == nine_spades);
    ASSERT_TRUE(nine_spades != jack_spades);
}

TEST_MAIN()
