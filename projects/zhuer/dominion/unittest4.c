#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "asserttrue.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Unit test for the updateCoins() function found in dominion.c
int main()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  int playerOne = 0;
  int playerTwo = 1;
  int playerOneOriginalCoinCount;

  printf("\n==================================================\n");
  printf("UNIT TEST 4: updateCoins()\n");
  printf("==================================================\n\n"); 

  printf ("Starting game (seed = %d).\n", seed);

  initializeGame(2, k, seed, &G);
  playerOneOriginalCoinCount = G.coins;

  printf("Player one coin count: %d\n", playerOneOriginalCoinCount);
  printf("\n-------------------- TEST 1 --------------------\n");
  printf("Updating coins with +0 bonus. Coin count shouldn't change.\n");
  updateCoins(playerOne, &G, 0);
  printf("Asserting: G.coins = playerOneOriginalCoinCount\n");
  asserttrue(G.coins = playerOneOriginalCoinCount);

  printf("\n-------------------- TEST 2 --------------------\n");
  printf("Updating coins with +1 bonus.\n");
  updateCoins(playerOne, &G, 1);
  printf("Asserting: G.coins = playerOneOriginalCoinCount + 1\n");
  asserttrue(G.coins = playerOneOriginalCoinCount + 1);

  printf("\n-------------------- TEST 3 --------------------\n");
  printf("Updating coins with -2 bonus.\n");
  updateCoins(playerOne, &G, -2);
  printf("Asserting: G.coins = playerOneOriginalCoinCount - 1\n");
  asserttrue(G.coins = playerOneOriginalCoinCount - 1);

  printf("\n-------------------- TEST 4 --------------------\n");
  printf("Updating other player's coins with +1 bonus. \
	Player one coin count shouldn't change\n");
  updateCoins(playerTwo, &G, 1);
  printf("Asserting: G.coins = playerOneOriginalCoinCount - 1\n");
  asserttrue(G.coins = playerOneOriginalCoinCount - 1);

  if(asserterrors){
    printf("UNIT TEST 4 FAILED!!! (%d assertion errors)\n", asserterrors);
  }
  else {
    printf("UNIT TEST 4 PASSED!!!\n");
  }

  return 0;
}
