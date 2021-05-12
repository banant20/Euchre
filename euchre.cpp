// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
#include "Player.h"
#include "Card.h"
#include "Pack.h"

using namespace std;

class Euchre {
private:
    vector <Player*> players;
    Pack pack;
    int team_1_score = 0;
    int team_2_score = 0;
    int team_1_tricks = 0;
    int team_2_tricks = 0;
    int winner = 0;
    int player_ordered_up = 0;
    string trump;
    Card led;
    Card played;
    Card highest;
    Card upcard;

public:
    Euchre(Player* one, Player* two, Player* three, Player* four) {
        players = { one, two, three, four };
    }

    int get_player_ordered_up() {
        return player_ordered_up;
    }

    int get_team_ordered_up() {
        if (player_ordered_up == 0 || player_ordered_up == 2) {
            return 1;
        }
        else {
            return 2;
        }
    }

    int get_team_1_score() {
        return team_1_score;
    }

    int get_team_2_score() {
        return team_2_score;
    }

    string get_player_name(int index) {
        return players.at(index)->get_name();
    }

    string get_team1_names() {
        return get_player_name(0) + " and " + get_player_name(2);
    }

    string get_team2_names() {
        return get_player_name(1) + " and " + get_player_name(3);
    }

    Card get_upcard() {
        return upcard;
    }

    void shuffle() {
        pack.shuffle();
    }

    void deal_two_cards(Player* player) {
        player->add_card(pack.deal_one());
        player->add_card(pack.deal_one());
    }

    void deal_three_cards(Player* player) {
        player->add_card(pack.deal_one());
        player->add_card(pack.deal_one());
        player->add_card(pack.deal_one());
    }
    

    void deal_to_players(int dealer) {
        pack.reset();

        cout << players[dealer]->get_name() << " " << "deals" << endl;

        deal_three_cards(players.at((dealer + 1) % 4));
        deal_two_cards(players.at((dealer + 2) % 4));
        deal_three_cards(players.at((dealer + 3) % 4));
        deal_two_cards(players.at(dealer));

        deal_two_cards(players.at((dealer + 1) % 4));
        deal_three_cards(players.at((dealer + 2) % 4));
        deal_two_cards(players.at((dealer + 3) % 4));
        deal_three_cards(players.at(dealer));

        upcard = pack.deal_one();
        cout << upcard << " " << "turned up" << endl;
    }



    string makeTrump(int dealer, const Card upcard) {
        
        for (int i = 1; i < 2; ++i) {
            for (int j = 1; j < 5; ++j) {
                if (players.at((dealer + j) % 4)->make_trump(upcard, i == 4, i, trump)) {
                    player_ordered_up = (dealer + j) % 4;
                    cout << players.at((dealer + j) % 4)->get_name() << " orders up "
                    << trump << endl;
                    players.at(dealer)->add_and_discard(upcard);
                    return trump;
                }
                cout << players.at((dealer + j) % 4)->get_name() << " passes" << endl;
            }
        }
        return trump;
    }
    
    void trick_score(int winner) {
        if (winner == 0 || winner == 2) {
            ++team_1_tricks;
        }

        else if (winner == 1 || winner == 3) {
            ++team_2_tricks;
        }
    }

    
    void trick_taking(int dealer, int eldest) {
        int leader = eldest;
        team_1_tricks = 0;
        team_2_tricks = 0;
           
        for (int i = 0; i < 5; ++i) {
            if (i == 0) {
                Card ledCard = players[eldest]->lead_card(trump);
                cout << ledCard << " led by " <<
                players[eldest]->get_name() << endl;
                highest = ledCard;
                winner = eldest;
                   
                   
                Card cardSecond =
                players[(eldest + 1) % 4]->play_card(ledCard, trump);
                cout << cardSecond << " played by " <<
                players[(eldest + 1) % 4]->get_name() << endl;

                if (Card_less(highest, cardSecond, ledCard, trump)) {
                    highest = cardSecond;
                    winner = (eldest + 1) % 4;
                }
                   
                   
                   
                Card cardThird =
                players[(eldest + 2) % 4]->play_card(ledCard, trump);
                cout << cardThird << " played by " <<
                players[(eldest + 2) % 4]->get_name() << endl;

                if (Card_less(highest, cardThird, ledCard, trump)) {
                    highest = cardThird;
                    winner = (eldest + 2) % 4;
                }
                   
                   
                   
                Card cardFourth =
                players[(eldest + 3) % 4]->play_card(ledCard, trump);
                cout << cardFourth << " played by " <<
                players[(eldest + 3) % 4]->get_name() << endl;

                if (Card_less(highest, cardFourth, ledCard, trump)) {
                    highest = cardFourth;
                    winner = dealer;
                }

                trick_score(winner);
            }
            else {
                leader = winner;
                Card ledCard = players[leader]->lead_card(trump);
                cout << ledCard << " led by " << players[leader]->get_name()
                << endl;
                highest = ledCard;
                            
                            
                Card cardSecond =
                players[(leader + 1) % 4]->play_card(ledCard, trump);
                cout << cardSecond << " played by " <<
                players[(leader + 1) % 4]->get_name() << endl;
                            
                if (Card_less(highest, cardSecond, ledCard, trump)) {
                    highest = cardSecond;
                    winner = (leader + 1) % 4;
                    
                }
                            
                Card cardThird =
                players[(leader + 2) % 4]->play_card(ledCard, trump);
                cout << cardThird << " played by " <<
                players[(leader + 2) % 4]->get_name() << endl;

                if (Card_less(highest, cardThird, ledCard, trump)) {
                    highest = cardThird;
                    winner = (leader + 2) % 4;
                    
                }
                            
                Card cardFourth =
                players[(leader + 3) % 4]->play_card(ledCard, trump);
                cout << cardFourth << " played by " <<
                players[(leader + 3) % 4]->get_name() << endl;

                if (Card_less(highest, cardFourth, ledCard, trump)) {
                    highest = cardFourth;
                    winner = (leader + 3) % 4;
                    
                }
                trick_score(winner);
            }
            cout << players.at(winner)->get_name() << " takes the trick" << endl
            << endl;
        }
    }

