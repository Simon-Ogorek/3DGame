#include "entity.h"
#include "simple_logger.h"

typedef struct
{
    Entity *entity_list;
    Uint32 entity_max;
} EntitySystem;

static EntitySystem entity_system = {0};

void entity_free(Entity *ent)
{
    if (!ent) return;
    gf3d_mesh_free(ent->mesh);
    gf3d_texture_free(ent->texture);
    memset(ent,0,sizeof(Entity));
}
void entity_system_close()
{
    int i;
    if (entity_system.entity_list)
    {
        for (i = 0; i < entity_system.entity_max; i++)
        {
            if(entity_system.entity_list[i]._inuse)
            {
                entity_free(&entity_system.entity_list[i]);
            }
        }
        free(entity_system.entity_list);
    }
}
void entity_system_init(Uint32 max_ents)
{

    GFC_Vector3D default_pos =gfc_vector3d(0,0,0);
    GFC_Vector3D default_rot = gfc_vector3d(0,0,0);
    GFC_Vector3D default_scale = gfc_vector3d(1,1,1);
    GFC_Color default_color = GFC_COLOR_WHITE;
    GFC_Matrix4 default_matrix;
    GFC_Vector3D default_lightPos = gfc_vector3d(0,0,0);
    GFC_Color default_lightColor = GFC_COLOR_WHITE;
    
    if (!max_ents)
    {
        slog("Cannot init entity system with zero ents");
        return;
    }
    entity_system.entity_list = (Entity *)gfc_allocate_array(sizeof(Entity), max_ents);
    if (!entity_system.entity_list)
    {
        slog("failed to allocate entity list");
        return;
    }
    

    for (int i = 0; i < max_ents; i++)
    {
        entity_system.entity_list[i].position = default_pos;
        entity_system.entity_list[i].rotation = default_rot;
        entity_system.entity_list[i].scale = default_scale;
        entity_system.entity_list[i].color = default_color;
        entity_system.entity_list[i].lightPos = default_lightPos;
        entity_system.entity_list[i].lightColor = default_lightColor;
        entity_system.entity_list[i]._inuse = 0;
        gfc_matrix4_copy(entity_system.entity_list[i].matrix, default_matrix);
    }


    

    entity_system.entity_max = max_ents;
    atexit(entity_system_close);
}

Entity *entity_new()
{
    Entity *ent;
    //slog("%i", sizeof(Entity));
    int i;
    if (entity_system.entity_list)
    {
        for (i = 0; i < entity_system.entity_max; i++)
        {
            slog("iterated %i, inuse: %i", i , entity_system.entity_list[i]._inuse);
            if(!entity_system.entity_list[i]._inuse)
            {
                entity_system.entity_list[i]._inuse = 1; 
                return &entity_system.entity_list[i];
            }
        }
    }
    slog("entity_new failed!!!");
    return ent;
}

void entity_system_draw_all()
{
    int i;
    if (entity_system.entity_list)
    {
        for (i = 0; i < entity_system.entity_max; i++)
        {
            if(entity_system.entity_list[i]._inuse && entity_system.entity_list[i].draw )
            {
                //slog("drawing %s", entity_system.entity_list[i].name);
                entity_system.entity_list[i].draw(&entity_system.entity_list[i]);
            }
        }
    }
}
void entity_system_think_all()
{
    int i;
    if (entity_system.entity_list)
    {
        for (i = 0; i < entity_system.entity_max; i++)
        {
            if(entity_system.entity_list[i].think )
            {
                entity_system.entity_list[i].think(&entity_system.entity_list[i]);
            }
        }
    }
}

void entity_system_update_all()
{
        int i;
    if (entity_system.entity_list)
    {
        for (i = 0; i < entity_system.entity_max; i++)
        {
            if(entity_system.entity_list[i].update )
            {
                entity_system.entity_list[i].update(&entity_system.entity_list[i]);
            }
        }
    }
}


/* FIX THIS DUMB SHIT
void entity_draw_shadow(Entity *ent)
{
    if ((!ent)||(ent->drawShadow))return;

    GFC_Vector3D drawPosition;
    GFC_Matrix4 modelMat = {0};
    GFC_Color shadowColor = gfc_color8(0,0,0,128);
    GFC_Vector3D shadowLightPos = gfc_vector3d(0,0,0);
    GFC_Color shadowLightColor = gfc_color8(0,0,0,0); 

    gfc_vector3d_copy(drawPosition,ent->position);
    drawPosition.z += 0.1;

    gfc_matrix4_from_vectors(
        modelMat,
        drawPosition,
        ent->rotation,
        ent->scale
    );

    gf3d_mesh_draw(
        ent->mesh,
        modelMat,
        shadowColor,
        ent->texture,
        shadowLightPos,
        shadowLightColor,
    );
}
    */

void entity_draw(Entity *ent)
{
    if (!ent->mesh || !ent->texture)
        slog("entity_draw missing texture or mesh");
    gf3d_mesh_draw(
        ent->mesh,
        ent->matrix,
        ent->color,
        ent->texture,
        ent->lightPos,
        ent->lightColor
    );



    

    
    /*gfc_matrix4_identity(id);
    gfc_matrix4_rotate_z(dinoM,id,0);
    gf3d_mesh_draw(ent->mesh,dinoM,GFC_COLOR_WHITE,ent->texture, lightPos, lightColor);*/
}