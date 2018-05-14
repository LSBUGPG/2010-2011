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

	const int werewolf_initiative = 7;
	const int werewolf_hit_bonus = 5;
	const int werewolf_damage_bonus = 4;
	const int werewolf_defence = 20;
	int werewolf_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;

	_cputs(
		"\n"
		"Hello, young kindred. Your initiation test is about to begin. Follow the instructions as you go along."
		"Good luck, you'll be a vampiric minion before sunrise."
		"\n"
		"Which is in an hour, so get a move on!\n"
		"\n");

describe_crypt:
	_cputs(
		"Within this crypt below the graveyard, you look at two doors. To the left is\n"
		"the entrance to the outside world full of humanity, yuck. On the right there is a door that leads to where quitters go.\n"
		
		"Do you:\n"
		"[p] Open the door with your minor super strength; or\n"
		"[f] Follow the back corridor of shame?\n"
		"\n");

	answer = _getche();
	if (answer == 'p') {
		goto enter_door;
	} else if (answer == 'f') {
		goto follow_corridor;
	} else {
		goto unknown_pain;
	}

enter_door:
	_cputs(
		"\n"
		"You push your hand up and inside the door.\n"
		"\n");
	goto inside_door;

follow_corridor:
    _cputs(
        "\n"
        "You follow the loser's corridor until you reach a point where you even more of a pussy.\n"
        "where it stops.\n"
        "\n");
    goto describe_corridorbed;

unknown_pain:
	_cputs(
		"\n"
		"I did not understand.\n"
		"\n");
	goto describe_crypt;

inside_door:
	_cputs(
		"Your hand eases into the doors knob.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a soft, subple human who's neck has a key lodged in it's bite marks.\n"
			"would fit perfectly in.\n"
			"[r] Put the key back into the alcove; or,\n"
			"[g] Get your hand out this door?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_door;
		} else if (answer == 'r') {
			goto return_key;
		} else {
			goto unknown_door;
		}
	} else {
		_cputs(
			"You notice the key is already inside the lock. Will you:\n"
			"[t] Unlock the door and proceed; or,\n"
			"[g] Lock the door and cower in the corner like a worthless piece of shit you are?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_door;
		} else if (answer == 't') {
			goto take_key;
		} else {
			goto unknown_door;
		}
	}

leave_door:
	_cputs(
		"\n"
		"You pull your hand out.\n"
		"\n");
	goto describe_crypt;

return_key:
	_cputs(
		"\n"
		"You return the small key to its original place.\n"
		"\n");
	have_key = false;
	goto inside_door;

unknown_door:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto inside_door;

take_key:
	_cputs(
		"\n"
		"You take the key and pull it out of the door.\n"
		"\n");
	have_key = true;
	goto describe_crypt;

describe_corridorbed:
	_cputs(
		"You are at the end of the corridor. There lies a large room.\n"
		"There is something in the middle of it.\n"
		"\n");

	if (door_locked && have_key) {
		_cputs(
			"The door is locked. It looks like the key you have fits the lock. Will you:\n"
			"[u] use the key to open the door; or,\n"
			"[g] go back through the corridor?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_crypt;
		} else if (answer == 'u') {
			goto unlock_door;
		} else {
			goto unknown_corridorbed;
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
			goto return_to_crypt;
		} else if (answer == 'e') {
			goto enter_cliff;
		} else if (answer == 'l') {
			goto lock_door;
		} else {
			goto unknown_corridorbed;
		}

	} else {
		_cputs(
			"The door is unlocked. Will you:\n"
			"[e] enter through the door; or,\n"
			"[g] go back the way you came?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_crypt;
		} else if (answer == 'e') {
			goto enter_cliff;
		} else {
			goto unknown_corridorbed;
		}
	}

return_to_crypt:
	_cputs(
		"\n"
		"You follow the corridor back to where you began.\n"
		"\n");
	goto describe_crypt;

unlock_door:
	_cputs(
		"\n"
		"The key opens the lock and the door opens with a creeking screech.\n"
		"\n");
	door_locked = false;
	goto enter_cliff;

	lock_door:
	_cputs(
		"\n"
		"As you lock the door you are shot by vivid images of human blood.\n"
		"\n");
	door_locked = true;
	goto failed_adventurer;

unknown_corridorbed:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_corridorbed;

return_for_key:
	_cputs(
		"The door is locked. You'll need a key to open it. You go back along the\n" 
		"corridorto look for one.\n"
		"\n");
	goto describe_crypt;

enter_cliff:
	_cputs(
		"\n"
		"You enter through the door in a cavern lit by torches.\n"
		"\n");
	goto describe_cliff;

describe_cliff:
	_cputs(
		"You are in a decrepit tomb. Just ahead of you, you can make out what seems to be a beastly\n"
		"figure covered in chains, probably a werewolf. It growls and looks at you with lustrous hunger and prepares to attack.\n"
		"\n"
		"Will you:\n"
		"[f] fight Wolfy; or,\n"
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
		"shut behind you, you suddenly crap your pants.\n"
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
		werewolf_turn 
	} phase = choose_initiative;
	while (player_is_attacking && werewolf_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + werewolf_initiative) {
					phase = player_turn;
				} else {
					phase = werewolf_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= werewolf_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit werewolf for %d points of damage.\n", damage);
					werewolf_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"You missed.\n");
				}
				if (werewolf_hit_points > 0 && player_hit_points > 0) {
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
				phase = werewolf_turn;
				break;
			case werewolf_turn:
				if (roll(20) + werewolf_hit_bonus >= player_defence) {
					damage = roll(8) + werewolf_damage_bonus;
					_cprintf(
						"\n"
						"werewolf hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"werewolf missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (werewolf_hit_points <= 0)	{
 		_cputs(
			"\n"
			"Incredibly, you fight and kill the werewolf and then escape the crypt and thus the test is complete, or so you assume...\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"As the werewolf's claws and rips through your body\n"
			"you cry on a puddle of blood, in horrible agony and then you die.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	

survivor:
	_cputs(
		"Your escape is at an end. You have looked werewolf in the eyes\n"
		"and yet live to tell the tale. However you're still stuck in the crypt and you're thirsty for blood.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"You died because you were reckless.\n"
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

