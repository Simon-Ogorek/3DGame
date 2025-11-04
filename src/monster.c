#include "simple_logger.h"

#include "monster.h"
#include "entity.h"
#include "player.h"

static Player* target_player;

void monsters_init(Player* player)
{
    target_player = player;
}

GFC_Vector3D gfc_vector3d_interpolate(GFC_Vector3D a, GFC_Vector3D b, float t)
{
  GFC_Vector3D res, diff;
  gfc_vector3d_sub(diff,b,a);
  gfc_vector3d_scale(diff,diff,t);
  gfc_vector3d_add(res,a,diff);
  return res;
}


Monster *spawn_monster()
{
    Monster* monst = (Monster *)malloc(sizeof(Monster));

    monst->ent = entity_new(); 

    monst->ent->think = &monster_think;
    monst->ent->update = &monster_update;
    monst->ent->draw = &monster_draw; 
    monst->stats = (Monster_Stats *)malloc(sizeof(Monster_Stats));
    monst->stats->speed = 5;

    monst->ent->calling_parent = (void *)monst;

    gfc_line_cpy(monst->ent->name, "Defaultous Monstorous");

    SJson *monst_def = sj_load("config/agumon.cfg");
    if (!monst_def)
        slog("fuck");
    char *monst_model = sj_object_get_string(monst_def, "mesh");
    slog("retrieved model path of %s", monst_model);

    char *monst_texture = sj_object_get_string(monst_def, "texture");
    slog("retrieved texture path of %s", monst_texture);
    slog_sync();
    monst->ent->mesh = gf3d_mesh_load(monst_model);
    monst->ent->texture = gf3d_texture_load(monst_texture);

    monst->ent->lightPos = gfc_vector3d(0,0,5);
    monst->ent->color = GFC_COLOR_WHITE;
    monst->ent->lightColor = GFC_COLOR_WHITE;
    monst->ent->position.z = 5;
    slog("I'm spawning a monster");
    
    GFC_Matrix4 id;
    gfc_matrix4_identity(id);
    gfc_matrix4_rotate_z(monst->ent->matrix,id,0);

    gfc_vector3d_scale(monst->ent->scale, monst->ent->scale,1);
    monst->ent->position.x = -1000;
    monst->ent->position.y = -1000;
    monst->ent->position.z = 8;
    monst->curr_path = (Path *)malloc(sizeof(Path));
    monst->curr_path->count = 2;
    monst->curr_path->curr_idx = 0;

    monst->curr_path->points = (GFC_Vector3D*)malloc(sizeof(GFC_Vector3D) *2);
    monst->curr_path->points[0].x = -1000;
    monst->curr_path->points[0].y = -1000;
    monst->curr_path->points[0].z = 8;

    monst->curr_path->points[1].x = 1000;
    monst->curr_path->points[1].y = 1000;
    monst->curr_path->points[1].z = 8;

    monst->ent->scale.z = 30;

    return monst;
}

Path *monster_navigate_to_player(Monster* tracker)
{
    return;
}

Path *monster_navigate_to_pos(Monster* tracker, GFC_Vector3D* target)
{
    return;
}

void monster_think(Entity *ent)
{
    Monster* monst = (Monster*)ent->calling_parent;

    if (!monst->curr_path)
    {
        monster_navigate_to_player(monst);
        return;
    }
    float distLeft = monst->stats->speed;
    // follow the path;
    if (monst->curr_path->curr_idx < monst->curr_path->count)
    {
        while (distLeft > 0)
        {
            GFC_Vector3D nextPoint = *(monst->curr_path->points + monst->curr_path->curr_idx);

            float length = gfc_vector3d_magnitude_between(ent->position, nextPoint);

            if (length < distLeft)
            {
                distLeft -= length;
                ent->position = nextPoint;
                monst->curr_path->curr_idx++;
                slog("ran 1");
            }
            else
            {
                ent->position = gfc_vector3d_interpolate(ent->position, nextPoint, distLeft/length);
                distLeft = 0;
                //monst->curr_path->curr_idx++;
                slog("ran 2");
            }
            slog("enemy pos is %f,%f,%f", monst->ent->position.x,monst->ent->position.y,monst->ent->position.z);

        }
        
    }
    
}
void monster_update(Entity *ent)
{
    gfc_matrix4_from_vectors(
        ent->matrix,
        ent->position,
        ent->rotation,
        ent->scale
    );
}
void monster_draw(Entity *ent)
{
    entity_draw(ent);
}


