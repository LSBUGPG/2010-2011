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
		"Welcome to the forest traveller. I see that you have arrived here to camp.\n"
		"I must warn you though that there are wild animals that will strike without warning."
		"\n"
		"Good luck traveller!\n"
		"\n");

describe_forest:
	_cputs(
		"You are in a strange forest.  Next to you is a river. The forest is\n"
		"alive with birds chirping and other exotic animals. You can also\n"
		"hear the river flowing. You see a cave in the distance.\n"
		"\n"
		"Will you:\n"
		"[w] walk towards the cave; or,\n"
		"[i] ignore it and keep walking?\n"
		"\n>");

	answer = _getche();
	if (answer == 'w') {
		goto enter_hut;
	} else if (answer == 'i') {
		goto follow_stream;
	} else {
		goto unknown_forest;
	}

enter_hut:
    _cputs(
        "\n"
        "You arrive at the cave.\n"
        "\n");
    goto describe_hut;

follow_stream:
    _cputs(
        "\n"
        "You follow the course of the river through the forest until you reach a suitable place\n"
        "where you can set up camp.\n"
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
		" The cave is huge and very dark and smells.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a torch light in your bag. Will you:\n"
			"[l] leave it in your bag; or,\n"
			"[u] use the torch light?\n"
			"\n>");

		answer = _getche();
		if (answer == 'u') {
			goto leave_hut;
		} else if (answer == 'l') {
			goto return_key;
		} else {
			goto unknown_hut;
		}
	} else {
		_cputs(
			"There is a torch light in your bag. Will you:\n"
			"[u] use the torch light; or,\n"
			"[g] go back outside?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_hut;
		} else if (answer == 'u') {
			goto take_key;
		} else {
			goto unknown_hut;
		}
	}

leave_hut:
	_cputs(
		"\n"
		"You leave the cave.\n"
		"\n");
	goto describe_forest;

return_key:
	_cputs(
		"\n"
		"You decide to leave the torch light in your bag and leave the cave.\n"
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
		"You use the torch light and you start to investigating the cave.\n"
		"\n");
	have_key = true;
	goto describe_streambed;

describe_streambed:
	_cputs(
		"You reach the end of the cave. \n"
		"There is a large metal door in the corner\n"
		"of the cave.\n"
		"\n");

	if (grate_locked && have_key) {
		_cputs(
			"The door is locked. You see a key on the floor that will fit the lock. Will you:\n"
			"[u] use the key to open the grate; or,\n"
			"[l] leave the cave?\n"
			"\n>");

		answer = _getche();
		if (answer == 'l') {
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
			"[l] lock the door;\n"
			"[e] enter through the door; or,\n"
			"[c] leave the cave?\n"
			"\n>");

		answer = _getche();
		if (answer == 'c') {
			goto return_to_forest;
		} else if (answer == 'e') {
			goto enter_cave;
		} else if (answer == 'l') {
			goto lock_grate;
		} else {
			goto unknown_streambed;
		}

	} else {
		_cputs(
			"The door is unlocked. Will you:\n"
			"[e] enter through the door; or,\n"
			"[l] leave the cave?\n"
			"\n>");

		answer = _getche();
		if (answer == 'l') {
			goto return_to_forest;
		} else if (answer == 'e') {
			goto enter_cave;
		} else {
			goto unknown_streambed;
		}
	}

return_to_forest:
	_cputs(
		"\n"
		"You leave the cave.\n"
		"\n");
	goto describe_forest;

unlock_grate:
	_cputs(
		"\n"
		"The key turns reluctantly in the rusty old lock.\n"
		"\n");
	grate_locked = false;
	goto describe_streambed;

lock_grate:
	_cputs(
		"\n"
		"As you lock the door you suddenly wake.\n"
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
		"The door is locked. You'll need a key to open it. You go back deeper in the cave \n"
		"to look for one.\n"
		"\n");
	goto describe_forest;

enter_cave:
	_cputs(
		"\n"
		"You descend through the door and into the darkness.\n"
		"\n");
	goto describe_cave;

describe_cave:
	_cputs(
		"You are in a dank cavern. Before you, in the darkness, you can make out the\n"
		"shape of an ancient creature. The creature bares its teeth and prepares to \n"
		"viciously strike.\n"
		"Will you:\n"
		"[f] fight the creature; or,\n"
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
		"Barehanded! Are you sure? Will you:\n"
		"[f] fight the dragon barehanded; or,\n"
		"[u] use your brain and escape the cave?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto kill_dragon;
	} else if (answer == 'u') {
		goto run;
	} else {
		goto unknown_cave;
	}

run:
	_cputs(
		"\n"
		"Your heart races as you escape from the cave. But, as you slam the door\n"
		"behind you, you snap out of it.\n"
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
		"Incredibly, you fight and kill the creature with your bare hands! You wake, with\n"
		"newfound confidence. You are a true adventurer.\n"
		"\n");
	goto the_end;

survivor:
	_cputs(
		"Your adventure is at an end. You have faced a powerful creature and yet live to tell the\n"
		"tale. You are a true survivor.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"Your adventure is at an end. You realise your too weak and pathetic.\n"
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
