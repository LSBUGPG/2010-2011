#include <windows.h>
#include <GL/gl.h>

struct Mix_Chunk;

void initialise_engine(void);
void quit(int code);
GLuint load_bitmap(const char * filename);
Mix_Chunk * load_audio(const char * filename);
void draw_bitmap(GLuint texture, const GLfloat * position, GLfloat size);
void play_audio(Mix_Chunk * audio);
void start_render(void);
void end_render(void);
