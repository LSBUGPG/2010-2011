#include <conio.h>

int main(int argc, char *argv[])
{
	int answer;
	bool have_key;
	bool grate_locked;

start_game:
	have_key = false;
	grate_locked = true;

	_cputs(
		"\n"
		"Welcome to the adventure. To play, I will describe your situation, and you must\n"
		"choose what to do."
		"\n"
		"Good luck adventurer!\n"
		"\n");

describe_Prison:
	_cputs(
		"You are in a abandoned prison unable to see. Your in a locked cell drenched in flammible fluid and a lot of broken glass scattered across the floor.\n"
		" it is unexpectedly quiet. The only sound is the gentle trickle of the water which reflects a lighter in the distance and is just about visible to see to the naked eye. There is\n"
		"also a key nearby but cannot be seen due to darkness, its very hard to know where your walking.\n"
		"\n"
		"Will you:\n"
		"[e] search for key; or,\n"
		"[f] use lighter to see your surroundings?\n"
		"\n>");

	answer = _getche();
	if (answer == 'u') {
		goto use_glass;
	} else if (answer == 's') {
		goto search_cell_floor;
	} else {
		goto use_lighter;
	}

search_cell_floor:
    _cputs(
        "\n"
        "you search the cell floor and find the cell key and unlock the cell door.\n"
        "\n");

use_glass:
    _cputs(
		"\n"
		"you use the glass on floor and cut your hand, very badly. \n" );

describe_use_lighter:
    _cputs(
        "\n"
        " You use the lighter and it egnights the whole cell room, as well as your self\n"
        "and you get burnt to a crisp.\n"
        "\n");
    goto use_lighter;

unknown_Prison:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_Prison_1;

describe_Prison_1:
	_cputs(
		"you are now looking down a long dark corridor but notice a shiny object a few yards away, your path has been blocked due to the ceiling caving in.\n"
		"\n");

	if (true) {
		_cputs(
			"There is another route facing the other way and hole a few yards behind you. Will you:\n"
			"[t] turn back and go down the other corridor and go down the hole; or,\n"
			"[t] try and find an object to destroy the obstruction blocking the path to the shiny object?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto go_down_hole;
		} else if (answer == 'f') {
			goto find_object;
		} else {
			goto go_back_to_prison_cell;
		}

describe_hole:
		_cputs("You fall to your death.\n");

describe_find_object:
		_cputs("You manage to find nothing useful and decide to go the opposite direction.\n");
	
	} else {
		_cputs(
			"There is a small crack facing opposite the prison cell and looks weak enough to break through. Will you:\n"
			"[u] use brutal force; or,\n"
			"[f] find object to smash the crack across wall?\n"
			"\n>");

		answer = _getche();
		if (answer == 'u') {
			goto use_brutal_force;
		} else if (answer == 'f') {
			goto find_object;
		}
	}

use_brutal_force:
	_cputs(
		"\n"
		"You break through the wall and notice nothing special inside the room which appears to be a office, theres a door to you right.\n"
		"\n");
	goto find_object;

find_object:
	_cputs(
		"\n"
		"You find a key on the office desk.\n"
		"\n");
	have_key = false;
	goto find_object;

unknown_prison:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_prison;

take_key:
	_cputs(
		"\n"
		"You take the small key and leave the office.\n"
		"\n");
	have_key = true;
	goto describe_prison;

describe_courtyard:
	_cputs(
		"You are now in the courtyard of the prison there is a high fence\n"
		"but a few guard dogs have been patrolling the premises. A few yards away is a gun covered in blood, the dogs notice you and start barking. There is a door just a few yards to your right, which is the guard tower\n"
		"the dogs start to run towards you.\n"
		"\n");

	_cputs(
		"The guard tower door appears to be locked. It looks like the key you have will fit the emergancy exit door. Will you:\n"
		"[k] killed dogs; or,\n"
		"[r] run past dogs and use prison fence?\n"
		"\n>");

	answer = _getche();
	if (answer == 'k') {
		goto use_the_gun_to_kill_dogs;
	} else if (answer == 'r') {
		goto describe_use_fence;
	}
		
climb_down_the_ladder:
	_cputs(
		"\n"
		"You climb down the ladder.\n"
		"\n");
	goto describe_use_fence;

describe_use_fence:
	_cputs("You manage to climb over the fence and climb down safely.\n");

describe_emergency_door:
	_cputs(" The emergency door is in front of you where you then use the key to access the ladder. \n");

describe_emergency_exit:
	_cputs(
		"You are now at the botttom of the ladder of the emergency exit room. Before you, in the darkness, you can make out the\n"
		"shape of an human shape in the distance. The man runs from the distance and prepares to strike.\n"
		"\n"
		"Will you:\n"
		"[r] run towards him and fight the phychopath; or,\n"
		"[r] run back ladder?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto last_chance;
	} else if (answer == 'r') {
		goto run;
	} else {
		
	}

last_chance:
	_cputs(
		"\n"
		"Barehanded! Are you sure? Will you:\n"
		"[f] fight the phychopath barehanded; or,\n"
		"[t] think better of it and run back to the surface?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto kill_phychopath;
	} else if (answer == 'r') {
		goto run;
	} else {
		goto unknown_prison;
	}

run:
	_cputs(
		"\n"
		"Your heart races as you climb back down the ladder to face the phychopath. \n");
	goto survivor;


kill_phychopath:
	_cputs(
		"\n"
		"Incredibly, you fight and kill the phychopath with your bare hands! You wake, with\n"
		"newfound confidence. You are a now the daddy.\n"
		"\n");
	goto the_end;

survivor:
	_cputs(
		"You are now officially free from the prison. You have lived to tell the\n"
		"tale. You are a true survivor.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"You get brutally attacked and collapse.\n"
		"\n");

you_died:
	_cputs(
		"You died.\n");

the_end:
	_cputs("The end\n");

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
