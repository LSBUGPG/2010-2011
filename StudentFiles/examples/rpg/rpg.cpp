#include "engine.h"

#include <conio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char*argv[])
{
     int answer;

start_game:
     srand(int(time(0)));

     creature player = { "player", 7, 5, 4, 20, 20 };
     creature dark = { "dark", 10, 8, 5, 18, 20 };

     do {
          _cputs(
               "\n"
               "You are in a tunnel.In the darkness, you can escape\n"
               "You must find a way out to escape.\n"
               "\n"
               "Will you:\n"
               "[f] walk in the dark; or,\n"
               "[r] shout for help?\n"
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
               "[f] walk in the dark; or,\n"
               "[r] shout for help?\n"
               "\n>");
          answer = _getche();
     } while (wrong_answer(answer, "fr"));

     if (answer == 'f') {
          goto attack_dark;
     }

run:
     _cputs(
          "\n"
          "Your heart races as you attempt to walk in the dark. But, as you walk\n"
          "another person starts to talk.\n"
          "\n");
     goto survivor;

attack_dark:
     battle_result result = do_battle(player, dark);

     switch (result) {
     case player_wins:
          _cputs(
               "\n"
               "Incredibly, the person helps you escape the tunnel\n"
               "newfound confidence. You are a true adventurer.\n"
               "\n");
          goto the_end;
     case dark_wins:
          _cputs(
               "\n"
               "The person is dying from hunger. You realise\n"
               "you do not have what it takes to be a human being.\n"
               "\n");
          goto the_end;
     case player_runs:
          goto run;
     }

survivor:
     _cputs(
          "Your adventure is at an end. You have faced a battle to survive\n"
          "tale. You are a true survivor.\n"
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
