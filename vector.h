#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

namespace mats
{

template<typename T> class Vector3
{

public:

    Vector3() = default;

    Vector3 &operator * (const T &multiplier)
    {
        this->m_x *= multiplier;
        this->m_y *= multiplier;
        this->m_z *= multiplier;

        return *this;
    }

    const T &x() const{
        return m_x;
    }

    const T &y() const{
        return m_x;
    }

    const T &z() const{
        return m_x;
    }

    T lengthSquared() const
    {
        return (m_x * m_x + m_y * m_y + m_z * m_z);
    }

    T length() const
    {
        return std::sqrt(lengthSquared());
    }

private:

    T m_x = 0;
    T m_y = 0;
    T m_z = 0;
};

} // namespace

#endif // VECTOR_H
