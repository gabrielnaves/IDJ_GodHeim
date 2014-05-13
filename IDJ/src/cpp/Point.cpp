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

void Point::SetPoint(const Point& point)
{
    x = point.x;
    y = point.y;
}

float Point::GetX() const { return x; }
float Point::GetY() const { return y; }

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

float Point::FindAngle(const Point& point)
{
    if (point.y == y)
        return (point.x >= x ? 0 : M_PI);
    if (point.x == x)
        return (point.y >= y ? M_PI/2 : 3*M_PI/2);
    if (point.x > x && point.y > y)
        return (atan((point.y - y)/(point.x-x)));
    if (point.x > x && point.y < y)
        return (2*M_PI - atan((y - point.y)/(point.x-x)));
    if (point.x < x && point.y < y)
        return (M_PI + atan((y - point.y)/(x-point.x)));
    if (point.x < x && point.y > y)
        return (M_PI - atan((point.y - y)/(x-point.x)));
    return 0;
}

bool Point::Equals(const Point& point)
{
    return Distance(point) < 10 ? true : false;
}

float Point::Distance(const Point& point)
{
    return (sqrt(pow(point.x-x, 2) + pow(point.y-y, 2)));
}

Point Point::operator+(const Point& rhs) const
{
    return Point(x + rhs.x, y + rhs.y);
}

Point Point::operator-(const Point& rhs) const
{
    return Point(x - rhs.x, y - rhs.y);
}

Point Point::operator*(const float rhs) const
{
    return Point(x * rhs, y * rhs);
}
