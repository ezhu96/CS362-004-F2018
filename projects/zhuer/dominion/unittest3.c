#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "asserttrue.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Unit test for the getCost() function found in dominion.c
int main()
{
  int cases[27] = {
	curse,
	estate,
	duchy,
	province,
	copper,
	silver,
	gold,
	adventurer,
	council_room,
	feast,
	gardens,
	mine,
	remodel,
	smithy,
	village,
	baron,
	great_hall,
	minion,
	steward,
	tribute,
	ambassador,
	cutpurse,
	embargo,
	outpost,
	salvager,
	sea_hag,
	treasure_map
  };
  int i;
  int devil = 666;

  printf("Testing getCost of cards: curse, estate, duchy, province, copper, silver, gold, adventurer, council room, feast, gardens, mine, remodel, smithy, village, baron, great hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea hag, and treasure map.\n");
  
  for(i=0; i<27; i++)
  {
    switch( cases[i] )
    {
      case curse:
        asserttrue(getCost(cases[i]) == 0);
        break;
      case estate:
        asserttrue(getCost(cases[i]) == 2);
        break;
      case duchy:
        asserttrue(getCost(cases[i]) == 5);
        break;
      case province:
        asserttrue(getCost(cases[i]) == 8);
        break;
      case copper:
        asserttrue(getCost(cases[i]) == 0);
        break;
      case silver:
        asserttrue(getCost(cases[i]) == 3);
        break;
      case gold:
        asserttrue(getCost(cases[i]) == 6);
        break;
      case adventurer:
        asserttrue(getCost(cases[i]) == 6);
        break;
      case council_room:
        asserttrue(getCost(cases[i]) == 5);
        break;
      case feast:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case gardens:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case mine:
        asserttrue(getCost(cases[i]) == 5);
        break;
      case remodel:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case smithy:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case village:
        asserttrue(getCost(cases[i]) == 3);
        break;
      case baron:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case great_hall:
        asserttrue(getCost(cases[i]) == 3);
        break;
      case minion:
        asserttrue(getCost(cases[i]) == 5);
        break;
      case steward:
        asserttrue(getCost(cases[i]) == 3);
        break;
      case tribute:
        asserttrue(getCost(cases[i]) == 5);
        break;
      case ambassador:
        asserttrue(getCost(cases[i]) == 3);
        break;
      case cutpurse:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case embargo: 
        asserttrue(getCost(cases[i]) == 2);
        break;
      case outpost:
        asserttrue(getCost(cases[i]) == 5);
        break;
      case salvager:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case sea_hag:
        asserttrue(getCost(cases[i]) == 4);
        break;
      case treasure_map:
        asserttrue(getCost(cases[i]) == 4);
        break;
    }
  } 

  printf("\nTesting getCost of non-existant card, devil. (It should return -1)\n");
  asserttrue(getCost(devil) == -1);

  return 0;
}
