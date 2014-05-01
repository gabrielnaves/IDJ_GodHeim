/*
 * Point.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Point.h"

Point::Point()
{
	x = 0, y = 0;
}

Point::Point(float x, float y)
{
	SetPoint(x, y);
}

void Point::SetPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Point::SetPoint(Point point)
{
    x = point.GetX();
    y = point.GetY();
}

float Point::GetX() { return x; }
float Point::GetY() { return y; }

void Point::MovePointWithAngle(float distance, float angle)
{
	x = x + cos(angle) * distance;
	y = y + sin(angle) * distance;
}

void Point::MovePoint(float x, float y)
{
    this->x += x;
    this->y += y;
}

void Point::Multiply(float c)
{
    x = x * c;
    y = y * c;
}

float Point::FindAngle(Point p)
{
    if (p.GetY() == y)
        return (p.GetX() >= x ? 0 : M_PI);
    if (p.GetX() == x)
        return (p.GetY() >= y ? M_PI/2 : 3*M_PI/2);
    if (p.GetX() > x && p.GetY() > y)
        return (atan((p.GetY() - y)/(p.GetX()-x)));
    if (p.GetX() > x && p.GetY() < y)
        return (2*M_PI - atan((y - p.GetY())/(p.GetX()-x)));
    if (p.GetX() < x && p.GetY() < y)
        return (M_PI + atan((y - p.GetY())/(x-p.GetX())));
    if (p.GetX() < x && p.GetY() > y)
        return (M_PI - atan((p.GetY() - y)/(x-p.GetX())));
    return 0;
}

bool Point::Equals(Point p)
{
    if (Distance(p) < 6)
        return true;
    return false;
}

float Point::Distance(Point p)
{
    return (sqrt(pow(p.GetX()-x, 2) + pow(p.GetY()-y, 2)));
}
