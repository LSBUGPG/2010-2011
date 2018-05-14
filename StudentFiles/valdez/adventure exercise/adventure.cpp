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
		"Welcome to the most craziest thing you've ever been in! The decisions you make \n"
		"will affect your game and I hope you get to the end of it."
		"\n"
		"Good luck adventurer!\n"
		"\n");

describe_forest:
	_cputs(
		"You are walking through a forest pathway and you seen a corpse lying\n"
		"on the side of the path\n"
		"\n"
		"Will you:\n"
		"[e] inspect corpse; or,\n"
		"[f] carry on walking\n"
		"\n>");

	answer = _getche();
	if (answer == 'e') {
		goto inspect_dead_body;
	} else if (answer == 'f') {
		goto carry_on_walking;
	} else {
		goto unknown_forest;
	}

inspect_dead_body:
    _cputs(
        "\n"
        "you walk towards the dead body and search it.\n"
        "\n");
    goto describe_dead_body;

carry_on_walking:
    _cputs(
        "\n"
        "you see a chest lying on the pathway not too far from the body\n"
        "\n");
    goto describe_chest;

unknown_forest:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_forest;

describe_dead_body:
	_cputs(
		"the body is still warm. He had just died less then a few hours ago.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a small golden key in his pocket. Will you:\n"
			"[g] take the key; or,\n"
			"[r] carry on walking?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto take_key;
		} else if (answer == 'r') {
			goto carry_on_walking;
		} else {
			goto unknown_path;
		}
	} else {
		_cputs(
			"There is a small golden key in his pocket. Will you:\n"
			"[t] take the key; or,\n"
			"[g] carry on walking?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto leave_body;
		} else if (answer == 't') {
			goto take_key;
		} else {
			goto unknown_path;
		}
	}

leave_body:
	_cputs(
		"\n"
		"You leave the body and carry on walking.\n"
		"\n");
	goto carry_on_walking;


unknown_path:
	_cputs(
		"\n"
		"what was that?.\n"
		"\n");
	goto describe_dead_body;

take_key:
	_cputs(
		"\n"
		"You take the gold key and leave the body.\n"
		"\n");
	have_key = true;
	goto carry_on_walking;

describe_chest:
	_cputs(
		"the chest is made out of thick planks of wood that are held together by metal bolts.\n"
		"the chest is quite large as well as heavy\n"
		"\n");

	if (grate_locked && have_key) {
		_cputs(
			"The chest is padlocked. It looks like the key you have will fit the padlock. Will you:\n"
			"[u] use the key to open the chest; or,\n"
			"[g] go back go back the way you came\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_forest;
		} else if (answer == 'u') {
			goto open_chest;
		} else {
			goto unknown_streambed;
		}

	} else if (grate_locked) {
		goto return_for_key;
	} else if (have_key) {
		_cputs(
			"The chest is unlocked. Will you:\n"
			"[l] leave the treasure;\n"
			"[e] take the treasure and exit the forest; or,\n"
			"[g] go back through the forest\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_forest;
		} else if (answer == 'e') {
			goto enter_cave;
		} else if (answer == 'l') {
			goto failed_adventurer;
		} else {
			goto unknown_streambed;
		}

	} else {
		_cputs(
			"The chest is unlocked and you see treasure inside. Will you:\n"
			"[e] take the treasure; or,\n"
			"[g] leave and exit the forest?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto failed_adventurer;
		} else if (answer == 'e') {
			goto enter_cave;
		} else {
			goto unknown_streambed;
		}
	}

return_to_forest:
	_cputs(
		"\n"
		"You follow the path back into the forest.\n"
		"\n");
	goto describe_forest;

open_chest:
	_cputs(
		"\n"
		"The key turns with ease and you open the chest to find treasure. you take the treasure and move on.\n"
		"\n");
	grate_locked = false;
	goto carry_on_walking;


unknown_streambed:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto carry_on_walking;

return_for_key:
	_cputs(
		"The chest is locked. You'll need a key to open it. i guess you have to go back and\n"
		"find one.\n"
		"\n");
	goto describe_forest;

enter_cave:
	_cputs(
		"\n"
		"You see the end of the forest... But a thief appears from the bushes!\n"
		"\n");
	goto describe_cave;

describe_cave:
	_cputs(
		"as he brandishes his sword he asks for the treasure in your possession\n"
		"\n"
		"Will you:\n"
		"[f] fight the thief; or,\n"
		"[r] hand over the treasure?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto last_chance;
	} else if (answer == 'r') {
		goto hand_treasure;
	} else {
		goto unknown_cave;
	}

last_chance:
	_cputs(
		"\n"
		"you take your sword out of its sheath! Are you sure? Will you:\n"
		"[f] fight the thief; or,\n"
		"[r] think better of it and run back to the surface?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto defeat_thief;
	} else if (answer == 'r') {
		goto run;
	} else {
		goto unknown_cave;
	}

run:
	_cputs(
		"\n"
		"You give the thief the treasure and gladly walk away with nothing\n"
		"\n");
	goto hand_treasure;

unknown_cave:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_cave;

defeat_thief:
	_cputs(
		"\n"
		"you whip the thief's ass so bad that he runs away leaving his wooden sword\n"
		"hah! a wooden sword,what was he thinking? You are a true adventurer.\n"
		"\n");
	goto the_end;

hand_treasure:
	_cputs(
		"You walk out of the forest with nothing gained.What the hell was that?.\n"
		"you don't deserve to be playing this game!\n"
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
