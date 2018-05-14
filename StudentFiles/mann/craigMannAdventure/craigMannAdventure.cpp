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

describe_beginning:
	_cputs(
		"\n"
		"You are in your favourite comic book store, reading the latest battle between \n"
		"the hero Quantum!! and his nemesis The Reaper!.\n"
		"Then all of a sudden the door slams open, wind rushing in and you see the silouhette of a man in a long trenchcoat\n"
		"then all you see is a flash of white, looking around you see you are inside Quantums headquarters, you think this cant be happening\n"
		"you turn and walk towards the doorway, towards a long corridor \n"
		"\n"
		"Will you:\n"
		"[c] continue on; through the corridor or,\n"
		"[g] go back to the main room and call for help?\n"
		"\n>");

	answer = _getche();
	if (answer == 'c') {
		goto enter_corridor;
	} else if (answer == 'g') {
		goto follow_back;
	} else {
		goto comic_book;
	}

comic_book:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_beginning;

follow_back:
    _cputs(
       "\n"
        "you turn back walking into the main room, approaching the main computer\n"
        "you press the Quantum button.\n"
        "\n");
    goto describe_main;
enter_corridor:
    _cputs(
       "\n"
        "you go through a small hallway to a large open room.\n"
        "\n");
    goto describe_room;

describe_room:
	_cputs(
		"\n"
		"you are in a vast room with a glass front, you look out to see the clean empire city.\n"
		"Will you...\n"
		"\n"
		"[l] continue on; leave the headquarters, head into empire bay or,\n"
		"[g] go back?\n"
		"\n>");

		answer = _getche();
	if (answer == 'l') {
		goto enter_empire;
	} else if (answer == 'g') {
		goto enter_corridor;
	} else {
		goto comic_book;
	}

enter_empire:
	_cputs(
		"\n"
		"you walk into the vast city,\n"
		"a stream of police cars zoom past\n"
		"'i have to get to Quantum, this must be a dream'\n"
		"will you?\n"
		"\n"
		"[f] follow the police cars?\n"
		"[g]go back?\n"
		"\n");

			answer = _getche();
	if (answer == 'f') {
		goto enter_scene;
	} else if (answer == 'g') {
		goto describe_room;
	} else {
		goto comic_book;
	}

enter_scene:
	_cputs(
		"\n"
		"you arrive at the scene,\n"
		"Quantum is standing there before you, he looks human\n"
		"approaching him you say\n"
		"'quantum will you...\n"
		"[h] help me?\n"
		"[n]ahh nevermind youre probably busy?\n"
		"\n");
				answer = _getche();
	if (answer == 'h') {
		goto help_me;
	} else if (answer == 'n') {
		goto nevermind;
	} else {
		goto comic_book;
	}

help_me:
	_cputs(
		"\n"
		"'of course citizen' he says,\n"
		"'i am yourr biggest fan, some how ive been sent into your comic book'\n"
		"he laughs, 'Im not joking! this is serious' you say falling to your knees\n"
		"'young man i am Quantum, i was created by that nuclear explosion'\n"
		"you stand up, looking in him the face you say....\n"
		"\n"
		"[h] please i you have to help me i am lost\n"
		"[a]youre right you cant help me [attack]?\n"
		"\n");
					answer = _getche();
	if (answer == 'h') {
		goto help_me;
	} else if (answer == 'n') {
		goto nevermind;
	} else {
		goto comic_book;
	}

nevermind:
	_cputs(
		"\n"
			"'of course citizen' he says,\n"
		"'i am yourr biggest fan, some how ive been sent into your comic book'\n"
		"he laughs, 'Im not joking! this is serious' you say falling to your knees\n"
		"'young man i am Quantum, i was created by that nuclear explosion'\n"
		"you stand up, looking in him the face you say....\n"
		"\n"
		"[h] please i you have to help me i am lost\n"
		"[a]youre right you cant help me [attack]?\n"
		"\n");
				answer = _getche();
	if (answer == 'h') {
		goto to_be_continued;
	} else if (answer == 'a') {
		goto to_be_continued;
	} else {
		goto comic_book;
	}

describe_main:
	_cputs(
		"\n"
		"You press the Quantum button'\n"
		"then he teleports in,\n"
		"and you say \n"
		"\n"
		"[h] help me Quantum i'm not supposed to be here\n"
		"[l] haha i have you now Quantum, reaper will be happy!|n"
		"\n");

			answer = _getche();
	if (answer == 'h') {
		goto nevermind;
	} else if (answer == 'l') {
		goto to_be_continued;
	} else {
		goto comic_book;
	}



to_be_continued:
	_cputs(
		"\n"
		"to be continued!\n"
		"[r] restart.\n"
		"[q] Quit.\n"
		"\n>");

	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto to_be_continued;
	}
	
quit:
	return 0;
}
