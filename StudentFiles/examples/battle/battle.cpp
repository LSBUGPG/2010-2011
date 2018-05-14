#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

bool wrong_answer(int have, const char* looking_for)
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

int main(int argc, char*argv[])
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
               "You enter the cave. Before you, is a door that has a vicious creature inside.\n"
               "You hear the roar of the creature and you begin to have second thoughts.\n"
               "\n"
               "Will you:\n"
               "[f] fight the creature; or,\n"
               "[r] run back through the door?\n"
               "\n>");
          answer = _getche();
     } while (wrong_answer(answer, "fr"));

     if (answer == 'r') {
          goto run;
     }

     do {
          _cputs(
               "\n"
               "Barehanded! The creature shows his sharp teeth as a warning! Are you sure? Will you:\n"
               "[f] fight the creature barehanded; or,\n"
               "[r] think better of it and leave the cave?\n"
               "\n>");
          answer = _getche();
     } while (wrong_answer(answer, "fr"));

     if (answer == 'f') {
          goto attack_dragon;
     }

run:
     _cputs(
          "\n"
          "Your heart races as you run out of the cave. But, as you hear the door slam\n"
          "behind you, you suddenly snap out of your state of fear.\n"
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
                         "You hit the creature for %d points of damage.\n", damage);
                    dragon_hit_points-= damage;
               } else {
                    _cputs(
                         "\n"
                         "You missed.\n");
               }
               if (dragon_hit_points > 0 && player_hit_points > 0) {
                    do {
                         _cputs(
                              "\n"
                              "Will you:\n"
                              "[c] continue to fight; or,\n"
                              "[r] run away?"
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
                         "The creature hit you for %d points of damage.\n", damage);
                    player_hit_points-= damage;
               } else {
                    _cputs(
                         "\n"
                         "The creature missed.\n");
               }
               phase = player_turn;
               break;
          }
     }

     if (dragon_hit_points <= 0)	{
          _cputs(
               "\n"
               "Incredibly, you fight and kill the creature with your bare hands! You leave with\n"
               "your head held high. You are a true survivor.\n"
               "\n");
          goto the_end;
     } else if (player_hit_points <= 0) {
          _cputs(
               "\n"
               "As the creature's sharp teeth pierces your body body you suddenly understand. That\n"
               "you aren't good enough and you aren't a survivor.\n"
               "\n");
          goto the_end;
     } else {
          goto run;
     }

survivor:
     _cputs(
          "You've faced the creatured and lived to tell the\n"
          "story. You are a true survivor.\n"
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
