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
	bool have_key;
	bool door_locked;

start_game:
	have_key = false;
	door_locked = true;
	srand(int(time(0)));

	const int satan_initiative = 7;
	const int satan_hit_bonus = 5;
	const int satan_damage_bonus = 4;
	const int satan_defence = 20;
	int satan_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;

	_cputs(
		"\n"
		"Hello and welcome to hell. To escape follow the descriptions and then\n"
		"choose how to act."
		"\n"
		"Good Luck pee head!\n"
		"\n");

describe_hell:
	_cputs(
		"You look around seeing the pure horror of hell. To the left is\n"
		"a dead giant demon. On the right there is a lava river.\n"
		
		"Do you:\n"
		"[p] Penetrate the demon with your fist; or\n"
		"[f] Follow the lava river?\n"
		"\n");

	answer = _getche();
	if (answer == 'p') {
		goto enter_demon;
	} else if (answer == 'f') {
		goto follow_lava;
	} else {
		goto unknown_pain;
	}

enter_demon:
	_cputs(
		"\n"
		"You push your hand up and inside the demon.\n"
		"\n");
	goto inside_demon;

follow_lava:
    _cputs(
        "\n"
        "You follow the lava river until you reach a point\n"
        "where it stops.\n"
        "\n");
    goto describe_lavabed;

unknown_pain:
	_cputs(
		"\n"
		"I did not understand.\n"
		"\n");
	goto describe_hell;

inside_demon:
	_cputs(
		"Your hand eases into the demons belly.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a soft, small alcove that a key\n"
			"would fit perfectly in.\n"
			"[r] Put the key back into the alcove; or,\n"
			"[g] Get your hand out this demon?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_demon;
		} else if (answer == 'r') {
			goto return_key;
		} else {
			goto unknown_demon;
		}
	} else {
		_cputs(
			"You feel there is a small metal key inside. Will you:\n"
			"[t] Take the key; or,\n"
			"[g] Get your hand out this demon?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_demon;
		} else if (answer == 't') {
			goto take_key;
		} else {
			goto unknown_demon;
		}
	}

leave_demon:
	_cputs(
		"\n"
		"You pull your hand out.\n"
		"\n");
	goto describe_hell;

return_key:
	_cputs(
		"\n"
		"You return the small key to its alcove.\n"
		"\n");
	have_key = false;
	goto inside_demon;

unknown_demon:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto inside_demon;

take_key:
	_cputs(
		"\n"
		"You take the small key and pull your hand out of the demon.\n"
		"\n");
	have_key = true;
	goto describe_hell;

describe_lavabed:
	_cputs(
		"You are at the end of the burning river. It flows into a sheer cliff face.\n"
		"There is a large metal door in the cliff face\n"
		"\n");

	if (door_locked && have_key) {
		_cputs(
			"The door is locked. It looks like the key you have fits the lock. Will you:\n"
			"[u] use the key to open the door; or,\n"
			"[g] go back along the lava river?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_hell;
		} else if (answer == 'u') {
			goto unlock_door;
		} else {
			goto unknown_lavabed;
		}
	
	} else if (door_locked) {
		goto return_for_key;
	} else if (have_key) {
		_cputs(
			"The door is unlocked. Will you:\n"
			"[l] lock the door;\n"
			"[e] enter through the door; or,\n"
			"[g] go back the way you came?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_hell;
		} else if (answer == 'e') {
			goto enter_cliff;
		} else if (answer == 'l') {
			goto lock_door;
		} else {
			goto unknown_lavabed;
		}

	} else {
		_cputs(
			"The door is unlocked. Will you:\n"
			"[e] enter through the door; or,\n"
			"[g] go back the way you came?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_hell;
		} else if (answer == 'e') {
			goto enter_cliff;
		} else {
			goto unknown_lavabed;
		}
	}

return_to_hell:
	_cputs(
		"\n"
		"You follow the lava river back to where you began.\n"
		"\n");
	goto describe_hell;

unlock_door:
	_cputs(
		"\n"
		"The key opens the lock and the door opens with a screech.\n"
		"\n");
	door_locked = false;
	goto enter_cliff;

	lock_door:
	_cputs(
		"\n"
		"As you lock the door you are shot by flaming arrows.\n"
		"\n");
	door_locked = true;
	goto failed_adventurer;

unknown_lavabed:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_lavabed;

return_for_key:
	_cputs(
		"The door is locked. You'll need a key to open it. You go back along the\n" 
		"lava river to look for one.\n"
		"\n");
	goto describe_hell;

enter_cliff:
	_cputs(
		"\n"
		"You enter through the door in a cavern lit by torches.\n"
		"\n");
	goto describe_cliff;

describe_cliff:
	_cputs(
		"You are in a poorly lit cavern. Just ahead of you, you can make out the\n"
		"the shape of Satan. Satan strokes his horns and prepares to attack.\n"
		"\n"
		"Will you:\n"
		"[f] fight Satan; or,\n"
		"[r] run back through the door?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto fight;
	} else if (answer == 'r') {
		goto run;
	} else {
		goto unknown_cliff;
	}

run:
	_cputs(
		"\n"
		"You run as fast you can and as you slam the door\n"
		"shut behind you, you suddenly wake.\n"
		"\n");
	goto survivor;

unknown_cliff:
	_cputs(
		"\n"
		"I did not understand.\n"
		"\n");
	goto describe_cliff;

fight:
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		satan_turn 
	} phase = choose_initiative;
	while (player_is_attacking && satan_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + satan_initiative) {
					phase = player_turn;
				} else {
					phase = satan_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= satan_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit Satan for %d points of damage.\n", damage);
					satan_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"You missed.\n");
				}
				if (satan_hit_points > 0 && player_hit_points > 0) {
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
				phase = satan_turn;
				break;
			case satan_turn:
				if (roll(20) + satan_hit_bonus >= player_defence) {
					damage = roll(8) + satan_damage_bonus;
					_cprintf(
						"\n"
						"Satan hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"Satan missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (satan_hit_points <= 0)	{
 		_cputs(
			"\n"
			"Incredibly, you fight and kill Satan and then escape hell\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"As Satan's horns protrude though your broken body\n"
			"you die painfully crying for mommy\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	

survivor:
	_cputs(
		"Your escape is at an end. You have looked satan in the eye\n"
		"and yet live to tell the tale. but your still stuck in hell.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"You died because your chicken.\n"
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

