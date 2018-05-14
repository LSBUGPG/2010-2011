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
		"Welcome to Die. To play this game, I will describe your situation, and you must\n"
		"choose what to do."
		"\n"
		"Good luck  and try not to die to soon!\n"
		"\n");

describe_cave:
	_cputs(
		"You wake up inside a cave. you slowly stand up and shake away your fatigue. Beside you is a large crack filled with larva. The cave is\n"
		"extremly quiet. with only the sounds of the flowing river to comfort you you cannot help but shudder in slight fear. you look around\n"
		"and find a hut nearby. The door seems to be unlocked.\n"
		"\n"
		"Will you:\n"
		"[h] enter the hut; or,\n"
		"[f] follow the river?\n"
		"\n>");

	answer = _getche();
	if (answer == 'h') {
		goto enter_hut;
	} else if (answer == 'r') {
		goto follow_river;
	} else {
		goto unknown_cave;
	}

enter_hut:
    _cputs(
        "\n"
        "You enter the hut unsure of what to expect.\n"
        "\n");
    goto describe_hut;

follow_river:
    _cputs(
        "\n"
        "You follow the course of the river and through an underground forest until you reach a point\n"
        "where it suddenly ends.\n"
        "\n");
    goto describe_streambed;

unknown_forest:
	_cputs(
		"\n"
		"try again that is not a correct choice.\n"
		"\n");
	goto describe_forest;

describe_hut:
	_cputs(
		"You cautiously enter ocaasionly looking from side to side incase of an attack.\n"
		"\n");

	if (have_key) {
		_cputs(
			"There is a small metal key  covered with a small layer of rust . Will you:\n"
			"[r] return the key to the hook on the wall; or will you ignore it and,\n"
			"[g] go back outside and get your bearings?\n"
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
	goto describe_cave;

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
		"try again that is not a correct choice.\n"
		"\n");
	goto describe_hut;

take_key:
	_cputs(
		"\n"
		"You take the small key and leave the hut.\n"
		"\n");
	have_key = true;
	goto describe_cave;

describe_larvabed:
	_cputs(
		"You are at the end the larva river. It trickles down into a large chasm in the\n"
		"ground. Beyond the hole, the larva bed is dry. There is a large metal grate in\n"
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
			goto unknown_larvabed;
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
			goto unknown_larvabed;
		}

	} else {
		_cputs(
			"The grate is unlocked. Will you:\n"
			"[e] enter through the grate; or,\n"
			"[g] go back ?\n"
			"\n>");

		answer = _getche();
		if (answer == 'g') {
			goto return_to_cave;
		} else if (answer == 'c') {
			goto enter_cave;
		} else {
			goto unknown_larvabed;
		}
	}

return_to_cave:
	_cputs(
		"\n"
		"You follow the larva river back into the cave.\n"
		"\n");
	goto describe_cave;

unlock_grate:
	_cputs(
		"\n"
		" at first the key refuses to turn but eventually the lock begins to give way untill you hear a click as the old lock falls to the ground.\n"
		"\n");
	grate_locked = false;
	goto describe_larvabed;

lock_grate:
	_cputs(
		"\n"
		"As you try to unlock the grate a cave in happens and a stray bolder colides with your head instantly killing you and leaving your prone bloody body to be covered by the rubble .\n"
		"\n");
	grate_locked = true;
	goto failed_adventurer;

unknown_larvabed:
	_cputs(
		"\n"
		"try again that is not a correct choice.\n"
		"\n");
	goto describe_larvabed;

return_for_key:
	_cputs(
		"The grate is locked. You'll need a key to open it. You go back upstream to look\n"
		"for one.\n"
		"\n");
	goto describe_cave;

enter_cave:
	_cputs(
		"\n"
		"You descend through the grate and into the darkness hopping that it leads to your salvation yet you cant help but feel that things are going to get worse.\n"
		"\n");
	goto describe_cave;

describe_cave:
	_cputs(
		"You enter a dark open cavern. it takes you afew seconds to adjust to the lack of light. you hear a loud rumbling and Before, in the darkness appears an small glow, you squintyour eyes and can just about make out the\n"
		"shape of an ancient golem. its eyes glow red as it prepares to atack the foolish mortal being that wondered into its lair.\n"
		"\n"
		" you realise now that you only have two options Will you:\n"
		"[f] fight the golem; or,\n"
		"[r] run back through the grate and search for another path?\n"
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
		" you realis eyou have know weapon and it would take a miricle to penetrate its thick armour with this in mind Will you:\n"
		"[f] fight and hope for a miricle; or,\n"
		"[r] reconsider your options and flee?\n"
		"\n>");

	answer = _getche();
	if (answer == 'f') {
		goto kill_golem;
	} else if (answer == 'r') {
		goto run;
	} else {
		goto unknown_cave;
	}

run:
	_cputs(
		"\n"
		"You  turn your back towards the golem and sprint for the grate at full speed. But, as you reach it a beam of light engulfs your body instantly vapourising you\n"
		"perhaps running was not such a good idea after all.\n"
		"\n");
	goto death;

unknown_cave:
	_cputs(
		"\n"
		"now is not the time for games you must choose care fully.\n"
		"\n");
	goto describe_cave;

kill_golem:
	_cputs(
		"\n"
		"you slowly begin to cicle the golem hoping to find its weakspot its eyes glow brighter alerting you to danger, suddenly a  beam of light streaks towards you at a blistering pace you stumble to the left narrorly avoiding it \n"
		"you loose conicse ness for a few sceonds and haer a loud explosion in front of you .fortunatly the beam of light hit the reflective suface of a mirror that you had previously been standing infront of and the attack had been sent back towards the golem instantly dstroying it .you thank the heavens for your luck and race towards the newly unviled exit.\n"
		"\n");
	goto the_end;

death:
	_cputs(
		" unfortunatly this is a DEAD END");
	goto the_end;

failed_adventurer:
	_cputs(
		"Your adventure is at an end. maybe next time you might think twice about your actions.\n"
		"\n");

the_end:
	_cputs(
		"GAME OVER.\n");

restart_or_quit:
	_cputs(
		"\n"
		"[r] want to try again.\n"
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
