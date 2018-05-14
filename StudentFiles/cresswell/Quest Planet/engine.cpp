#include "engine.h"

#include <windows.h>
#include <GL/gl.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <conio.h>
#include <math.h>

static void setup_opengl(GLdouble width, GLdouble height);

void initialise_engine(int width, int height, float scale)
{
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
          _cprintf("Video initialization failed: %s\n", SDL_GetError());
          quit(1);
     }

     const int frequency = 44100;
     const int stereo = 2;
     const int buffer_size = 1024;

     const SDL_VideoInfo * info = SDL_GetVideoInfo();
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

     setup_opengl(GLdouble(width * scale), GLdouble(height * scale));

     if (TTF_Init() == -1) {
          _cprintf("Font init failed: %s\n", TTF_GetError());
          quit(1);
     }
}

void quit(int code)
{
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

void start_render(void)
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glEnable(GL_BLEND);
     glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

static void send_vertex(const GLfloat * texture_coordinates, const GLfloat * position)
{
     glTexCoord2fv(texture_coordinates);
     glVertex2fv(position);
}

void draw_bitmap(int texture, const float * position, const float * size)
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

void end_render(void)
{
     SDL_GL_SwapBuffers();
}

void premultiply_alpha(SDL_Surface *surface)
{
     for (int x = 0; x < surface->w; x++) {
          for (int y = 0; y < surface->h; y++) {
               size_t offset = (y * surface->pitch + x * 4);
               unsigned char *channel = (unsigned char*)surface->pixels + offset;

               channel[0] = (channel[0] * channel[3]) / 255;
               channel[1] = (channel[1] * channel[3]) / 255;
               channel[2] = (channel[2] * channel[3]) / 255;
          }
     }
}

int load_bitmap(const char * filename)
{
     GLuint handle;
     glGenTextures(1, &handle);
     glBindTexture(GL_TEXTURE_2D, handle);

     SDL_Surface * surface = SDL_LoadBMP(filename);
     if (surface) {
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

          SDL_FreeSurface(surface);
     } else {
          _cprintf("Failed to load bitmap file: %s\n", filename);
     }

     return int(handle);
}

void delete_bitmap(int handle)
{
     GLuint gl_handle(handle);
     glDeleteTextures(1, &gl_handle);
}

int load_text_line(TTF_Font * font, const char * line, float * size)
{
     GLuint handle;
     glGenTextures(1, &handle);
     glBindTexture(GL_TEXTURE_2D, handle);

     if (font) {
          SDL_Color col = {255, 255, 255};

          SDL_Surface *surface = TTF_RenderUTF8_Blended(font, line, col);
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

TTF_Font * load_font(const char * file_name)
{
     TTF_Font * font = TTF_OpenFont(file_name, 24);
     if (!font) {
          _cprintf("Could not load font: %s\n", file_name);
     }

     return font;
}
