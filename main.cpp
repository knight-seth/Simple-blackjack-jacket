//
//  main.cpp
//  Blackjack
//
//  Created by Seth Knight on 9/11/26.
//

#include <random>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <unistd.h>

using namespace::std;


struct card {
    string  suit;
    string  rank;
    int val;
};

const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

const int DECK_SIZE = 52;
const int MAX_HAND = 12;

void create_deck(card deck[]){
    
    int index = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 13; j++){
            
            int value = j  + 2;
            if (value > 10) value = 10;
                if (j == 12) value = 11;
            deck[index].suit = SUITS[i];
            deck[index].rank = RANKS[j];
            deck[index].val = value;
            index++;
            
        }
}
    
    return void();
    
 
}

void clear_screen() { cout << "\033[2J\033[1;1H"; }

void shuffle_deck(card deck[]){
    
    for(int i = DECK_SIZE - 1; i > 0; i--){
        int j = rand() % (i + 1);
        
        card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
    
    return void();
}

stack<card> convert_array_to_stack(card deck[]) {
    stack<card> cardStack;
    for (int i = 0; i < DECK_SIZE; i++) {
        cardStack.push(deck[i]);
    }
    return cardStack;
}

int calculate_score(card hand[], int handSize) {
    int total = 0;
    int aces = 0;
    for (int i = 0; i < handSize; i++) {
        total += hand[i].val;
        if (hand[i].rank == "Ace") aces++;
    }
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    return total;
}
int calculate_hand_value(card hand[], int handSize){
    int total = 0 ;
    int aceCount = 0;
    
    for (int i = 0; i < handSize; i++ ){
        
        total += hand[i].val;
    
    
    if (hand[i].rank == "Ace") {
      aceCount++ ;
    }}

    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }
    return total;
}




int main(){
    char wants_play ='y';
    while (wants_play == 'y') {
        
        
        srand(time(0));
        
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║          ♠ BLACKJACK ♥               ║\n";
        cout << "╚══════════════════════════════════════╝\n\n";
        cout<<  "               dealing                       "<<endl;
        sleep(1);
        
        card myDeck[DECK_SIZE];
        
        create_deck(myDeck);
        shuffle_deck(myDeck);
        stack<card> gameDeck = convert_array_to_stack(myDeck);
        cout << "\n=== Loaded Stack with " << gameDeck.size() << " Shuffled Cards ===\n\n";
        sleep(1);
        
        card playerHand[MAX_HAND];
        int playerSize = 0;
        
        card dealerHand[MAX_HAND];
        int dealerSize = 0;
        
        playerHand[playerSize] = gameDeck.top();
        cout<<"your first card is "<< playerHand[playerSize].rank<< " of "<<playerHand[playerSize].suit <<endl;
        gameDeck.pop();
        playerSize++;
        sleep(1);
        
        dealerHand[dealerSize] = gameDeck.top(); // Deals card 1 (Hidden Card)
        gameDeck.pop();
        dealerSize++;
        sleep(1);
        
        playerHand[playerSize] = gameDeck.top();
        cout<<"your Second card is "<< playerHand[playerSize].rank<< " of "<<playerHand[playerSize].suit <<endl;
        gameDeck.pop();
        playerSize++;
        sleep(1);
        
        dealerHand[dealerSize] = gameDeck.top();
        cout<<endl<< "[Dealer's upcard is " << dealerHand[dealerSize].rank << " of " << dealerHand[dealerSize].suit <<"]"<< endl << endl;
        gameDeck.pop();
        dealerSize++;
        sleep(1);
        
        int score = calculate_hand_value(playerHand, playerSize);
        
        
        cout <<"your initial score is "<< score <<endl;
        sleep(1);
        char Choice ='s';
        
        while( score  < 21){
            
            cout << "hit or stand?: type 'h' or 's': ";
            cin >> Choice;
            if (Choice == 'h' || Choice == 'H'){
                playerHand[playerSize] = gameDeck.top();
                cout<<"you Drew "<< playerHand[playerSize].rank<< " of "<<playerHand[playerSize].suit <<endl;
                sleep(1);
                gameDeck.pop();
                playerSize++;
                score = calculate_hand_value(playerHand, playerSize);
                cout<<"your score is now "<<score<<endl;
                sleep(1);
                if( score > 21){
                    cout<<"bust!!!"<<endl;
                    sleep(1);
                    break;
                }
            }else if (Choice == 's'|| Choice == 'S') {
                score = calculate_hand_value(playerHand, playerSize);
                cout<<"you stood with a score of "<<score<<endl;
                sleep(1);
                break;
            }
            sleep(1);
        }
        
        if(score <= 21){
            cout<<endl<< "----- Dealers Turn -----"<<endl;
            sleep(1);
            
            int dealers_score = calculate_hand_value(dealerHand, dealerSize);
            cout<<"Dealer reveals "<<dealerHand[0].rank<<" of "<<dealerHand[0].suit<<endl<<"his score is now "<<dealers_score<<endl;
            sleep(1);
            
            while (dealers_score < 17) {
                dealerHand[dealerSize] =gameDeck.top();
                cout<<"dealer hits "<<dealerHand[dealerSize].rank<<" of "<<dealerHand[dealerSize].suit<<endl;
                gameDeck.pop();
                dealerSize++;
                dealers_score = calculate_hand_value(dealerHand,dealerSize);
                cout<<"his score is now "<<dealers_score<<endl;
                sleep(1);
                
                
                
                if(dealers_score > 21){
                    cout <<"dealer bust"<<endl;
                    sleep(1);
                    break;
                }
            }
            cout<<"=== Final scores ==="<<endl;
            sleep(1);
            cout<<"your score: "<<score<<" deal: "<<dealers_score<<endl;
            if (dealers_score < score){cout<<"you win!!!"<<endl;}
            else if (dealers_score > score){cout<<"dealer wins"<<endl;}
            else {cout<<"Game ended with a push"<<endl;}
        }
        
        
        else{
            cout<<"Game over"<<endl;
            
        }
        
        cout<<"would you like to play again?\n";
        cout << "y = Yes\n"<<endl;
        cout << "n = No\n"<<endl;
        cout << "Choice: "<<endl;;
        
        cin >> wants_play;
    }
    
        return 0;
    }

