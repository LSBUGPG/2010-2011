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

describe_forest:
	_cputs(
		"You are in a mysterious forest. Beside you is a small stream. The forest is\n"
		"unexpectedly quiet. The only sound is the gentle trickle of the water. There is\n"
		"also a small wooden hut nearby. The door appears unlocked.\n"
		"\n"
		"Will you:\n"
		"[e] enter the hut; or,\n"
		"[f] follow the stream?\n"
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
        "You enter the small wooden hut.\n"
        "\n");
    goto describe_hut;

follow_stream:
    _cputs(
        "\n"
        "You follow the course of the stream through the forest until you reach a point\n"
        "where it suddenly ends.\n"
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
		"You are inside a musty old wooden hut.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a small metal key hook on the wall. Will you:\n"
			"[r] return the key to the hook; or,\n"
			"[g] go back outside?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_hut;
		} else if (answer == 'r') {
			goto return_key;
		} else {
			goto unknown_hut;
		}
	} else {
		_cputs(
			"There is a small metal key hanging from a hook on the wall. Will you:\n"
			"[t] take the key; or,\n"
			"[g] go back outside?\n"
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
		"You leave the hut.\n"
		"\n");
	goto describe_forest;

return_key:
	_cputs(
		"\n"
		"You return the small key to its hook.\n"
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
		"You take the small key and leave the hut.\n"
		"\n");
	have_key = true;
	goto describe_forest;

describe_streambed:
	_cputs(
		"You are at the end of a small stream. It trickles down into a small hole in the\n"
		"ground. Beyond the hole, the stream bed is dry. There is a large metal grate in\n"
		"the dry earth.\n"
		"\n");

	if (grate_locked && have_key) {
		_cputs(
			"The grate is locked. It looks like the key you have will fit the lock. Will you:\n"
			"[u] use the key to open the grate; or,\n"
			"[g] go back upstream?\n"
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
			"The grate is unlocked. Will you:\n"
			"[l] lock the grate;\n"
			"[e] enter through the grate; or,\n"
			"[g] go back upstream?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
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
			"The grate is unlocked. Will you:\n"
			"[e] enter through the grate; or,\n"
			"[g] go back upstream?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
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
		"You follow the stream back into the forest.\n"
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
		"As you lock the grate you suddenly wake.\n"
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
		"The grate is locked. You'll need a key to open it. You go back upstream to look\n"
		"for one.\n"
		"\n");
	goto describe_forest;

enter_cave:
	_cputs(
		"\n"
		"You descend through the grate and into the darkness.\n"
		"\n");
	goto describe_cave;

describe_cave:
	_cputs(
		"You are in a dank cavern. Before you, in the darkness, you can make out the\n"
		"shape of an ancient dragon. The dragon bares its teeth and prepares to strike.\n"
		"\n"
		"Will you:\n"
		"[f] fight the dragon; or,\n"
		"[r] run back through the grate?\n"
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
		"[r] think better of it and run back to the surface?\n"
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
		"Your heart races as you climb back out of the cave. But, as you slam the grate\n"
		"shut behind you, you suddenly wake.\n"
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
		"Incredibly, you fight and kill the dragon with your bare hands! You wake, with\n"
		"newfound confidence. You are a true adventurer.\n"
		"\n");
	goto the_end;

survivor:
	_cputs(
		"Your adventure is at an end. You have faced a dragon and yet live to tell the\n"
		"tale. You are a true survivor.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"Your adventure is at an end. You realise you do not have what it takes.\n"
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
