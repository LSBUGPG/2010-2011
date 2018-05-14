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
	bool ammo;

start_game:

srand(int(time(0)));

	const int stranger_initiative = 7;
	const int stranger_hit_bonus = 5;
	const int stranger_damage_bonus = 4;
	const int stranger_defence = 20;
	int stranger_hit_points = 20;

	const int player_initiative = 10;
	const int player_hit_bonus = 8;
	const int player_damage_bonus = 5;
	const int player_defence = 18;
	int player_hit_points = 20;


	ammo = false;
	

	_cputs
		(
			"\n"
			"Welcome to the most awesome game ever!\n"
			"All you need to do is choose which path you would like to take \n"
			"on this epic adventure of epicness. \n"
			"\n"
		);


describe_garage:

	_cputs
		(	
			"\n"
			"You're walking down a carpark, it's late and you see \n"
			"a shifty looking dude walking towards you, he see's you \n"
			"and pulls out an AK47. \n"
			"\n"
			"Do you: \n"
			"[a] - Turn around and haul a*? outta there? \n"
			"[b] - Pull out your FN Scar-H and start ripping s*!? up? \n"
			"\n"
		);

	answer = _getche();
	if (answer == 'a') 
		{
		goto you_coward;
		} 
	else if (answer == 'b') 
		{
		goto shooting_him;
		}
	else 
		{
		goto unknown_garage;
		}
	
unknown_garage:

	_cputs
		(	
			"\n"
			"Sorry I don't understand that choice. \n"
			"\n"
		);

	goto describe_garage;


you_coward:

	_cputs
		(	
			"\n"
			"WOW you're a total coward! \n"
			"Do you want to: \n"
			"\n"
			"[r] - Start again? \n"
			"[q] - Quit? \n"
			"\n"
		);

	answer = _getche();
	if (answer == 'r') 
		{
		goto describe_garage;
		} 
	else if (answer == 'q') 
		{
		goto quit;
		}
	else 
		{
		goto unknown_coward;
		}

unknown_coward:
	
	_cputs
		(	
			"\n"
			"Sorry I don't understand that choice. \n"
			"\n"
		);

	goto you_coward;


shooting_him:

	_cputs
		(	
			"\n"
			"You pull out your gun and you start shooting. \n"
			"But don't be silly you never keep it loaded, or do you? \n"
			"Do you: \n"
			"\n"
			"[c] - Check the gun is loaded? \n"
			"[d] - Fire wildley? \n"
			"\n"

		);

	answer = _getche();
	if (answer == 'c') 
		{
		goto loaded_gun;
		} 
	else if (answer == 'd') 
		{
		goto fire_wild;
		}
	else 
		{
		goto unknown_shooting;
		}


loaded_gun:

	_cputs
		(	
			"\n"
			"You check your gun to see if it's loaded before shooting. \n"
			"It's not, better load it with mags from your pocket. \n"
			"You're gun is loaded time to roll!! \n"
			"\n"
		);
	ammo = true; 
	goto stand_off;


fire_wild:

	_cputs
		(	
			"\n"
			"CLICK CLICK! That's the sound of \n"
			"an empty gun! better check your pockets. \n"
			"\n"
		);

	ammo = false;
	goto shooting_him; 	




unknown_shooting:

		_cputs
		(	
			"\n"
			"Sorry I don't understand that choice. \n"
			"\n"
		);

	goto shooting_him;



stand_off:
	bool player_is_attacking = true;
	enum 
		{ 
			choose_initiative, 
			player_turn, 
			stranger_turn 
		} phase = choose_initiative;

	while (player_is_attacking && stranger_hit_points > 0 && player_hit_points > 0) 
		{
			int damage;

				switch (phase) 
		{
					case choose_initiative:
						if (roll(20) + player_initiative >= roll(20) + stranger_initiative) 
		{
					phase = player_turn;
		
		} 
		else 
		{
					phase = stranger_turn;
		}
				
		break;
			
		case player_turn:
		if (roll(20) + player_hit_bonus >= stranger_defence) 
		{
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit the stranger for %d points of damage.\n", damage);
					stranger_hit_points-= damage;
		} 
		else 
		{
					_cputs(
						"\n"
						"You missed.\n");
		}
		
		if (stranger_hit_points > 0 && player_hit_points > 0) 
		{
					do 
					{
						_cputs(
							"\n"
							"Will you:\n"
							"[e] continue to fight; or,\n"
							"[f] run away?"
							"\n>");
						answer = _getche();
					} while (wrong_answer(answer, "ef"));

					player_is_attacking = (answer == 'e');
			}
				phase = stranger_turn;
				break;

			case stranger_turn:
			if (roll(20) + stranger_hit_bonus >= player_defence) 
			{
					damage = roll(8) + stranger_damage_bonus;
					_cprintf(
						"\n"
						"The stranger hit you for %d points of damage.\n", damage);
					player_hit_points-= damage;
			}
			else 
			{
					_cputs(
						"\n"
						"The stranger missed.\n");
			}
				phase = player_turn;
				break;
		}
	}

	if (stranger_hit_points <= 0)	
		{
 			_cputs(
				"\n"
				"OMG you totally beat that guy!! Way to go! \n"
				"\n");
			goto the_end;
		} 
	else if (player_hit_points <= 0) 
		{
 			_cputs(
				"\n"
				"You lost that totally suck man \n" 
				"\n");
			goto the_end;
		} 
	else 
		{
			goto quit;
		}
	
survivor:
	_cputs
		(
			"It's over, you fought that dude and lived congrats dude. \n"
			"\n"
		);
	goto the_end;

the_end:
	_cputs(
		"The end.\n");



quit:
	return 0;
}