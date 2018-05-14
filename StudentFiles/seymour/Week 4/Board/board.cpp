#include "engine.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <conio.h>

struct sound_key_definition {
     const char * image;
     const char * prompt;
     const char * audio;
     SDLKey keycode;
     GLfloat position[3];
};

struct sound_key_instance {
     GLuint image;
     GLuint prompt;
     Mix_Chunk * audio;
     bool held;
};
         

const sound_key_definition definition[] = {
     {
          "Snare.bmp",
          "letter_a.bmp",
          "Snare.wav",
          SDLK_a,
          { -200.0f, -100.0f }
     }, {
          "Kick.bmp",
          "letter_b.bmp",
          "Kick.wav",
          SDLK_b,
          { 0.0f, -100.0f }  

	 }, {
		 "Tom 1.bmp",
		 "letter_f.bmp",
		 "Tom 1.wav",
		 SDLK_f,
		 { -200.0f, 50.0f }

	 }, {
		 "Tom 2.bmp",
		 "letter_g.bmp",
		 "Tom 2.wav",
		 SDLK_g,
		 { 0.0f, 50.0f }

	 }, {
		 "Tom 3.bmp",
		 "letter_h.bmp",
		 "Tom 3.wav",
		 SDLK_h,
		 { 200.0f, 50.0f }

	 }, 
		 "Cowbell.bmp",
		 "letter_r.bmp",
		 "Cow Bell.wav",
		 SDLK_r,
		 { 0.0f, 200.0f }
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

     GLfloat prompt_position[9] = {
          source.position[0] - zoom_size,
          source.position[1] - (zoom_size + prompt_size),
		  source.position[2] - zoom_size,
		  source.position[3] - zoom_size,
		  source.position[4] - zoom_size,
		  source.position[5] - zoom_size,
		  source.position[6] - zoom_size,
		  source.position[7] - zoom_size,
		  source.position[8] - zoom_size,

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
