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
		"Welcome to the mission. Your situation will be described. You\n"
		"choose what to do."
		"\n"
		"Good luck soldier!\n"
		"\n");

describe_forest:
	_cputs(
		"You are in an office corridor at night. The office is\n"
		"quiet. The footsteps of the patrol can be heard in the distance. There is\n"
		"an office cubicle next to you. The lamp is on.\n"
		"\n"
		"Will you:\n"
		"[e] enter the cubicle; or,\n"
		"[f] follow the corridor?\n"
		"\n>");

	answer = _getche();
	if (answer == 'e') {
		goto enter_hut;
	} else if (answer == 'f') {
		goto follow_stream;
	} else {
		goto unknown_forest;
	}

enter_hut:
    _cputs(
        "\n"
        "You enter the office cubicle.\n"
        "\n");
    goto describe_hut;

follow_stream:
    _cputs(
        "\n"
        "You make your way down the corridor quietly. \n"
        "At the end of the corridor you see a closed door.\n"
        "\n");
    goto describe_streambed;

unknown_forest:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_forest;

describe_hut:
	_cputs(
		"You are inside the office cubicle.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a security ID card on the desk. Will you:\n"
			"[p] Leave the card on the desk; or,\n"
			"[g] go back into the corridor?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_hut;
		} else if (answer == 'p') {
			goto return_key;
		} else {
			goto unknown_hut;
		}
	} else {
		_cputs(
			"There is a security ID card on the desk. Will you:\n"
			"[t] take the ID card; or,\n"
			"[g] go back into the corridor?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_hut;
		} else if (answer == 't') {
			goto take_key;
		} else {
			goto unknown_hut;
		}
	}

leave_hut:
	_cputs(
		"\n"
		"You leave the office cubicle.\n"
		"\n");
	goto describe_forest;

return_key:
	_cputs(
		"\n"
		"You leave the ID card on the desk.\n"
		"\n");
	have_key = false;
	goto describe_hut;

unknown_hut:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_hut;

take_key:
	_cputs(
		"\n"
		"You take the ID card and walk back into the corridor.\n"
		"\n");
	have_key = true;
	goto describe_forest;

describe_streambed:
	_cputs(
		"You are at the end of the corridor. The light above you flickers on and off quickly\n"
		"There is a door with a keycard reader.\n"
		"\n");

	if (grate_locked && have_key) {
		_cputs(
			"The door is locked. It appears the keycard you have will open the door. Will you:\n"
			"[u] use the keycard to open the door; or,\n"
			"[g] go back back down the corridor?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_forest;
		} else if (answer == 'u') {
			goto unlock_grate;
		} else {
			goto unknown_streambed;
		}

	} else if (grate_locked) {
		goto return_for_key;
	} else if (have_key) {
		_cputs(
			"The door is unlocked. Will you:\n"
			"[l] lock the door again;\n"
			"[o] open the door and enter the room; or,\n"
			"[g] go back door the corridor?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_forest;
		} else if (answer == 'o') {
			goto enter_cave;
		} else if (answer == 'l') {
			goto lock_grate;
		} else {
			goto unknown_streambed;
		}

	} else {
		_cputs(
			"The door is unlocked. Will you:\n"
			"[o] open the door and enter the room; or,\n"
			"[g] go back down the corridor?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_forest;
		} else if (answer == 'o') {
			goto enter_cave;
		} else {
			goto unknown_streambed;
		}
	}

return_to_forest:
	_cputs(
		"\n"
		"You follow the corridor back to the cubicle entrance.\n"
		"\n");
	goto describe_forest;

unlock_grate:
	_cputs(
		"\n"
		"The keycard reader beeps quietly. A green light appears.\n"
		"\n");
	grate_locked = false;
	goto describe_streambed;

lock_grate:
	_cputs(
		"\n"
		"As lock the door a gunshot is heard. You fall to the floor.\n"
		"\n");
	grate_locked = true;
	goto failed_adventurer;

unknown_streambed:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_streambed;

return_for_key:
	_cputs(
		"The door is locked. You'll need a keycard to open it. You could go back down the corridor and\n"
		"to look for one.\n"
		"\n");
	goto describe_forest;

enter_cave:
	_cputs(
		"\n"
		"You enter through the door and into a dimly lit office.\n"
		"\n");
	goto describe_cave;

describe_cave:
	_cputs(
		"You are in a dark office. From the darkness steps the office patrol\n"
		"the security guard is carrying a baton. He runs at you .\n"
		"\n"
		"Will you:\n"
		"[f] fight the security guard; or,\n"
		"[r] run back through the door?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto last_chance;
	} else if (answer == 'r') {
		goto run;
	} else {
		goto unknown_cave;
	}

last_chance:
	_cputs(
		"\n"
		"Barehanded! The guard is armed! Are you sure? Will you:\n"
		"[f] fight the security guard barehanded; or,\n"
		"[r] think better of it and run back into the corridor?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto kill_dragon;
	} else if (answer == 'r') {
		goto run;
	} else {
		goto unknown_cave;
	}

run:
	_cputs(
		"\n"
		"You quickly run from the room and slam the door behind you.\n" 
		"As you turn back into the corridor. You see a guard with a gun\n"
		"he shoots you. You fall to the floor\n"
		"\n");
	goto survivor;

unknown_cave:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_cave;

kill_dragon:
	_cputs(
		"\n"
		"The guard swings his baton at you. You parry his attack\n" 
		"and knock him out! You quickly grab the file from the desk,\n"
		"You smash through the window and pull your parachute cord.\n"
		"you glide in the air and land on a nearby rooftop.\n"
		"\n");
	goto the_end;

survivor:
	_cputs(
		"Your mission is over. You retrived the documents and got them back to HQ!\n"
		"Your superiors will take it from here. Good job!\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"You were killed in action and the mission was a failure!\n"
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