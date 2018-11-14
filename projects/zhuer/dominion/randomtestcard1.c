#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include "asserttrue.h"
#include "rngs.h"

int getRandomInt() {
  return Random() * INT_MAX * pow(-1, floor(Random() * 2));
}

int checkSmithyCardEffect(int p, struct gameState *post) {
  printf("Checking Adventurer card effect.\n");
  struct gameState pre;
  int i;
  int drawnCoinValue = 0;
  int choice1 = getRandomInt();
  int choice2 = getRandomInt();
  int choice3 = getRandomInt();
  int handPos = floor(Random() * post->handCount[p] * 0.999);
  int bonus = getRandomInt();
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    
  r = drawCard (p, post);

  //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

  if (pre.deckCount[p] > 0) {
    pre.handCount[p]++;
    pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
    pre.deckCount[p]--;
  } else if (pre.discardCount[p] > 0) {
    memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
    memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
    pre.handCount[p]++;
    pre.deckCount[p] = pre.discardCount[p]-1;
    pre.discardCount[p] = 0;
  }

  assert (r == 0);

  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing drawCard.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkSmithyCardEffect(p, &G);
  }

  printf ("ALL TESTS OK\n");

  printf ("SIMPLE FIXED TESTS.\n");
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState)); 
	  r = initializeGame(2, k, 1, &G);
	  G.deckCount[p] = deckCount;
	  memset(G.deck[p], 0, sizeof(int) * deckCount);
	  G.discardCount[p] = discardCount;
	  memset(G.discard[p], 0, sizeof(int) * discardCount);
	  G.handCount[p] = handCount;
	  memset(G.hand[p], 0, sizeof(int) * handCount);
	  checkSmithyCardEffect(p, &G);
	}
      }
    }
  }

  return 0;
}
