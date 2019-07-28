// random test for cardEffectMinion
#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>



int main() {
    // generate random seed
    int seed = time(NULL);
    
    srand(seed);//passing seed to rand() for future values
    
    
    // define game state
    struct gameState *state;
                            
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    
    // loop to generate random test cases
    bool successful = true;
    while (successful) {
        // generate random set of parameters for game, within defined bounds
        int numPlayers = (rand() % (MAX_PLAYERS - 1)) + 2;//random value from min (2) to max (MAX_PLAYERS)
        
        int choice1 = (rand() % 1) + 1; // random value, 0 or 1;
        int choice2;
        
        if (choice1 == 1) {
            choice2 = 0;
        } else {
            choice2 = 1;
        }
        
        int currentPlayer = (rand() % numPlayers); // random player
        
        
        // initialize game
        memset(&state, 23, sizeof(struct gameState));   // clear the game state
        
        int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
        
        
        // save original state variables
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
        
        int initialHandCount[numPlayers];
        memcpy(initialHandCount, state->handCount, sizeof(state->handCount));
        
        
        // call cardEffectMinion with random parameters
        int cardEffect = cardEffectMinion(choice1, choice2, &state, 0, currentPlayer);
        
        
        // check if successful
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
    return 0;
}