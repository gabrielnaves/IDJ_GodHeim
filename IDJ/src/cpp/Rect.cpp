/*
 * Rect.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Rect.h"

Rect::Rect()
{
	p.SetPoint(0, 0);
	w = 0, h = 0;
}

Rect::Rect(Point point, float w, float h)
{
    SetRect(point, w, h);
}

Rect::Rect(float x, float y, float w, float h)
{
	SetRect(x, y, w, h);
}

void Rect::SetRect(float x, float y, float w, float h)
{
	p.SetPoint(x, y);
	this->w = w;
	this->h = h;
}

void Rect::SetRect(Point point, float w, float h)
{
    p.SetPoint(point);
    this->w = w;
    this->h = h;
}

void Rect::SetPoint(Point point)
{
    p.SetPoint(point);
}

Point Rect::GetPoint() { return p; }
float Rect::GetX() { return p.GetX(); }
float Rect::GetY() { return p.GetY(); }
float Rect::GetW() { return w; }
float Rect::GetH() { return h; }

bool Rect::IsInside(float x, float y)
{
	if (x >= p.GetX() && x <= (p.GetX() + w))
		if (y >= p.GetY() && y <= (p.GetY() + h))
			return true;
	return false;
}

bool Rect::IsInside(Point point)
{
    if (point.GetX() >= p.GetX() && point.GetX() <= (p.GetX() + w))
        if (point.GetY() >= p.GetY() && point.GetY() <= (p.GetY() + h))
            return true;
    return false;
}

Point Rect::GetCenter()
{
    return Point((p.GetX()+w/2), (p.GetY()+h/2));
}

void Rect::MoveRect(float x, float y)
{
    p.MovePoint(x, y);
}

void Rect::MoveRectWithAngle(float distance, float angle)
{
    p.MovePointWithAngle(distance, angle);
}