#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "gf3d_mesh.h"
#include "gfc_primitives.h"

Uint8 gfc_prim_ray_collide(GFC_Edge3D edge, MeshPrimitive* prim, GFC_Vector3D* out);

#endif