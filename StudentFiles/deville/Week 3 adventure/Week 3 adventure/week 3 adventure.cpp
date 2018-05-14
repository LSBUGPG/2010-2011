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
		"You have followed your target to an empty office building\n"
		"The building is dark. The target has taken the lift up to the 12th floor\n"
		"The security desk in the foyer is empty.\n"
		"\n"
		"Will you:\n"
		"[e] examine the security desk; or,\n"
		"[g] Go to the lift?\n"
		"\n>");

	answer = _getche();
	if (answer == 'e') {
		goto enter_hut;
	} else if (answer == 'g') {
		goto follow_stream;
	} else {
		goto unknown_forest;
	}

enter_hut:
    _cputs(
        "\n"
        "You are at the security desk.\n"
        "\n");
    goto describe_hut;

follow_stream:
    _cputs(
        "\n"
        "You follow the corridor to the lifts\n"
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
		"You are at the security desk.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a lift overide key on the desk. Will you:\n"
			"[l] leave the key on the desk; or,\n"
			"[g] go back to the foyer?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_hut;
		} else if (answer == 'l') {
			goto return_key;
		} else {
			goto unknown_hut;
		}
	} else {
		_cputs(
			"There is a lift overide key on the desk. Will you:\n"
			"[t] take the overide key; or,\n"
			"[g] go back to the foyer?\n"
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
		"You walk back to the foyer.\n"
		"\n");
	goto describe_forest;

return_key:
	_cputs(
		"\n"
		"You leave the lift overide key on the desk.\n"
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
		"You take the overide key and walk back into the foyer.\n"
		"\n");
	have_key = true;
	goto describe_forest;

describe_streambed:
	_cputs(
		"You are in the lift area of the foyer.\n"
		"All lifts are out of order except the centre lift.\n"
		"\n");

	if (grate_locked && have_key) {
		_cputs(
			"The lift is locked down. The lift overide key you have will open the lockdown. Will you:\n"
			"[u] use the overide key to activate the lift; or,\n"
			"[g] go back into the main foyer?\n"
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
			"The lockdown has been lifted Will you:\n"
			"[l] Lockdown the lift again;\n"
			"[t] Take the lift to the 12th floor; or,\n"
			"[g] go back into the main foyer?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_forest;
		} else if (answer == 't') {
			goto enter_cave;
		} else if (answer == 'l') {
			goto lock_grate;
		} else {
			goto unknown_streambed;
		}

	} else {
		_cputs(
			"The lockdown has been lifted. Will you:\n"
			"[t] Take the lift to the 12th floor; or,\n"
			"[g] Go back to the main foyer ?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_forest;
		} else if (answer == 't') {
			goto enter_cave;
		} else {
			goto unknown_streambed;
		}
	}

return_to_forest:
	_cputs(
		"\n"
		"You walk back into the main foyer.\n"
		"\n");
	goto describe_forest;

unlock_grate:
	_cputs(
		"\n"
		"The overide key turns in the lock. The lift is now operational.\n"
		"\n");
	grate_locked = false;
	goto describe_streambed;

lock_grate:
	_cputs(
		"\n"
		"As you lock the lift again. You are stabbed from behind.\n"
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
		"The lift is locked down. You will need the overide key.\n"
		"try looking on the security desk.\n"
		"\n");
	goto describe_forest;

enter_cave:
	_cputs(
		"\n"
		"You push the 12th floor button and the lift doors shut.\n"
		"\n");
	goto describe_cave;

describe_cave:
	_cputs(
		"You are on the 12th floor. As you exit the lift your target quickly turns\n"
		" and notices you. Panicked he quickly attacks you with a knife.\n"
		"\n"
		"Will you:\n"
		"[f] fight your target; or,\n"
		"[r] run back into the lift?\n"
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
		"Barehanded! He has a knife! Are you sure? Will you:\n"
		"[f] fight your target barehanded; or,\n"
		"[s] have second thoughts and run back into the lift?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto kill_dragon;
	} else if (answer == 's') {
		goto run;
	} else {
		goto unknown_cave;
	}

run:
	_cputs(
		"\n"
		"You quickly run back into the lift. As the doors open a bodyguard\n"
		"shoots you and you fall to the floor\n"
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
		"You dodge the knife attacks of your target and deliver a quick blow to the\n"
		"neck. Your target has been assassinated.\n"
		"\n");
	goto the_end;

survivor:
	_cputs(
		"Your target has been assassinated and your mission is complete\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"You fall to the floor and black out as the bodyguard approaches you\n"
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
