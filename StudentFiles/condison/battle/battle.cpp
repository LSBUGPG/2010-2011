#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

bool wrong_answer(int have, const char * looking_for)
{
	bool wrong = (strchr(looking_for, have) == NULL);
	if (wrong) {
		_cputs(
			"\n"
			"no no no you pushed the WRONG KEY!.\n"
			"\n");
	}
	return wrong;
}

int roll(int sides)
{
	return (rand() % sides) + 1;
}

int main(int argc, char *argv[])
{
	int answer;

start_game:
	srand(int(time(0)));

	const int dragon_initiative = 1;
	const int dragon_hit_bonus = 57;
	const int dragon_damage_bonus = 1500;
	const int dragon_defence = 207;
	int dragon_hit_points = 207;

	const int player_initiative = 25;
	const int player_hit_bonus = 1;
	const int player_damage_bonus = 1;
	const int player_defence = 1;
	int player_hit_points = 20;

	do {
		_cputs(
			"\n"
			"You are in a dank cavern. Before you, in the darkness, you can make out the\n"
			"shape of an ancient dragon. The dragon bares its teeth and prepares to strike.\n"
			"\n"
			"she looks like a LVL100 creature Will you:\n"
			"[f] fight the dragon; or,\n"
			"[r] steal it's loot and run?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'r') {
		goto run;
	}

	do {
		_cputs(
			"\n"
			"The dragon draws closer\n" 
			"this looks like a good time to use your special attack Will you:\n"
			"[f] use your scream attack; or,\n"
			"[r] steel its loot and run back to the surface?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'f') {
		goto attack_dragon;
	}
	
run:
	_cputs(
		"\n"
		"succsessfully steeling its loot you run back to the gate\n"
		"well done you stole the incredabaly rare silver dragon teeth.\n"
		"\n");
	goto survivor;

attack_dragon:
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		dragon_turn 
	} phase = choose_initiative;
	while (player_is_attacking && dragon_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + dragon_initiative) {
					phase = player_turn;
				} else {
					phase = dragon_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= dragon_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit the dragon for %d points of damage.\n", damage);
					dragon_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"no effect the dragon seems to be growing more angry.\n");
					    "BLAST IT.\n" ;

				}
				if (dragon_hit_points > 0 && player_hit_points > 0) {
					do {
						_cputs(
							"\n"
							"Will you:\n"
							"[c] appologise and smile; or,\n"
							"[r] steel and run?"
							"\n>");
						answer = _getche();
					} while (wrong_answer(answer, "cr"));

					player_is_attacking = (answer == 'c');
				}
				phase = dragon_turn;
				break;
			case dragon_turn:
				if (roll(20) + dragon_hit_bonus >= player_defence) {
					damage = roll(8) + dragon_damage_bonus;
					_cprintf(
						"\n"
						"The dragon hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"The dragon missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (dragon_hit_points <= 0)	{
 		_cputs(
			"\n"
			"Incredibly, you fight and kill the dragon with your bare hands! You wake, with\n"
			"newfound confidence. You are a true adventurer.\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"As the dragon's jaws close on your broken body You realise\n"
			"ah nuts I was never gonna win that.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	
survivor:
	_cputs(
		"Your adventure is at an end. You have faced a dragon and stole its\n"
		"valuable silver teeth You are a true survivor.\n"
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
