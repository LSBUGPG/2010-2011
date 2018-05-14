#include <conio.h>

int main(int argc, char *argv[])
{
	int answer;
	bool step;
	bool strife;

start_game:

	_cputs(
		"\n"
		"Adventure? I call this a nightmare! Plunged deep into the pits of tyrants, tormented day in day out\n"
		"Will you choose to take yourself out of the picture, before you go mad?."
		"\n"
		"Each to their own!\n"
		"\n");

describe_situation:
	_cputs(
		"Since birth you have felt secluded, denied by those around you, forever increasing the uncertainty of people's true intentions\n"
		"because of those before. Beginning to shut yourself out, you have become a mere shadow in the day, what is left in the course of action?\n"
		"Keep your sanity or relinquish it all to feel safer in death?.\n"
		"\n"
		"Will you:\n"
		"[e] Carry on living a seemingly fake life; or,\n"
		"[f] Take a leap of faith and be free\n"
		"\n>");

	answer = _getche();
	if (answer == 'e') {
		goto enter_fakeliving;
	} else if (answer == 'f') {
		goto follow_leapoffaith;
	} else {
		goto unknown_end;
	}

enter_fakeliving:
    _cputs(
        "\n"
        "Hours turn to days, days to turn years and wait about till the misery ends at the end of time.\n"
        "\n");
    goto describe_whylife;

follow_leapoffaith:
    _cputs(
        "\n"
        "Dusk is approaching on a cold November day, you pass a few highrise apartment blocks on your way home pondering\n"
        "Could you take the leap?\n"
        "\n");
    goto describe_roof;

unknown_end:
	_cputs(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto describe_situation;

describe_whylife:
	_cputs(
		"You are here once again back where you usually are, communicating with people who don't give a rats arse about you.\n"
		"With always trying to be compassionate with the best intentions at heart to have it thrown back at you tenfold\n");


describe_roof:
	_cputs(
		"You are at the edge with your head held high looking forwards into the past, memories revisiting you. With no contigency plans in sight\n"
		"and with the ground calling your name. Will you allow yourself to be freed? Life has its ups and downs but yours more than the fair share\n"
		"take it in strife or take the step\n"
		"\n");

	if (step) {
		_cputs(
			"With your eyes shut, the sound of wind and traffic noise blocking out all else, you feel the embrace of the ground\n"
			"\n>");

	} else if (strife) {
		goto walk_away;
	}

walk_away:
	_cputs(
		"Despite two faced evil, all you need is the connection to stand with your family. You take a step back, take a breath and clear your head\n"
		"and set off to find your family.\n"
		"\n");
	goto the_end;



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
