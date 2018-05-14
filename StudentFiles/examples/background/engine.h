typedef struct _Mix_Music Mix_Music;

void initialise_engine(int width, int height);
void quit(int code);
int load_bitmap(const char* filename);
void start_render();
void end_render();
void draw_bitmap(int texture, const float* position, const float* size);
Mix_Music* load_music(const char* filename);
void play_music(Mix_Music* music);
void pause_music();
void resume_music();
