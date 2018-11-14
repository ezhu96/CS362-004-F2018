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
  int preDeckTreasures = getTreasuresInDeck(p, &pre);

  if(preDeckTreasures < 2) {
    printf("Not enough treasures in deck. Test skipped.\n");
    return -1;
  }

  int r;
    
  r = cardEffect(adventurer, choice1, choice2, choice3, post, handPos, &bonus);

  asserttrue(r == 0);

  asserttrue(post->numPlayers == pre.numPlayers);
  for(i=0; i<treasure_map+1; i++){
    asserttrue(post->supplyCount[i] == pre.supplyCount[i]);
    asserttrue(post->embargoTokens[i] == pre.embargoTokens[i]);
  }
  asserttrue(post->outpostPlayed == pre.outpostPlayed);
  asserttrue(post->outpostTurn == pre.outpostTurn);
  asserttrue(post->whoseTurn == pre.whoseTurn);
  asserttrue(post->phase == pre.phase);
  asserttrue(post->numActions == pre.numActions);
  for(i=post->handCount[p]-2; i<post->handCount[p]; i++){
    if(post->hand[p][i] == copper){
      drawnCoinValue++;
    }
    else if(post->hand[p][i] == silver){
      drawnCoinValue+=2;
    }
    else if(post->hand[p][i] == gold){
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
  asserttrue(post->coins == pre.coins);
  asserttrue(post->numBuys == pre.numBuys);
  asserttrue(post->hand[p][handPos] == pre.hand[p][pre.handCount[p]-1]);
  for(i=handPos+1; i<pre.handCount[p]-1; i++){
    asserttrue(post->hand[p][i] == pre.hand[p][i]);
  }
  asserttrue(post->handCount[p] == pre.handCount[p]+1);
  for(i=0; i<pre.deckCount[p]-post->discardCount[p]; i++){
    asserttrue(post->deck[p][i] == pre.deck[p][i]);
  }
  asserttrue(post->deckCount[p] == pre.deckCount[p]-post->discardCount[p]-1);
  asserttrue(post->playedCards[0] == pre.hand[p][handPos]);
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
    checkAdventurerCardEffect(p, &G);
  }

  printf ("RANDOM TESTS END.\n");

  printf ("FIXED TESTS BEGIN (Random coppers in deck).\n");
  for (n = 0; n < 30; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * (MAX_DECK-2))+2;
    for (j = 0; j < 3; j++) {
      c = floor(Random() * (G.deckCount[p]-1));
      G.deck[p][c] = copper;
    }
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.playedCardCount = floor(Random() * (MAX_DECK-1));
    checkAdventurerCardEffect(p, &G);
  }

  return 0;
}