    void euchre_scoring() {
        if (team_1_tricks > team_2_tricks) {
            if (get_team_ordered_up() == 1) {
                if (team_1_tricks == 5) {
                    team_1_score += 2;
                    cout << get_team1_names() << " win the hand" << endl;
                    cout << "march!" << endl;
                }
                else {
                    team_1_score += 1;
                    cout << get_team1_names() << " win the hand" << endl;
                }
            }
            else  {
                team_1_score += 2;
                cout << get_team1_names() << " win the hand" << endl;
                cout << "euchred!" << endl;
            }
        }
        if (team_2_tricks > team_1_tricks) {
            if (get_team_ordered_up() == 2) {
                if (team_2_tricks == 5) {
                    team_2_score += 2;
                    cout << get_team2_names() << " win the hand" << endl;
                    cout << "march!" << endl;
                }
                else {
                    team_2_score += 1;
                    cout << get_team2_names() << " win the hand" << endl;
                }
            }
            else {
                team_2_score += 2;
                cout << get_team2_names() << " win the hand" << endl;
                cout << "euchred!" << endl;
            }
        }
        cout << get_team1_names() << " have " << team_1_score << " points" << endl;
        cout << get_team2_names() << " have " << team_2_score << " points" << endl
            << endl;
    }

    void findWinner() {
        if (get_team_1_score() > get_team_2_score()) {
            cout << get_team1_names() << " win!" << endl;
        }
        else {
            cout << get_team2_names() << " win!" << endl;
        }
    }
    
    int winning_score() {
        if (team_1_score > team_2_score) {
            return team_1_score;
        }
        else {
            return team_2_score;
        }
    }
    
    void print_error_message() {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
    }

    void delete_euchre_players() {
        for (int i = 0; i < int(players.size()); ++i) {
            delete players[i];
        }
    }
};

int main(int argc, char* argv[]) {
    Player* one = Player_factory(argv[4], argv[5]);
    Player* two = Player_factory(argv[6], argv[7]);
    Player* three = Player_factory(argv[8], argv[9]);
    Player* four = Player_factory(argv[10], argv[11]);

    Euchre driver(one, two, three, four);

    if ((argc != 12) || (stoi(argv[3]) > 100 || stoi(argv[3]) < 1) ||
        (string(argv[2]) != "noshuffle" && string(argv[2]) != "shuffle") ||
        (string(argv[5]) != "Human" && string(argv[5]) != "Simple" &&
        string(argv[7]) != "Human" && string(argv[7]) != "Simple" &&
        string(argv[9]) != "Human" && string(argv[9]) != "Simple" &&
        string(argv[11]) != "Human" && string(argv[11]) != "Simple")) {
        
        driver.print_error_message();
        return 1;
    }

    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;

    ifstream fin(argv[1]);

    if (!(fin.is_open())) {
        cout << "Error opening file: " << argv[1] << endl;
        return 0;
    }

    int hand = 0;
    int winning_score = stoi(argv[3]);
    int max = 0;

    while (max < winning_score) {
        cout << "Hand " << hand << endl;

        int dealer = hand % 4;
        int eldest = ((dealer + 1) % 4);

        if (string(argv[2]) == "shuffle") {
            driver.shuffle();
        }
        driver.deal_to_players(dealer);

        string trump = driver.makeTrump(dealer, driver.get_upcard());
        
        cout << endl;

        driver.trick_taking(dealer, eldest);
        driver.euchre_scoring();
        max = driver.winning_score();
        hand++;
    }
    
    driver.findWinner();
    driver.delete_euchre_players();
    return 0;
}
