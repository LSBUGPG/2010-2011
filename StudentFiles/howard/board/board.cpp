#include "engine.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <conio.h>

struct sound_key_definition {
	const char * image;
	const char * prompt;
	const char * audio;
	SDLKey keycode;
	GLfloat position[2];
};

struct sound_key_instance {
	GLuint image;
	GLuint prompt;
	Mix_Chunk * audio;
	bool held;
};

const sound_key_definition definition[] = {	
	{
		"drum1.bmp",
		"letter_b.bmp",
		"bongo1.wav",
		SDLK_b,
		{ -100.0f, 16.0f } 
	}, {
		"drum2.bmp",
		"letter_p.bmp", 
		"bongo2.wav",
		SDLK_p,
		{ 100.0f, 16.0f } 
	}
};

const int key_count = sizeof(definition) / sizeof(sound_key_definition);

sound_key_instance instance[key_count];

void handle_key(SDL_keysym * key, bool held)
{
    if (key->sym == SDLK_ESCAPE) {
        quit(0);
	} else {
		for (int index = 0; index < key_count; index++) {
			if (key->sym == definition[index].keycode) {
				if (!instance[index].held && held) {
					play_audio(instance[index].audio);
				}
				instance[index].held = held;
			}
		}
	}
}

void process_events(void)
{
    SDL_Event an_event;

    while (SDL_PollEvent(&an_event)) {
        switch (an_event.type) {
        case SDL_KEYDOWN:
            handle_key(&an_event.key.keysym, true);
            break;
		case SDL_KEYUP:
            handle_key(&an_event.key.keysym, false);
			break;
        case SDL_QUIT:
            quit(0);
            break;
        }
    }
}

void draw(const sound_key_definition & source, const sound_key_instance & data)
{
	const GLfloat normal_size = 50.0f;
	const GLfloat zoom_size = 70.0f;
	const GLfloat prompt_size = 16.0f;

	GLfloat size;
	if (data.held) {
		size = zoom_size;
	} else {
		size = normal_size;
	}

	draw_bitmap(data.image, source.position, size);

	GLfloat prompt_position[2] = { 
		source.position[0] - zoom_size, 
		source.position[1] - (zoom_size + prompt_size) 
	};

	size = prompt_size;

	draw_bitmap(data.prompt, prompt_position, size);
}

void load(const sound_key_definition & source, sound_key_instance & data)
{
	data.image = load_bitmap(source.image);
	data.prompt = load_bitmap(source.prompt);
	data.audio = load_audio(source.audio);
}

int main(int argc, char * argv[])
{
	initialise_engine();

	int index = 0;
	for (index = 0; index < key_count; index++) {
		load(definition[index], instance[index]);
	}

	while (true) {
		process_events();
		start_render();
		for (index = 0; index < key_count; index++) {
			draw(definition[index], instance[index]);
		}
		end_render();
    }

	return 0;
}
