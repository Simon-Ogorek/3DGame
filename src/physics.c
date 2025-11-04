#include "physics.h"
#include "gf3d_obj_load.h"
#include "gfc_primitives.h"
#include "simple_logger.h"
#define MAX_CHUNK 100

typedef struct Primitive_Cache
{
    MeshPrimitive owner;
    GFC_Vector3D* avg_pos;
    Face *faces;
    int faces_per_chunk;
    Uint8 inuse;
}Primitive_Cache;

typedef struct Physics_Cache_Manger
{
    Primitive_Cache* data;
    int count;
}Physics_Cache_Manger;

Physics_Cache_Manger cache;

Uint8 gfc_prim_ray_collide(GFC_Edge3D edge, MeshPrimitive* prim, GFC_Vector3D* out)
{
    slog("%i", prim->objData->face_vert_count);
    GFC_Triangle3D tri;
    Vertex* verts = prim->objData->faceVertices;
    for (int i = 0; i < 10404; i += 3)
    {   
        tri = gfc_triangle(verts[i].vertex, verts[i+ 1].vertex, verts[i + 2].vertex);
        slog("checking tri: (%f,%f,%f), (%f,%f,%f), (%f,%f,%f)", tri.a.x,tri.a.y,tri.a.z, tri.b.x,tri.b.y,tri.b.z, tri.c.x,tri.c.y,tri.c.z);
        //tri = gfc_triangle(vert[0],)
        //slog("testing a tri");
        if (gfc_trigfc_angle_edge_test(edge,tri,out))
        {
            slog("t");
            return 1;
        }
    }
    return 0;
}
/*
void gfc_phyics_init(int prims)
{
    cache.data = (Primitive_Cache *)malloc(sizeof(Primitive_Cache) * prims);
    cache.count = prims;


}

void gfc_add_prim_to_cache(MeshPrimitive* prim)
{
    for (int i = 0; i < cache.count; i++)
    {
        if (!cache.data->inuse)
        {

            prim->objData->face_count

            cache.data->inuse = 1;
        }
    }
}
    */