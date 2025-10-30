/*#include "gf3d_mesh.h"

Mesh *gf3d_mesh_new()
{
    int i;
    for (i = 0; i < mesh_manager.mesh_count; i++)
    {

    }
}

Mesh *gf3d_mesh_get_by_filename(const char * filename)
{
    int i;
    if (!filename)
    {
        return NULL;
    }
    for (i = 0; i < mesh_manager.mesh_count; i++)
    {
        if (gfc_line_cmp(mesh_manager.meshList[i].filename, filename) == 0)
        {
            return &mesh_manager.meshList[i];
        }
    }
    return NULL;
}

Mesh *gf3d_mesh_load(const char *filename)
{
    MeshPrimitive *primitive;
    Mesh *mesh;
    ObjData *obj;
    if (!filename)return NULL;
    mesh = gf3d_mesh_get_by_filename(filename);
    if (mesh)
    {
        mesh->_refCount++;
        return mesh;
    }
    obj = gf3d_obj_loaf_from_file(filename);
    
    if (!obj)
    {
        return NULL;
    }

    mesh = gf3d_mesh_new();
    if (!mesh)

}*/