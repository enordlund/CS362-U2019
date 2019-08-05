// Unit test for cardEffectMine

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

void testCardEffectMine() {
      // generate random seed
      int seed = time(NULL);
      
      srand(seed);//passing seed to rand() for future values
    //----------------------------- handle hand count in a for loop, might need to initialize it (see coin example)
    for (int handSize = 1; handSize <= MAX_HAND; ++handSize) {
    
        for (int numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers) {
            // testing for all possible numbers of players
            for (int currentPlayer = 0; currentPlayer < numPlayers; ++currentPlayer) {
                // testing for all possible current players
                
                for (int choice1 = 0; choice1 < handSize; ++choice1) {// might be better in a while loop once state.handCount can be used
                    for (int choice2 = 0; choice2 <= 2; ++choice2) {
                        // testing both choices
                        // - choice1 is the chosen card to reveal
                        // - choice2 is the chosen number of those cards to discard
                        
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
                        
                        // keeping track of initial treasure cards for current player, for later comparison
                        int initialTreasures = 0;
                        int initialTreasureValue = 0;
                        for (int card = 0; card < state.handCount[currentPlayer]; ++card) {
                             if (state.hand[currentPlayer][card] == copper) {
                               initialTreasures++;
                               initialTreasureValue = initialTreasureValue + 1;
                             } else if (state.hand[currentPlayer][card] == silver) {
                               initialTreasures++;
                               initialTreasureValue = initialTreasureValue + 2;
                             } else if (state.hand[currentPlayer][card] == gold) {
                               initialTreasures++;
                               initialTreasureValue = initialTreasureValue + 3;
                             }
                        }
                        
                        cardEffectMine(choice1, choice2, &state, 0, currentPlayer);
                        
                        assert(initialHandCount[currentPlayer] == state.handCount[currentPlayer]);
                        
                        int currentTreasures = 0;
                        int currentTreasureValue = 0;
                        for (int card = 0; card < state.handCount[currentPlayer]; ++card) {
                             if (state.hand[currentPlayer][card] == copper) {
                               currentTreasures++;
                               currentTreasureValue = currentTreasureValue + 1;
                             } else if (state.hand[currentPlayer][card] == silver) {
                               currentTreasures++;
                               currentTreasureValue = currentTreasureValue + 2;
                             } else if (state.hand[currentPlayer][card] == gold) {
                               currentTreasures++;
                               currentTreasureValue = currentTreasureValue + 3;
                             }
                        }
                        
                        int expectedTreasureValueMax = initialTreasureValue + 3;
                        
                        assert(initialTreasures == currentTreasures);
                        assert(expectedTreasureValueMax >= currentTreasureValue);
                        assert(currentTreasureValue >= initialTreasureValue);
                        
                        
                    }
                }
                
            }
        }
    }
}

int main() {
    testCardEffectMine();
    return 0;
}