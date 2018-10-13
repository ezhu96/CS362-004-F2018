#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "asserttrue.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;

  printf ("Starting game (seed = %d).\n", seed);

  initializeGame(2, k, seed, &G);

  printf("\n-------------------- TEST 1 --------------------\n");
  printf("Asserting: supplyCount(adventurer, &G) == 10\n");
  asserttrue(supplyCount(adventurer, &G) == 10);

  printf("\n-------------------- TEST 2 --------------------\n");
  printf("G.supplyCount[adventurer] = 0;\n");
  G.supplyCount[adventurer] = 0;

  printf("Asserting: supplyCount(adventurer, &G) == 0\n");
  asserttrue(supplyCount(adventurer, &G) == 0);

  printf("\n-------------------- TEST 3 --------------------\n");
  printf("G.supplyCount[adventurer] = -10;\n");
  G.supplyCount[adventurer] = -10;

  printf("Asserting: supplyCount(adventurer, &G) == -10\n");
  asserttrue(supplyCount(adventurer, &G) == -10);

  return 0;
}
