#include "window.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL_mixer.h>

#include "object.h"
#include "collection.h"
#include "engine.h"
#include "measurements.h"

struct window_type {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * spawn;
     Mix_Chunk * hit;
};

static window_type type;
const float growth_rate = 20.0f;

inline float square(float number)
{
     return number * number;
}

inline float square_distance_between(const float * point_a, const float * point_b)
{
     return square(point_a[0] - point_b[0]) + square(point_a[1] - point_b[1]);
}

class window_instance: public object {
     float position[2];
     float velocity[2];
     float radius;
     enum { grow, move } stage;

public:
     window_instance(void) {
     }
     window_instance(const float * spawn_position, const float * initial_velocity) {
          position[0] = spawn_position[0];
          position[1] = spawn_position[1];
          velocity[0] = initial_velocity[0];
          velocity[1] = initial_velocity[1];
          stage = grow;
          radius = 1.0f;
     }
     void reset(void) {
          expire_window(*this);
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
               position[0] += velocity[0] * time;
               position[1] += velocity[1] * time;

               if (position[0] < screen_left + type.radius) {
                    position[0] = screen_left + type.radius;
                    velocity[0] *= -1.0f;
               }

               if (position[0] > screen_right - type.radius) {
                    position[0] = screen_right - type.radius;
                    velocity[0] *= -1.0f;
               }

               if (position[1] > screen_top - type.radius) {
                    position[1] = screen_top - type.radius;
                    velocity[1] *= -1.0f;
               }

               if (position[1] < screen_bottom + type.radius) {
                    position[1] = screen_bottom + type.radius;
                    velocity[1] *= -1.0f;
               }
               break;
          }
     }
     void draw(void) {
          draw_bitmap(type.image, position, radius, 0.0f);
     }
     bool collide(const float * collision_position, float collision_radius) {
          float square_distance = square_distance_between(position, collision_position);
          bool hit = (stage == move && square_distance < square(radius + collision_radius));
          if (hit) {
               play_audio(type.hit);
               expire_window(*this);
          }
          return hit;
     }
};

const int maximum_windows = 30;
const int initial_speed = 20;

class window_pool: public object_pool<window_instance> {
     window_instance instance[maximum_windows];
public:
     window_pool(): object_pool(&instance[0], &instance[maximum_windows]) {
     }
     void spawn(void) {
          float position[2] = {
               float((rand() % screen_width) - screen_width / 2),
               float((rand() % screen_height) - screen_height / 2)
          };
          float velocity[2] = {
               float((rand() % 2) * initial_speed * 2 - initial_speed),
               float((rand() % 2) * initial_speed * 2 - initial_speed)
          };
          if (add(window_instance(position, velocity))) {
               play_audio(type.spawn);
          }
     }
};

static window_pool windows;

object & load_windows(const char * image, const char * spawn_audio,
                       const char * hit_audio, float radius)
{
     type.image = load_bitmap(image);
     type.radius = radius;
     type.spawn = load_audio(spawn_audio);
     type.hit = load_audio(hit_audio);

     static collection_object instance(windows);
     return instance;
}

void spawn_window(void)
{
     windows.spawn();
}

static void copy_position(float * to, const float * from)
{
     to[0] = from[0];
     to[1] = from[1];
}

class collision_test: public test_function {
     float position[2];
     float radius;
public:
     collision_test(const float * collision_position, float collision_radius):
          radius(collision_radius) {

          copy_position(&position[0], collision_position);
     }
     bool test(object & instance) const {
          window_instance & window = *((window_instance*)&instance);
          return window.collide(position, radius);
     }
};

bool hit_windows(const float * position, float radius)
{
     return windows.find_object(collision_test(position, radius));
}

void expire_window(window_instance & instance)
{
     windows.remove(instance);
}
