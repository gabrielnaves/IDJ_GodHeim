/*
 * Point.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 */

#include "../include/Point.h"

// Constructors
Point::Point() { x = 0, y = 0; }
Point::Point(float x, float y) { SetPoint(x, y); }

// Set Methods
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

// Get Methods
float Point::GetX() { return x; }
float Point::GetY() { return y; }

/**
 * Moves the point to another position, given the distance
 * to the new position and its angle in radians.
 */
void Point::MovePointWithAngle(float distance, float angle)
{
	x = x + cos(angle) * distance;
	y = y + sin(angle) * distance;
}

/**
 * Moves the point to another position, given the amount
 * to be incremented on both axes.
 */
void Point::MovePoint(float x, float y)
{
    this->x += x;
    this->y += y;
}

/**
 * Multiplies both the x and y values by a constant.
 */
void Point::Multiply(float c)
{
    x = x * c;
    y = y * c;
}

/**
 * Finds the angle in radians of the line defined by
 * the current point and the point given as a parameter,
 * relative to the positive x axis. The angle returned
 * is on the interval 0 <= angle < 2*PI.
 */
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

/**
 * Checks if the current point is equal to the point
 * given as a parameter. Two points will be considered
 * to be equal if the distance between them is less
 * than 6 pixels.
 */
bool Point::Equals(Point p)
{
    if (Distance(p) < 6)
        return true;
    return false;
}

/**
 * Returns the distance between the current point and the
 * point given as a parameter.
 */
float Point::Distance(Point p)
{
    return (sqrt(pow(p.GetX()-x, 2) + pow(p.GetY()-y, 2)));
}

// TODO comment the operator overloads properly.
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
