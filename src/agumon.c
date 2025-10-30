#include "agumon.h"
#include "simple_logger.h"
#include "gf3d_mesh.h"

Agumon *spawn_agumon()
{
    Agumon *ag = (Agumon *)malloc(sizeof(Agumon));
    ag->ent = entity_new();
    if (ag)
        slog("ag");
    if (ag->ent)
        slog("ent");

    ag->ent->think = &agumon_think;
    ag->ent->update = &agumon_update;
    ag->ent->draw = &agumon_draw; 

    gfc_line_cpy(ag->ent->name, "John Agumon");

    SJson *agumon_def = sj_load("config/agumon.cfg");
    if (!agumon_def)
        slog("fuck");
    char *agumon_model = sj_object_get_string(agumon_def, "mesh");
    slog("retrieved model path of %s", agumon_model);

    char *agumon_texture = sj_object_get_string(agumon_def, "texture");
    slog("retrieved texture path of %s", agumon_texture);
    slog_sync();
    ag->ent->mesh = gf3d_mesh_load(agumon_model);
    ag->ent->texture = gf3d_texture_load(agumon_texture);

    ag->ent->lightPos = gfc_vector3d(0,0,5);
    ag->ent->color = GFC_COLOR_WHITE;
    ag->ent->lightColor = GFC_COLOR_WHITE;

    slog("I'm spawning a agumon");
    
    GFC_Matrix4 id;
    gfc_matrix4_identity(id);
    gfc_matrix4_rotate_z(ag->ent->matrix,id,0);
    return ag;

    
}

void dance(Entity *ent)
{
    slog("dance");
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

void agumon_think(Entity *ent)
{
    /*slog("agumon think");

    */

    ent->position.z += gfc_random() - 0.5;
}

void agumon_update(Entity *ent)
{
    //slog("agumon update");

    gfc_matrix4_from_vectors(
        ent->matrix,
        ent->position,
        ent->rotation,
        ent->scale
    );
}

void agumon_draw(Entity *ent)
{
    //slog("agumon draw");
    entity_draw(ent);
}

void free_agumon(Agumon *ag)
{
    if (ag->ent)
        entity_free(ag->ent);
    if (ag)
        free(ag);

    slog("Freeing a Agumon");
}
