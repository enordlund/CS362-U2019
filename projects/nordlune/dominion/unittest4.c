// Unit test for cardEffectTribute

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

void testCardEffectTribute() {
     // generate random seed
     int seed = time(NULL);
     
     srand(seed);//passing seed to rand() for future values
    //----------------------------- handle hand count in a for loop, might need to initialize it (see coin example)
    for (int handSize = 1; handSize <= MAX_HAND; ++handSize) {
    
        for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
            // testing for all possible numbers of players
            for (int currentPlayer = 0; currentPlayer < numPlayers; ++currentPlayer) {
               
               struct gameState state;

               int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

               memset(&state, 23, sizeof(struct gameState));   // clear the game state

               int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game

               // populating hands
               for (int player = 0; player < numPlayers; ++player) {
                   for (int card = 0; card < handSize; ++card) {
                       drawCard(player, &state);
                   }
               }


               // copying hand counts for later comparison
               int initialHandCount[numPlayers];
               memcpy(initialHandCount, state.handCount, sizeof(state.handCount));
               
               int nextPlayer = 0;
               if (currentPlayer != (numPlayers - 1)) {
                  nextPlayer = currentPlayer + 1;
               }
               
               int initialActions = state.numActions;
               
               // keeping track of initial treasure cards for current player, for later comparison
               int initialTreasures = 0;
               for (int card = 0; card < state.handCount[currentPlayer]; ++card) {
                    if (state.hand[currentPlayer][card] == copper) {
                      initialTreasures++;
                    } else if (state.hand[currentPlayer][card] == silver) {
                      initialTreasures++;
                    } else if (state.hand[currentPlayer][card] == gold) {
                      initialTreasures++;
                    }
               }
               
               cardEffectTribute(&state, 0, currentPlayer, nextPlayer);
               
               // check expectations
               int expectedActionsMax = initialActions + 2;
               
               assert(expectedActionsMax >= state.numActions);
               
               
               int expectedTreasuresMax = initialTreasures + 2;
               
               int currentTreasures = 0;
               for (int card = 0; card < state.handCount[currentPlayer]; ++card) {
                    if (state.hand[currentPlayer][card] == copper) {
                      currentTreasures++;
                    } else if (state.hand[currentPlayer][card] == silver) {
                      currentTreasures++;
                    } else if (state.hand[currentPlayer][card] == gold) {
                      currentTreasures++;
                    }
               }
               
               assert(expectedTreasuresMax >= currentTreasures);
               
               
               int expectedHandCountMax = initialHandCount[currentPlayer] + 2;
               
               assert(expectedHandCountMax >= state.handCount[currentPlayer]);
               
                               
            }
        }
    }
}

int main() {
    testCardEffectTribute();
    return 0;
}