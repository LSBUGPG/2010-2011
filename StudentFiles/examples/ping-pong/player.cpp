#include "player.h"

#include <windows.h>
#include <GL/gl.h>

#include "object.h"
#include "ball.h"
#include "engine.h"
#include "measurements.h"

class player_instance : public object {
     GLfloat position[2];
     GLfloat charge_time;
     bool charging;
     table_side side;
public:
     player_instance(table_side player_side) {
          switch (player_side) {
          case left:
               position[0] = -table_width;
               position[1] = table_top + ball_radius* 2.0f;
               break;
          case right:
               position[0] = table_width;
               position[1] = table_top + ball_radius* 2.0f;
               break;
          }
          side = player_side;
     }

     void reset() {
          charge_time = 0.0f;
          charging = false;
     }

     void update(float time) {
          if (charging) {
               charge_time += time;
          }
     }

     void draw() {}

     void charge() {
          charging = true;
          charge_time = 0.0f;
     }

     void begin_serve() {
          reset();
          hold_ball(position);
     }

     void swing() {
          float power = 0.5f + min(0.5f, charge_time);
          notify_swing(side, power);
          reset();
     }
};

static player_instance player[] = { left, right };
static const int number_of_players = sizeof(player) / sizeof(player[0]);

class player_collection : public object_collection {
protected:
     void for_each_object(object_function& function) {
          for (int index = 0; index < number_of_players; index++) {
               function.call(player[index]);
          }
     }
};

object* load_player_objects()
{
     static player_collection collection;
     return &collection;
}

void swing_racket(table_side side)
{
     switch (side) {
     case left:
          player[0].swing();
          break;
     case right:
          player[1].swing();
          break;
     }
}

void begin_serve(table_side side)
{
     switch (side) {
     case left:
          player[0].begin_serve();
          break;
     case right:
          player[1].begin_serve();
          break;
     }
}

void charge_racket(table_side side)
{
     switch (side) {
     case left:
          player[0].charge();
          break;
     case right:
          player[1].charge();
          break;
     }
     notify_racket_charge(side);
}
