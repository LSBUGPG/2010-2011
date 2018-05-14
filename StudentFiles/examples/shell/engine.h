typedef struct _Mix_Music Mix_Music;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;

void initialise_engine(int width, int height);
void quit(int code);
int load_bitmap(const char* filename);
TTF_Font* load_font(const char* fontname, int size);
void release_font(TTF_Font* font);
int load_text_line(TTF_Font* font, const char* line, float* size);
void start_render();
void end_render();
void draw_bitmap(int texture, const float* position, const float* size);
Mix_Music* load_music(const char* filename);
void play_music(Mix_Music* music);
void pause_music();
void resume_music();
