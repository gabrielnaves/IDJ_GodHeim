/*
 * Camera.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Camera.h"

GameObject* Camera::focus = NULL;
Point Camera::pos;
float Camera::speed = 450;

void Camera::Follow(GameObject* newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = NULL;
}

void Camera::Update(float dt)
{
    if (focus)
    {
        pos.SetPoint(focus->box.GetCenter());
        pos.MovePoint(-512, -300);
    }
    else
    {
        InputManager &im = InputManager::GetInstance();
        float hm = 0, vm = 0;

        if (im.IsKeyDown(RIGHT_ARROW_KEY) || im.KeyPress(RIGHT_ARROW_KEY))
            hm = hm + 1;
        if (im.IsKeyDown(LEFT_ARROW_KEY) || im.KeyPress(LEFT_ARROW_KEY))
            hm = hm - 1;
        if (im.IsKeyDown(DOWN_ARROW_KEY) || im.KeyPress(DOWN_ARROW_KEY))
            vm = vm + 1;
        if (im.IsKeyDown(UP_ARROW_KEY) || im.KeyPress(UP_ARROW_KEY))
            vm = vm - 1;

        pos.MovePoint(hm * (hm != 0 && vm != 0 ? speed * cos(M_PI/4) : speed) * dt,
                      vm * (hm != 0 && vm != 0 ? speed * cos(M_PI/4) : speed) * dt);
    }
}
