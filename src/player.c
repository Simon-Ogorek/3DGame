#include "player.h"
#include "simple_logger.h"
#include "gf3d_mesh.h"
#include "gfc_input.h"
#include "world.h"
#include "physics.h"

#include "gfc_list.h"

#include "gf3d_obj_load.h"

#include "gf2d_mouse.h"

World* curr_world;

Player *spawn_player(World* world)
{
    Player *ag = (Player *)malloc(sizeof(Player));
    curr_world = world;
    slog("%p",curr_world);
    ag->ent = entity_new();
    if (ag)
        slog("ag");
    if (ag->ent)
        slog("ent");

    ag->ent->think = &player_think;
    ag->ent->update = &player_update;
    ag->ent->draw = &player_draw; 

    gfc_line_cpy(ag->ent->name, "Player Maximus");

    SJson *player_def = sj_load("config/agumon.cfg");
    if (!player_def)
        slog("fuck");
    char *player_model = sj_object_get_string(player_def, "mesh");
    slog("retrieved model path of %s", player_model);

    char *player_texture = sj_object_get_string(player_def, "texture");
    slog("retrieved texture path of %s", player_texture);
    slog_sync();
    ag->ent->mesh = gf3d_mesh_load(player_model);
    ag->ent->texture = gf3d_texture_load(player_texture);

    ag->ent->lightPos = gfc_vector3d(0,0,5);
    ag->ent->color = GFC_COLOR_WHITE;
    ag->ent->lightColor = GFC_COLOR_WHITE;
    ag->ent->position.z = 5;
    slog("I'm spawning a player");
    
    GFC_Matrix4 id;
    gfc_matrix4_identity(id);
    gfc_matrix4_rotate_z(ag->ent->matrix,id,0);

    gfc_vector3d_scale(ag->ent->scale, ag->ent->scale,1);
    ag->ent->position.z += 50;
    ag->ent->position.x -= 270;
    return ag;

    
}

/*
gf3d_mesh_draw(
    ent->mesh, fine
    ent->matrix, ?
    ent->color, ?
    ent->texture, fine
    ent->lightPos, ?
    ent->lightColor ?
);
*/

void player_think(Entity *ent)
{
    /*slog("player think");

    */

    //ent->position.z += gfc_random() - 0.5;
    
    float speed = 10;
    GFC_Vector3D predicted_move = ent->position;

    if (gfc_input_key_held("a"))
    {
        //slog("LOOK MA, I'm moving left!!!");
        predicted_move.x += speed;
    }
    if (gfc_input_key_held("d"))
    {
        //slog("LOOK MA, I'm moving left!!!");
        predicted_move.x -= speed;
    }
    if (gfc_input_key_held("w"))
    {
        //slog("LOOK MA, I'm moving left!!!");
        predicted_move.y -= speed;
    }
    if (gfc_input_key_held("s"))
    {
        //slog("LOOK MA, I'm moving left!!!");
        predicted_move.y += speed;
    }

    if (gfc_input_key_held(" "))
    {
        //slog("LOOK MA, I'm moving left!!!");
        predicted_move.z += speed;
    }

    if (gfc_input_key_held("c"))
    {
        //slog("LOOK MA, I'm moving left!!!");
        predicted_move.z -= speed;
    }

    
    GFC_Vector3D groundTestPoint = gfc_vector3d_added(predicted_move, gfc_vector3d(0,0,-100));
    GFC_Edge3D groundTestEdge = gfc_edge3d_from_vectors(predicted_move, groundTestPoint);
    GFC_Vector3D contact;

    MeshPrimitive* world_prim = (MeshPrimitive *)curr_world->walkable->mesh->primitives->elements[0].data;

    if (gf3d_obj_edge_test(world_prim->objData, curr_world->ent->matrix, groundTestEdge, &contact))
    {
        //slog("got a hit %f,%f,%f", contact.x, contact.y, contact.z);
        contact.z += 8;
        ent->position = contact ;
    }
    //slog("%f,%f,%f",ent->position.x,ent->position.y,ent->position.z);

    return;
}
void player_update(Entity *ent)
{
    //slog("player update");

    gfc_matrix4_from_vectors(
        ent->matrix,
        ent->position,
        ent->rotation,
        ent->scale
    );
}

void player_draw(Entity *ent)
{
    //slog("player draw");
    entity_draw(ent);
}

void free_player(Player *ag)
{
    if (ag->ent)
        entity_free(ag->ent);
    if (ag)
        free(ag);

    slog("Freeing a player");
}
