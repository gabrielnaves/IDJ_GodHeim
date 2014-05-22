/*
 * Loki.cpp
 *
 *  Created on: May 19, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Loki.h"

Loki* Loki::characterLoki;

Loki::Loki(float x, float y)
{
	hp = 100;
	rotation = 0;
	tempLoki.Open("img/tempLoki.jpg");
	box.SetRect(x-tempLoki.GetWidth()/2, y-tempLoki.GetHeight()/2, tempLoki.GetWidth(), tempLoki.GetHeight());
	characterLoki = this;
	horizontal = 0;
	vertical = 0;
}

Loki::~Loki()
{
	characterLoki = NULL;
}

void Loki::Input()
{
	InputManager &input = InputManager::GetInstance();
	//sets the directions in which the camera must move
	if (input.KeyPress(RIGHT_ARROW_KEY) || input.IsKeyDown(RIGHT_ARROW_KEY))
		horizontal+=1;
	if (input.KeyPress(LEFT_ARROW_KEY) || input.IsKeyDown(LEFT_ARROW_KEY))
		horizontal-=1;
	if (input.KeyPress(UP_ARROW_KEY) || input.IsKeyDown(UP_ARROW_KEY))
		vertical-=1;
	if (input.KeyPress(DOWN_ARROW_KEY) || input.IsKeyDown(DOWN_ARROW_KEY))
		vertical+=1;
}

void Loki::Move(float dt)
{
	float linearSpeed;
	vertical = 0;
	horizontal = 0;

	Input();

	if (vertical!=0 && horizontal!=0) //in case the camera moves diagonally
		//must reduce the speed of x and y so the absolute value of the vectorial speed is constant
		linearSpeed=vel/sqrt(pow(vertical,2)+pow(horizontal,2));
	else
		linearSpeed=vel;

	box.MoveRect(linearSpeed*horizontal*dt,linearSpeed*vertical*dt);
}

void Loki::Update(float dt)
{
	Move(dt);
}

void Loki::Render()
{
	tempLoki.Render(box.GetX()-Camera::pos.GetX(), box.GetY()-Camera::pos.GetY());
}

void Loki::NotifyCollision(GameObject& other)
{

}

bool Loki::IsDead()
{
	return hp <= 0 ? true : false;
}

bool Loki::Is(std::string type)
{
	return type == "Loki" ? true : false;
}
