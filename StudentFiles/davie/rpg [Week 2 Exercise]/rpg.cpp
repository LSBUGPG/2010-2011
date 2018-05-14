#include "engine.h"

#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int answer;

start_game:
	srand(int(time(0)));

	creature player = { "player", 7, 5, 4, 20, 20 };
	creature nan = { "nan", 10, 8, 5, 18, 20 };

	do {
		_cputs(
			"\n"
			"You are in a dank house. Before you, in the darkness, you can make out the\n"
			"shape of your nan, nan bares her dentures and prepares to hug you.\n"
			"\n"
			"Will you:\n"
			"[f] fight off nan; or,\n"
			"[r] run?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'r') {
		goto run;
	}

	do {
		_cputs(
			"\n"
			"With a duster! Are you sure? Will you:\n"
			"[f] fight off nan with your duster; or,\n"
			"[r] run?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'f') {
		goto attack_nan;
	}
	
run:
	_cputs(
		"\n"
		"You run out of the house.\n"
		"You suddenly wake.\n"
		"\n");
	goto survivor;

attack_nan:
	battle_result result = do_battle(player, nan);

	switch (result) {
		case player_wins: 
			_cputs(
				"\n"
				"Incredibly, you fight and kill your nan with your duster! You wake, with\n"
				"newfound confidence. You are a true adventurer.\n"
				"\n");
			goto the_end;
		case nan_wins:
	 		_cputs(
				"\n"
				"As nan's closes in on you, you suddenly wake. You realise\n"
				"you do not have what it takes.\n"
				"\n");
			goto the_end;
		case player_runs:
			goto run;
	}
	
survivor:
	_cputs(
		"Your adventure is at an end. You have faced nan and yet live to tell the\n"
		"tale. You are a true survivor.\n"
		"\n");
	goto the_end;

the_end:
	_cputs(
		"The end.\n");

	do {
		_cputs(
			"\n"
			"[r] Restart this game.\n"
			"[q] Quit.\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "rq"));

	if (answer == 'r') {
		goto start_game;
	}
	
	return 0;
}
