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

	const int goons_initiative = 7;
	const int goons_hit_bonus = 5;
	const int goons_damage_bonus = 4;
	const int goons_defence = 20;
	int goons_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;

	do {
	_cputs(
		"\n"
		"Welcome to the adventure. To play, I will describe your situation, and you must\n"
		"choose what to do."
		"\n"
		"Good luck adventurer!\n"
		"\n");

describe_beginning:
	_cputs(
		"\n"
		"You are in your favourite comic book store, reading the latest battle between \n"
		"the hero Quantum!! and his nemesis The Reaper!.\n"
		"Then all of a sudden the door slams open, wind rushing in and you see the silouhette of a man in a long trenchcoat\n"
		"then all you see is a flash of white, looking around you see you are inside Quantums headquarters, you think this cant be happening\n"
		"you turn and walk towards the doorway, towards a long corridor \n"
		"\n"
		"Will you:\n"
		"[c] continue on; through the corridor or,\n"
		"[g] go back to the main room and call for help?\n"
		"\n>");

	answer = _getche();
	if (answer == 'c') {
		goto enter_corridor;
	} else if (answer == 'g') {
		goto follow_back;
	} else {
		goto comic_book;
	}

comic_book:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_beginning;

follow_back:
    _cputs(
       "\n"
        "you turn back walking into the main room, approaching the main computer\n"
        "you press the Quantum button.\n"
        "\n");
    goto describe_main;
enter_corridor:
    _cputs(
       "\n"
        "you go through a small hallway to a large open room.\n"
        "\n");
    goto describe_room;

describe_room:
	_cputs(
		"\n"
		"you are in a vast room with a glass front, you look out to see the clean empire city.\n"
		"Will you...\n"
		"\n"
		"[l] continue on; leave the headquarters, head into empire bay or,\n"
		"[g] go back?\n"
		"\n>");

		answer = _getche();
	if (answer == 'l') {
		goto enter_empire;
	} else if (answer == 'g') {
		goto enter_corridor;
	} else {
		goto comic_book;
	}

enter_empire:
	_cputs(
		"\n"
		"you walk into the vast city,\n"
		"a stream of police cars zoom past\n"
		"'i have to get to Quantum, this must be a dream'\n"
		"will you?\n"
		"\n"
		"[f] follow the police cars?\n"
		"[g]go back?\n"
		"\n");

			answer = _getche();
	if (answer == 'f') {
		goto enter_scene;
	} else if (answer == 'g') {
		goto describe_room;
	} else {
		goto comic_book;
	}

enter_scene:
	_cputs(
		"\n"
		"you arrive at the scene,\n"
		"Quantum is standing there before you, he looks human\n"
		"approaching him you say\n"
		"'quantum will you...\n"
		"[h] help me?\n"
		"[n]ahh nevermind youre probably busy?\n"
		"\n");
				answer = _getche();
	if (answer == 'h') {
		goto help_me;
	} else if (answer == 'n') {
		goto nevermind;
	} else {
		goto comic_book;
	}

help_me:
	_cputs(
		"\n"
		"'of course citizen' he says,\n"
		"'i am yourr biggest fan, some how ive been sent into your comic book'\n"
		"he laughs, 'Im not joking! this is serious' you say falling to your knees\n"
		"'young man i am Quantum, i was created by that nuclear explosion'\n"
		"you stand up, looking in him the face you say....\n"
		"\n"
		"[h] please i you have to help me i am lost\n"
		"[a]youre right you cant help me [attack]?\n"
		"\n");
					answer = _getche();
	if (answer == 'h') {
		goto battle;
	} else if (answer == 'n') {
		goto nevermind;
	} else {
		goto comic_book;
	}

nevermind:
	_cputs(
		"\n"
			"'of course citizen' he says,\n"
		"'i am yourr biggest fan, some how ive been sent into your comic book'\n"
		"he laughs, 'Im not joking! this is serious' you say falling to your knees\n"
		"'young man i am Quantum, i was created by that nuclear explosion'\n"
		"you stand up, looking in him the face you say....\n"
		"\n"
		"[h] please i you have to help me i am lost\n"
		"[a]youre right you cant help me [attack]?\n"
		"\n");
				answer = _getche();
	if (answer == 'h') {
		goto battle;
	} else if (answer == 'a') {
		goto battle;
	} else {
		goto comic_book;
	}

describe_main:
	_cputs(
		"\n"
		"You press the Quantum button'\n"
		"then he teleports in,\n"
		"and you say \n"
		"\n"
		"[h] help me Quantum i'm not supposed to be here\n"
		"[l] haha i have you now Quantum, reaper will be happy!|n"
		"\n");

			answer = _getche();
	if (answer == 'h') {
		goto battle;
	} else if (answer == 'l') {
		goto battle;
	} else {
		goto comic_book;
	}

battle:
		_cputs(
			"\n"
			"At this moment a group of reaper goons drop into the headquarters\n"
			"you stand next to quantum, your hero.\n"
			"\n"
			"Will you:\n"
			"[f] fight with him; or,\n"
			"[r] or run away?\n"
			"\n>");

		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'f') {
		goto attack_goons;
	}
	
run:
	_cputs(
		"\n"
		"you run out of the building, into a swarm of people\n"
		"your head spins and everything goes black.\n"
		"\n");
	goto survivor;

attack_goons:
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		goons_turn 
	} phase = choose_initiative;
	while (player_is_attacking && goons_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + goons_initiative) {
					phase = player_turn;
				} else {
					phase = goons_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= goons_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit the goons for %d points of damage.\n", damage);
					goons_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"You missed.\n");
				}
				if (goons_hit_points > 0 && player_hit_points > 0) {
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
				phase = goons_turn;
				break;
			case goons_turn:
				if (roll(20) + goons_hit_bonus >= player_defence) {
					damage = roll(8) + goons_damage_bonus;
					_cprintf(
						"\n"
						"The goons hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"The goons missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (goons_hit_points <= 0)	{
 		_cputs(
			"\n"
			"you and Quantum, your hero, defeat the goons,\n"
			"he shakes your hand and you stand there, ready for aything.\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"you collapse, everything goes black\n"
			"you awaken in the comic shop, dzed and confused.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	
survivor:
	_cputs(
		"you feel though this is your destiny, to fight with your hero\n"
		"you're here now, ready for anything.\n"
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


to_be_continued:
	_cputs(
		"\n"
		"to be continued!\n"
		"[r] restart.\n"
		"[q] Quit.\n"
		"\n>");

	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto to_be_continued;
	}
	
quit:
	return 0;
}
