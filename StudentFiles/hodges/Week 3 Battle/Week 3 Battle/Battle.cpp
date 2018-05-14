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
			"You are in a dark office. From the darkness steps the office patrol\n"
		    "the security guard is carrying a baton. He runs at you .\n"
			"\n"
			"Will you:\n"
			"[f] fight the security guard; or,\n"
			"[r] run back into the corridor?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'r') {
		goto run;
	}

	do {
		_cputs(
			"\n"
			"Barehanded! The guard is armed! Are you sure? Will you:\n"
			"[f] fight the guard barehanded; or,\n"
			"[r] think better of it run back into the corridor?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'f') {
		goto attack_dragon;
	}
	
run:
	_cputs(
		"\n"
		"You quickly run from the room and slam the door behind you.\n" 
		"As you turn back into the corridor. You see a guard with a gun\n"
		"he shoots you. You fall to the floor\n"
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
						"You hit the security guard for %d points of damage.\n", damage);
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
						"The security guard hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"The guard missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (dragon_hit_points <= 0)	{
 		_cputs(
			"\n"
			"The guard swings his baton at you. You parry his attack\n" 
		    "and knock him out! You quickly grab the file from the desk,\n"
		    "You smash through the window and pull your parachute cord.\n"
		    "you glide in the air and land on a nearby rooftop.\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"As the guard brings down his baton on your skull you black out\n"
			" you are taken hostage. The mission was a failure.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	
survivor:
	_cputs(
		"Your mission is over. You retrived the documents and got them back to HQ!\n"
		"Your superiors will take it from here. Good job!\n"
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