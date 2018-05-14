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
			"No, that ain't it.\n"
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

	const int demon_initiative = 7;
	const int demon_hit_bonus = 5;
	const int demon_damage_bonus = 4;
	const int demon_defence = 20;
	int demon_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;

	do {
		_cputs(
			"\n"
			"The Cold, dark street lays littered with the filth it has accumulated over the years.\n"
			"As you step over the bones of the numerous creatures that expired on this very brickwork,\n"
			"you cannot escape the feeling that you are being followed, a sudden movement ahead makes you,\n"
			"look up, and there is a dark figure at the mouth of the street, parrallel to you, it's red eyes,\n"
			"gleaming and it's bloody fangs bared. You realize that a struggle is inevitable but the choice to fight,\n"
			"is yours alone..."
			"\n"
			"You must decide:\n"
			"[f] Fight and risk getting killed like the countless before you? or,\n"
			"[r] turn away and hope it ends quickly?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'r') {
		goto run;
	}

	do {
		_cputs(
			"\n"
			"Your heart starts to pound as your mind comprehends what you are about to do,\n"
			"There is no time for you to gather your wits as you prepare, the weapons that you,\n"
			"wield, have virtually no success rate as countless have proved before you, the creature\n"
			"beams, lovingly, like a mother, as it carresses you towards it, you must decide...\n"
			"[r] run and attack with all you have; or,\n"
			"[f] attempt to kick the bones towards it for a distraction before striking?\n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'f') {
		goto attack_demon;
	}
	
run:
	_cputs(
		"\n"
		"The creature lunges out with its tongue, its scaly texture wraps around your neck, you close your\n"
		"eyes hoping that it will end quickly and pray, but to whom, you do not know..."
		"\n");
	goto survivor;

attack_demon:
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		demon_turn 
	} phase = choose_initiative;
	while (player_is_attacking && demon_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + demon_initiative) {
					phase = player_turn;
				} else {
					phase = demon_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= demon_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit the demon for %d points of damage.\n", damage);
					demon_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"You missed.\n");
				}
				if (demon_hit_points > 0 && player_hit_points > 0) {
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
				phase = demon_turn;
				break;
			case demon_turn:
				if (roll(20) + demon_hit_bonus >= player_defence) {
					damage = roll(8) + demon_damage_bonus;
					_cprintf(
						"\n"
						"The demon hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"The demon missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (demon_hit_points <= 0)	{
 		_cputs(
			"\n"
			"Incredibly, you fight and kill the demon with your sword piercing  its heart! Perhaps all is not lost aftr all\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"As the demon's jaws close on your broken body you suddenly wake. You realise\n"
			"you do not have what it takes to be a true adventurer.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	
survivor:
	_cputs(
		"There is no hope for mankind, you think as your last breath is exhaled...\n"
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
