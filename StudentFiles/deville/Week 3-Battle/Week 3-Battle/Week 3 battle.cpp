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
			"I did not understand that answer.\n"
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

	const int dragon_initiative = 7;
	const int dragon_hit_bonus = 5;
	const int dragon_damage_bonus = 4;
	const int dragon_defence = 20;
	int dragon_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;

	do {
		_cputs(
			"\n"
			"You are on the 12th floor. As you exit the lift your target quickly turns\n"
			"and notices you. Panicked he quickly attacks you with a knife.\n"
			"\n"
			"Will you:\n"
			"[f] fight your target; or,\n"
			"[r] run back into the lift?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'r') {
		goto run;
	}

	do {
		_cputs(
			"\n"
			"Barehanded! He has a knife! Are you sure? Will you:\n"
			"[f] fight your target barehanded; or,\n"
			"[r] have second thoughts and run back into the lift?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'f') {
		goto attack_dragon;
	}
	
run:
	_cputs(
		"\n"
		"You quickly run back into the lift. As the doors open a bodyguard\n"
		"shoots you and you fall to the floor.\n"
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
						"You hit your target for %d points of damage.\n", damage);
					dragon_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"You missed.\n");
				}
				if (dragon_hit_points > 0 && player_hit_points > 0) {
					do {
						_cputs(
							"\n"
							"Will you:\n"
							"[c] continue to fight; or,\n"
							"[r] run away?"
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
						"The target hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"The target missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (dragon_hit_points <= 0)	{
 		_cputs(
			"\n"
			"You dodge the knife attacks of your target and deliver a quick blow to the\n"
		    "neck. Your target has been assassinated.\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"The target quickly stabs you in the chest and you fall to the floor.\n"
			"You have been killed and the target has escaped.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	
survivor:
	_cputs(
		"Your target has been assassinated and your mission is complete\n"
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