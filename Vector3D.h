
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <QtGui/qtguiglobal.h>
#include <QtCore/qpoint.h>
#include <QtCore/qmetatype.h>

QT_BEGIN_NAMESPACE


class QMatrix4x4;
class QVector2D;
class QVector4D;
class QRect;

#ifndef QT_NO_VECTOR3D

class Q_GUI_EXPORT Vector3D
{
public:
    Q_DECL_CONSTEXPR Vector3D();
    explicit Vector3D(Qt::Initialization) {}
    Q_DECL_CONSTEXPR Vector3D(double xpos, double ypos, double zpos) : xp(xpos), yp(ypos), zp(zpos) {}

    Q_DECL_CONSTEXPR explicit Vector3D(const QPoint& point);
    Q_DECL_CONSTEXPR explicit Vector3D(const QPointF& point);
#ifndef QT_NO_VECTOR2D
    Vector3D(const QVector2D& vector);
    Vector3D(const QVector2D& vector, double zpos);
#endif
#ifndef QT_NO_VECTOR4D
    explicit Vector3D(const QVector4D& vector);
#endif

    bool isNull() const;

    Q_DECL_CONSTEXPR double x() const;
    Q_DECL_CONSTEXPR double y() const;
    Q_DECL_CONSTEXPR double z() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double &operator[](int i);
    double operator[](int i) const;

    double length() const;
    double lengthSquared() const;

    Vector3D normalized() const;
    void normalize();

    Vector3D &operator+=(const Vector3D &vector);
    Vector3D &operator-=(const Vector3D &vector);
    Vector3D &operator*=(double factor);
    Vector3D &operator*=(const Vector3D& vector);
    Vector3D &operator/=(double divisor);
    inline Vector3D &operator/=(const Vector3D &vector);

    static double dotProduct(const Vector3D& v1, const Vector3D& v2); //In Qt 6 convert to inline and constexpr
    static Vector3D crossProduct(const Vector3D& v1, const Vector3D& v2); //in Qt 6 convert to inline and constexpr

    static Vector3D normal(const Vector3D& v1, const Vector3D& v2);
    static Vector3D normal
        (const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

    Vector3D project(const QMatrix4x4 &modelView, const QMatrix4x4 &projection, const QRect &viewport) const;
    Vector3D unproject(const QMatrix4x4 &modelView, const QMatrix4x4 &projection, const QRect &viewport) const;

    double distanceToPoint(const Vector3D& point) const;
    double distanceToPlane(const Vector3D& plane, const Vector3D& normal) const;
    double distanceToPlane(const Vector3D& plane1, const Vector3D& plane2, const Vector3D& plane3) const;
    double distanceToLine(const Vector3D& point, const Vector3D& direction) const;

    Q_DECL_CONSTEXPR friend inline bool operator==(const Vector3D &v1, const Vector3D &v2);
    Q_DECL_CONSTEXPR friend inline bool operator!=(const Vector3D &v1, const Vector3D &v2);
    Q_DECL_CONSTEXPR friend inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
    Q_DECL_CONSTEXPR friend inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
    Q_DECL_CONSTEXPR friend inline const Vector3D operator*(double factor, const Vector3D &vector);
    Q_DECL_CONSTEXPR friend inline const Vector3D operator*(const Vector3D &vector, double factor);
    Q_DECL_CONSTEXPR friend const Vector3D operator*(const Vector3D &v1, const Vector3D& v2);
    Q_DECL_CONSTEXPR friend inline const Vector3D operator-(const Vector3D &vector);
    Q_DECL_CONSTEXPR friend inline const Vector3D operator/(const Vector3D &vector, double divisor);
    Q_DECL_CONSTEXPR friend inline const Vector3D operator/(const Vector3D &vector, const Vector3D &divisor);

    Q_DECL_CONSTEXPR friend inline bool qFuzzyCompare(const Vector3D& v1, const Vector3D& v2);

#ifndef QT_NO_VECTOR2D
    QVector2D toVector2D() const;
#endif
#ifndef QT_NO_VECTOR4D
    QVector4D toVector4D() const;
#endif

    Q_DECL_CONSTEXPR QPoint toPoint() const;
    Q_DECL_CONSTEXPR QPointF toPointF() const;

    operator QVariant() const;

private:
    double xp, yp, zp;

    friend class QVector2D;
    friend class QVector4D;
#ifndef QT_NO_MATRIX4X4
    friend Vector3D operator*(const Vector3D& vector, const QMatrix4x4& matrix);
    friend Vector3D operator*(const QMatrix4x4& matrix, const Vector3D& vector);
#endif
};

Q_DECLARE_TYPEINFO(Vector3D, Q_PRIMITIVE_TYPE);

Q_DECL_CONSTEXPR inline Vector3D::Vector3D() : xp(0.0f), yp(0.0f), zp(0.0f) {}

Q_DECL_CONSTEXPR inline Vector3D::Vector3D(const QPoint& point) : xp(point.x()), yp(point.y()), zp(0.0f) {}

Q_DECL_CONSTEXPR inline Vector3D::Vector3D(const QPointF& point) : xp(point.x()), yp(point.y()), zp(0.0f) {}

inline bool Vector3D::isNull() const
{
    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp);
}

