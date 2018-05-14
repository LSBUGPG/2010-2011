#include <conio.h>

int main(int argc, char *argv[])
{
     int answer;
     bool have_key;
     bool grate_locked;

start_game:
     have_key = false;
     grate_locked = true;

     _cputs(
          "\n"
          "Welcome to sleepway camp 2. To play, I will describe your situation, and you must\n"
          "choose what to do."
          "\n"
          "let the challenge begin!\n"
          "\n");

describe_forest:
     _cputs(
          "You are inside a mysterious forest, near a forest. Beside you is a small lake. The forest is\n"
          "unexpectedly quiet. The only sound is the gentle trickle of the water. There is\n"
          "also a small wooden cottage nearby. The door appears unlocked.\n"
          "\n"
          "Will you:\n"
          "[e] enter the cottage; or,\n"
          "[f] follow the lake?\n"
          "\n>");

     answer = _getche();
     if (answer == 'e') {
          goto enter_hut;
     } else if (answer == 'f') {
          goto follow_stream;
     } else {
          goto unknown_forest;
     }

enter_hut:
     _cputs(
          "\n"
          "You enter the cottage.\n"
          "\n");
     goto describe_hut;

follow_stream:
     _cputs(
          "\n"
          "You follow the lake through the forest until you reach a point\n"
          "A dead end.\n"
          "\n");
     goto describe_streambed;

unknown_forest:
     _cputs(
          "\n"
          "I didnt understand that answer.\n"
          "\n");
     goto describe_forest;

describe_hut:
     _cputs(
          "You are inside a creepy cottage.\n"
          "\n");

     if (have_key) {
          _cputs(
               "There is a gold key hook on the wall. Will you:\n"
               "[r] return the key to the hook; or,\n"
               "[g] go back outside?\n"
               "\n>");

          answer = _getche();
          if (answer == 'g') {
               goto leave_hut;
          } else if (answer == 'r') {
               goto return_key;
          } else {
               goto unknown_hut;
          }
     } else {
          _cputs(
               "There is a small metal key hanging from a hook on the wall. Will you:\n"
               "[t] take the key; or,\n"
               "[g] go back outside?\n"
               "\n>");

          answer = _getche();
          if (answer == 'g') {
               goto leave_hut;
          } else if (answer == 't') {
               goto take_key;
          } else {
               goto unknown_hut;
          }
     }

leave_hut:
     _cputs(
          "\n"
          "You exit the cottage.\n"
          "\n");
     goto describe_forest;

return_key:
     _cputs(
          "\n"
          "You return the small key to its hook.\n"
          "\n");
     have_key = false;
     goto describe_hut;

unknown_hut:
     _cputs(
          "\n"
          "I didnt understand the answer.\n"
          "\n");
     goto describe_hut;

take_key:
     _cputs(
          "\n"
          "You grab the key and exit the cottage.\n"
          "\n");
     have_key = true;
     goto describe_forest;

describe_streambed:
     _cputs(
          "You reach the end of the lake. It trickles down into a small hole in the\n"
          "ground. Beyond the hole, the stream bed is dry. There is a house in\n"
          "the dry earth.\n"
          "\n");

     if (grate_locked && have_key) {
          _cputs(
               "The door is loked. the key you have apperes to fit the lock. Will you:\n"
               "[u] use the key to open the grate; or,\n"
               "[g] go back up ?\n"
               "\n>");

          answer = _getche();
          if (answer == 'g') {
               goto return_to_forest;
          } else if (answer == 'u') {
               goto unlock_grate;
          } else {
               goto unknown_streambed;
          }

     } else if (grate_locked) {
          goto return_for_key;
     } else if (have_key) {
          _cputs(
               "The door is unlocked. Will you:\n"
               "[l] lock the door;\n"
               "[e] enter through the doors; or,\n"
               "[g] go back up?\n"
               "\n>");

          answer = _getche();
          if (answer == 'g') {
               goto return_to_forest;
          } else if (answer == 'e') {
               goto enter_cave;
          } else if (answer == 'l') {
               goto lock_grate;
          } else {
               goto unknown_streambed;
          }

     } else {
          _cputs(
               "The doors are unlocked. Will you:\n"
               "[e] enter through the doors; or,\n"
               "[g] go back up?\n"
               "\n>");

          answer = _getche();
          if (answer == 'g') {
               goto return_to_forest;
          } else if (answer == 'e') {
               goto enter_cave;
          } else {
               goto unknown_streambed;
          }
     }

return_to_forest:
     _cputs(
          "\n"
          "You go back up and into the forest.\n"
          "\n");
     goto describe_forest;

unlock_grate:
     _cputs(
          "\n"
          "The key turns in the old lock.\n"
          "\n");
     grate_locked = false;
     goto describe_streambed;

lock_grate:
     _cputs(
          "\n"
          "As you lock the doors you suddenly wake.\n"
          "\n");
     grate_locked = true;
     goto failed_adventurer;

unknown_streambed:
     _cputs(
          "\n"
          "I didnt understand that answer.\n"
          "\n");
     goto describe_streambed;

return_for_key:
     _cputs(
          "The doors are locked. You'll need a key to open it. You go back up to look\n"
          "for one.\n"
          "\n");
     goto describe_forest;

enter_cave:
     _cputs(
          "\n"
          "You step inside the house into the darkness.\n"
          "\n");
     goto describe_cave;

describe_cave:
     _cputs(
          "You are in dark house. You approach a balcony, you kick open the doors\n"
          "You hear howling and snarling. The wolf bares its teeth and prepares to strike.\n"
          "\n"
          "Will you:\n"
          "[f] fight the wolf; or,\n"
          "[r] exit through the doors?\n"
          "\n>");

     answer = _getche();
     if (answer == 'f') {
          goto last_chance;
     } else if (answer == 'r') {
          goto run;
     } else {
          goto unknown_cave;
     }

last_chance:
     _cputs(
          "\n"
          "Barehanded! Are you sure? Will you:\n"
          "[f] fight the wolf barehanded; or,\n"
          "[r] think better of it and run back out ?\n"
          "\n>");

     answer = _getche();
     if (answer == 'f') {
          goto kill_dragon;
     } else if (answer == 'r') {
          goto run;
     } else {
          goto unknown_cave;
     }

run:
     _cputs(
          "\n"
          "Your heart races as. But, as you slam the doors\n"
          "shut behind you, you suddenly wake.\n"
          "\n");
     goto survivor;

unknown_cave:
     _cputs(
          "\n"
          "I didnt not understand that answer.\n"
          "\n");
     goto describe_cave;

kill_dragon:
     _cputs(
          "\n"
          "Amasingly, you fight and kill the wolf! You wake, with\n"
          "with courage and confidence. You are a true adventurer.\n"
          "\n");
     goto the_end;

survivor:
     _cputs(
          "your at the end of the challenge. You have faced a visous wolf and live \n"
          "You are a true survivor.\n"
          "\n");
     goto the_end;

failed_adventurer:
     _cputs(
          "Your challenge ends. You realise you do not have what it takes.\n"
          "\n");

the_end:
     _cputs(
          "The end.\n");

restart_or_quit:
     _cputs(
          "\n"
          "[r] Restart game.\n"
          "[q] Quit.\n"
          "\n>");

     answer = _getche();
     if (answer == 'r') {
          goto start_game;
     } else if (answer == 'q') {
          goto quit;
     } else {
          goto restart_or_quit;
     }

quit:
     return 0;
}
