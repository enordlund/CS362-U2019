// Unit test for drawCard

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


void testDrawCard() {
     for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
          // testing for all possible numbers of players
          struct gameState state;

          int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

          memset(&state, 23, sizeof(struct gameState));   // clear the game state

          int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
          
          
          for (int player = 0; player < numPlayers; ++player) {
               int initialHandCount = state.handCount[player];
               drawCard(player, &state);
               
               int expectedHandCount = initialHandCount + 1;
               
               assert(state.handCount[player] == expectedHandCount);
          }
          
     }
}

int main() {
    testDrawCard();
    return 0;
}