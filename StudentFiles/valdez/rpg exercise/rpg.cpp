 #include "engine.h"

#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char*argv[])
{
     int answer;

start_game:
     srand(int(time(0)));

     creature player = { "player", 5, 9, 6, 12, 18 };
     creature dragon = { "dragon", 4, 7, 7, 16, 19 };

     do {
          _cputs(
               "\n"
               "You are in Hell. You see Satan in all his might\n"
               "and he gives a proposition that if you defeat him you go free.\n"
               "\n"
               "Will you:\n"
               "[f] fight Satan; or,\n"
               "[r] run back to your fiery cave?\n"
               "\n>");
          answer = _getche();
     } while (wrong_answer(answer, "fr"));

     if (answer == 'r') {
          goto run;
     }

     do {
          _cputs(
               "\n"
               "Barehanded! Are you sure? Will you:\n"
               "[f] fight the Devil; or,\n"
               "[r] think better of it and run back to your cave?\n"
               "\n>");
          answer = _getche();
     } while (wrong_answer(answer, "fr"));

     if (answer == 'f') {
          goto attack_dragon;
     }

run:
     _cputs(
          "\n"
          "You run back to your cave and as you're about to get eaten by your fiery cave\n"
          "you suddenly wake.\n"
          "\n");
     goto survivor;

attack_dragon:
     battle_result result = do_battle(player, dragon);

     switch (result) {
     case player_wins:
          _cputs(
               "\n"
               "Incredibly, you fight and defeat the devil! you escape from the fiery hell and\n"
               "wake up with the feeling of bravery you did it!.\n"
               "\n");
          goto the_end;
     case monster_wins:
          _cputs(
               "\n"
               "The Devil rips your head off and leaves it on a pike as a sign off victory.\n"
               "you do not have what it takes to fight your fear.\n"
               "\n");
          goto the_end;
     case player_runs:
          goto run;
     }

survivor:
     _cputs(
          "You deny the challenge and run back to face your fiery cave but you wake up in disbelief\n"
          "You are a coward\n"
          "\n");
     goto the_end;

the_end:
     _cputs(
          "The end.\n");

     do {
          _cputs(
               "\n"
               "[r] Restart this game.\n"
               "[q] Quit.\n"
               "\n>");
          answer = _getche();
     } while (wrong_answer(answer, "rq"));

     if (answer == 'r') {
          goto start_game;
     }

     return 0;
}
