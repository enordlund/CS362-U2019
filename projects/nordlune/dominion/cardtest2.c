// Unit test for shuffle

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


void testShuffle() {
     // generate random seed
     int seed = time(NULL);
     
     srand(seed);//passing seed to rand() for future values
     for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
          // testing for all possible numbers of players
          struct gameState state;

          int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

          memset(&state, 23, sizeof(struct gameState));   // clear the game state

          int game = initializeGame(numPlayers, k, seed, &state); // initialize a new game
          
          
          for (int player = 0; player < numPlayers; ++player) {
               // now that the game is initialized, copy current deck order
               int deckCount = state.deckCount[player];
               
               int initialHandCount[numPlayers];
                        memcpy(initialHandCount, state.handCount, sizeof(state.handCount));
               
               int initialDeck[deckCount];
               memcopy(initialDeck, state.deck[player], sizeof(state.deck[player]));
               shuffle(player, &state);
               
               bool deckDidShuffle = false;
               for (int card = 0; card < deckCount; ++card) {
                    if (initialDeck[card] != state.deck[player][card]) {
                         deckDidShuffle = true;
                    }
               }
               
               assert(deckDidShuffle);
          }
          
     }
}

int main() {
    testShuffle();
    return 0;
}