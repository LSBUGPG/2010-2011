#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "collection.h"
#include "player.h"
#include "spike.h"
#include "platform.h"


#include <windows.h>
#include <SDL.h>
#include <conio.h>

bool pause = false;
bool step = false;
bool reset = true;

enum keystate { press, release };

void handle_key(SDL_keysym & key, keystate state)
{
	if (state == release) {
		switch (key.sym) {
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_F1:
			pause = !pause;
			break;
		case SDLK_F2:
			step = true;
			break;
		case SDLK_F3:
			reset = true;
			break;
		case SDLK_SPACE:
			make_player_jump();
			break;
		default:
			break;
		}
	}
}

void process_events(void)
{
	SDL_Event an_event;

	while (SDL_PollEvent(&an_event)) {
		switch (an_event.type) {
		case SDL_KEYUP:
			handle_key(an_event.key.keysym, release);
			break;
		case SDL_KEYDOWN:
			handle_key(an_event.key.keysym, press);
			break;
		case SDL_QUIT:
			quit(0);
			break;
		}
	}
}

int main(int argc, char * argv[])
{
	_cputs("F1 - pause / unpause the game\n");
	_cputs("F2 - while paused, advance one frame\n");
	_cputs("F3 - reset game\n");
	_cputs("You are Subject 45.\n");
	_cputs("You have been tasked with completing this course. Navigate the course and hope\n");
	_cputs("to survive. Jump using the Space Bar to make the character jump and get to the\n");
	_cputs("end of the course. Press F3 to restart when you reach the end.\n");
	_cputs("Controls- Space Bar to jump\n");


	initialise_engine(screen_width, screen_height, scale);

	static abstract_object instances[] = {
		load_player_object(),

		load_platform_objects()
	};
	static const int size = sizeof(instances) / sizeof(instances[0]);
	static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
	static collection_object subject_45(game_objects);

	while (true) {
		const float time = 1.0f / 60.0f;

		process_events();
		if (reset) {
			reset = false;
			subject_45.reset();
		} else if (!pause || step) {
			step = false;
			subject_45.update(time);
		}
		start_render();
		subject_45.draw();
		end_render();
	}

	return 0;
}

void reset_game()
{
	reset = true;
}

