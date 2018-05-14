#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "background.h"
#include "music.h"
#include "collection.h"

#include <windows.h>
#include <SDL.h>
#include <conio.h>

bool pause = false;
bool step = false;
bool reset = true;

void handle_key(SDL_keysym& key)
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
     default:
          break;
     }
}

void process_events()
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

int main(int argc, char* argv[])
{
     _cputs("p - pause / unpause the game\n");
     _cputs("f - while paused, advance one frame\n");
     _cputs("r - reset game\n");

     initialise_engine(screen_width, screen_height);

     static abstract_object instances[] = {
          load_background_object("lake.jpg"),
          load_music_object("promises.ogg")
     };
     static const int size = sizeof(instances) / sizeof(instances[0]);
     static object_array<abstract_object> game_objects(&instances[0], &instances[size]);
     static collection_object example(game_objects);

     while (true) {
          const float time = 1.0f / 60.0f;

          process_events();
          if (reset) {
               reset = false;
               example.reset();
          } else if (!pause || step) {
               step = false;
               example.update(time);
          }
          start_render();
          example.draw();
          end_render();
     }

     return 0;
}
