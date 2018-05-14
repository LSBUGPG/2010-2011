#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "collection.h"
#include "state.h"
#include "controls.h"

#include <windows.h>
#include <SDL.h>

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
     case SDLK_SPACE:
          skip = true;
          start = true;
          action = true;
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
     initialise_engine(screen_width, screen_height);

     static object* shell = load_shell();

     while (true) {
          const float time = 1.0f / 60.0f;

          process_events();
          if (reset) {
               reset = false;
               shell->reset();
          } else if (!pause || step) {
               step = false;
               shell->update(time);
          }
          start_render();
          shell->draw();
          end_render();
     }

     return 0;
}
