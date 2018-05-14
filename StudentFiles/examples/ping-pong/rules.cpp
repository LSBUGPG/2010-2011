#include "rules.h"

#include <conio.h>

#include "object.h"
#include "player.h"
#include "table.h"
#include "ball.h"
#include "measurements.h"

enum state { start, service, rally, end };

static table_side server = none;
static int remaining_serves = 2;
static table_side last_bounce = none;
static table_side last_hit = none;
static int score[] = { 0, 0 };
static state game_state = start;

class ping_pong_game : public object_collection {
     object** object_array;
     int size;
protected:
     void for_each_object(object_function& function) {
          for (int index = 0; index < size; index++) {
               function.call(*object_array[index]);
          }
     }
public:
     ping_pong_game() {
          static object* game_objects[] = {
               load_ball_object("ball.bmp", "hit.wav"),
               load_player_objects(),
               load_table_object("table.bmp", "bounce.wav")
          };

          object_array = game_objects;
          size = sizeof(game_objects) / sizeof(game_objects[0]);
     }

     void reset() {
          _cputs("game begins\n");
          server = left;
          remaining_serves = 2;
          last_hit = none;
          last_bounce = none;
          score[0] = 0;
          score[1] = 0;
          game_state = start;
          object_collection::reset();
     }

     void update(float time) {
          switch (game_state) {
          case start:
               begin_serve(server);
               game_state = service;
               break;
          case service:
               break;
          case rally:
               break;
          case end:
               break;
          }
          object_collection::update(time);
     }
};

object* load_ping_pong_game()
{
     static ping_pong_game instance;
     return &instance;
}

static table_side other_side(table_side side)
{
     table_side other = none;

     switch (side) {
     case left:
          other = right;
          break;
     case right:
          other = left;
          break;
     }

     return other;
}

static void next_service()
{
     remaining_serves--;
     if (remaining_serves <= 0) {
          server = other_side(server);
          remaining_serves = 2;
     }

     last_hit = none;
     last_bounce = none;
     game_state = start;
}

void add_point(table_side side)
{
     remove_ball_from_play();

     switch (side) {
     case left:
          score[0]++;
          break;
     case right:
          score[1]++;
          break;
     }

     if (score[0] > 10 && score[0] >= score[1] + 2) {
          game_state = end;
          _cputs("player 1 wins\n");
     } else if (score[1] > 10 && score[1] >= score[0] + 2) {
          game_state = end;
          _cputs("player 2 wins\n");
     } else {
          next_service();
     }

     _cprintf("player 1: %d   player 2: %d\n", score[0], score[1]);
}

void notify_bounce(table_side side)
{
     switch (side) {
     case left:
          if (last_bounce == left) {
               _cputs("ball bounced twice on the left, point to player 2\n");
               add_point(right);
          } else {
               last_bounce = left;
          }
          break;

     case right:
          if (last_bounce == right) {
               _cputs("ball bounced twice on the right, point to player 1\n");
               add_point(left);
          } else {
               last_bounce = right;
          }
          break;
     }
}

void notify_out_of_play()
{
     switch (last_bounce) {
     case left:
          _cputs("ball went out of play after bouncing on the left, point to player 2\n");
          break;
     case right:
          _cputs("ball went out of play after bouncing on the right, point to player 1\n");
          break;
     }
     add_point(other_side(last_bounce));
}

void notify_swing(table_side side, float power)
{
     switch (game_state) {
     case service:
          if (side == server) {
               hit_ball(side, power);
               last_hit = side;
               game_state = rally;
          }
          break;
     case rally:
          if (side == last_hit) {
               switch (side) {
               case left:
                    _cputs("ball was hit twice by player 1, point to player 2\n");
                    break;
               case right:
                    _cputs("ball was hit twice by player 2, point to player 1\n");
                    break;
               }
               add_point(other_side(last_hit));
          } else if (side != last_bounce) {
               switch (side) {
               case left:
                    _cputs("ball hit by player 1 before bouncing on the left, point to player 2\n");
                    break;
               case right:
                    _cputs("ball hit by player 2 before bouncing on the right, point to player 1\n");
                    break;
               }
               add_point(other_side(side));
          } else {
               hit_ball(side, power* 2.0f);
               last_hit = side;
          }
          break;
     default:
          // ignore
          break;
     }
}

void notify_racket_charge(table_side side)
{
     if (game_state == service && side == server) {
          toss_ball();
     }
}
