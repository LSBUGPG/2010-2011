#include "object.h"
#include "engine.h"
#include "player.h"
#include "measurements.h"

#include <windows.h>
#include <SDL.h>
#include <conio.h>

bool pause = false;
bool step = false;
bool reset = true;

void handle_key(SDL_keysym & key, keystate state)
{
     control action = none;
     switch (key.sym) {
     case SDLK_UP:
          action = thrust;
          break;
     case SDLK_LEFT:
          action = left;
          break;
     case SDLK_RIGHT:
          action = right;
          break;
     case SDLK_LCTRL:
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
     _cputs("p - pause / unpause the game\n");
     _cputs("f - while paused, advance one frame\n");
     _cputs("r - reset game\n");

     initialise_engine(screen_width, screen_height, scale);

     object & player = load_player("ship.bmp", 10.0f);

     while (true) {
          const float time = 1.0f / 60.0f;

          process_events();
          if (reset) {
               reset = false;
               player.reset();
          } else if (!pause || step) {
               step = false;
               player.update(time);
          }
          start_render();
          player.draw();
          end_render();
     }

     return 0;
}
