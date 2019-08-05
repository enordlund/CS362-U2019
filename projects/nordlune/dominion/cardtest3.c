// Unit test for endTurn

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


void testEndTurn() {
     // generate random seed
     int seed = time(NULL);
     
     srand(seed);//passing seed to rand() for future values
     for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
          // testing for all possible numbers of players
          struct gameState state;

          int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

          memset(&state, 23, sizeof(struct gameState));   // clear the game state

          int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
          
          int initialTurn = state.whoseTurn;
          
          int ended = endTurn(&state);
          
          int expectedTurn = 0;
          if (initialTurn != (numPlayers - 1)) {
               expectedTurn = initialTurn + 1;
          }
          
          assert(state.whoseTurn == expectedTurn);
     }
}

int main() {
    testEndTurn();
    return 0;
}