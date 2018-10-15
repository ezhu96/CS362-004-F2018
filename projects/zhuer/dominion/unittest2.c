#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "asserttrue.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int dominionCompare(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

void testShuffle(struct gameState *state) {

  int playerOne = 0;
  int originalDeckCount;
  int originalDeck[10];
  int shuffledOnceDeck[10];
  int shuffledTwiceDeck[10];
  int orderedSame = 0;
  int i;

  originalDeckCount = state->deckCount[playerOne];

  printf("Before shuffle: card numbers {\n");
  for(i=0; i<originalDeckCount; i++)
  {
    printf("\t%d\n", state->deck[playerOne][i]);
    originalDeck[i] = state->deck[playerOne][i];
  }
  printf("}\n");

  printf("\nShuffling...\n");
  if(shuffle(playerOne, state)!=0)
  {
    printf("Didn't shuffle...\n");
  }

  printf("After one shuffle: card numbers {\n");
  for(i=0; i<originalDeckCount; i++)
  {
    shuffledOnceDeck[i] = state->deck[playerOne][i];
    printf("\t%d\n", shuffledOnceDeck[i]);
    if(originalDeck[i] == shuffledOnceDeck[i])
    {
      orderedSame++;
    }
  }
  printf("}\n");
  if(state->deckCount[playerOne] != originalDeckCount)
  {
    printf("\nDECK COUNT CHANGED AFTER SHUFFLING!!!\n");
  }
  if(orderedSame < originalDeckCount)
  {
    orderedSame = 0;
  }
  else
  {
    printf("\nORDER DID NOT CHANGE AFTER FIRST SHUFFLE!!!\n");
  }

  printf("\nShuffling...\n");
  if(shuffle(playerOne, state)!=0)
  {
    printf("Didn't shuffle...\n");
  }

  printf("After two shuffles: card numbers {\n");
  for(i=0; i<originalDeckCount; i++)
  {
    shuffledTwiceDeck[i] = state->deck[playerOne][i];
    printf("\t%d\n", shuffledTwiceDeck[i]);
    if(originalDeck[i] == shuffledTwiceDeck[i])
    {
      orderedSame++;
    }
  }
  printf("}\n");
  if(state->deckCount[playerOne] != originalDeckCount)
  {
    printf("\nDECK COUNT CHANGED AFTER SHUFFLING!!!\n");
  }
  if(orderedSame >= originalDeckCount)
  {
    printf("\nORDER DID NOT CHANGE AFTER SECOND SHUFFLE!!!\n");
    if(orderedSame == 2 * originalDeckCount)
    {
      printf("\nBOTH SHUFFLES DID NOT CHANGE THE ORDER!!!\n");
    }
  }

  qsort ((void*)(originalDeck), originalDeckCount, sizeof(int), dominionCompare); 
  qsort ((void*)(shuffledOnceDeck), originalDeckCount, sizeof(int), dominionCompare); 
  qsort ((void*)(shuffledTwiceDeck), originalDeckCount, sizeof(int), dominionCompare); 

  for(i=0; i<originalDeckCount; i++)
  {
    if(originalDeck[i] != shuffledOnceDeck[i] || 
	originalDeck[i] != shuffledTwiceDeck[i])
    {
      printf("\nCARDS HAVE CHANGED AFTER SHUFFLING!!!\n");
      break;
    }
  }
}

//Unit test for the shuffle() function found in dominion.c
int main()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  int seed = 2;

  printf("\n==================================================\n");
  printf("UNIT TEST 2: shuffle()\n");
  printf("==================================================\n\n"); 

  printf ("Starting game (seed = %d).\n", seed);
  initializeGame(2, k, seed, &G);

  testShuffle(&G);

  printf("\nDrawing a card, then repeating the tests...\n");
  drawCard(0, &G);

  testShuffle(&G);

  if(asserterrors){
    printf("UNIT TEST 2 FAILED!!! (%d assertion errors)\n", asserterrors);
  }
  else {
    printf("UNIT TEST 2 PASSED!!!\n");
  }

  return 0;
}
