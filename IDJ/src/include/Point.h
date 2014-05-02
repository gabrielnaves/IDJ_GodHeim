/*
 * Point.h
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 */

#ifndef POINT_H_
#define POINT_H_

#include <cmath>

class Point
{
  public:
	Point();
	Point(float x, float y);

	void SetPoint(float x, float y);
	void SetPoint(Point point);

	float GetX();
	float GetY();

	void MovePointWithAngle(float distance, float angle);
	void MovePoint(float x, float y);
	void Multiply(float c);

	float FindAngle(Point p);
	bool Equals(Point p);
	float Distance(Point p);

	Point operator+(const Point& rhs) const;
    Point operator-(const Point& rhs) const;
    Point operator*(const float rhs) const;

  private:
	float x, y;
};

#endif /* POINT_H_ */
