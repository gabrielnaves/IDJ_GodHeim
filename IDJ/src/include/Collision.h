/*
 * Collision.h
 *
 *  Created on: Apr 29, 2014
 *      Author: Gabriel Naves
 */

#ifndef COLLISION_H_
#define COLLISION_H_
/*
#include <cmath>
#include <algorithm>

#include "Rect.h"

// Essa é uma implementação do SAT feita pelo Lucas Neves.
// Recebe dois Rects e suas rotações, e detecta se os retângulos colidem.
// Mais informações sobre o método podem ser encontradas nos seguintes links:
// http://www.metanetsoftware.com/technique/tutorialA.html
// http://www.gamedev.net/page/resources/_/technical/game-programming/2d-rotated-rectangle-collision-r2604

class Collision
{
  public:
    static inline bool IsColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB)
    {
        Point A[] = { Point( a.p.x, a.p.y + a.h ),
                      Point( a.p.x + a.w, a.p.y + a.h ),
                      Point( a.p.x + a.w, a.p.y ),
                      Point( a.p.x, a.p.y )
                    };
        Point B[] = { Point( b.p.x, b.p.y + b.h ),
                      Point( b.p.x + b.w, b.p.y + b.h ),
                      Point( b.p.x + b.w, b.p.y ),
                      Point( b.p.x, b.p.y )
                    };

        for (auto& v : A) {
            v = Rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
        }

        for (auto& v : B) {
            v = Rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();
        }

        Point axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

        for (auto& axis : axes) {
            float P[4];

            for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

            float minA = *std::min_element(P, P + 4);
            float maxA = *std::max_element(P, P + 4);

            for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

            float minB = *std::min_element(P, P + 4);
            float maxB = *std::max_element(P, P + 4);

            if (maxA < minB || minA > maxB)
                return false;
        }

        return true;
    }

  private:
    static inline float Mag(const Point& p) {
        return std::sqrt(p.x * p.x + p.y * p.y);
    }

    static inline Point Norm(const Point& p) {
        return p * (1.f / Mag(p));
    }

    static inline float Dot(const Point& a, const Point& b) {
        return a.x * b.x + a.y * b.y;
    }

    static inline Point Rotate(const Point& p, float angle) {
        float cs = std::cos(angle), sn = std::sin(angle);
        return Point ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
    }
};

// Aqui estão três operadores que sua classe Point deve precisar, se já não tiver.
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Point operator+(const Point& rhs) const {
//    return Point(x + rhs.x, y + rhs.y);
// }

// Point operator-(const Point& rhs) const {
//    return Point(x - rhs.x, y - rhs.y);
// }

// Point Point::operator*(const float rhs) const {
//    return Point(x * rhs, y * rhs);
// }
*/
#endif /* COLLISION_H_ */
