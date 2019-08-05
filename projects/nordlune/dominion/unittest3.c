// Unit test for cardEffectAmbassador

#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

struct testStruct {
    int choice1;
    int choice2;
    struct gameState *state;
    int handPos;
    int currentPlayer;
}

void testCardEffectAmbassador() {
    //----------------------------- handle hand count in a for loop, might need to initialize it (see coin example)
    for (int handSize = 1; handSize <= maxHandSize; ++handSize) {
    
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
                                drawCard(player, state);
                            }
                        }
                        
                        
                        // copying hand counts for later comparison
                        int initialHandCount[numPlayers];
                        memcpy(initialHandCount, state.handCount, sizeof(state.handCount));
                        
                        cardEffectAmbassador(choice1, choice2, &state, 0, currentPlayer);
                        
                        // hand count of currentPlayer should be 0-2 cards less than the initial count
                        int expectedMaxHandCount = initialHandCount[currentPlayer];
                        int expectedMinHandCount = expectedMaxHandCount - 2;
                        assert(state.handCount[currentPlayer] >= expectedMinHandCount);
                        assert(state.handCount[currentPlayer] <= expectedMaxHandCount);
                        
                        // hand counts of other players should be 1 more than initial counts
                        for (int player = 0; player < numPlayers; ++player) {
                           int expectedPlayerHandCount = initialHandCount[player] + 1;
                           assert(state.handCount[player] == expectedPlayerHandCount);
                        }
                        
                    }
                }
                
            }
        }
    }
}

int main() {
    testCardEffectAmbassador();
    return 0;
}