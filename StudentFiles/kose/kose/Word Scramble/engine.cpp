#include "engine.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <conio.h>
#include <math.h>

static void setup_opengl(GLdouble width, GLdouble height);

void initialise_engine(int width, int height)
{
     if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
          _cprintf("Video or audio initialization failed: %s\n", SDL_GetError());
          quit(1);
     }

     const int frequency = 44100;
     const int stereo = 2;
     const int buffer_size = 2048;

     if (Mix_OpenAudio(frequency, AUDIO_S16, stereo, buffer_size)) {
          _cputs("Unable to open audio!\n");
          quit(1);
     }

     const SDL_VideoInfo* info = SDL_GetVideoInfo();
     if (!info) {
          _cprintf("Video query failed: %s\n", SDL_GetError());
          quit(1);
     }

     SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
     SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

     int bpp = info->vfmt->BitsPerPixel;
     Uint32 flags = SDL_OPENGL;

     if (SDL_SetVideoMode(width, height, bpp, flags) == 0) {
          _cprintf("Video mode set failed: %s\n", SDL_GetError());
          quit(1);
     }

     setup_opengl(GLdouble(width), GLdouble(height));

     int format = IMG_INIT_JPG;
     if (IMG_Init(format) != format) {
          _cprintf("Failed to initialise image library: %s\n", IMG_GetError());
          quit(1);
     }

     if (TTF_Init() == -1) {
          _cprintf("Font init failed: %s\n", TTF_GetError());
          quit(1);
     }
}

void quit(int code)
{
     Mix_CloseAudio();
     IMG_Quit();
     SDL_Quit();
     exit(code);
}

void setup_opengl(GLdouble width, GLdouble height)
{
     glClearColor(0, 0, 0, 0);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     const GLdouble left = -width / 2.0;
     const GLdouble right = width / 2.0;
     const GLdouble top = height / 2.0;
     const GLdouble bottom = -height / 2.0;
     const GLdouble front = 0.0;
     const GLdouble back = 100.0;

     glOrtho(left, right, bottom, top, front, back);

     glEnable(GL_TEXTURE_2D);
}

void start_render()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glEnable(GL_BLEND);
     glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

static void send_vertex(const GLfloat* texture_coordinates, const GLfloat* position)
{
     glTexCoord2fv(texture_coordinates);
     glVertex2fv(position);
}

void draw_bitmap(int texture, const float* position, const float* size)
{
     const GLfloat quad[4][2] = {
          { GLfloat(-size[0]), GLfloat( size[1]) },
          { GLfloat( size[0]), GLfloat( size[1]) },
          { GLfloat( size[0]), GLfloat(-size[1]) },
          { GLfloat(-size[0]), GLfloat(-size[1]) }
     };

     const GLfloat texture_coordinates[4][2] = {
          { 0.0f, 0.0f },
          { 1.0f, 0.0f },
          { 1.0f, 1.0f },
          { 0.0f, 1.0f }
     };

     GLubyte white[] = { 255, 255, 255 };

     glBindTexture(GL_TEXTURE_2D, texture);
     glPushMatrix();
     glTranslatef(position[0], position[1], 0.0f);
     glBegin(GL_TRIANGLES);
     glColor3ubv(white);

     send_vertex(texture_coordinates[0], quad[0]);
     send_vertex(texture_coordinates[1], quad[1]);
     send_vertex(texture_coordinates[2], quad[2]);

     send_vertex(texture_coordinates[2], quad[2]);
     send_vertex(texture_coordinates[3], quad[3]);
     send_vertex(texture_coordinates[0], quad[0]);

     glEnd();
     glPopMatrix();
}

void end_render()
{
     SDL_GL_SwapBuffers();
}

static bool premultiply_alpha(SDL_Surface*surface)
{
     bool alpha = false;

     for (int x = 0; x < surface->w; x++) {
          for (int y = 0; y < surface->h; y++) {
               size_t offset = (y* surface->pitch + x* 4);
               unsigned char*channel = (unsigned char*)surface->pixels + offset;

               channel[0] = (channel[0]* channel[3]) / 255;
               channel[1] = (channel[1]* channel[3]) / 255;
               channel[2] = (channel[2]* channel[3]) / 255;

               if (channel[3] > 0) {
                    alpha = true;
               }
          }
     }

     return alpha;
}

