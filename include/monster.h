#include "entity.h"

typedef struct Path
{
    GFC_Vector3D* points;
    int curr_idx;
    int count;
}Path;

typedef struct Monster_Stats
{
    float health;
    float attack_speed;
    float last_attack_time;
    float range;
    float damage;

    float last_path_resync_time;

    float speed;
}Monster_Stats;

typedef struct Monster
{
    Entity *ent;
    Path* curr_path;
    Monster_Stats* stats;
}Monster;


Monster *spawn_monster();

Path *monster_navigate_to_player(Monster* tracker);
Path *monster_navigate_to_pos(Monster* tracker, GFC_Vector3D* target);
void monster_kill(Monster* monst);

void monster_think(Entity *ent);

void monster_update(Entity *ent);
void monster_draw(Entity *ent);


