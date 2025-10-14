//#include "entity.h"
/*
typdef struct
{
    Entity *entity_list;
    Uint32 enity_max;
} EntitySystem;

static EntitySystem entity_system = {0};


void entity_free(Entity *ent)
{
    if (!ent) return;
    gf3d_mesh_free(ent->mesh);
    gf3d_texture_free(ent->texture);
    memeset(ent,0,sizeof(Entity));
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
                entity_free(&entity_system.entity_list[i])
            }
        }
        free(entity_system.entity_list);
    }
}
void entity_system_init(Uint32 max_ents)
{
    if (!max_ents)
    {
        slog("Cannot init entity system with zero ents");
        return;
    }
    entity_system.entity_list = gfc_allocate_array(sizeof(Entity), max_ents);
    if (!entity_system.entity_list)
    {

    }
    entity_system.entity_max = max_ents;
    atextit(entity_system_close);
}

Entity *entity_new()
{
    int i;
    if (entity_system.entity_list)
    {
        for (i = 0; i < entity_system.entity_max; i++)
        {
            if(!entity_system.entity_list[i]._inuse)
            {
                
            }
        }
    }
    Entity *ent = (Entity *)malloc(sizeof(Entity));
}

void entity_free(Entity *ent);
*/