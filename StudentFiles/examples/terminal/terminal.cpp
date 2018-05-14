#include "terminal.h"

#include "object.h"
#include "collection.h"
#include "engine.h"
#include "measurements.h"

#include <string.h>

const int column_count = 80;
const int row_count = 24;
const int max_unicode_width = 4;
static TTF_Font* font = 0;
static int scroll = 0;
static const char cursor[] = "\xE2\x96\x88"; // UNICODE full block encoded as UTF8

class text_line;
static void delete_line(text_line& instance);

class text_line : public object {
     int row;
     int texture;
     float size[2];
     bool created;

     void clear() {
          if (created) {
               delete_bitmap(texture);
               created = false;
          }
     }

public:
     text_line() :row(0), texture(0), created(false) {
     }

     text_line(const char* text, int copy_row) :row(copy_row), texture(0), created(false) {
          if (font && text && text[0]) {
               texture = load_text_line(font, text, size);
               created = true;
          }
     }

     void reset() {
          clear();
     }

     void update(float) {
          if (scroll) {
               row -= scroll;
          }
          if (row < 0) {
               clear();
               delete_line(*this);
          }
     }

     void draw() {
          if (created) {
               const float row_height = float(screen_height) / float(row_count);
               float position[] = {
                    screen_left + size[0],
                    screen_top - (float(row) + 0.5f) * row_height
               };
               draw_bitmap(texture, position, size);
          }
     }
};

static text_line line[row_count];
static object_pool<text_line> line_pool(&line[0], &line[row_count]);

void delete_line(text_line& instance)
{
     line_pool.remove(instance);
}

class edit_line : public object {
     int column;
     bool created;
     int texture;
     char buffer[column_count+sizeof(cursor)];
     float size[2];

     void create_texture() {
          clear();
          if (font) {
               texture = load_text_line(font, buffer, size);
               created = true;
          }
     }

     void clear() {
          if (created) {
               delete_bitmap(texture);
               created = false;
          }
     }

     void end_line() {
          scroll++;
          buffer[column] = 0;
          line_pool.add(text_line(buffer, row_count+scroll-2));
          reset();
     }

public:
     edit_line() :column(0), created(false), texture(0) {
          reset();
     }

     void reset() {
          clear();
          strcpy_s(buffer, cursor);
          column = 0;
     }

     void update(float) {
          if (!created) {
               create_texture();
          }
     }

     void draw() {
          if (created) {
               const float row_height = float(screen_height) / float(row_count);
               float position[] = {
                    screen_left + size[0],
                    screen_top - (float(row_count-1) + 0.5f) * row_height
               };
               draw_bitmap(texture, position, size);
          }
     }

     void set_character(char value) {
          if (value == '\n') {
               end_line();
          } else {
               if (value < 32) {
                    value = 32;
               }
               if (column < column_count) {
                    buffer[column] = value;
                    column++;
                    buffer[column] = 0;
                    if (column == column_count) {
                         end_line();
                    } else {
                         strcat_s(&buffer[column], sizeof(buffer)-column, cursor);
                         clear();
                    }
               }
          }
     }
};

static const float characters_per_second = 20.0f;
static const float send_time = 1.0f / characters_per_second;
static const int max_buffer_size = 2048; // 2K buffer

class terminal : public collection_object {
     float send_remainder;
     char buffer[max_buffer_size];
     edit_line current;

public:
     terminal() :collection_object(line_pool), send_remainder(0.0f) {
     }

     void reset() {
          collection_object::reset();

          line_pool.clear();
          send_remainder = 0.0f;
          current.reset();
          buffer[0] = 0;

          send_line("F1 - pause / unpause the game\n");
          send_line("F2 - while paused, advance one frame\n");
          send_line("F3 - reset game\n");
          send_line("F4 - send a test string to the terminal\n");
     }

     void update(float time) {
          int length = strlen(buffer);
          float remaining = time + send_remainder;
          while (length > 0 && remaining > send_time) {
               current.set_character(buffer[0]);
               memmove_s(buffer, sizeof(buffer), &buffer[1], length);
               length--;
               remaining -= send_time;
          }
          if (length > 0) {
               send_remainder = remaining;
          } else {
               send_remainder = 0.0f;
          }

          collection_object::update(time);
          current.update(time);
          scroll = 0;
     }

     void draw() {
          collection_object::draw();
          current.draw();
     }

     void send(const char* text) {
          strcat_s(buffer, text);
     }
};

static terminal* terminal_instance = 0;

object& load_terminal_object()
{
     font = load_font("LiberationMono-Regular.ttf", 12);

     static terminal instance;
     terminal_instance = &instance;
     return instance;
}

void send_line(const char* text)
{
     if (terminal_instance) {
          terminal_instance->send(text);
     }
}