Q_DECL_CONSTEXPR inline double Vector3D::x() const { return xp; }
Q_DECL_CONSTEXPR inline double Vector3D::y() const { return yp; }
Q_DECL_CONSTEXPR inline double Vector3D::z() const { return zp; }

inline void Vector3D::setX(double aX) { xp = aX; }
inline void Vector3D::setY(double aY) { yp = aY; }
inline void Vector3D::setZ(double aZ) { zp = aZ; }

inline double &Vector3D::operator[](int i)
{
    Q_ASSERT(uint(i) < 3u);
    return *(&xp + i);
}

inline double Vector3D::operator[](int i) const
{
    Q_ASSERT(uint(i) < 3u);
    return *(&xp + i);
}

inline Vector3D &Vector3D::operator+=(const Vector3D &vector)
{
    xp += vector.xp;
    yp += vector.yp;
    zp += vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator-=(const Vector3D &vector)
{
    xp -= vector.xp;
    yp -= vector.yp;
    zp -= vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator*=(double factor)
{
    xp *= factor;
    yp *= factor;
    zp *= factor;
    return *this;
}

inline Vector3D &Vector3D::operator*=(const Vector3D& vector)
{
    xp *= vector.xp;
    yp *= vector.yp;
    zp *= vector.zp;
    return *this;
}

inline Vector3D &Vector3D::operator/=(double divisor)
{
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;
    return *this;
}

inline Vector3D &Vector3D::operator/=(const Vector3D &vector)
{
    xp /= vector.xp;
    yp /= vector.yp;
    zp /= vector.zp;
    return *this;
}

Q_DECL_CONSTEXPR inline bool operator==(const Vector3D &v1, const Vector3D &v2)
{
    return v1.xp == v2.xp && v1.yp == v2.yp && v1.zp == v2.zp;
}

Q_DECL_CONSTEXPR inline bool operator!=(const Vector3D &v1, const Vector3D &v2)
{
    return v1.xp != v2.xp || v1.yp != v2.yp || v1.zp != v2.zp;
}

Q_DECL_CONSTEXPR inline const Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.xp + v2.xp, v1.yp + v2.yp, v1.zp + v2.zp);
}

Q_DECL_CONSTEXPR inline const Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.xp - v2.xp, v1.yp - v2.yp, v1.zp - v2.zp);
}

Q_DECL_CONSTEXPR inline const Vector3D operator*(double factor, const Vector3D &vector)
{
    return Vector3D(vector.xp * factor, vector.yp * factor, vector.zp * factor);
}

Q_DECL_CONSTEXPR inline const Vector3D operator*(const Vector3D &vector, double factor)
{
    return Vector3D(vector.xp * factor, vector.yp * factor, vector.zp * factor);
}

Q_DECL_CONSTEXPR inline const Vector3D operator*(const Vector3D &v1, const Vector3D& v2)
{
    return Vector3D(v1.xp * v2.xp, v1.yp * v2.yp, v1.zp * v2.zp);
}

Q_DECL_CONSTEXPR inline const Vector3D operator-(const Vector3D &vector)
{
    return Vector3D(-vector.xp, -vector.yp, -vector.zp);
}

Q_DECL_CONSTEXPR inline const Vector3D operator/(const Vector3D &vector, double divisor)
{
    return Vector3D(vector.xp / divisor, vector.yp / divisor, vector.zp / divisor);
}

Q_DECL_CONSTEXPR inline const Vector3D operator/(const Vector3D &vector, const Vector3D &divisor)
{
    return Vector3D(vector.xp / divisor.xp, vector.yp / divisor.yp, vector.zp / divisor.zp);
}

Q_DECL_CONSTEXPR inline bool qFuzzyCompare(const Vector3D& v1, const Vector3D& v2)
{
    return qFuzzyCompare(v1.xp, v2.xp) &&
           qFuzzyCompare(v1.yp, v2.yp) &&
           qFuzzyCompare(v1.zp, v2.zp);
}

Q_DECL_CONSTEXPR inline QPoint Vector3D::toPoint() const
{
    return QPoint(qRound(xp), qRound(yp));
}

Q_DECL_CONSTEXPR inline QPointF Vector3D::toPointF() const
{
    return QPointF(qreal(xp), qreal(yp));
}

#ifndef QT_NO_DEBUG_STREAM
Q_GUI_EXPORT QDebug operator<<(QDebug dbg, const Vector3D &vector);
#endif

#ifndef QT_NO_DATASTREAM
Q_GUI_EXPORT QDataStream &operator<<(QDataStream &, const Vector3D &);
Q_GUI_EXPORT QDataStream &operator>>(QDataStream &, Vector3D &);
#endif

#endif

QT_END_NAMESPACE

#endif
