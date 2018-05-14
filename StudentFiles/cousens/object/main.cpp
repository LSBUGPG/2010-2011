#include "object.h"
#include "engine.h"
#include "ball.h"
#include "mote.h"
#include "wisp.h"

#include <windows.h>
#include <SDL.h>

bool pause = true;
bool step = false;
bool reset = true;

void handle_key(SDL_keysym & key)
{
    switch (key.sym) {
	case SDLK_ESCAPE:
        quit(0);
		break;
	case SDLK_p:
		pause = !pause;
		break;
	case SDLK_f:
		step = true;
		break;
	case SDLK_r:
		reset = true;
		break;
	}
}

void process_events(void)
{
    SDL_Event an_event;

    while (SDL_PollEvent(&an_event)) {
        switch (an_event.type) {
		case SDL_KEYUP:
            handle_key(an_event.key.keysym);
			break;
        case SDL_QUIT:
            quit(0);
            break;
        }
    }
}

class object_types_array: public object_collection {
	object ** type_array;
	int size;
protected:
	void for_each_object(object_function & function)
	{
		for (int index = 0; index < size; index++) {
			function.call(*type_array[index]);
		}
	}
public:
	object_types_array()
	{
		static object * object_types[] = {
			load_ball_objects("ball.bmp", "bounce.wav", 40.0f),
			load_mote_objects("ball.bmp", 5.0f),
			load_wisp_objects("wisp.bmp", 50.0f)
		};

		type_array = object_types;
		size = sizeof(object_types) / sizeof(object_types[0]);
	}
};

int main(int argc, char * argv[])
{
	initialise_engine();

	object_types_array game_objects;

	while (true) {
		const float time = 1.0f / 60.0f;

		process_events();
		if (reset) {
			reset = false;
			game_objects.reset();
		} else if (!pause || step) {
			step = false;
			game_objects.update(time);
		}
		start_render();
		game_objects.draw();
		end_render();
    }

	return 0;
}
