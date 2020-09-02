#ifndef UTILS_H
#define UTILS_H

#include <QPointF>
#include "vector.h"

namespace mats
{

using real = qreal;
using Vec3 = mats::Vector3<real>;

inline Vec3 q2v(const QPointF &p) {return Vec3(p.x(), p.y(), 0.0);}
inline QPointF v2q(const Vec3 &v) {return QPointF(v.x(), v.y());}

} // namespace

#endif // UTILS_H
