struct _TTF_Font;
typedef _TTF_Font TTF_Font;
struct Mix_Chunk;

void initialise_engine(int width, int height, float scale);
void quit(int code);
int load_bitmap(const char * filename);
Mix_Chunk * load_audio(const char * filename);
void play_audio(Mix_Chunk * audio);
void start_render(void);
void end_render(void);
void draw_bitmap(int texture, const float * position, const float * size);
float radians(float degrees);
TTF_Font* load_font(const char* file_name);
int load_text_line(TTF_Font* font, const char* line, float* size);
void delete_bitmap(int handle);
