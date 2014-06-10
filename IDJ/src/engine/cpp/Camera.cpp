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
float Camera::upperLimit = 0;
float Camera::lowerLimit = 0;
float Camera::leftLimit = 0;
float Camera::rightLimit = 0;
bool Camera::isLimited = false;

/**
 * Follows a new object. An object that is being followed will
 * always be centered on the screen.
 */
void Camera::Follow(GameObject* newFocus, bool isLimited, float left, float upper, float right, float lower)
{
    focus = newFocus;
    Camera::isLimited = isLimited;
    if (isLimited)
        SetLimit(left, upper, right, lower);
}

/**
 * Stops following an object.
 */
void Camera::Unfollow()
{
    focus = NULL;
}

/**
 * Sets the limits of the camera movement, when needed.
 */
void Camera::SetLimit(float left, float upper, float right, float lower)
{
    upperLimit = upper, lowerLimit = lower;
    leftLimit = left, rightLimit = right;
}

/**
 * Updates the camera position. If there is a focus, it will be
 * centered on the screen. If the camera is not following any
 * objects, it will respond to input (arrow keys).
 * @param dt The time elapsed between frames.
 */
void Camera::Update(float dt)
{
    if (focus)
    {
        pos.Set(focus->box.Center()); //sets the position of the camera on the center of the focus
        pos = pos + Point(-Game::GetInstance().GetWindowWidth()/2, -Game::GetInstance().GetWindowHeight()/2);
        if (isLimited)
        {
            if (pos.GetX() < leftLimit) pos.Set(leftLimit, pos.GetY());
            if (pos.GetX() > rightLimit) pos.Set(rightLimit, pos.GetY());
            if (pos.GetY() < upperLimit) pos.Set(pos.GetX(), upperLimit);
            if (pos.GetY() > lowerLimit) pos.Set(pos.GetX(), lowerLimit);
        }
    }
    else
    {
        InputManager &im = InputManager::GetInstance();
        float hm = 0, vm = 0;

        //sets the directions in which the camera must move
        if (im.IsKeyDown(RIGHT_ARROW_KEY) || im.KeyPress(RIGHT_ARROW_KEY))
            hm = hm + 1;
        if (im.IsKeyDown(LEFT_ARROW_KEY) || im.KeyPress(LEFT_ARROW_KEY))
            hm = hm - 1;
        if (im.IsKeyDown(DOWN_ARROW_KEY) || im.KeyPress(DOWN_ARROW_KEY))
            vm = vm + 1;
        if (im.IsKeyDown(UP_ARROW_KEY) || im.KeyPress(UP_ARROW_KEY))
            vm = vm - 1;

        //updates the position of the camera in the directions asked
        //remembering that the absolute value of the speed must be constant, even when moving diagonally
        pos = pos + Point(hm * (hm != 0 && vm != 0 ? speed * cos(M_PI/4) : speed) * dt,
                          vm * (hm != 0 && vm != 0 ? speed * cos(M_PI/4) : speed) * dt);
    }
    pos.Set(floor(pos.GetX()), floor(pos.GetY()));
}
