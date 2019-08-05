// random test for cardEffectTribute
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
        int initialHandCount[numPlayers];
        memcpy(initialHandCount, state->handCount, sizeof(state->handCount));
       
        int nextPlayer = 0;
        if (currentPlayer != (numPlayers - 1)) {
          nextPlayer = currentPlayer + 1;
        }

        int initialActions = state->numActions;
        
        int initialTreasures = 0;
        for (int card = 0; card < state->handCount[currentPlayer]; ++card) {
            if (state->hand[currentPlayer][card] == copper) {
              initialTreasures++;
            } else if (state->hand[currentPlayer][card] == silver) {
              initialTreasures++;
            } else if (state->hand[currentPlayer][card] == gold) {
              initialTreasures++;
            }
        }
        
        
        // call cardEffectTribute with random parameters
        int cardEffect = cardEffectTribute(&state, currentPlayer, nextPlayer);
        
        
        // check if successful
        int expectedActionsMax = initialActions + 2;
               
        assert(expectedActionsMax >= state->numActions);
        
        int expectedTreasuresMax = initialTreasures + 2;
        
        int currentTreasures = 0;
        for (int card = 0; card < state->handCount[currentPlayer]; ++card) {
            if (state->hand[currentPlayer][card] == copper) {
                currentTreasures++;
            } else if (state->hand[currentPlayer][card] == silver) {
                currentTreasures++;
            } else if (state->hand[currentPlayer][card] == gold) {
                currentTreasures++;
            }
        }
        
        assert(expectedTreasuresMax >= currentTreasures);
        
        int expectedHandCountMax = initialHandCount[currentPlayer] + 2;
        
        assert(expectedHandCountMax >= state->handCount[currentPlayer]);
        
        
    }
    return 0;
}