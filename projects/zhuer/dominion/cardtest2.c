#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "asserttrue.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Unit test for cardEffect(adventurer) found in dominion.c
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
  int drawnCoinValue = 0;

  printf("\n==================================================\n");
  printf("CARD TEST 2: cardEffect(adventurer)\n");
  printf("==================================================\n\n"); 

  printf ("Starting game (seed = %d).\n", seed);
  initializeGame(2, k, seed, &G);
  memcpy(&GCopy, &G, sizeof(struct gameState));

  printf("\n-------------------- TEST 1 --------------------\n");
  printf("Activating adventurer card effect.\n");
  cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
  printf("Looking for differences in gameState ");
  printf("(+2 treasure cards drawn from deck, other cards before the 2 treasure cards discarded, and card at handPos played).\n");
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
  for(i=G.handCount[playerOne]-2; i<G.handCount[playerOne]; i++){
    if(G.hand[playerOne][i] == copper){
      drawnCoinValue++;
    }
    else if(G.hand[playerOne][i] == silver){
      drawnCoinValue+=2;
    }
    else if(G.hand[playerOne][i] == gold){
      drawnCoinValue+=3;
    }
    else {
      printf("ERROR! Treasure card wasn't drawn!\n");
      drawnCoinValue = -10;
    }
  }
  if(drawnCoinValue < 2){
    printf("Last two cards of player one's hand aren't treasures.\n");
  }
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
  printf("Asserting: G.handCount[playerOne] == GCopy.handCount[playerOne]+1\n");
  asserttrue(G.handCount[playerOne] == GCopy.handCount[playerOne]+1);
  for(i=0; i<GCopy.deckCount[playerOne]-G.discardCount[playerOne]; i++){
    printf("Asserting: G.deck[playerOne][i] == GCopy.deck[playerOne][i])\n");
    asserttrue(G.deck[playerOne][i] == GCopy.deck[playerOne][i]);
  }
  printf("Asserting: G.deckCount[playerOne] == GCopy.deckCount[playerOne]-G.discardCount[playerOne]-1)\n");
  asserttrue(G.deckCount[playerOne] == GCopy.deckCount[playerOne]-G.discardCount[playerOne]-1);
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

  printf("Activating adventurer card effect.\n");
  cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);
  printf("Looking for differences in gameState ");
  printf("(+2 treasure cards drawn from deck, other cards before the 2 treasure cards discarded, and card at handPos played).\n");
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
  for(i=G.handCount[playerOne]-2; i<G.handCount[playerOne]; i++){
    if(G.hand[playerOne][i] == copper){
      drawnCoinValue++;
    }
    else if(G.hand[playerOne][i] == silver){
      drawnCoinValue+=2;
    }
    else if(G.hand[playerOne][i] == gold){
      drawnCoinValue+=3;
    }
    else {
      printf("ERROR! Treasure card wasn't drawn!\n");
      drawnCoinValue = -10;
    }
  }
  if(drawnCoinValue < 2){
    printf("Last two cards of player one's hand aren't treasures.\n");
  }
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
  printf("Asserting: G.handCount[playerOne] == GCopy.handCount[playerOne]+1\n");
  asserttrue(G.handCount[playerOne] == GCopy.handCount[playerOne]+1);
  for(i=0; i<GCopy.deckCount[playerOne]-G.discardCount[playerOne]; i++){
    printf("Asserting: G.deck[playerOne][i] == GCopy.deck[playerOne][i])\n");
    asserttrue(G.deck[playerOne][i] == GCopy.deck[playerOne][i]);
  }
  printf("Asserting: G.deckCount[playerOne] == GCopy.deckCount[playerOne]-G.discardCount[playerOne]-1)\n");
  asserttrue(G.deckCount[playerOne] == GCopy.deckCount[playerOne]-G.discardCount[playerOne]-1);
  printf("Asserting: G.playedCards[0] == GCopy.hand[playerOne][handPos]\n");
  asserttrue(G.playedCards[0] == GCopy.hand[playerOne][handPos]);
  printf("Asserting: G.playedCardCount == GCopy.playedCardCount+1\n");
  asserttrue(G.playedCardCount == GCopy.playedCardCount+1);
  return 0;
}
