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

int getTreasuresInDeck(int p, struct gameState *state) {
  int card;
  int treasures = 0;
  for(card = 0; card < state->deckCount[p]; card++) {
    if(state->deck[p][card] == copper || 
	state->deck[p][card] == silver || 
	state->deck[p][card] == gold) {
      treasures++;
    }
  }
  return treasures;
}

int checkAdventurerCardEffect(int p, struct gameState *post) {
  struct gameState pre;
  int i;
  int choice1 = getRandomInt();
  int choice2 = getRandomInt();
  int choice3 = getRandomInt();
  int handPos = floor(Random() * post->handCount[p] * 0.999);
  int bonus = getRandomInt();
  memcpy (&pre, post, sizeof(struct gameState));
  int preDeckTreasures = getTreasuresInDeck(p, &pre);

  if(preDeckTreasures < 2) {
    printf("Not enough treasures in deck. Test skipped.\n");
    return -1;
  }

  int r;
    
  r = cardEffect(adventurer, choice1, choice2, choice3, post, handPos, &bonus);

  asserttrue(r == 0);

  printf("Asserting (post->numPlayers == pre.numPlayers)\n");
  asserttrue(post->numPlayers == pre.numPlayers);
  printf("Asserting (post->supplyCount[i] == pre.supplyCount[i]) && (post->embargoTokens[i] == pre.embargoTokens[i])\n");
  for(i=0; i<treasure_map+1; i++){
    asserttrue(post->supplyCount[i] == pre.supplyCount[i]);
    asserttrue(post->embargoTokens[i] == pre.embargoTokens[i]);
  }
  printf("Asserting (post->outpostPlayed == pre.outpostPlayed)\n");
  asserttrue(post->outpostPlayed == pre.outpostPlayed);
  printf("Asserting (post->outpostTurn == pre.outpostTurn)\n");
  asserttrue(post->outpostTurn == pre.outpostTurn);
  printf("Asserting (post->whoseTurn == pre.whoseTurn)\n");
  asserttrue(post->whoseTurn == pre.whoseTurn);
  printf("Asserting (post->phase == pre.phase)\n");
  asserttrue(post->phase == pre.phase);
  printf("Asserting (post->numActions == pre.numActions)\n");
  asserttrue(post->numActions == pre.numActions);
  printf("Asserting (post->coins == pre.coins)\n");
  asserttrue(post->coins == pre.coins);
  printf("Asserting (post->numBuys == pre.numBuys)\n");
  asserttrue(post->numBuys == pre.numBuys);
  printf("Asserting asserttrue(post->hand[p][i] == pre.hand[p][i])\n");
  for(i=handPos+1; i<pre.handCount[p]-1; i++){
    asserttrue(post->hand[p][i] == pre.hand[p][i]);
  }
  printf("Asserting (post->handCount[p] == pre.handCount[p]+1)\n");
  asserttrue(post->handCount[p] == pre.handCount[p]+1);
  printf("Asserting asserttrue(post->deck[p][i] == pre.deck[p][i])\n");
  for(i=0; i<pre.deckCount[p]-post->discardCount[p]; i++){
    asserttrue(post->deck[p][i] == pre.deck[p][i]);
  }
  printf("Asserting (post->deckCount[p]+post->discardCount[p]<= pre.deckCount[p]+pre.discardCount[p])\n");
  asserttrue(post->deckCount[p]+post->discardCount[p]<= pre.deckCount[p]+pre.discardCount[p]);
  printf("Asserting (post->playedCards[post->playedCardCount-1] == pre.hand[p][handPos])\n");
  asserttrue(post->playedCards[post->playedCardCount-1] == pre.hand[p][handPos]);
  printf("Asserting (post->playedCardCount == pre.playedCardCount+1)\n");
  asserttrue(post->playedCardCount == pre.playedCardCount+1);
  return 0;
}

int main () {

  int c, i, j, n, p;

  struct gameState G;

  printf ("Testing cardEffect(adventurer).\n");

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
    printf("Random test #%d, Checking Adventurer card effect.\n", n);
    checkAdventurerCardEffect(p, &G);
  }

  printf ("RANDOM TESTS END.\n");

  printf ("FIXED TESTS BEGIN (Random coppers in deck).\n");
  for (n = 0; n < 30; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.whoseTurn = p;
    G.deckCount[p] = floor(Random() * (MAX_DECK-2))+2;
    for (j = 0; j < 3; j++) {
      c = floor(Random() * (G.deckCount[p]-1));
      G.deck[p][c] = copper;
    }
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.playedCardCount = floor(Random() * (MAX_DECK-1));
    printf("Fixed random test #%d, Checking Adventurer card effect.\n", n);
    checkAdventurerCardEffect(p, &G);
  }

  return 0;
}
