// random test for cardEffectBaron
#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>



int main() {
    
    
    
    // define game state
    struct gameState *state;
                            
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    
    // loop to generate random test cases
    bool successful = true;
    while (successful) {
        // generate random seed
        int seed = time(NULL);
        
        srand(seed);//passing seed to rand() for future values
        // generate random set of parameters for game, within defined bounds
        int numPlayers = (rand() % (MAX_PLAYERS - 1)) + 2;//random value from min (2) to max (MAX_PLAYERS)
        
        int choice = (rand() % 1) + 1; // random value, 0 or 1;
        int currentPlayer = (rand() % numPlayers); // random player
        
        // initialize game
        memset(&state, 23, sizeof(struct gameState));   // clear the game state
        
        int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
        
        
        // save original state variables
        
        int initialEstateCount = 0;
        for (int card = 0; card < state->handCount[currentPlayer]; ++card) {
            if (hand[currentPlayer][card] == estate) {
                initialEstateCount++;
            }
        }
        
        int initialEstateSupplyCount = state->supplyCount[estate];
        
        int initialDiscardCount = state->discardCount[currentPlayer];
        
        
        // call cardEffectBaron with random parameters
        
        int cardEffect = cardEffectBaron(choice, &state, currentPlayer);
        
        
        // check if successful
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
    return 0;
}