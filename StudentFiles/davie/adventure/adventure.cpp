#include <conio.h>

int main(int argc, char *argv[])
{
	int answer; 
	bool have_paper;
	bool musicbox_locked;

	start_game:
	have_paper = false;
	musicbox_locked = true;

	_cputs(
		"\n"
		"* * * * * * * * * * * * * * * * * * * * * * * * * *\n"
		"Mind - A text based adventure game \n"
		"Created by Matthew Davie,\n"
		"Of Davie.Creations\n"
		"Copyright 2011©\n"
		"* * * * * * * * * * * * * * * * * * * * * * * * * *\n"
		"\n"); //Creation Build 2011 - Versions 1.0

	_cputs(
		"\n"
		"Welcome to your mind.\n"
		"There are many tests you must face some are strange,\n"
		"and others will test your skill.\n"
		"\n"
		"Good luck.\n"
		"\n"
		"* * * * * * * * * * * * * * * * * * * * * * * * * * \n"
		"\n");

describe_room:
	_cputs(
		"A room appears in front of you\n"
		"To your left is a door, to your right is a corridor,\n"
		"In front of you is a set of steps leading underground,\n"
		"The choice is yours.\n"
		"\n"
		"Will you:\n"
		"[l] turn left; or,\n"
		"[r] turn right\n"
		"[u] go underground\n"
		"\n>");

	answer = _getche();
	if (answer == 'l') {
		goto enter_library;
	} else if (answer == 'r') {
		goto follow_corridor;
	} else if (answer == 'u') {
		goto go_underground; 
	} else {
		goto enter_room;
	}

enter_library:
	_cputs(
		"\n"
		"You arrive in a library.\n"
		"\n");
	goto describe_library;

follow_corridor:
	_cputs(
		"\n"
		"You follow the corridor until you reach a dead end,\n"
		"You go back to the start.\n"
		"\n");
	goto describe_room;

go_underground:
	_cputs(
		"\n"
		"You find yourself trapped in a room,\n"
		"You turn to notice the stairs have gone,\n"
		"The floor beneath you disappears,\n"
		"You fall into the void.\n"
		"\n");
	goto describe_void;
                     
enter_room:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_room;

describe_library:
	_cputs(
		"The library is old, dust covers the books, a fire is lit in the corner.\n"
		"There is a grand piano in the corner, a tune is playing.\n"
		"\n");

	if (have_paper) {
		_cputs(
			"You take out the paper from your pocket. Will you:\n"
			"[p} put it back; or,\n"
			"[r] read it\n"
			"\n>");

		answer = _getche();
		if (answer == 'p') {
			goto leave_paper;
		} else if (answer == 'r') {
			goto read_paper;
		} else {
			goto describe_library;
		}
	} else {
		_cputs(
			"You find a piece of paper in your pocket. Will you:\n"
			"[r] read it; or,\n"
			"[w] walk around library some more\n"
			"\n>");

		answer = _getche();
		if (answer == 'w') {
			goto describe_library;
		} else if (answer == 'r') {
			goto read_paper;
		} else {
			goto describe_library;
		}
	}

leave_paper:
	_cputs(
		"\n"
		"You leave the paper in your pocket.\n"
		"\n");
	have_paper = false;
	goto describe_library;

read_paper:
	_cputs(
		"\n"
		"You read the paper and notice a musical score is written on it.\n"
		"\n");
	have_paper = true;
	goto describe_piano;

describe_piano:
	_cputs(
		"You walk up to the piano. \n"
		"It appears to be playing on its own\n"
		"there appears to be a locked music box within it.\n"
		"\n");

	if (musicbox_locked && have_paper) {
		_cputs(
			"The box is locked. Will you:\n"
			"[p] play the score on the paper; or,\n"
			"[w] walk away from piano and return to library\n"
			"\n>");

		answer = _getche();
		if (answer == 'w') {
			goto describe_library;
		} else if (answer == 'p') {
			goto unlock_musicbox;
		} else {
			goto describe_library;
		}

	} else if (musicbox_locked) {
		goto describe_library;
	} else if (have_paper) {
		_cputs(
			"The box is unlocked. Will you:\n"
			"[o] open the box;\n"
			"[l] leave the box; or,\n"
			"[r] return to library?\n"
			"\n>");

		answer = _getche();
		if (answer == 'r') {
			goto return_to_library;
		} else if (answer == 'l') {
			goto leave_box;
		} else if (answer == 'o') {
			goto open_musicbox;
		} else {
			goto describe_piano;
		}
	}

return_to_library:
	_cputs(
		"\n"
		"You return to the library.\n"
		"\n");
	goto describe_library;

unlock_musicbox:
	_cputs(
		"\n"
		"The box opens.\n"
		"\n");
	musicbox_locked = false;
	goto open_musicbox;

leave_box:
	_cputs(
		"\n"
		"As walk away from the piano, you fall to the floor.\n"
		"\n");
	musicbox_locked = true;
	goto failed_adventurer;

open_musicbox:
	_cputs(
		"\n"
		"As the box opens, you get sucked in,\n"
		" you descend into darkness.\n"
		"\n");
	goto describe_void;

describe_void:
	_cputs(
		"You are in the void. Before you, in the darkness, you can make out the\n"
		"shape of a man. You move closer and realise it is yourself \n"
		"without warning it attacks you.\n"
		"Will you:\n"
		"[f] fight yourself; or,\n"
		"[v] let the void consume you?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto last_chance;
	} else if (answer == 'v') {
		goto void_deeper;
	}

last_chance:
	_cputs(
		"\n"
		"Within the void you take your chances and attack yourself:\n"
		"[f] fight yourself; or,\n"
		"[e] try to escape?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto kill_yourself;
	} else if (answer == 'e') {
		goto void_deeper;
	} else {
		goto failed_adventurer;
	}

void_deeper:
	_cputs(
		"\n"
		"Your heart races the void consumes you. But, as the darkness takes hold\n"
		", you awaken.\n"
		"\n");
	goto survivor;

kill_yourself:
	_cputs(
		"\n"
		"You fight and kill yourself! You wake, to realise\n"
		"that your wost enemy is yourself.\n"
		"\n");
	goto the_end;

survivor:
	_cputs(
		"The void has taught you a that within the shadows is a greater enemy.\n"
		"You live, for now.\n"
		"\n");
	goto the_end;

failed_adventurer:
	_cputs(
		"You have escaped the world you found yourself in,\n"
		"but when will you find yourself there again?\n"
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
