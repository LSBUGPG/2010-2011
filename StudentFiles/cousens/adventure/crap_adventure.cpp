#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]);

bool wrong_answer(int have, const char * looking_for)
{
	bool wrong = (strchr(looking_for, have) == NULL);
	if (wrong) {
		_cputs(
			"\n"
			"Come again?.\n"
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
	bool have_turd;
	bool bog_locked;

start_game:
	have_turd = false;
	bog_locked = true;
	srand(int(time(0)));

	const int turdgod_initiative = 7;
	const int turdgod_hit_bonus = 5;
	const int turdgod_damage_bonus = 4;
	const int turdgod_defence = 20;
	int turdgod_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;

	_cputs(
		"\n"
		"Hello Citizen, welcome to your life."
		"\n"
		"Good Luck...\n"
		"\n");

describe_toilet: //describe toilet
	_cputs(
		"You're in a toilet. To the left is\n"
		"a wooden cubicle. On the right there is a stream.\n"
		
		"Do you:\n"
		"[p] Enter the cubicle; or\n"
		"[f] Follow the stream?\n"
		"\n");

	answer = _getche();
	if (answer == 'p') {
		goto enter_cubicle;
	} else if (answer == 'f') {
		goto follow_stream;
	} else {
		goto unknown_pain;
	}

enter_cubicle:
	_cputs(
		"\n"
		"You enter the cubicle, it's dank and musty.\n"
		"\n");
	goto inside_cubicle;

follow_stream:
    _cputs(
        "\n"
        "You follow the stream\n"
        "\n");
    goto describe_alcove;

unknown_pain:
	_cputs(
		"\n"
		"Come again?.\n"
		"\n");
	goto describe_toilet;

inside_cubicle:
	_cputs(
		"You looks around the cubicle.\n"
		"\n");

	if (have_turd) {
		_cputs(
			"A bare hook on the wall\n"
			"[r] Put the turd back onto the hook; or,\n"
			"[g] Leave the cubicle?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_cubicle;
		} else if (answer == 'r') {
			goto return_turd;
		} else {
			goto unknown_cubicle;
		}
	} else {
		_cputs(
			"There is a small unicorn turd hanging on a hook. Will you:\n"
			"[t] Take the turd; or,\n"
			"[g] Leave the cubicle?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_cubicle;
		} else if (answer == 't') {
			goto take_turd;
		} else {
			goto unknown_cubicle;
		}
	}

leave_cubicle:
	_cputs(
		"\n"
		"You leave the cubicle.\n"
		"\n");
	goto describe_toilet;

return_turd:
	_cputs(
		"\n"
		"You return the small turd to its hook.\n"
		"\n");
	have_turd = false;
	goto inside_cubicle;

unknown_cubicle:
	_cputs(
		"\n"
		"Come again?.\n"
		"\n");
	goto inside_cubicle;

take_turd:
	_cputs(
		"\n"
		"You take the small turd and leave the cubicle.\n"
		"\n");
	have_turd = true;
	goto describe_toilet;

describe_alcove:
	_cputs(
		"You come to the end of the stream. It flows into a small alcove.\n"
		"There is a metal bog in the alcove.\n"
		"\n");

	if (bog_locked && have_turd) {
		_cputs(
			"The bog is locked, but the turd you have looks like it'd fit it. Will you:\n"
			"[u] use the turd to open the bog; or,\n"
			"[g] go back along the stream?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_toilet;
		} else if (answer == 'u') {
			goto unlock_bog;
		} else {
			goto unknown_alcove;
		}
	
	} else if (bog_locked) {
		goto return_for_turd;
	} else if (have_turd) {
		_cputs(
			"The bog is unlocked. Will you:\n"
			"[l] lock the bog;\n"
			"[e] Swim through the bog; or,\n"
			"[g] go back the way you came?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_toilet;
		} else if (answer == 'e') {
			goto enter_sewer;
		} else if (answer == 'l') {
			goto lock_bog;
		} else {
			goto unknown_alcove;
		}

	} else {
		_cputs(
			"The bog is unlocked. Will you:\n"
			"[e] enter through the bog; or,\n"
			"[g] go back the way you came?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_toilet;
		} else if (answer == 'e') {
			goto enter_sewer;
		} else {
			goto unknown_alcove;
		}
	}

return_to_toilet:
	_cputs(
		"\n"
		"You follow the stream back to the toilet.\n"
		"\n");
	goto describe_toilet;

unlock_bog:
	_cputs(
		"\n"
		"You sqeeze the turd into the mouth of the bog and it opens.\n"
		"\n");
	bog_locked = false;
	goto enter_sewer;

	lock_bog:
	_cputs(
		"\n"
		"You pull the turd out and the bog locks.\n"
		"\n");
	bog_locked = true;
	goto failed_adventurer;

unknown_alcove:
	_cputs(
		"\n"
		"Come again?.\n"
		"\n");
	goto describe_alcove;

return_for_turd:
	_cputs(
		"The bog is locked. You'll need something to open it.\n" 
		"You go back along the stream to look for something.\n"
		"\n");
	goto describe_toilet;

enter_sewer:
	_cputs(
		"\n"
		"You swim through the bog into a sewer.\n"
		"\n");
	goto describe_sewer;

describe_sewer:
	_cputs(
		"You are in a sewer. You have angered the turd god by taking.\n"
		"the sacred unicorn turd. The turdgod attacks.\n"
		"\n"
		"Will you:\n"
		"[f] fight turd god; or,\n"
		"[r] swim back through the bog?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto fight;
	} else if (answer == 'r') {
		goto run;
	} else {
		goto unknown_sewer;
	}

run:
	_cputs(
		"\n"
		"As you swim back through the bog you hear the turd god roar\n"
		"the bog shuts behind you, you find yourself back in the toilet.\n"
		"\n");
	goto survivor;

unknown_sewer:
	_cputs(
		"\n"
		"Come again?.\n"
		"\n");
	goto describe_sewer;

fight:
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		turdgod_turn 
	} phase = choose_initiative;
	while (player_is_attacking && turdgod_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + turdgod_initiative) {
					phase = player_turn;
				} else {
					phase = turdgod_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= turdgod_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit turd god for %d points of damage.\n", damage);
					turdgod_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"You missed.\n");
				}
				if (turdgod_hit_points > 0 && player_hit_points > 0) {
					do {
						_cputs(
							"\n"
							"Will you:\n"
							"[c] continue to fight; or,\n"
							"[r] swim away?"
							"\n>");
						answer = _getche();
					} while (wrong_answer(answer, "cr"));

					player_is_attacking = (answer == 'c');
				}
				phase = turdgod_turn;
				break;
			case turdgod_turn:
				if (roll(20) + turdgod_hit_bonus >= player_defence) {
					damage = roll(8) + turdgod_damage_bonus;
					_cprintf(
						"\n"
						"turd god hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"turd god missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (turdgod_hit_points <= 0)	{
 		_cputs(
			"\n"
			"Incredibly, you fight and kill turd god and then escape toilet\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"the turd god ravishes your body\n"
			"you die\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	

survivor:
	_cputs(
		"You ran citizen, and so you survive\n"
		"But you're a coward, enjoy eternity in a toilet.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"Curiosity killed the cat, but citizens aren't cats.\n"
		"You no longer interest the powers that be and so you die.\n"
		"\n");

the_end:
	_cputs(
		"The end.\n");

restart_or_quit:
	_cputs(
		"\n"
		"[r] Restart this game.\n"
		"[q] Quit.\n"
		"\n>");

	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto restart_or_quit;
	}
	
quit:
	return 0;
}

