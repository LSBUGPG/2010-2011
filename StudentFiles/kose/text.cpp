#include "text.h"

#include "object.h"
#include "engine.h"
#include "Answer.h"
#include "score.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>


static TTF_Font * font = 0;

class text: public object {
     int texture;
     float position[2];
     float size[2];
     bool created;

public:
     text(const char * message): created(false) {
          new_challenge(message);
     }

     void new_challenge(const char * message) {
          if (created) {
               delete_bitmap(texture);
          }
          texture = load_text_line(font, message, size);
          created = true;
     }

     void reset(void) {
          position[0] = -100.0f;
          position[1] = 0.0f;
     }

     void update(float time) {
     }

     void draw(void) {
          if (created) {
               draw_bitmap(texture, position, size);
          }
     }
};

static void swap(char & in, char & out)
{
     char temporary = in;
     in = out;
     out = temporary;
}

struct challenge {
     const char * word;
     const char * hint;
};

challenge random_challenge(void)
{
     const char * words[] = {
          "computer",
          "programs",
          "software",
          "handheld",
          "mobilephone",
          "bluetooth",
          "hardware",
          "keyboard",
          "network"
          
     };

     const char * hint[] = {
          "Another name for a PC",
          "write programs on this thing...",
          "Relating to communication usage wireless",
          "Opposite of Hardware",
          "To ring people on",
          "To send pictures from using a device"
     };

     const int number_of_words = sizeof(words) / sizeof(words[0]);

     srand((int)time(0));
     int choice = (rand() % number_of_words);
     const char * theWord = words[choice];  // word to guess
     const char * theHint = hint[choice];  // hint for word
     
     challenge instance = { theWord, theHint };
     return instance;
}

static const char * original = 0;

static text * scrambled_word = 0;
static const int maximum_letters = 20;
static char scrambled[maximum_letters + 1];

static void next_challenge(void)
{
     challenge current = random_challenge();
     original = current.word;
     strcpy_s(scrambled, original);

     int length = strlen(scrambled);
     for (int index = 0; index < length; index++) {
          swap(scrambled[index], scrambled[(rand() % length)]);
     }
}

object & load_text_object(TTF_Font * input_font)
{
     srand(int(time(0)));

     font = input_font;

     next_challenge();

     static text message(scrambled);
     scrambled_word = &message;
     return message;
}

void test_guess(const char * guess)
{
     if (strcmp(guess, original) == 0) {
          add_score();
          next_challenge();
          if (scrambled_word) {
               scrambled_word->new_challenge(scrambled);
          }
          reset_answer();
     }
}
