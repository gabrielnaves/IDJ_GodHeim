/*
 * Point.h
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Expresses a position of a point in 2D
 *
 */

#ifndef POINT_H_
#define POINT_H_

#include <cmath>

class Point
{
  public:
	Point();
	Point(float x, float y);

	void Set(float x, float y);
	void Set(const Point& point);

	float GetX() const;
	float GetY() const;

	void MovePointWithAngle(float distance, float angle);

	float FindAngle(const Point& point) const;
	bool Equals(const Point& point);
	float Distance(const Point& point);

	Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    Point operator*(const float rhs) const;
    Point operator/(const float rhs) const;
    bool operator==(const Point& rhs) const;

  private:
	float x, y;
};

#endif /* POINT_H_ */
