// Unit test for cardEffectBaron

#include<stdio.h>
#include<stdlib.h>
#include "dominion_helpers.h"


void testCardEffectBaron() {
    //----------------------------- handle hand count in a for loop, might need to initialize it (see coin example)
    for (int handSize = 1; handSize <= maxHandSize; ++handSize) {
    
        for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
            // testing for all possible numbers of players
            for (int currentPlayer = 0; currentPlayer < numPlayers; ++currentPlayer) {
                // testing for all possible current players
                for (int initialEstateCount = 0; initialEstateCount <= handCount; ++initialEstateCount) {
                    // testing starting without an estate card, and with an estate card.
                    for (int choice = 0; choice <= 1; ++choice) {
                        // testing both choices for choice1
                        // // if choice1 == 0, gain estate
                        // // if choice1 > 0, discard estate
                        
                        bool checkedInitialEstate = false;
                        bool checkedNoInitialEstate = false;
                        // looping until gameState covers cases of a player having an initial estate card, and not having one.
                        while (!checkedInitialEstate || !checkedNoInitialEstate) {
                            struct gameState *state;
                            
                            int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
                            
                            memset(&state, 23, sizeof(struct gameState));   // clear the game state
                            
                            int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
                            
                            // populating hand for current player
                            for (int player = 0; player < numPlayers; ++player) {
                                for (int card = 0; card < handSize; ++card) {
                                    drawCard(player, state);
                                }
                            }
                            
                            
                            
                            // ------------------------------last step is making sure we count all cases of the initialEstateCount in some kind of loop, because this is partially determined by the initializeGame function
                            // loop through hand of current player to check for number of estate cards
                            int initialEstateCount = 0;
                            for (int card = 0; card < state->handCount[currentPlayer]; ++card) {
                                if (hand[currentPlayer][card] == estate) {
                                    initialEstateCount++;
                                }
                            }
                            
                            if (initialEstateCount == 0) {
                                checkedNoInitialEstate = true;
                            } else {
                                checkedInitialEstate = true;
                            }
                            
                            int initialEstateSupplyCount = state->supplyCount[estate];
                            
                            int initialDiscardCount = state->discardCount[currentPlayer];
                            CARD mostRecentDiscard = state->discard[currentPlayer][initialDiscardCount - 1];
                            
                            cardEffectBaron(choice, &state, currentPlayer);
                            
                            int newEstateCount = 0;
                            for (int card = 0; card < state->handCount[currentPlayer]; ++card) {
                                if (hand[currentPlayer][card] == estate) {
                                    newEstateCount++;
                                }
                            }
                            
                            int newEstateSupplyCount = state->supplyCount[estate];
                            
                            if (choice == 0) {
                                // testing for the case of gaining an estate
                                // // state should remain the same, except for the following:
                                // // - currentPlayer gains an estate card
                                // // - supplyCount[estate] decreases by 1
                                int expectedEstateCount = initialEstateCount + 1;
                                int expectedEstateSupplyCount = initialEstateSupplyCount - 1;
                                
                                assert(newEstateCount == expectedEstateCount);
                                assert(newEstateSupplyCount == expectedEstateSupplyCount);
                                
                            } else if (choice == 1) {
                                // player has opted to 
                                if (initialEstateCount < 1) {
                                    // testing for the case of gaining an estate
                                    // // state should remain the same, except for the following:
                                    // // - currentPlayer gains an estate card
                                    // // - supplyCount[estate] decreases by 1
                                    
                                    int expectedEstateCount = initialEstateCount + 1;
                                    int expectedEstateSupplyCount = initialEstateSupplyCount - 1;
                                    
                                    assert(newEstateCount == expectedEstateCount);
                                    assert(newEstateSupplyCount == expectedEstateSupplyCount);
                                    
                                } else {
                                    // testing for the case of discarding an estate
                                    
                                    int expectedEstateCount = initialEstateCount - 1;
                                    int expectedDiscardCount = initialDiscardCount + 1;
                                    CARD expectedDiscard = estate;
                                    
                                    int lastDiscardIndex = state->discardCount[currentPlayer] - 1;
                                    CARD lastDiscard = state->discard[currentPlayer][lastDiscardIndex];
                                    
                                    assert(newEstateCount == expectedEstateCount);
                                    assert(newEstateSupplyCount == expectedEstateSupplyCount);
                                    assert(lastDiscard == expectedDiscard);
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    // testing choice1 == 0, when the player doesn't have an estate card
    // // results in discarding an estate
    
    test1.choice1 = 1;
    
    test1.state->numPlayers = 2; //number of players
    test1.state->supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
    test1.state->embargoTokens[treasure_map+1];
    test1.state->outpostPlayed;
    test1.state->outpostTurn;
    test1.state->whoseTurn;
    test1.state->phase;
    test1.state->numActions = 1; /* Starts at 1 each turn */
    test1.state->coins; /* Use as you see fit! */
    test1.state->numBuys = 1; /* Starts at 1 each turn */
    test1.state->hand[MAX_PLAYERS][MAX_HAND];
    test1.state->handCount[MAX_PLAYERS];
    test1.state->deck[MAX_PLAYERS][MAX_DECK];
    test1.state->deckCount[MAX_PLAYERS];
    test1.state->discard[MAX_PLAYERS][MAX_DECK];
    test1.state->discardCount[MAX_PLAYERS];
    test1.state->playedCards[MAX_DECK];
    test1.state->playedCardCount = 0;
    
    
}

int main() {
    testCardEffectBaron();
    return 0;
}