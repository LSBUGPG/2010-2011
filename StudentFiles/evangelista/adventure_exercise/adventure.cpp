#include <conio.h>

int main(int argc, char *argv[])
{
     int answer;
     bool have_rope;
     bool grate_locked;

start_game:
     have_rope = false;
     grate_locked = true;

     _cputs(
                    "\n"
          "Hello and welcome!\n"
          "You are to leave this world and survive!"
          "\n"
          "Good luck the lost one!\n"
          "\n");

describe_desert:
     _cputs(
          "You wake up and you find yourself in a desert.\n"
          "Looking around you see tumblweeds and dead plants.\n"
          "You see a hill in a distance.\n"
          "\n"
          "Will you:\n"
          "[w] walk towards the hill; or,\n"
          "[i] ignore it and keep walking?\n"
          "\n>");

     answer = _getche();
     if (answer == 'w') {
          goto reach_hill;
     } else if (answer == 'i') {
          goto walk_aimlessly;
     } else {
          goto unknown_desert;
     }

reach_hill:
     _cputs(
          "\n"
          "You reached the top of the hill.\n"
          "\n");
     goto describe_surroundings;

walk_aimlessly:
     _cputs(
          "\n"
          "As you wander around the desert aimlessly.\n"
          "\n");
     goto describe_nearby;

unknown_desert:
     _cputs(
          "\n"
          "Say what?\n"
          "\n");
     goto describe_desert;

describe_surroundings:
     _cputs(
          " You see a train in a distance.\n"
          "\n");

     if (have_rope) {
          _cputs(
			  "There's a rope on the ground, will you:\n"
               "[l] leave it on the ground; or,\n"
               "[t] take the rope?\n"
               "\n>");

          answer = _getche();
          if (answer == 't') {
               goto leave_hill;
          } else if (answer == 'l') {
               goto return_rope;
          } else {
               goto unknown_hill;
          }
     } else {
          _cputs(
               "There is a rope on the ground, will you:\n"
               "[t] take the rope; or,\n"
               "[w] walk down the hill?\n"
               "\n>");

          answer = _getche();
          if (answer == 'w') {
               goto leave_hill;
          } else if (answer == 't') {
               goto take_rope;
          } else {
               goto unknown_hill;
          }
     }

leave_hill:
     _cputs(
          "\n"
          "You walked down the hill.\n"
          "\n");
     goto describe_desert;

return_rope:
     _cputs(
          "\n"
          "You decided to leave the rope on the ground and walked down the hill.\n"
          "\n");
     have_rope = false;
     goto describe_surroundings;

unknown_hill:
     _cputs(
          "\n"
          "Huh?\n"
          "\n");
     goto describe_surroundings;

take_rope:
     _cputs(
          "\n"
          "You took the rope and looked around.\n"
          "\n");
     have_rope = true;
     goto describe_nearby;

describe_nearby:
     _cputs(
          "There's a wild horse nearby. \n"
          "\n");

     if (grate_locked && have_rope) {
          _cputs(
			  "The horse looks thirsty. You have a container with water, will you:\n"
               "[g] give water to the horse; or,\n"
               "[w] walk away from it?\n"
               "\n>");

          answer = _getche();
          if (answer == 'w') {
               goto return_to_desert;
          } else if (answer == 'g') {
               goto lead_rope;
          } else {
               goto unknown_nearby;
          }

     } else if (grate_locked) {
          goto return_for_rope;
     } else if (have_rope) {
          _cputs(
               "The wild horse became friendly. Will you:\n"
               "[k] kick the horse;\n"
               "[m] mount the horse; or,\n"
               "[l] leave it alone?\n"
               "\n>");

          answer = _getche();
          if (answer == 'l') {
               goto return_to_desert;
          } else if (answer == 'm') {
               goto mount_horse;
          } else if (answer == 'k') {
               goto kick_horse;
          } else {
               goto unknown_nearby;
          }

     } else {
          _cputs(
               "You placed the rope on the horse as a lead rope. Will you:\n"
               "[m] mount it; or,\n"
               "[l] leave it alone?\n"
               "\n>");

          answer = _getche();
          if (answer == 'l') {
               goto return_to_desert;
          } else if (answer == 'm') {
               goto mount_horse;
          } else {
               goto unknown_nearby;
          }
     }

return_to_desert:
     _cputs(
          "\n"
          "You walked away from the horse.\n"
          "\n");
     goto describe_desert;

lead_rope:
     _cputs(
          "\n"
          "You placed the rope on the horse to lead it.\n"
          "\n");
     grate_locked = false;
     goto describe_nearby;

kick_horse:
     _cputs(
          "\n"
          "As you kicked the horse it ran and you became\n"
		  "thirsty and collapsed.\n"
          "\n");
     grate_locked = true;
     goto waste_man;

unknown_nearby:
     _cputs(
          "\n"
          "What are you saying?\n"
          "\n");
     goto describe_nearby;

return_for_rope:
     _cputs(
          "The horse is wild. You will need a lead rope. You looked around for one.\n"
          "\n");
     goto describe_desert;

mount_horse:
     _cputs(
          "\n"
          "You mounted the horse and chased after the train.\n"
          "\n");
     goto describe_train;

describe_train:
     _cputs(
          "You are near the back of the train.\n"
          "The horse is getting tired and slowing down.\n"
          "\n"
          "Will you:\n"
          "[s] stand on your horse and jump; or,\n"
          "[t] take off the lead rope from the horse and use it as a lasso?\n"
          "\n>");

     answer = _getche();
     if (answer == 's') {
          goto last_chance;
     } else if (answer == 't') {
          goto run;
     } else {
          goto unknown_train;
     }

last_chance:
     _cputs(
          "\n"
          "The distance between you and the train is pretty far! Are you sure? Will you:\n"
          "[s] still jump; or,\n"
          "[g] give up and wait for the next train?\n"
          "\n>");

     answer = _getche();
     if (answer == 's') {
          goto jump_train;
     } else if (answer == 'g') {
          goto run;
     } else {
          goto unknown_train;
     }

run:
     _cputs(
          "You failed to catch the train.\n"
          "You waited for the next train but it took 3 days for the next one to arrive.\n"
          "\n");
     goto hungry;

unknown_train:
     _cputs(
          "\n"
          "I did not understand that answer.\n"
          "\n");
     goto describe_train;

jump_train:
     _cputs(
          "\n"
          "Amazingly, you managed to jump the big distance between you and the train."
          "\n");
     goto the_end;

hungry:
     _cputs(
          "You are able to get on the train but you are feeling weak caused by hunger"
		  "You enter the train and collapses"
          "\n");
     goto the_end;

waste_man:
     _cputs(
          "Your adventure is at an end. You realise your too weak and pathetic.\n"
          "\n");

the_end:
     _cputs(
          "The end.\n");

restart_or_quit:
     _cputs(
          "\n"
          "[r] Restart this game.\n"
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
