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
			"The Annabel Testing Module will repeat the question ONE MORE TIME.\n"
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
	bool basement_locked;


start_game:

	srand(int(time(0)));

	const int child_initiative = 2;
	const int child_hit_bonus = 4;
	const int child_damage_bonus = 5;
	const int child_defence = 20;
	int child_hit_points = 20;

	const int player_initiative = 19;
	const int player_hit_bonus = 5;
	const int player_damage_bonus = 5;
	const int player_defence = 20;
	int player_hit_points = 20;

	have_key = false;
	basement_locked = true;


	_cputs(
		"\n"
		"Welcome, captive human, to the Annabel Testing Module.\n"
		"\n"
		"After initiation the Annabel Testing Module will present you with a series of\n"
		"hypothetical situations. It is in your best interests to respond to these\n"
		"situations in a truthful manner. Subjects who do not pass the tests are\n"
		"recycled into food for the native species of carniverous flamingo.\n"
		"\n"
		"\n");


describe_scenario: 
	_cputs(
		"\n"
		"Initiating test...\n"
		"\n"
		"It is your birthday. Your human partner surprises you by giving you a kitten.\n"
		"You do not like kittens.\n"
		"You like flamingos.\n"
		"\n"
		"Do you:\n"
		"\n"
		"[a] accept the kitten; or,\n"
		"[b] blast both the kitten and your human counterpart with your Death-Ray 9000\n"
		"Mega-Blaster?\n"
		"\n");


	answer = _getche();
	if (answer == 'a') {
		goto hold_kitten;
	} else if (answer == 'b') {
		goto dead_kitten;   
	} else {
		goto unknown;
	}


hold_kitten: 
    _cputs(
        "\n"
        "To the delight of your human partner you accept the kitten but, within\n"
		"seconds of touching its curiously soft exterior, you feel an inner surge of\n"
		"rage and you blast the kitten and your human spouse with your Death-Ray\n"
		"9000 Mega-Blaster.\n"
        "\n");
    goto describe_basement;


dead_kitten: 
    _cputs(
         "\n"
        "The kitten and your human partner are deceased but your choice of\n"
		"weaponry was poor, the Death-Ray 9000 Mega-Blaster is not a stealth\n"
		"weapon. You must find somewhere to conceal the bodies quickly. \n"
        "\n"
		"\n");
    goto describe_basement;  


unknown:  
	_cputs(
		"\n"
		"The Annabel Testing Module will repeat the question ONE MORE TIME.\n"
		"\n");
	goto describe_scenario;


describe_basement:  
	_cputs(
		"\n"
		"You stand over your human partner and the kitten's remains.\n"
		"\n>");

	if (have_key && basement_locked) {
		_cputs(
			"The eviscerated limbs of your partner and Birthday kitten remain\n"
			"on your floor but you hold the blue keycard, moist with human\n"
			"life-fluid.\n"
			"\n"
			"Will you:\n"
			"[r] return the keycard to the remains; or,\n"
			"[f] find somewhere else to stash the corpses\n"
			"\n>");

		answer = _getche();
		if (answer == 'f') {
			goto do_nothing;
		} else if (answer == 'r') {
			goto return_key;
		} else {
			goto unknown_answer;
		}
	} else {
		_cputs(
			"There is a blue keycard among the stray limbs and organs on\n"
			"the ground. You do not have time to question how the blue\n"
			"keycard got there.\n"
			"\n"
			"Will you:\n"
			"\n"
			"[t] take the keycard; or,\n"
			"[l] leave it?\n"
			"\n>");

		answer = _getche();
		if (answer == 'l') {
			goto do_nothing;
		} else if (answer == 't') {
			goto take_key;
		} else {
			goto unknown_answer;
		}
	}


do_nothing:   
	_cputs(
		"\n"
		"You're fast running out of time. The human authorities will\n"
		"arrive soon.\n"
		"\n");
	goto dead_kitten;


return_key:   
	_cputs(
		"\n"
		"You return the keycard to its previous owner.\n"
		"\n");
	have_key = false;
	goto describe_basement;


