#include "player_camera.h"
#include "simple_logger.h"
#include "gf3d_mesh.h"
#include "gfc_input.h"
#include "gf3d_camera.h"
#include "gf2d_mouse.h"

Player *tracked_player;
P_Camera *cam;

GFC_Vector3D camera_offset = {0,10,150};
P_Camera *spawn_camera(Player *player)
{
    cam = (P_Camera *)malloc(sizeof(P_Camera));
    tracked_player = player;
    cam->ent = entity_new();
    if (cam)
        slog("cam");
    if (cam->ent)
        slog("ent");

    cam->ent->think = &camera_think;
    cam->ent->update = &camera_update;
    cam->ent->draw = NULL;

    gfc_line_cpy(cam->ent->name, "Stalker Cam");

    //SJson *camera_def = sj_load("config/camera.cfg");
    
    slog_sync();
    slog("I'm spawning a camera");
    
    GFC_Matrix4 id;
    gfc_matrix4_identity(id);
    gfc_matrix4_rotate_z(cam->ent->matrix,id,0);

    gfc_vector3d_copy(cam->ent->position, tracked_player->ent->position);

    cam->ent->position.z += 10;
    cam->ent->position.y += 50;
    cam->sens_x = 0.004;
    cam->sens_y = 0.005;
    
    return cam;

    
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

void camera_think(Entity *ent)
{
    /*slog("camera think");

    */

    //ent->position.z += gfc_random() - 0.5;



    GFC_Vector2D mouse_vel = gf2d_mouse_get_position_from_center();
    //cam->ent->rotation.x += mouse_vel.x * cam->sens_x;
    //cam->ent->rotation.y += mouse_vel.y * cam->sens_y;
    
    //slog("x mouse strength is %f", mouse_vel.x * cam->sens_x * -1);
    GFC_Vector3D old_offset = camera_offset;
    gfc_vector3d_rotate_about_z(&camera_offset,mouse_vel.x * cam->sens_x * -1);
    gfc_vector3d_rotate_about_x(&camera_offset,mouse_vel.y * cam->sens_y * -1);  

    GFC_Vector3D worldUp = gfc_vector3d(0,0,1);
    GFC_Vector3D worldDown = gfc_vector3d(0,0,-1);
    /*GFC_Vector3D worldRight =  gfc_vector3d(1,0,0);
    GFC_Vector3D camera_right;

    GFC_Vector3D camera_forward = gfc_vector3d_subbed(tracked_player->ent->position, camera_offset);
    gfc_vector3d_normalize(&camera_forward);
    gfc_vector3d_cross_product(&camera_right, worldUp, camera_forward);

    slog("Camera right: %f,%f,%f",camera_right.x,camera_right.y,camera_right.z);

    gfc_vector3d_rotate_about_vector(&camera_offset, camera_right, camera_offset, mouse_vel.y * cam->sens_y * -1);

    
    */
    GFC_Vector3D offset_normalized = camera_offset;
    gfc_vector3d_normalize(&offset_normalized);
    
    
    float distToUp = gfc_vector3d_dot_product(offset_normalized, worldUp);
    float distToDown = gfc_vector3d_dot_product(offset_normalized, worldDown);
    //slog("angle to top is %f", gfc_vector3d_dot_product(offset_normalized, worldUp));

    //slog("%f, %f", distToUp, distToDown);
    if (SDL_fabsf( distToUp) > 0.9 || SDL_fabsf(distToDown) < -0.9)
    {
        camera_offset = old_offset;
        return;
    }
    gfc_vector3d_rotate_about_z(&tracked_player->ent->rotation,mouse_vel.x * cam->sens_x * -1);
    gfc_vector3d_rotate_about_x(&tracked_player->ent->rotation,mouse_vel.y * cam->sens_y);

}
void camera_update(Entity *ent)
{
    //slog("camera update");
    GFC_Vector3D playerPos = tracked_player->ent->position;
    GFC_Vector3D newPos = gfc_vector3d_added(playerPos,camera_offset);
    
    //slog("Player at %f,%f,%f Tracking %f,%f,%f", playerPos.x, playerPos.y, playerPos.z, newPos.x, newPos.y, newPos.z);
    gf3d_camera_look_at(playerPos, &newPos);
}


void free_camera(P_Camera *camera)
{
    if (camera->ent)
        entity_free(camera->ent);
    if (camera)
        free(camera);

    slog("Freeing a camera");
}
