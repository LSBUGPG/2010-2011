struct Mix_Chunk;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;

void initialise_engine(int width, int height, float scale);
void quit(int code);
int load_bitmap(const char * filename);
Mix_Chunk * load_audio(const char * filename);
void play_audio(Mix_Chunk * audio);
void start_render(void);
void end_render(void);
void draw_bitmap(int texture, const float * position, float radius,
                 float heading);
void draw_bitmap(int texture, const float * position, const float * size);
void delete_bitmap(int texture);
float radians(float degrees);
int load_text_line(TTF_Font * font, const char * line, float * size);
TTF_Font * load_font(const char * fontname, int size);
void release_font(TTF_Font * font);
