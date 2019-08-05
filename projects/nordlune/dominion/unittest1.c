// Unit test for cardEffectBaron

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


void testCardEffectBaron() {
    //----------------------------- handle hand count in a for loop, might need to initialize it (see coin example)
    for (int handSize = 1; handSize <= MAX_HAND; ++handSize) {
    
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
                            struct gameState state;
                            
                            int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
                            
                            memset(&state, 23, sizeof(struct gameState));   // clear the game state
                            
                            int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
                            
                            // populating hand for current player
                            for (int player = 0; player < numPlayers; ++player) {
                                for (int card = 0; card < handSize; ++card) {
                                    drawCard(player, &state);
                                }
                            }
                            
                            
                            
                            // ------------------------------last step is making sure we count all cases of the initialEstateCount in some kind of loop, because this is partially determined by the initializeGame function
                            // loop through hand of current player to check for number of estate cards
                            int initialEstateCount = 0;
                            for (int card = 0; card < state.handCount[currentPlayer]; ++card) {
                                if (state.hand[currentPlayer][card] == estate) {
                                    initialEstateCount++;
                                }
                            }
                            
                            if (initialEstateCount == 0) {
                                checkedNoInitialEstate = true;
                            } else {
                                checkedInitialEstate = true;
                            }
                            
                            int initialEstateSupplyCount = state.supplyCount[estate];
                            
                            int initialDiscardCount = state.discardCount[currentPlayer];
                            int mostRecentDiscard = state.discard[currentPlayer][initialDiscardCount - 1];
                            
                            cardEffectBaron(choice, &state, currentPlayer);
                            
                            int newEstateCount = 0;
                            for (int card = 0; card < state.handCount[currentPlayer]; ++card) {
                                if (state.hand[currentPlayer][card] == estate) {
                                    newEstateCount++;
                                }
                            }
                            
                            int newEstateSupplyCount = state.supplyCount[estate];
                            
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
                                    int expectedDiscard = 1;
                                    
                                    int lastDiscardIndex = state.discardCount[currentPlayer] - 1;
                                    int lastDiscard = state.discard[currentPlayer][lastDiscardIndex];
                                    
                                    assert(newEstateCount == expectedEstateCount);
                                    assert(newEstateSupplyCount == initialEstateSupplyCount);
                                    assert(lastDiscard == expectedDiscard);
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    testCardEffectBaron();
    return 0;
}