#include "object.h"
#include "engine.h"
#include "rules.h"
#include "player.h"
#include "measurements.h"

#include <windows.h>
#include <SDL.h>
#include <conio.h>

bool pause = false;
bool step = false;
bool reset = true;

enum keystate { press, release };

void handle_key(SDL_keysym& key, keystate state)
{
     switch (state) {
     case press:
          switch (key.sym) {
          case SDLK_LCTRL:
               charge_racket(left);
               break;
          case SDLK_RCTRL:
               charge_racket(right);
               break;
          }
          break;
     case release:
          switch (key.sym) {
          case SDLK_LCTRL:
               swing_racket(left);
               break;
          case SDLK_RCTRL:
               swing_racket(right);
               break;
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
          break;
     }
}

void process_events()
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

int main(int argc, char* argv[])
{
     _cputs("p - pause / unpause the game\n");
     _cputs("f - while paused, advance one frame\n");
     _cputs("r - reset game\n");
     _cputs("left control key  - hold to charge player 1 racket\n");
     _cputs("                    release to swing player 1 racket\n");
     _cputs("right control key - hold to charge player 2 racket\n");
     _cputs("                    release to swing player 2 racket\n");

     initialise_engine(screen_width, screen_height, scale);

     object* ping_pong_game = load_ping_pong_game();

     while (true) {
          const float time = 1.0f / 60.0f;

          process_events();
          if (reset) {
               reset = false;
               ping_pong_game->reset();
          } else if (!pause || step) {
               step = false;
               ping_pong_game->update(time);
          }
          start_render();
          ping_pong_game->draw();
          end_render();
     }

     return 0;
}
