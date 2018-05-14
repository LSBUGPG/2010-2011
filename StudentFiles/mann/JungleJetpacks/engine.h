struct Mix_Chunk;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;

void initialise_engine(int width, int height, float scale);
void quit(int code);
int load_bitmap(const char * filename);
TTF_Font* load_font(const char* fontname, int size);
void release_font(TTF_Font* font);
int load_text_line(TTF_Font* font, const char* line, float* size);
Mix_Chunk * load_audio(const char * filename);
void play_audio(Mix_Chunk * audio);
void start_render(void);
void end_render(void);
void draw_bitmap(int texture, const float * position, const float * size);
void draw_bitmap(int texture, const float * position, float radius,
                 float heading);
float radians(float degrees);