// Unit test for cardEffectMinion

#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "dominion_helpers.h"

struct testStruct {
    int choice1;
    int choice2;
    struct gameState *state;
    int handPos;
    int currentPlayer;
}

void testCardEffectMinion() {
    //----------------------------- handle hand count in a for loop, might need to initialize it (see coin example)
    for (int handSize = 1; handSize <= maxHandSize; ++handSize) {
    
        for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
            // testing for all possible numbers of players
            for (int currentPlayer = 0; currentPlayer < numPlayers; ++currentPlayer) {
                // testing for all possible current players
                
                for (int choice1 = 0; choice1 <= 1; ++choice1) {
                    for (int choice2 = 0; choice2 <= 1; ++choice2) {
                        // testing both choices
                        
                        struct gameState *state;
                        
                        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
                        
                        memset(&state, 23, sizeof(struct gameState));   // clear the game state
                        
                        int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
                        
                        // populating hands
                        for (int player = 0; player < numPlayers; ++player) {
                            for (int card = 0; card < handSize; ++card) {
                                drawCard(player, state);
                            }
                        }
                        
                        
                        // keeping track of initial treasure cards for current player, for later comparison if choice1
                        int initialTreasures = 0;
                        for (int card = 0; card < state->handCount[currentPlayer]; ++card) {
                            if (hand[currentPlayer][card] == copper) {
                                initialTreasures++;
                            } else if (hand[currentPlayer][card] == silver) {
                                initialTreasures++;
                            } else if (hand[currentPlayer][card] == gold) {
                                initialTreasures++;
                            }
                        }
                        
                        // copying hand counts for later comparison if choice2
                        int initialHandCount[numPlayers];
                        memcpy(initialHandCount, state->handCount, sizeof(state->handCount));
                        
                        cardEffectMinion(choice1, choice2, &state, 0, currentPlayer);
                        
                        
                        
                        if (choice1 && !choice2) {
                            // testing for the case of the current player gaining two treasures
                            // // state should remain the same, except for the following:
                            // // - currentPlayer gains two treasures
                            int expectedTreasureCount = initialTreasures + 2;
                            
                            int newTreasureCount = 0;
                            for (int card = 0; card < state->handCount[currentPlayer]; ++card) {
                                if (hand[currentPlayer][card] == copper) {
                                    newTreasureCount++;
                                } else if (hand[currentPlayer][card] == silver) {
                                    newTreasureCount++;
                                } else if (hand[currentPlayer][card] == gold) {
                                    newTreasureCount++;
                                }
                            }
                            
                            assert(newTreasureCount == expectedTreasureCount);
                            
                        } else if (choice2 && !choice1) {
                            // testing for the second choice
                            // // state should remain the same, except for the following:
                            // // - currentPlayer should have four cards
                            // // - other players who had at least five cards should now have four cards
                            
                            for (int player = 0; player < numPlayers; ++player) {
                                if (player == currentPlayer) {
                                    assert(state->handCount[player] == 4);
                                } else {
                                    if (initialHandCount[player] > 4) {
                                        assert(state->handCount[player] == 4);
                                    } else {
                                        assert(state->handCount[player] == initialHandCount[player]);
                                    }
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
    testCardEffectMinion();
    return 0;
}