unknown_answer:    
	_cputs(
		"\n"
		"The Annabel Testing Module will repeat the question ONE MORE TIME.\n"
		"\n");
	goto describe_basement;


take_key:  
	_cputs(
		"\n"
		"You pull the blue keycard from the kitten and wipe it clean.\n"
		"\n");
	have_key = true;
	goto open_basement;


open_basement:  
	_cputs(
		"You suddenly remember having an industrial furnace built in your\n"
		"basement last summer. You knew it would come in useful.\n"
		"The blue keycard opens the basement.\n"
		"\n");

	if (have_key) {
		_cputs(
			"You stand over your human partner's remains where, seconds ago,\n"
			"you removed the keycard. Will you:\n"
			"\n"
			"[r] return the key to the pile of human organs and kitten fluff; or,\n"
			"[m] move to the basement door\n"
			"\n>");

		answer = _getche();
		if (answer == 'r') {
			goto describe_basement;
		} else if (answer == 'm') {
			goto unlock_basement; 
	
		}


	} else if (have_key) {
		_cputs(
			"The basement is now unlocked. Down below the flames of your industrial\n"
			"furnace flicker. \n"
			"Will you:\n"
			"\n"
			"[l] lock the basement;\n"
			"[e] enter the basement; or,\n"
			"\n>");

		answer = _getche();
		if (answer == 'e') {
			goto enter_basement;
		} else if (answer == 'l') {
			goto fail_one;
		} else {
			goto unknown_response;
		}

	} else {
		_cputs(
			"The basement is unlocked. Will you:\n"
			"[e] enter into the darkness; or,\n"
			"[c] consider your limited options?\n"
			"\n>");

		answer = _getche();
		if (answer == 'c') {
			goto open_basement;
		} else if (answer == 'e') {
			goto enter_basement;
		} else {
			goto unknown_response;
		}
	}


unlock_basement:   
	_cputs(
		"\n"
		"The keycard opens the basement door.\n"
		"\n");
	basement_locked = false;
	goto inside_basement;


fail_one:   
	_cputs(
		"\n"
		"WITH UNPRECEDENTED COWARDESS AND STUPIDTY YOU HAVE FAILED THE ANNABEL\n"
		"TESTING MODULE. \n"
		"\n"
		"Prepare for immediate grinding into tinned Flamingo food.\n"
		"\n");
	basement_locked = true;
	goto failed_subject;


unknown_response:  
	_cputs(
		"\n"
		"The Annabel Testing Module will repeat the question ONE MORE TIME.\n"
		"\n");
	goto describe_basement;


enter_basement:  
	_cputs(
		"\n"
		"Dragging your deceased human partner and kitten in tow you descend into\n"
		"the basement. \n"
		"\n");
	goto inside_basement;


inside_basement:  
	_cputs(
		"You are in your basement. Ahead is the furnace.\n"
		"You throw the bodies of your once loved human spouse and your birthday kitty\n" 
		"into the fire without remorse. You are safe. \n"
		"\n"
		"But what is that noise? Idiot human! In your haste you failed to lock your\n"
		"house entry portal and an inquisitive, defenseless human child has entered\n"
		"the basement. \n"
		"\n"
		"Will you:\n"
		"[f] fight the human child to the death; or,\n"
		"[l] leap into the inferno, forever concealing the truth?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto last_chance;
	} else if (answer == 'l') {
		goto failed_subject;
	} else {
		goto unknown_response_final;
	}


