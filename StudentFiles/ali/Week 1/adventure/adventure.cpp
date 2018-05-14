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
		"Welcome back gangsta. It's been a while since you've been around, I will describe your situation, and you must\n"
		"choose what to do."
		"\n"
		"Good luck homeboy!\n"
		"\n");

describe_forest:
	_cputs(
		"You are back on the streets after being framed for a crime you didnt commit. Things have\n"
		"become unexpectedly quiet. You realize that things have changed. Your old house\n"
		"is nearby. The door appears unlocked.\n"
		"\n"
		"Will you:\n"
		"[e] enter the house; or,\n"
		"[w] walk up the road?\n"
		"\n>");

	answer = _getche();
	if (answer == 'e') {
		goto enter_hut;
	} else if (answer == 'w') {
		goto follow_stream;
	} else {
		goto unknown_forest;
	}

enter_hut:
    _cputs(
        "\n"
        "You enter your old house.\n"
        "\n");
    goto describe_hut;

follow_stream:
    _cputs(
        "\n"
        "You follow the road until you reach a dead end.\n"
        "A building you don't recognize appears before with the name of your old gang written on it.\n"
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
		"The house has definitely aged and seems to be dusty as hell.\n"
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
		"You leave the house.\n"
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
		"The building is a Night club. Your desire for revenge suddenly consumes\n"
		"you. However the Club is protected by two heavy looking doors, there is no one around. The two\n"
		"doors seem to need some kind of key.\n"
		"\n");

	if (grate_locked && have_key) {
		_cputs(
			"The door is locked. It looks like the key you have will fit the lock. Will you:\n"
			"[u] use the key to open the door; or,\n"
			"[g] go back up the road?\n"
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
			"[l] lock the door;\n"
			"[e] enter through the door; or,\n"
			"[g] go back up the road?\n"
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
		"You follow the road back to the main area.\n"
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
		"As you lock the door you suddenly begin to understand.\n"
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
		"The door is locked. You'll need a key to open it. You go back up the road to look\n"
		"for one.\n"
		"\n");
	goto describe_forest;

enter_cave:
	_cputs(
		"\n"
		"You enter through the doors and go down the corridor.\n"
		"\n");
	goto describe_cave;

describe_cave:
	_cputs(
		"The club seems to be of high class. Before you, is the door leading\n"
		"to the boss's room. You begin to have 2nd thoughts and waver in your resolution.\n"
		"\n"
		"Will you:\n"
		"[f] fight the boss; or,\n"
		"[r] run back through the doors?\n"
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
		"Barehanded! The boss has a gun! Are you sure? Will you:\n"
		"[f] fight the boss barehanded; or,\n"
		"[r] think better of it and run back to the streets?\n"
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
		"Your heart races as you run right out of the club. But, as you slam the doors\n"
		"shut behind you, you suddenly begin to understand.\n"
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
		"Incredibly, you fight and kill the boss with your bare hands! You leave, with\n"
		"your head high. You are a true gangsta.\n"
		"\n");
	goto the_end;

survivor:
	_cputs(
		"Your roll is at an end. You tried to take on the boss and still live to tell the\n"
		"tale. You're a survivor for sure bruv!.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"Your roll is at an end. I guess you really don't have what it takes to take back your streets.\n"
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
