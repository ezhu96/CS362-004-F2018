#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include "asserttrue.h"
#include "rngs.h"

//returns random integer between negative INT_MAX and positive INT_MAX
int getRandomInt() {
  return Random() * INT_MAX * pow(-1, floor(Random() * 2));
}

int checkSmithyCardEffect(int p, struct gameState *post) {
  struct gameState pre;
  int i;
  int choice1 = getRandomInt();
  int choice2 = getRandomInt();
  int choice3 = getRandomInt();
  int handPos = floor(Random() * post->handCount[p] * 0.999);
  int bonus = getRandomInt();
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  
  r = cardEffect(smithy, choice1, choice2, choice3, post, handPos, &bonus);

  for (i=0; i<3; i++){  
  
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

  }
  //smithy played
  discardCard(handPos, p, &pre, 0);

  asserttrue(r == 0);
  asserttrue(memcmp(&pre, post, sizeof(struct gameState)) == 0);

  return 0;
}

int main () {

  int i, n, p;

  struct gameState G;

  printf ("Testing Smithy card effect.\n");

  printf ("RANDOM TESTS BEGIN.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 5000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.whoseTurn = p;
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.playedCardCount = floor(Random() * (MAX_DECK-1));
    printf("Random test #%d: checking Smithy card effect.\n", n);
    checkSmithyCardEffect(p, &G);
  }

  printf ("RANDOM TESTS END. Assertion errors: %d\n", asserterrors);

  return 0;
}
