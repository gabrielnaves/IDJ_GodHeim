/*
 * Rect.h
 *
 *  Created on: Mar 28, 2014
 *      Author: Gabriel Naves
 *
 *  Description: Expresses a position (upper left corner of the rectangle) and dimensions of the rectangle
 *
 */

#ifndef RECT_H_
#define RECT_H_

#include "Point.h"

class Rect
{
  public:
	Rect();
	Rect(Point point, float w, float h);
	Rect(float x, float y, float w, float h);
	void Set(const Rect& rect);
	void Set(Point point, float w, float h);
	void Set(float x, float y, float w, float h);
	void SetPoint(Point point);
	void SetPoint(float x, float y);

	Point Center() const;
	Point GetPoint() const;
	float GetX() const;
	float GetY() const;
	float GetW() const;
	float GetH() const;

	bool IsInside(float x, float y);
	bool IsInside(Point point);

	void MoveRect(float x, float y);
	void MoveRect(const Point& point);
	void MoveRectWithAngle(float distance, float angle);

  private:
	Point p;
	float w, h;
};

#endif /* RECT_H_ */
