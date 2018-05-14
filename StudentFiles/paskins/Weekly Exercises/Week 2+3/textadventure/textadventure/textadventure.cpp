#include <conio.h>

int main(int argc, char *argv[]) {

	int glyphs_found;
	int action;

	bool portal_open;

begin_adventure:
	portal_open = false;
	glyphs_found = 0;
	
	_cputs(
		"\nWelcome to the Realm of the Forgotten.\n\n");

the_plains:
	_cputs(
		"\n\nYou awake to find yourself in the middle of a large, open field."
		"\nThere are four possible ways you can go:"
		"\n[n] North - The Portal"
		"\n[e] East - The Crater"
		"\n[s] South - The Road"
		"\n[w] West - The River\n"
		"\n[b] Check backpack"
		"\n>");

	action = _getche();
	if (action == 'n') {
		goto the_portal;
	}
	else if (action == 'e') {
		goto crater;
	} 
	else if (action == 's') {
		goto blocked_path;
	} 
	else if (action == 'w') {
		goto river;
	}
	else if (action == 'b') {
		goto backpack;
	} 
	else {
		goto the_plains_wrong;
	}

the_plains_wrong:
	_cputs(
		"\n\nIncorrect input.\n\n"
		);
	goto the_plains;

backpack:
	if (glyphs_found > 0) {
		_cprintf(
			"\n\nYou currently possess %d glyph(s).\n", glyphs_found
		);
	}
	else {
		_cputs(
		"\n\nYou currently hold nothing...\n");
	}
	goto the_plains;

crater:
	_cputs(
		"\n\nYou take the path east. After walking a mile or so, you encounter a giant crater."
		"\nIn the middle of the crater is a smouldering rock that seems to be glistening in the sunlight."
		"\nDo you:"
		"\n[r] Inspect the rock"
		"\n[l] Take a cautious stroll around the perimeter"
		"\n>");

	action = _getche();
	if (action == 'r') {
		goto the_rock;
	} 
	else if (action == 'l') {
		goto perimeter;
	} 
	else {
		goto crater_wrong;
	}

crater_wrong:
	_cputs(
		"\n\nIncorrect input.\n\n");
	goto crater;

the_rock:
	_cputs(
		"\n\nYou approach the rock. The glistening appears to be coming from an inscription in the rock."
		"\nYou carve out the glyph and store it in your backpack."
		"\nSuddenly, you are overwhelmed with blinding light..."
		);
	glyphs_found++;
	goto the_plains;

perimeter:
	_cputs(
		"\n\nYou take a stroll around the perimeter of the crater."
		"\nA glinting figure on the floor catches your eye."
		"\nYou bend down to inspect the object. It appears to be a glyph of some form."
		"\nYou pick up the glyph and store it in your backpack."
		"\nSuddenly, you are overwhelmed with blinding light...\n\n"
		);

	glyphs_found++;
	goto the_plains;

blocked_path:
	_cputs(
		"\n\nThe road behind you is blocked by a weird energy."
		"\nYou take a deep breath and walk through it..."
		);
	goto the_plains;

river:
	_cputs(
		"\n\nYou take the path west, to the river front."
		"\nIn the water, you see a glint of light..."
		"\nDo you:"
		"\n[l] Dive into the river and check the light"
		"\n[f] Follow the stream further"
		"\n>");

	action = _getche();
	if (action == 'l') {
		goto under_water;
	} 
	else if (action == 'f') {
		goto river_further;
	} 
	else {
		goto river_wrong;
	}

river_wrong:
	_cputs(
		"\n\nIncorrect input.\n\n");
	goto river;

under_water:
	_cputs(
		"\n\nYou dive into the lake and swim down to the glinting light."
		"\nIt looks like some form of glyph... you stretch out, grab it and place it in your backpack."
		"\nSuddenly, you are overwhelmed with blinding light..."
		);
	glyphs_found++;
	goto the_plains;

river_further:
	_cputs(
		"\n\nYou continue to follow the stream further, you see another glinting light on the ground."
		"\nCurious, you bend down and pick it up - it appears to be some form of a glyph... You put it in your backpack."
		"\nSuddenly, you are overwhelmed with blinding light..."
		);
	glyphs_found++;
	goto the_plains;

the_portal:
	_cputs(
		"\n\nYou approach the portal cautiously.\n"
	);
		if(glyphs_found == 0) {
			_cputs(
				"\nYour mind is assaulted with the energy around the portal..."
				);
			goto the_plains;
		}

		else if(glyphs_found == 1) {
			_cputs(
				"\nYour mind is assaulted with the energy around the portal."
				"\nYou try to fight it back, but it overwhelms you..."
				);
			goto the_plains;
		}

		else if(glyphs_found == 2) {
			_cputs(
				"\nYour mind is assaulted with the energy around the portal."
				"\nYou fight back the energy and sprint towards the portal!"
				);
			goto ending_1;
		}

		else if(glyphs_found == 3) {
			_cputs(
				"\nYou can slightly sense the energy surrounding the portal."
				"\nYou walk through the portal."
				);
			goto ending_2;
		}

		else if(glyphs_found == 4) {
			_cputs(
				"\nYou can feel the spirits cowering before you."
				"\nYou walk through the portal."
				);
			goto ending_3;
		}

ending_1:
		_cputs(
			"\n\n\nCongratulations on making it out alive!"
			"\nAlthough it was only just, you live to tell the tale."
			);
		_getche();
		return(0);

ending_2:
		_cputs(
			"\n\n\nCongratulations on making it out alive!"
			"\nHaving found 3 of the strange glyphs, you feel powerful."
			"\nPerhaps you should seek advice on the glyphs..."
			"\nYou are left wondering if there were more..."
			);
		_getche();
		return(0);

ending_3:
		_cputs(
			"\n\n\nCongratulations on making it out alive!"
			"\nYou feel the power of the glyphs coarsing through your body."
			"\nYou possess knowledge now that no other does."
			"\nPerhaps you can utilize this immense power..."
			);
		_getche();
		return(0);

}