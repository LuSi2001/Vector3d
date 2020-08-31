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

    T length2() const
    {
        return (m_x * m_x + m_y * m_y + m_z * m_z);
    }

    T length() const
    {
        return std::sqrt(length2());
    }

private:

    T m_x = 0;
    T m_y = 0;
    T m_z = 0;
};

} // namespace

#endif // VECTOR_H