last_chance:  
	
	bool player_is_attacking = true;
	enum { 
		choose_initiative, 
		player_turn, 
		child_turn 
	} phase = choose_initiative;
	while (player_is_attacking && child_hit_points > 0 && player_hit_points > 0) {
		int damage;

		switch (phase) {
			case choose_initiative:
				if (roll(20) + player_initiative >= roll(20) + child_initiative) {
					phase = player_turn;
				} else {
					phase = child_turn;
				}
				break;
			case player_turn:
				if (roll(20) + player_hit_bonus >= child_defence) {
					damage = roll(8) + player_damage_bonus;
					_cprintf(
						"\n"
						"You hit a defenseless human child for %d points of damage.\n", damage);
					child_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"Somehow, you missed.\n");
				}
				if (child_hit_points > 0 && player_hit_points > 0) {
					do {
						_cputs(
							"\n"
							"Will you:\n"
							"[c] continue fighting the human child; or,\n"
							"[r] flee from the wrath of the human child?"
							"\n>");
						answer = _getche();
					} while (wrong_answer(answer, "cr"));

					player_is_attacking = (answer == 'c');
				}
				phase = child_turn;
				break;
			case child_turn:
				if (roll(20) + child_hit_bonus >= player_defence) {
					damage = roll(8) + child_damage_bonus;
					_cprintf(
						"\n"
						"The child uses his stealth attack for %d points of damage.\n", damage);
					player_hit_points-= damage;
				} else {
					_cputs(
						"\n"
						"The child's pitiful slap proved ineffective.\n");
				}
				phase = player_turn;
				break;
		}
	}

	if (child_hit_points <= 0)	{
 		_cputs(
			"\n"
		"Incredible. Against all odds and without provokation you fight and kill\n"
		"the defenseless human child!\n"
		"\n"
		"You emerge from the basement with a new found sense of pride and self worth.\n"
		"You are a true hero.\n"
		"\n"
		"\n");

		goto the_end;
	} else if (player_hit_points <= 0) {
 		_cputs(
		"The unarmed human child pummels you into pulp, stopping only to take a bite\n"
		"out of its chocolate spread sandwich.\n"
		"\n"
		"WITH UNPRECEDENTED COWARDESS AND STUPIDTY YOU HAVE FAILED THE ANNABEL\n"
		"TESTING MODULE. AND AT THE HANDS OF A CHILD. \n"
		"\n"
		"Prepare for immediate grinding into tinned Flamingo food.\n"
		"\n");

			
	
		goto restart_or_quit;

	} else {
		goto run;
	}
	_cputs(
		"\n"
		"The human child is a ferocious foe. Will you:\n"
		"[f] fight the human child to the death; or,\n"
		"[l] leap into the inferno, forever concealing the truth?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto kill_child;
	} else if (answer == 'l') {
		goto run;
	} else {
		goto unknown_response_final;
	}


run:   
	_cputs(
		"\n"
		"The defenseless human child proved an impossible adversary and you\n"
		"flee the basement in terror.\n"
		"\n"
		"Outside the human authorities wait and mow you down in a flurry of\n"
		"plasma blasts. An ash pile is all that remains.\n"
		"\n"
		"Nobody attends your funeral.\n"
		"\n");
	goto failed_subject;


unknown_response_final:   
	_cputs(
		"\n"
		"The Annabel Testing Module will repeat the question ONE MORE TIME.\n"
		"\n");
	goto inside_basement;


kill_child:   
	_cputs(
		"\n"
		"Incredible. Against all odds and without provokation you fight and kill\n"
		"the defenseless human child! Then, without mercy, you hurl its corpse into\n" 
		"the incinerator.\n"
		"\n"
		"You emerge from the basement with a new found sense of pride and self worth.\n"
		"You are a true hero.\n"
		"\n");
	goto the_end;


failed_subject:   
	_cputs(
		"\n"
		"WITH UNPRECEDENTED COWARDESS AND STUPIDTY YOU HAVE FAILED THE ANNABEL\n"
		"TESTING MODULE.\n"
		"\n"
		"Prepare for immediate grinding into tinned Flamingo food.\n"
		"\n");
	goto restart_or_quit;


the_end:   // the end
	_cputs(
		"\n"
		"Exercise complete\n"
		"\n"
		"Humans slain:               2/2\n"
		"Kittens maimed:             1/1\n"
		"Witnesses:                  0\n"
		"Estimated moral integrity: -27\n"
		"Final grade:                A+\n"
		"Result:                     Employ as meatshield in the fight against humankind\n"
		"\n");


restart_or_quit:  
	_cputs(
		"\n"
		"[r] Restart this training module.\n"
		"[q] Quit this training module.\n"
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
