/*
 * Thor.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Thor.h"

Thor* Thor::characterThor;

Thor::Thor(float x, float y)
{
	hp = 100;
	rotation = 0;
	tempThor.Open("img/penguinface.png");
	box.SetRect(x-tempThor.GetWidth()/2, y-tempThor.GetHeight()/2, tempThor.GetWidth(), tempThor.GetHeight());
	characterThor = this;
	horizontal = 0;
	vertical = 0;
}

Thor::~Thor()
{
	characterThor = NULL;
}

void Thor::Input()
{
	InputManager &input = InputManager::GetInstance();
	//sets the directions in which the camera must move
	if (input.KeyPress(SDLK_l) || input.IsKeyDown(SDLK_l))
		horizontal+=1;
	if (input.KeyPress(SDLK_j) || input.IsKeyDown(SDLK_j))
		horizontal-=1;
	if (input.KeyPress(SDLK_i) || input.IsKeyDown(SDLK_i))
		vertical-=1;
	if (input.KeyPress(SDLK_k) || input.IsKeyDown(SDLK_k))
		vertical+=1;
}

void Thor::Move(float dt)
{
	float linearSpeed;

	if (vertical!=0 && horizontal!=0) //in case the camera moves diagonally
		//must reduce the speed of x and y so the absolute value of the vectorial speed is constant
		linearSpeed=vel/sqrt(pow(vertical,2)+pow(horizontal,2));
	else
		linearSpeed=vel;

	box.MoveRect(linearSpeed*horizontal*dt,linearSpeed*vertical*dt);

	vertical = 0;
	horizontal = 0;
}

void Thor::Update(float dt)
{
	Input();
	Move(dt);
}

void Thor::Render()
{
	tempThor.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Thor::NotifyCollision(GameObject& other)
{

}

bool Thor::IsDead()
{
	return hp <= 0 ? true : false;
}

bool Thor::Is(std::string type)
{
	return type == "Thor" ? true : false;
}
