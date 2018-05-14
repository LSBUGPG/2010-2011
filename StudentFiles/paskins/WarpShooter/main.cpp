#include "engine.h"
#include "state.h"
#include "measurements.h"
#include "controls.h"
#include "background.h"
#include "collection.h"
#include "object.h"

#include <windows.h>
#include <SDL.h>

bool pause = false;
bool step = false;
bool reset = true;

void handle_key(SDL_keysym & key, keystate state)
{
     control action = none;
     switch (key.sym) {
     case SDLK_UP:
          action = warp;		//pressing the up arrow key will warp the player's ship to the top or bottom, depending on current location
          break;
     case SDLK_LEFT:
          action = left;
          break;
     case SDLK_RIGHT:
          action = right;
          break;
     case SDLK_SPACE:
          action = fire;
          break;
     default:
          break;
     }

     if (action != none) {
          control_ship(action, state);
     } else if (state == release) {
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
          case SDLK_RETURN:
               skip = true;
               start = true;
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
     initialise_engine(screen_width, screen_height, scale);

     object * shell = load_shell();

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



