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
		"Welcome back gangsta. This is The Streets! It's been a while since you've been around, I'll give you the low down on the situation, and you\n"
		"gotta choose what to do."
		"\n"
		"Good luck homeboy!\n" 
		"If you think you're ready hit the P button and LETS GO!\n"
		"\n");  
	answer = _getche(); 
	if (answer == 'p') {
		goto describe_streets;
	}

	describe_streets:
	_cputs(
		"You are back on the streets after being framed for a crime you didnt commit. Things have\n"
		"become unexpectedly quiet. You realize that things have changed. You look\n"
		"to your left and see a poster on the wall.\n"
		"\n"
		"Will you:\n"
		"[l] look at the poster; or,\n"
		"[w] walk up the road?\n"
		"\n>"); 

	answer = _getche();
	if (answer == 'l') {
		goto look_poster;
	} else if (answer == 'w') {
		goto walk_road;
	} else {
		goto unknown_answer;
	}

	unknown_answer: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n"); 
	goto describe_streets;


	look_poster:
    _cputs(
        "\n"
        "You look at the poster and find out that there is a party going on tonight.\n"
        "The party is for a new club opening and you may be able to find some answers there.\n"
		"\n"
		"Will you:\n" 
		"[g] go to the party; or,\n" 
		"[i] ignore it and continue walking up the road?\n"
		"\n");	   

	answer = _getche();
	if (answer == 'g') {
		goto club_party;
	} else if (answer == 'i') {
		goto walk_road;
	} else {
		goto unknown_poster;
	}   

	unknown_poster: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n"); 
	goto look_poster;

	club_party: 
	_cputs( 
		"\n"
        "You head for the club where the party is happening and find out that an old business man is running it.\n"
        "It looks like it's invitation only and you wont be able to just walk in.\n"
		"\n"
		"Will you:\n" 
		"[f] force your way in; or,\n" 
		"[s] see if there's another entrance?\n"
		"\n");	    
	 answer = _getche();
	if (answer == 'f') {
		goto failed_entry;
	} else if (answer == 's') {
		goto second_entrance;
	} else {
		goto unknown_club;
	}  

	 unknown_club: 
	 _cputs( 
		"\n"
		"Stop acting stupid player! And answer me properly.\n"
		"\n");
	goto club_party; 

	walk_road:
	_cputs( 
		"\n" 
		"You continue walking until you suddenly stop outside your old house.\n" 
		"The place looks empty and no one seems to be around.\n" 
		"\n" 
		"Will you:\n" 
		"[t] try to go inside the house; or,\n"  
		"[k] Knock on the door and see if someone answers?\n" 
		"\n"); 
	answer = _getche();
	if (answer == 't') {
		goto enter_house;
	} else if (answer == 'k') {
		goto knock_door;
	} else {
		goto unknown_road; 
	}    

	unknown_road: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n"); 
	goto describe_streets;

	second_entrance: 
	_cputs( 
		"\n" 
		"You realise that forcing your way through is not such a great option.\n" 
		"You look round the side of the building and find a backdoor.\n" 
		"\n"
		"Will you:\n" 
		"[u] use the backdoor to gain entry; or,\n"  
		"[e] forget the whole thing and walk away?\n"
		"\n"); 
	answer = _getche();
	if (answer == 'u') {
		goto back_club;
	} else if (answer == 'e') {
		goto new_day;
	} else {
		goto unknown_entrance; 
	}    

	unknown_entrance: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto second_entrance;

	back_club: 
	_cputs(
		"\n" 
		"You manage to sneak in through the back door without anyone noticing.\n" 
		"You're walking through the corridor but suddlenly two guards spot you.\n" 
		"You notice the dance area is close and you may be able to lose them in the crowd." 
		"\n" 
		"Will you:\n" 
		"[m] Make a run for the dance floor; or,\n" 
		"[l] look for another way out?\n"
		"\n"); 
	answer = _getche();
	if (answer == 'm') {
		goto dance_floor;
	} else if (answer == 'l') {
		goto new_way;
	} else {
		goto unknown_backclub; 
	}    

	unknown_backclub: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto back_club; 

	dance_floor: 
	_cputs( 
		"\n" 
		"You decide to try lose them in the dance floor and as you mix in with\n" 
		"the crowd, the guards pass you by and you seem to be safe for the time\n" 
		"being. You notice two double doors at the other end and a door on the right\n" 
		"as well." 
		"Will you:\n" 
		"[g] Go towards the double doors; or,\n"
		"[d] Go towards the door on the right?\n"
		"\n"); 
	 answer = _getche();
	if (answer == 'g') {
		goto double_doors;
	} else if (answer == 'd') {
		goto safe_life;
	} else {
		goto unknown_dancefloor; 
	}    

	unknown_dancefloor: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto dance_floor; 

	 new_way: 
	 _cputs( 
		 "\n" 
		 "You back up slowly as the guards approach, eventually you back up so\n" 
		 "much that you fall through the door to the store room and a lot of junk\n" 
		 "falls over and traps you. The guards pull you out and throw you out of\n" 
		 "of the club. Looks like you won't be able to get back in."
		 "\n" 
		 "GAME OVER!" 
		 "\n"
		 "Do you:\n" 
		 "[r] wish to restart the game; or,\n"  
		 "[q] quit\n" 
		 "\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_newway;
	} 
	
	unknown_newway: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto new_way;  

	safe_life: 
	_cputs( 
		"\n" 
		"You make a door for the right and it leads you out! You ran in to the\n" 
		"Lions den and made it out alive, no shame in saving your neck." 
		"\n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_safelife;
	} 

	unknown_safelife: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto safe_life;   

	double_doors: 
	_cputs( 
		"\n" 
		"You decide to make use of the double doors and hide behind them.\n" 
		"The guards pass you by and you've ended up in a long corridor.\n" 
		"You can hear a voice in the distance and you peek round the corner\n" 
		"to see that it's one of the guards from earlier." 
		"\n" 
		"Will you:\n" 
		"[s] suprise attack the guard; or,\n" 
		"[l] let him pass by?\n"
		"\n"); 
	answer = _getche();
	if (answer == 's') {
		goto suprise_attack;
	} else if (answer == 'l') {
		goto pass_by;
	} else {
		goto unknown_doubledoors;
	} 

	unknown_doubledoors: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto double_doors;    

	suprise_attack: 
	_cputs( 
		"\n" 
		"You decide to attack the guard and the ambush was a SUCCESS!\n" 
		"You search the guard and take gun in which you may need later.\n" 
		"You continue to head down the corridor and arrive at a huge door." 
		"\n" 
		"Will you:\n" 
		"[t] go through the door; or,\n" 
		"[b] turn back?\n" 
		"\n"); 
	answer = _getche();
	if (answer == 't') {
		goto through_door;
	} else if (answer == 'b') {
		goto new_day;
	} else {
		goto unknown_supriseattack;
	}  

	unknown_supriseattack: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto suprise_attack;    

	through_door: 
	_cputs( 
		"\n"
		"You slowly enter through the door and as you do, a gun is put in\n" 
		"front of your face. The man who is doing this is the owner of the\n" 
		"club and he seems to know you. He wishes for you to listen to his\n" 
		"story."
		"\n" 
		"Will you:\n" 
		"[l] listen to his story; or,\n" 
		"[t] try get your gun out and shoot him?\n" 
		"\n"); 
	answer = _getche();
	if (answer == 'l') {
		goto listen_story;
	} else if (answer == 't') {
		goto one_chance;
	} else {
		goto unknown_throughdoor;
	}  

	unknown_throughdoor: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto through_door;  

	listen_story: 
	_cputs( 
		"\n" 
		"The man explains how he framed you for murder after you wrecked his business\n" 
		"all those years ago. He was finally able to bring things back together\n" 
		"with the opening of the new club. He sent over someone to your old place\n" 
		"and guessed that the messenger must have lead you here." 
		"\n" 
		"Will you:\n" 
		"[f] forgive and forget all about it; or,\n" 
		"[s] shoot him where he stands?\n"  
		"\n");
		answer = _getche();
	if (answer == 'f') {
		goto settlement;
	} else if (answer == 's') {
		goto end_road;
	} else {
		goto unknown_listenstory;
	}  

	unknown_listenstory: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto listen_story; 

	settlement: 
	_cputs( 
		"\n" 
		"You both realise that living a life full of hate and regret has done\n" 
		"nothing but hurt both sides. You've come to understand each other's\n" 
		"situations and shake hands." 
		"\n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_settlement;
	} 

	unknown_settlement: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto settlement;

	end_road: 
	_cputs( 
		"\n" 
		"Sudden sirens are heard in the distance and the club owner turns his head\n" 
		"for a moment to take a look. You use this small window to pull the trigger\n" 
		"The owner gasps in pain before collapsing on the ground and passing away.\n" 
		"The sound of the sirens are getting louder as you walk up to the dead body to\n" 
		"have one last look. You're eye catches on to a photo on his desk and you move\n" 
		"in closer to have a better look but in that moment a huge shock hits you.\n" 
		"\n" 
		"The people in the picture were the club owner but also someone who looked\n" 
		"exactly like him, practically a twin! You being to wonder if you even had the\n" 
		"right man in the 1st place. There was no time to contemplate the matter as you\n" 
		"escape the club before the sirens got any closer." 
		"\n" 
		"Looks like there was more to your framing then just that club owner. Who is the\n" 
		"other man in the picture and could he have been part of it as well? Well...that's\n" 
		"something for next time." 
		"\n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_endroad;
	} 

	unknown_endroad: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto end_road;

	one_chance: 
    _cputs( 
		"\n" 
		"You attempt to outdo the man by shooting him 1st however, he was thinking\n" 
		"exactly the same thing. You both take critical damage and hit the floor.\n" 
		"Complete silence befalls the room but your are both still conscious.\n" 
		"You may be able to finish the job but you're losing a lot of blood." 
		"\n" 
		"Will you:\n" 
		"[e] endure the pain and finish him off; or,\n" 
		"[i] Stay still and stop the bleeding?\n" 
		"\n"); 
	answer = _getche();
	if (answer == 'e') {
		goto noman_alive;
	} else if (answer == 'i') {
		goto next_time;
	} else {
		goto unknown_onechance;
	}  

	unknown_onechance: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto one_chance;  

	noman_alive: 
	_cputs( 
		"\n" 
		"The embarrassment of those years in prison, silence the pain.\n" 
		"With your last remaining energy, you pick up the gun and take him\n" 
		"out. A huge weight seems to have been lifted off your shoulders, you\n" 
		"finally feel like a free man as you collapse on the ground." 
		"\n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_nomanalive;
	} 

	unknown_nomanalive: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto noman_alive;   

	next_time: 
 	 _cputs( 
		 "\n" 
		 "You decide to hold back and try to keep yourself alive. You can hear\n" 
		 "emergency sirens in the distance as you slowly fade away. You wake up\n" 
		 "a few days later in hospital and in shock that you're still alive.\n" 
		 "You were given a second chance at life however your mind can only think\n" 
		 "of next time." 
		 "\n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_nexttime;
	} 

	unknown_nexttime: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto next_time;   

	pass_by: 
	_cputs( 
		"\n" 
		"You decide to let the guard pass by but you want to follow him.\n" 
		"While following him another guard passing by see's you and shoots\n" 
		"you on the spot." 
		"\n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_passby;
	} 

	unknown_passby: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto pass_by;   
                      
	enter_house: 
	_cputs( 
		"\n" 
		"You enter the house to find it still abdandoned after all this time\n" 
		"suddenly someone runs out from around the corner and jumps out of the window.\n" 
		"\n" 
		"Will you:\n" 
		"[c] chase after the mysterious person; or,\n" 
		"[z] let them go?\n" 
		"\n"); 
	answer = _getche();
	if (answer == 'c') {
		goto chase_scene;
	} else if (answer == 'z') {
		goto new_day;
	} else {
		goto unknown_enterhouse; 
	}    

	unknown_enterhouse: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto enter_house;   

	knock_door: 
	_cputs( 
		"\n" 
		"You knock on the door to try and confirm if anyone is inside but then\n" 
		"suddenly you are surrounded from behind by a group of masked street thugs./n" 
		"The sound of gunshots are heard from the distance as it fades into the night.\n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_knockdoor;
	} 

	unknown_knockdoor: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto knock_door; 

	new_day: 
	_cputs( 
		"\n"
		"You found that chasing after past ghosts will do you no good\n" 
		"and you look forward to a new day./n" 
		"GAME OVER!" 
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_newday;
	} 

	unknown_newday: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto new_day; 

	chase_scene:
	_cputs( 
		"\n" 
		"You decided to pursue the mysterious person out of the window\n" 
		"and the chase takes you down the street. The mysterious person is getting\n"
		"further and further away." 
		"\n"
		"Will you:\n" 
		"[c] continue the chase; or,\n" 
		"[g] give up?\n" 
		"\n"); 
	answer = _getche();
	if (answer == 'c') {
		goto struck_ground;
	} else if (answer == 'g') {
		goto new_path;
	} else {
		goto unknown_chasescene;
	}  

	unknown_chasescene: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto enter_house; 

	struck_ground: 
	_cputs( 
		"\n" 
		"You chase the person round the corner but suddenly you're struck and you hit the ground.\n" 
		"A few minutes later you regain consciousness and as you try to get up a note falls from the\n"
		"inside of your jacket."
		"\n"
		"Will you:\n" 
		"[r] read the note; or,\n" 
		"[c] call it a day?\n" 
		"\n");
	answer =_getche();  
	if (answer == 'r') {
		goto read_note;
	} else if (answer == 'c') {
		goto new_day;
	} else {
		goto unknown_struckground;
	}  
	unknown_struckground: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto struck_ground; 

	new_path: 
	_cputs( 
		"\n" 
		"You try to chase the mysterious person down but they are too fast for you. You slow down\n" 
		"in the middle of the road trying to catch your breath once again. In the midst of this, you\n" 
		"turn your head and notice the same poster from earlier. The poster talks about the party." 
		"\n" 
		"Will you:\n" 
		"[h] head for the club; or,\n" 
		"[d] go back home\n" 
		"\n");
	if (answer == 'h') {
		goto club_party;
	} else if (answer == 'd') {
		goto new_day;
	} else {
		goto unknown_newpath;
	}  

	unknown_newpath: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto new_path; 

	read_note: 
	_cputs( 
		"\n" 
		"The note says: If you want to find out the truth, if you want to know who betayed you,\n" 
		"head for the club or forever be wasted.Looks like the mysterious person could be someone \n" 
		"you know and there may be answers at the club." 
		"\n" 
		"Will you:\n" 
		"[h] head for the club; or,\n" 
		"[g] give up the chase?\n"
		"\n"); 
	answer = _getche();
	if (answer == 'h') {
		goto club_party;
	} else if (answer == 'g') {
		goto new_day;
	} else {
		goto unknown_readnote;
	}  

	unknown_readnote: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto read_note; 

	failed_entry: 
	_cputs( 
		"\n"
		"You try to force your way past the guards, however they were just too strong.\n"
		"The police were called and you were taken away."
		"GAME OVER!"	
		"\n"
		"Do you:\n" 
		"[r] wish to restart the game; or,\n"  
		"[q] quit\n" 
		"\n");   
	answer = _getche();
	if (answer == 'r') {
		goto start_game;
	} else if (answer == 'q') {
		goto quit;
	} else {
		goto unknown_failedentry;
	}
	
	unknown_failedentry: 
	_cputs( 
		"\n" 
		"Stop acting stupid player! And answer me properly.\n" 
		"\n");  
	goto failed_entry; 

quit:
	return 0; 

}