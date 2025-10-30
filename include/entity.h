#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_text.h"
#include "gf3d_mesh.h"
#include "gf3d_texture.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gfc_primitives.h"

typedef struct Entity_S Entity;

struct Entity_S
{
    Uint8        _inuse;
    GFC_TextLine name;
    Mesh          *mesh;
    Texture       *texture;
    GFC_Color     color;
    GFC_Vector3D  lightPos;
    GFC_Color     lightColor;
    GFC_Matrix4   matrix;
    GFC_Vector3D  position;
    GFC_Vector3D  rotation;
    GFC_Vector3D  scale;
    GFC_Box   bounds;
    void      (*draw)(struct Entity_S *self);
    void      (*think)(struct Entity_S *self);
    void      (*update)(struct Entity_S *self);
    Uint8     drawShadow;
};

Entity *entity_new();

void entity_free(Entity *ent);

void entity_system_init(Uint32 max_ents);

void entity_system_draw_all();
void entity_system_think_all();
void entity_system_update_all();

void entity_draw(Entity *ent);

#endif