int load_bitmap(const char* filename)
{
      GLuint handle;
     glGenTextures(1, &handle);
     glBindTexture(GL_TEXTURE_2D, handle);

     GLint image_format;
     GLenum byte_order;
     bool upload = false;
     SDL_Surface* surface = IMG_Load(filename);
     if (!surface) {
          _cprintf("Failed to load image file: %s.\n", filename);
     } else switch (surface->format->BitsPerPixel) {
          case 32:
               image_format = GL_RGBA8;
               byte_order = GL_BGRA_EXT;
               if (premultiply_alpha(surface)) {
                    upload = true;
               } else {
                    _cprintf(
                         "Warning: the alhpa channel of bitmap file %s is totally blank.\n",
                         filename);
               }
               break;
          case 24:
               image_format = GL_RGB8;
               byte_order = GL_RGB;
               upload = true;
               break;
          default:
               _cprintf(
                    "The bitmap file: %s loaded but it is %d bit format.\n"
                    "This engine only draws 24 or 32 bit with alpha.\n",
                    filename, surface->format->BitsPerPixel);
               break;
          }

     if (upload) {
          const GLint mipmap_level = 0;
          const GLint no_border = 0;

          glTexImage2D(
               GL_TEXTURE_2D,
               mipmap_level,
               image_format,
               surface->w,
               surface->h,
               no_border,
               byte_order,
               GL_UNSIGNED_BYTE,
               surface->pixels);

          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     }

     if (surface) {
          SDL_FreeSurface(surface);
     }

     return handle;
}

void delete_bitmap(int handle)
{
     GLuint gl_handle(handle);
     glDeleteTextures(1, &gl_handle);
}

int load_text_line(TTF_Font* font, const char* line, float* size)
{
     GLuint handle;
     glGenTextures(1, &handle);
     glBindTexture(GL_TEXTURE_2D, handle);

     if (font) {
          SDL_Color col = {255, 255, 255};

          SDL_Surface*surface = TTF_RenderUTF8_Blended(font, line, col);
          if (surface) {
               if (surface->format->BitsPerPixel == 32) {
                    premultiply_alpha(surface);

                    const GLint mipmap_level = 0;
                    const GLint no_border = 0;

                    glTexImage2D(
                         GL_TEXTURE_2D,
                         mipmap_level,
                         GL_RGBA8,
                         surface->w,
                         surface->h,
                         no_border,
                         GL_BGRA_EXT,
                         GL_UNSIGNED_BYTE,
                         surface->pixels);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    size[0] = GLfloat(surface->w) / 2.0f;
                    size[1] = GLfloat(surface->h) / 2.0f;
               }

               SDL_FreeSurface(surface);
          }
     }
     return int(handle);
}

TTF_Font* load_font(const char* file_name, int point_size)
{
     TTF_Font* font = TTF_OpenFont(file_name, point_size);
     if (!font) {
          _cprintf("Could not load font: %s\n", file_name);
     }

     return font;
}

void release_font(TTF_Font* font)
{
     if (font) {
          TTF_CloseFont(font);
     }
}

Mix_Music* load_music(const char* filename)
{
     Mix_Music* music = Mix_LoadMUS(filename);
     if (!music) {
          _cprintf("Failed to load audio file: %s\n", filename);
     }
     return music;
}

void play_music(Mix_Music* music)
{
     if (Mix_PlayingMusic()) {
          Mix_RewindMusic();
          resume_music();
     } else {
          const int loop_forever = -1;
          if (Mix_PlayMusic(music, loop_forever) != 0) {
               _cputs("Failed to play music\n");
          }
     }
}

void pause_music()
{
     if (!Mix_PausedMusic()) {
          Mix_PauseMusic();
     }
}

void resume_music()
{
     if (Mix_PausedMusic()) {
          Mix_ResumeMusic();
     }
}