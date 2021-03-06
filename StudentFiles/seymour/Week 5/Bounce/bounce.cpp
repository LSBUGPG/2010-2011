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
     GLfloat position[1]; 
     GLfloat velocity[1]; 
};

void handle_key(SDL_keysym & key)
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
	 instance.position[0] = GLfloat((rand() % 600) - 300);  
	 instance.position[1] = GLfloat((rand() % 400) - 200);
     instance.velocity[0] = 0.0f;
     instance.velocity[1] = 0.0f;
}

const int screen_height = 480;
const int sceen_width = 680;

const GLfloat base = GLfloat(-screen_height / 3);


GLfloat distance_to_bottom(const ball_type & type, const ball_instance & instance)
{
     return (instance.position[1] - type.radius) - base;
}

void update(const ball_type & type, ball_instance & instance, float time)
{
     instance.position[0] += instance.velocity[0] * time;
     instance.position[1] += instance.velocity[1] * time;

     GLfloat distance = distance_to_bottom(type, instance);
     if (distance < 0.0f) {
          instance.position[1] = base + type.radius - distance;
          instance.velocity[1] *= -1.0f;

		  if (instance.position[0] < -250)

	{

		  instance.velocity[0] = 0.01; 
	
		  }
	 }

	 instance.velocity[1] -= 1500.0f * time; 
	 instance.velocity[0] -= 100.0f * time; 

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
