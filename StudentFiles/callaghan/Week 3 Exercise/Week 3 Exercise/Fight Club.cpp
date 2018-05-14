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
			"Choose already! \n"
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

	const int tyler_initiative = 7;
	const int tyler_hit_bonus = 5;
	const int tyler_damage_bonus = 4;
	const int tyler_defence = 20;
	int tyler_hit_points = 30;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 30;

	do {
		_cputs(
			"\n"
			"Welcome to Fight Club. Now before we start destroying something beautiful, \n"
			"you need to know the ground rules.\n"
			"\n"
			"\n"
			"1. You don't talk about fight club.\n"
			"\n"
			"2. You don't talk about fight club.\n"
			"\n"
			"3. When someone says stop, or goes limp, the fight is over. \n"
			"\n"
			"4. As this is your first night at fight club, you have to fight. \n"
			"\n"
			"\n"
			"Now hit me as hard as you can. \n"
			"\n"
			"[1] HIT TYLER \n"
			"\n"
			"[2] RUN AWAY\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "12"));

	if (answer == '2') {
		goto run;
	}

	do {
		_cputs(
			"\n"
			"\n"
			"* * * You hit TYLER for 3 points * * * \n"
			"\n"
			"You call that a beating? Hit me harder! \n"
			"\n"
			"[1] HIT TYLER AGAIN BUT HARDER \n"
			"\n"
			"[2] RUN AWAY \n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "12"));

	if (answer == '1') {
		goto attack_tyler;
	}

	run:
	_cputs(
		"\n"
		"* * * You run away from FIGHT CLUB * * * \n"
		"\n");
	goto loser;

attack_tyler:
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		tyler_turn 
	} phase = choose_initiative;
	while (player_is_attacking && tyler_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + tyler_initiative) {
					phase = player_turn;
				} else {
					phase = tyler_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= tyler_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"\n"
						"* * * You hit TYLER for %d points of damage * * *\n"
						"\n"
						"Now that's more like it. \n", damage);
					tyler_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"\n"
						"You missed.\n");
				}
				if (tyler_hit_points > 0 && player_hit_points > 0) {
					do {
						_cputs(
							"\n"
							"Will you:\n"
							"\n"
							"[1] CONTINUE TO FIGHT \n"
							"\n"
							"[2] RUN AWAY? \n"
							"\n>");
						answer = _getche();
					} while (wrong_answer(answer, "12"));

					player_is_attacking = (answer == '1');
				}
				phase = tyler_turn;
				break;
			case tyler_turn:
				if (roll(20) + tyler_hit_bonus >= player_defence) {
					damage = roll(8) + tyler_damage_bonus;
					_cprintf(
						"\n"
						"\n"
						"* * * TYLER hit you for %d points of damage.\n"
						"\n"
						"Felt good, right? \n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"\n"
						"TYLER missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (tyler_hit_points <= 0)	{
 		_cputs(
			"\n"
			"WINNER! TYLERS broken body hits the ground in a heap. You never felt anything\n"
			"like that before. Welcome to Fight Club.\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"LOSER: As TYLERS gives the final punch, your body goes limp. You realise\n"
			"you never had what it took to be in Fight Club.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	
loser:
	_cputs(
		"\n"
		"You'll be back once reality starts to kick in, low life.\n"
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