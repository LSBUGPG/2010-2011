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
			"No time for gibberish, tell me what you're going to do!\n"
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
	bool swipe_card;
	bool door_locked;

start_game:
	srand(int(time(0)));

	const int alien_initiative = 7;
	const int alien_hit_bonus = 5;
	const int alien_damage_bonus = 4;
	const int alien_defence = 20;
	int alien_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;
	swipe_card = false;
	door_locked = true;

	_cputs(
		"\n"
		"You are chased by aliens. I will watch your back, but you must\n"
		"choose what to do."
		"\n"
		"Find the card!\n"
		"\n");

stage_one_aliens:
	_cputs(
		"Look there is a rusty door on your left.\n"
		"You might try to break it with the chair on your right and escape.\n"
		"\n"
		"[b] Break the door; or,\n"
		"[c] Continue running?\n"
		"\n");

	answer = _getche();
	if (answer == 'b') {
		goto broken_door;
	} else if (answer == 'c') {
		goto continue_running;
	} else {
		goto wrong_answer;
	}

	wrong_answer:
	_cputs(
		"\n"
		"No time for gibberish, tell me what you're going to do!\n"
		"\n");

	goto stage_one_aliens;


broken_door:
    _cputs(
        "\n"
        "You try to break the door with the wooden chair.\n"
		"What were you thinking?\n"
		"The aliens are sorrounding you now.\n"
        "\n");

    goto game_over;



continue_running:
    _cputs(
        "\n"
        "You run to the end of the corridor and in a bloody ambulatory.\n"
        "There's the corpse of a dead doctor.\n"
		
		"[s] Search the corpse; or \n"
		"[c] Continue running away. \n"
		"\n");

	answer = _getche();
	if (answer == 's')
	{
		goto search_corpse;
	} 
	else if (answer == 'c')
	{
		goto continue_running_away;
	} 

  
	_cputs(
		"\n"
		"No time for gibberish, tell me what you're going to do!\n"
		"\n");

	goto continue_running;



continue_running_away:
	_cputs(
		"There is no way out, and the corridor where you\n" 
		"came from is filled with more than 100 of them.\n"

		"[f] Fight them; or\n"
		"[d] Leave it to the destiny.\n"
		"\n");

	answer=_getche();
	if (answer == 'f')
	{
		goto battle;
	}
	else if (answer == 'd')
	{
		goto game_over;
	}

	_cputs(
		"\n"
		"No time for gibberish, tell me what you're going to do!\n"
		"\n");

	goto continue_running_away;




	
battle:
	do {
		_cputs(
			"\n"
			"[f] Fight; or \n"
			"[r] run away \n"
			"\n>");
		answer = _getche();
	} while (wrong_answer(answer, "fr"));

	if (answer == 'r') {
		goto run;
	}
	else if (answer == 'f')
	{
		goto attack_alien;
	}

	
run:
	_cputs(
		"\n"
		"There is no escape!\n"
		"\n");

	goto the_end;

attack_alien:
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		alien_turn 
	} phase = choose_initiative;
	while (player_is_attacking && alien_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + alien_initiative) {
					phase = player_turn;
				} else {
					phase = alien_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= alien_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit the aliens for %d points of damage.\n", damage);
					alien_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"You missed.\n");
				}
				if (alien_hit_points > 0 && player_hit_points > 0) {
					do {
						_cputs(
							"Will you:\n"
							"[s] Strike again; or,\n"
							"[r] run away?"
							"\n>");
						answer = _getche();
					} while (wrong_answer(answer, "sr"));

					player_is_attacking = (answer == 's');
				}
				phase = alien_turn;
				break;
			case alien_turn:
				if (roll(20) + alien_hit_bonus >= player_defence) {
					damage = roll(8) + alien_damage_bonus;
					_cprintf(
						"\n"
						"The aliens hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"The aliens missed.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (alien_hit_points <= 0)	{
 		_cputs(
			"\n"
			"You manage to survive to the attack of more then 100 enemies\n"
			"You walk out from the labyrinth of doors and corridors, you can go home now.\n"
			"\n");
		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
			"\n"
			"You tried your best, but you don't have what it takes.\n"
			"\n");
		goto the_end;
	} else {
		goto run;
	}
	

the_end:
	_cputs(
		"\n");

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


	
	
					
				
			
			
search_corpse:
	_cputs(
		"You find a swipe card.\n"

		"[l] Grab the swipe card and look around; or \n"
		"[r] run back to the corridor. \n"
		"\n");

	answer=_getche();
	if (answer == 'l') 
	{
		goto found_door;
	}
	else if (answer == 'r')
	{
		goto continue_running_away;
	}


	_cputs(
		"\n"
		"No time for gibberish, tell me what you're going to do!\n"
		"\n");

	goto search_corpse;

found_door:
	_cputs(
		"You find a door 10 meters from where you are./n"

		"Do you want to: \n"
		"[o] Open the door; or \n"
		"[r] run back to the corridor. \n"
		"\n");

	answer =_getche();
		if (answer == 'o')
		{
			goto break_free;
		}
		else if (answer == 'r')
		{
			goto continue_running_away;
		}
		

	_cputs(
		"\n"
		"No time for gibberish, tell me what you're going to do!\n"
		"\n");

	goto found_door;


	swipe_card =true;

	if (swipe_card)
		_cputs(
			"You try to swipe the card and the door opens. \n"			
			"\n");

break_free:
	_cputs(
		"You are safe now, you walk through the room and you find an exit.\n"
		"Your nightmare has come to an end. \n"
		"/n");

	goto the_end;

game_over:
	_cputs(
		"You are dead. Game over. \n"
		"\n");

	goto the_end;

	}