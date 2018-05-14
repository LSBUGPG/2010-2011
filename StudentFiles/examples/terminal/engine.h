struct _TTF_Font;
typedef _TTF_Font TTF_Font;

void initialise_engine(int width, int height, float scale);
void quit(int code);
int load_bitmap(const char* filename);
void delete_bitmap(int handle);
void start_render();
void end_render();
void draw_bitmap(int texture, const float* position, const float* size);
TTF_Font* load_font(const char* file_name, int size);
int load_text_line(TTF_Font* font, const char* line, float* size);
