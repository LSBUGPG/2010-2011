#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

bool wrong_answer(int have, const char * looking_for)
{
     bool wrong = (strchr(looking_for, have) == NULL);
     if (wrong) {
          _cputs(
               "\n"
               "I did not understand that answer.\n"
               "\n");
     }
     return wrong;
}

int roll(int sides)
{
     return (rand() % sides) + 1;
}

int main(int argc, char *argv[])
{
     int answer;

start_game:
     srand(int(time(0)));

     const int dragon_initiative = 7;
     const int dragon_hit_bonus = 5;
     const int dragon_damage_bonus = 4;
     const int dragon_defence = 20;
     int dragon_hit_points = 20;

     const int player_initiative = 10;
     const int player_hit_bonus = 8;
     const int player_damage_bonus = 5;
     const int player_defence = 18;
     int player_hit_points = 20;

     do {
          _cputs(
               "\n"
               "You are in a dark house. In total Darkness, you can hear holwing and snarls\n"
               "brefore you stands a visouse wolf. The wolf bares its teeth and prepares to attack.\n"
               "\n"
               "Will you:\n"
               "[f] fight the wolf; or,\n"
               "[r] run back through the doors?\n"
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
               "[f] fight the wolf; or,\n"
               "[r] think better of it and run?\n"
               "\n>");
          answer = _getche();
     } while (wrong_answer(answer, "fr"));

     if (answer == 'f') {
          goto attack_dragon;
     }

run:
     _cputs(
          "\n"
          "Your heart is punding as you climb run towrds the doors. But, as you slam the doors\n"
          "shut behind you, you suddenly wake.\n"
          "\n");
     goto survivor;

attack_dragon:
     bool player_is_attacking = true;
     enum {
          choose_initiative,
          player_turn,
          dragon_turn
     } phase = choose_initiative;
     while (player_is_attacking && dragon_hit_points > 0 && player_hit_points > 0) {
          int damage;

          switch (phase) {
          case choose_initiative:
               if (roll(20) + player_initiative >= roll(20) + dragon_initiative) {
                    phase = player_turn;
               } else {
                    phase = dragon_turn;
               }
               break;
          case player_turn:
               if (roll(20) + player_hit_bonus >= dragon_defence) {
                    damage = roll(8) + player_damage_bonus;
                    _cprintf(
                         "\n"
                         "You attack the wolf %d points of damage.\n", damage);
                    dragon_hit_points-= damage;
               } else {
                    _cputs(
                         "\n"
                         "poor accuracy you missed.\n");
               }
               if (dragon_hit_points > 0 && player_hit_points > 0) {
                    do {
                         _cputs(
                              "\n"
                              "Will you:\n"
                              "[c] fight to the end; or,\n"
                              "[r] leg it?"
                              "\n>");
                         answer = _getche();
                    } while (wrong_answer(answer, "cr"));

                    player_is_attacking = (answer == 'c');
               }
               phase = dragon_turn;
               break;
          case dragon_turn:
               if (roll(20) + dragon_hit_bonus >= player_defence) {
                    damage = roll(8) + dragon_damage_bonus;
                    _cprintf(
                         "\n"
                         "The wolf hit you for %d points of damage.\n", damage);
                    player_hit_points-= damage;
               } else {
                    _cputs(
                         "\n"
                         "The wolf missed.\n");
               }
               phase = player_turn;
               break;
          }
     }

     if (dragon_hit_points <= 0)	{
          _cputs(
               "\n"
               "amazingly, you kill the wolf with your bare hands! You wake, with\n"
               "extream confidence. You challenger.\n"
               "\n");
          goto the_end;
     } else if (player_hit_points <= 0) {
          _cputs(
               "\n"
               "As wolves the teeth jaws close on your brused body you suddenly wake. You realise\n"
               "you not a true challenger and havent got what it takes to continue.\n"
               "\n");
          goto the_end;
     } else {
          goto run;
     }

survivor:
     _cputs(
          "Your challenege come to an end You defeted the wolf and live\n"
          "You are a true survivor.\n"
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
