// Unit test for initializeGame

#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "dominion_helpers.h"


void testInitializeGame() {
     for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
          // testing for all possible numbers of players
          struct gameState state;

          int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

          memset(&state, 23, sizeof(struct gameState));   // clear the game state

          int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
          
          // now that the game is initialized, check state
          assert(state.numPlayers == numPlayers);
          
          assert(state.numActions == 1);
          
          assert(state.numBuys == 1);
          
          for (int player = 0; player < numPlayers; ++player) {
               assert(state.handCount[player] == 5);
          }
     }
}

int main() {
    testInitializeGame();
    return 0;
}