enum battle_result {
     player_wins,
     monster_wins,
     player_runs
};

struct creature {
     const char* name;
     int initiative;
     int hit_bonus;
     int damage_bonus;
     int defence;
     int hit_points;
};

bool wrong_answer(int have, const char* looking_for);
battle_result do_battle(creature& player, creature& monster);
