struct Mix_Chunk;

void initialise_engine(int width, int height, float scale);
void quit(int code);
int load_bitmap(const char * filename);

void start_render();
void end_render();
void draw_bitmap(int texture, const float* position, const float* size);

Mix_Chunk * load_audio(const char * filename);
void play_audio(Mix_Chunk * audio);
void start_render(void);
void end_render(void);
void draw_bitmap(int texture, const float * position, float radius);
float radians(float degrees);