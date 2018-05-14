#include "engine.h"

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

battle_result do_battle(creature& player, creature& monster)
{
     battle_result result;
     bool player_is_attacking = true;
     enum {
          choose_initiative,
          player_turn,
          monster_turn
     } phase = choose_initiative;

     while (player_is_attacking && monster.hit_points > 0 && player.hit_points > 0) {
          int damage;
          switch (phase) {
          case choose_initiative:
               if (roll(20) + player.initiative >= roll(20) + monster.initiative) {
                    phase = player_turn;
               } else {
                    phase = monster_turn;
               }
               break;
          case player_turn:
               if (roll(20) + player.hit_bonus >= monster.defence) {
                    damage = roll(8) + player.damage_bonus;
                    _cprintf(
                         "\n"
                         "You hit the %s for %d points of damage.\n", monster.name, damage);
                    monster.hit_points-= damage;
               } else {
                    _cputs(
                         "\n"
                         "You missed.\n");
               }
               if (monster.hit_points > 0 && player.hit_points > 0) {
                    int answer;
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
               phase = monster_turn;
               break;
          case monster_turn:
               if (roll(20) + monster.hit_bonus >= player.defence) {
                    damage = roll(8) + monster.damage_bonus;
                    _cprintf(
                         "\n"
                         "The %s hit you for %d points of damage.\n", monster.name, damage);
                    player.hit_points-= damage;
               } else {
                    _cprintf(
                         "\n"
                         "The %s missed.\n", monster.name);
               }
               phase = player_turn;
               break;
          }
     }

     if (monster.hit_points <= 0)	{
          result = player_wins;
     } else if (player.hit_points <= 0) {
          result = monster_wins;
     } else {
          result = player_runs;
     }

     return result;
}
