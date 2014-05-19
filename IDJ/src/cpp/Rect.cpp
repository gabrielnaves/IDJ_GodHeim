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

void Rect::SetPoint(float x, float y)
{
    p.SetPoint(x, y);
}

Point Rect::GetPoint() const { return p; }
float Rect::GetX() const { return p.GetX(); }
float Rect::GetY() const { return p.GetY(); }
float Rect::GetW() const { return w; }
float Rect::GetH() const { return h; }

bool Rect::IsInside(float x, float y)
{
	if (x >= p.GetX() && x <= (p.GetX() + w))
		if (y >= p.GetY() && y <= (p.GetY() + h))
			return true;
	return false;
}

/**
 * Checks whether a given point is inside the rectangle.
 * TODO: Implement this method with a rotation angle.
 */
bool Rect::IsInside(Point point)
{
    if (point.GetX() >= p.GetX() && point.GetX() <= (p.GetX() + w))
        if (point.GetY() >= p.GetY() && point.GetY() <= (p.GetY() + h))
            return true;
    return false;
}

/**
 * Returns the position of the center of the rectangle.
 */
Point Rect::GetCenter() const
{
    return Point((p.GetX()+w/2), (p.GetY()+h/2));
}

/**
 * Moves the rectangle by adding
 */
void Rect::MoveRect(float x, float y)
{
    p = p + Point(x, y);
}

void Rect::MoveRectWithAngle(float distance, float angle)
{
    p.MovePointWithAngle(distance, angle);
}
