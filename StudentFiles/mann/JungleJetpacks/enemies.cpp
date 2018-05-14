#include "enemies.h"
#include "collection.h"

#include <windows.h>
#include <GL/gl.h>

#include "object.h"
#include "engine.h"
#include "measurements.h"
#include "state.h"

struct enemy_type {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * spawn;
     Mix_Chunk * hit;
};

static enemy_type type;
const float growth_rate = 15.0f;
const int initial_speed = 80;

inline float square(float number)
{
     return number * number;
}
inline float square_distance_between(const float * point_a, const float * point_b)
{
     return square(point_a[0] - point_b[0]) + square(point_a[1] - point_b[1]);

}

class enemy_instance: public object {
     float position[2];
     float velocity[2];
     float radius;
     enum { grow, move } stage;

public:
     enemy_instance(void) {
     }
     void reset(void) {
          position[1] = float((rand() % screen_width) - screen_width / 5);// position of enemies
          position[1] = float((rand() % screen_height) - screen_height  / 2);

          if (rand() % 2) {
               velocity[0] = initial_speed;
               velocity[1] = 0.0f;
          } else {
               velocity[0] = 40.0f;
               velocity[1] = initial_speed;
          }
          stage = grow;
          radius = 1.0f;
     }
     void update(float time) {
          switch (stage) {
          case grow:
               if (radius < type.radius) {
                    radius += growth_rate * time;
               } else {
                    radius = type.radius;
                    stage = move;
               }
               break;
          case move:
               position[0] -= velocity[0] * time;

               if (position[0] < screen_left + type.radius) {
                    position[0] = screen_left + type.radius;
                    position[0] *= -1.0f;
               }

               if (position[0] > screen_right - type.radius) {
                    position[0] = screen_right - type.radius;
                    position[0] *= -1.0f;
               }
               break;
          }
     }

     void draw(void) {
          draw_bitmap(type.image, position, radius, 0.0f);
     }

     bool collide(const float * collision_position,float collision_radius) {
          float square_distance = square_distance_between(position, collision_position);
          return square_distance < square(radius + collision_radius);
     }
};

class collision_test: public test_function {
     float position[2];
     float radius;
public:
     collision_test(const float * collision_position,
                    float collision_radius): radius(collision_radius) {
          position[0] = collision_position[0];
          position[1] = collision_position[1];
     }

     bool test(object & instance) const {
          enemy_instance & enemy = *((enemy_instance*)&instance);
          return enemy.collide(position, radius);
	 }

	 void notify_win(bool win)
{
     change_state(gameover_state());
}

};

static object_array<enemy_instance> * enemies_instance = 0;

object & load_enemies(const char * image, float position)
{
     type.image = load_bitmap(image);
     type.radius = 30.0f;
     static enemy_instance enemies[10];
     const int number_of_enemies =
          sizeof(enemies) / sizeof(enemy_instance);

     static object_array<enemy_instance>
     enemy_array(&enemies[0], &enemies[number_of_enemies]);

     static collection_object instance(enemy_array);
     enemies_instance = &enemy_array;
     return instance;
}

bool enemies_collide(const float * position, float radius)
{
     bool collide = false;
     if (enemies_instance) {
          collide = enemies_instance->find_object(collision_test(position, radius));
     }
     return collide;
}
