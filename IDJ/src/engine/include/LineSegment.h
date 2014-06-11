/*
 * LineSegment.h
 *
 *  Created on: Jun 9, 2014
 *      Author: Gabriel Naves
 */

#ifndef LINESEGMENT_H_
#define LINESEGMENT_H_

#include "Point.h"

class LineSegment
{
  public:
    LineSegment();
    LineSegment(const Point& p1, const Point& p2);
    LineSegment(float x1, float y1, float x2, float y2);

    void Set(const Point& p1, const Point& p2);
    void Set(float x1, float y1, float x2, float y2);

    float GetHighestX();
    float GetLowestX();
    float GetVerticalDistance(const Point& point);

    bool IsAbove(const Point& point);
    bool IsBelow(const Point& point);

  private:
    void FindAandB();
    Point p1, p2;
    float a, b;
};

#endif /* LINESEGMENT_H_ */
