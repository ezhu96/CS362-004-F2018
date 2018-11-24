#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "asserttrue.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Unit test for cardEffect(smithy) found in dominion.c
int main()
{
  struct gameState G;
  struct gameState GCopy;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int handPos = 0;
  int bonus = 0;
  int playerOne = 0;
  int i;

  printf("\n==================================================\n");
  printf("CARD TEST 1: cardEffect(smithy)\n");
  printf("==================================================\n\n"); 

  printf ("Starting game (seed = %d).\n", seed);
  initializeGame(2, k, seed, &G);
  memcpy(&GCopy, &G, sizeof(struct gameState));

  printf("\n-------------------- TEST 1 --------------------\n");
  printf("Activating smithy card effect.\n");
  cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
  printf("Looking for differences in gameState ");
  printf("(+3 cards drawn from deck and card at handPos played).\n");
  printf("Asserting: G.numPlayers == GCopy.numPlayers\n");
  asserttrue(G.numPlayers == GCopy.numPlayers);
  for(i=0; i<treasure_map+1; i++){
    printf("Asserting: G.supplyCount[i] == GCopy.supplyCount[i]\n");
    asserttrue(G.supplyCount[i] == GCopy.supplyCount[i]);
    printf("Asserting: G.embargoTokens[i] == GCopy.embargoTokens[i]\n");
    asserttrue(G.embargoTokens[i] == GCopy.embargoTokens[i]);
  }
  printf("Asserting: G.outpostPlayed == GCopy.outpostPlayed\n");
  asserttrue(G.outpostPlayed == GCopy.outpostPlayed);
  printf("Asserting: G.outpostTurn == GCopy.outpostTurn\n");
  asserttrue(G.outpostTurn == GCopy.outpostTurn);
  printf("Asserting: G.whoseTurn == GCopy.whoseTurn\n");
  asserttrue(G.whoseTurn == GCopy.whoseTurn);
  printf("Asserting: G.phase == GCopy.phase\n");
  asserttrue(G.phase == GCopy.phase);
  printf("Asserting: G.numActions == GCopy.numActions\n");
  asserttrue(G.numActions == GCopy.numActions);
  printf("Asserting: G.coins == GCopy.coins\n");
  asserttrue(G.coins == GCopy.coins);
  printf("Asserting: G.numBuys == GCopy.numBuys\n");
  asserttrue(G.numBuys == GCopy.numBuys);
  printf("Asserting: G.hand[playerOne][handPos] == GCopy.hand[playerOne][GCopy.handCount[playerOne]-1])\n");
  asserttrue(G.hand[playerOne][handPos] == GCopy.hand[playerOne][GCopy.handCount[playerOne]-1]);
  for(i=handPos+1; i<GCopy.handCount[playerOne]-1; i++){
    printf("Asserting: G.hand[playerOne][i] == GCopy.hand[playerOne][i]\n");
    asserttrue(G.hand[playerOne][i] == GCopy.hand[playerOne][i]);
  }
  printf("Asserting: G.handCount[playerOne] == GCopy.handCount[playerOne]+2\n");
  asserttrue(G.handCount[playerOne] == GCopy.handCount[playerOne]+2);
  for(i=0; i<GCopy.deckCount[playerOne]-3; i++){
    printf("Asserting: G.deck[playerOne][i] == GCopy.deck[playerOne][i])\n");
    asserttrue(G.deck[playerOne][i] == GCopy.deck[playerOne][i]);
  }
  printf("Asserting: G.deckCount[playerOne] == GCopy.deckCount[playerOne]-3)\n");
  asserttrue(G.deckCount[playerOne] == GCopy.deckCount[playerOne]-3);
  printf("Asserting: G.discardCount[playerOne] == GCopy.discardCount[playerOne])\n");
  asserttrue(G.discardCount[playerOne] == GCopy.discardCount[playerOne]);
  printf("Asserting: G.playedCards[0] == GCopy.hand[playerOne][handPos]\n");
  asserttrue(G.playedCards[0] == GCopy.hand[playerOne][handPos]);
  printf("Asserting: G.playedCardCount == GCopy.playedCardCount+1\n");
  asserttrue(G.playedCardCount == GCopy.playedCardCount+1);

  memcpy(&G, &GCopy, sizeof(struct gameState));

  printf("\n-------------------- TEST 2 --------------------\n");
  printf("choice1 = 1, choice2 = 1, choice3 = 1, handPos = 1, bonus = 1\n");
  choice1++;
  choice2++;
  choice3++;
  handPos++;
  bonus++;

  printf("Activating smithy card effect.\n");
  cardEffect(smithy, choice1, choice2, choice3, &G, handPos, &bonus);
  printf("Looking for differences in gameState ");
  printf("(+3 cards drawn from deck and card at handPos played).\n");
  printf("Asserting: G.numPlayers == GCopy.numPlayers\n");
  asserttrue(G.numPlayers == GCopy.numPlayers);
  for(i=0; i<treasure_map+1; i++){
    printf("Asserting: G.supplyCount[i] == GCopy.supplyCount[i]\n");
    asserttrue(G.supplyCount[i] == GCopy.supplyCount[i]);
    printf("Asserting: G.embargoTokens[i] == GCopy.embargoTokens[i]\n");
    asserttrue(G.embargoTokens[i] == GCopy.embargoTokens[i]);
  }
  printf("Asserting: G.outpostPlayed == GCopy.outpostPlayed\n");
  asserttrue(G.outpostPlayed == GCopy.outpostPlayed);
  printf("Asserting: G.outpostTurn == GCopy.outpostTurn\n");
  asserttrue(G.outpostTurn == GCopy.outpostTurn);
  printf("Asserting: G.whoseTurn == GCopy.whoseTurn\n");
  asserttrue(G.whoseTurn == GCopy.whoseTurn);
  printf("Asserting: G.phase == GCopy.phase\n");
  asserttrue(G.phase == GCopy.phase);
  printf("Asserting: G.numActions == GCopy.numActions\n");
  asserttrue(G.numActions == GCopy.numActions);
  printf("Asserting: G.coins == GCopy.coins\n");
  asserttrue(G.coins == GCopy.coins);
  printf("Asserting: G.numBuys == GCopy.numBuys\n");
  asserttrue(G.numBuys == GCopy.numBuys);
  printf("Asserting: G.hand[playerOne][handPos] == GCopy.hand[playerOne][GCopy.handCount[playerOne]-1])\n");
  asserttrue(G.hand[playerOne][handPos] == GCopy.hand[playerOne][GCopy.handCount[playerOne]-1]);

  for(i=handPos+1; i<GCopy.handCount[playerOne]-1; i++){
    printf("Asserting: G.hand[playerOne][i] == GCopy.hand[playerOne][i]\n");
    asserttrue(G.hand[playerOne][i] == GCopy.hand[playerOne][i]);
  }
  printf("Asserting: G.handCount[playerOne] == GCopy.handCount[playerOne]+2\n");
  asserttrue(G.handCount[playerOne] == GCopy.handCount[playerOne]+2);
  for(i=0; i<GCopy.deckCount[playerOne]-3; i++){
    printf("Asserting: G.deck[playerOne][i] == GCopy.deck[playerOne][i])\n");
    asserttrue(G.deck[playerOne][i] == GCopy.deck[playerOne][i]);
  }
  printf("Asserting: G.deckCount[playerOne] == GCopy.deckCount[playerOne]-3)\n");
  asserttrue(G.deckCount[playerOne] == GCopy.deckCount[playerOne]-3);
  printf("Asserting: G.discardCount[playerOne] == GCopy.discardCount[playerOne])\n");
  asserttrue(G.discardCount[playerOne] == GCopy.discardCount[playerOne]);
  printf("Asserting: G.playedCards[0] == GCopy.hand[playerOne][handPos]\n");
  asserttrue(G.playedCards[0] == GCopy.hand[playerOne][handPos]);
  printf("Asserting: G.playedCardCount == GCopy.playedCardCount+1\n");
  asserttrue(G.playedCardCount == GCopy.playedCardCount+1);

  if(asserterrors){
    printf("CARD TEST 1 FAILED!!! (%d assertion errors)\n", asserterrors);
  }
  else {
    printf("CARD TEST 1 PASSED!!!\n");
  }

  return 0;
}
