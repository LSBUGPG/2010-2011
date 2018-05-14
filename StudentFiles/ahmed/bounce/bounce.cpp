#include "engine.h"

#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>

bool pause = true;
bool step = false;
bool reset = true;

struct ball_definition {
     const char * image;
     const char * audio;
     GLfloat radius; // units in mm
};

struct ball_type {
     GLfloat radius;
     GLuint image;
     Mix_Chunk * audio;
};

struct ball_instance {
     GLfloat position[2]; // [] defines an array
     GLfloat velocity[2];
};

void handle_key(SDL_keysym & key)
{
     switch (key.sym) {
     case SDLK_ESCAPE:
          quit(0);
          break;
     case SDLK_p:
          pause = !pause; //! = Not
          break;
     case SDLK_f:
          step = true;
          break;
     case SDLK_r:
          reset = true;
          break;
     }
}

void process_events(void)
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

void draw(const ball_type & type, const ball_instance & instance)
{
     draw_bitmap(type.image, instance.position, type.radius);
}

void set_start(ball_instance & instance)
{
     instance.position[0] = 0.0f;
     instance.position[1] = 0.0f;
     instance.velocity[0] = 80.0f;
     instance.velocity[1] = 0.0f;
}

const int screen_height = 480;
const int screen_width = 640;
const GLfloat base = GLfloat(-screen_height / 2);
const GLfloat left = GLfloat(-screen_width / 2);
const GLfloat right = GLfloat(screen_width / 2);

GLfloat distance_to_bottom(const ball_type & type, const ball_instance & instance)
{
     return (instance.position[1] - type.radius) - base;
}

GLfloat distance_to_left(const ball_type & type, const ball_instance & instance)
{
     return (instance.position[0] - type.radius) - base;
}

GLfloat distance_to_right(const ball_type & type, const ball_instance & instance)
{
     return (instance.position[0] - type.radius) - base;
}

void update(const ball_type & type, ball_instance & instance, float time)
{
     instance.position[0] += instance.velocity[0] * time;
     instance.position[1] += instance.velocity[1] * time;

     GLfloat distance = distance_to_bottom(type, instance);
     if (distance < 0.0f) {
          instance.position[1] = base + type.radius - distance;
          instance.velocity[1] *= -1.0f;
          play_audio (type.audio);
     }

     distance = distance_to_left(type, instance);
     if (distance < 0.0f) {
          instance.position[0] = left + (type.radius + distance);
          instance.velocity[0] *= -1.0f;

          play_audio (type.audio);
     }

     distance = distance_to_right(type, instance);
     if (distance < 0.0f) {
          instance.position[0] = right - (type.radius + distance);
          instance.velocity[0] *= -1.0f;

          play_audio (type.audio);
     }

     instance.velocity[1] -= 9810.0f * time; // acceleration due to gravity in mm
}

int main(int argc, char * argv[])
{
     initialise_engine();

     ball_definition definition = { "ball.bmp", "bounce.wav", 40.0f };
     ball_type type;
     ball_instance instance;

     type.image = load_bitmap(definition.image);
     type.audio = load_audio(definition.audio);
     type.radius = definition.radius;

     while (true) {
          const float time = 1.0f / 60.0f;

          process_events();
          if (reset) {
               set_start(instance);
               reset = false;
          } else if (!pause || step) {
               update(type, instance, time);
               step = false;
          }
          start_render();
          draw(type, instance);
          end_render();
     }

     return 0;
}
