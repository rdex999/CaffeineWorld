#include "dVector2d.h"

dVector2d::dVector2d()
{
    X = 0;
    Y = 0;
}

dVector2d::dVector2d(double X, double Y)
{
    this->X = X;
    this->Y = Y;
}

dVector2d dVector2d::norm()
{
    double mag = std::sqrt(this->X * this->X + this->Y * this->Y);
    return dVector2d(this->X/mag, this->Y/mag);
}

bool dVector2d::inBox(dVector2d point1, dVector2d point2)
{
    return (this->X >= point1.X && this->X <= point2.X) && 
        (this->Y >= point1.Y && this->Y <= point2.Y);
}

void dVector2d::printVec()
{
    std::cout << "Vector: (" << this->X << ", " << this->Y << ")" << std::endl;
}

void dVector2d::operator+=(const dVector2d &vec)
{
    this->X += vec.X;
    this->Y += vec.Y;
}

void dVector2d::operator-=(const dVector2d &vec)
{
    this->X -= vec.X;
    this->Y -= vec.Y;
}

void dVector2d::operator*=(const dVector2d &vec)
{
    this->X *= vec.X;
    this->Y *= vec.Y;
}

void dVector2d::operator/=(const dVector2d &vec)
{
    this->X /= vec.X;
    this->Y /= vec.Y;
}

void dVector2d::operator+=(const double &val)
{
    this->X += val;
    this->Y += val;
}

void dVector2d::operator-=(const double &val)
{
    this->X -= val;
    this->Y -= val;
}

void dVector2d::operator*=(const double &val)
{
    this->X *= val;
    this->Y *= val;
}

void dVector2d::operator/=(const double &val)
{
    this->X /= val;
    this->Y /= val;
}

dVector2d dVector2d::operator+(const dVector2d &vec)
{
    return dVector2d(this->X + vec.X, this->Y + vec.Y);
}

dVector2d dVector2d::operator-(const dVector2d &vec)
{
    return dVector2d(this->X - vec.X, this->Y - vec.Y);
}

dVector2d dVector2d::operator*(const dVector2d &vec)
{
    return dVector2d(this->X * vec.X, this->Y * vec.Y);
}

dVector2d dVector2d::operator/(const dVector2d &vec)
{
    return dVector2d(this->X / vec.X, this->Y / vec.Y);
}

dVector2d dVector2d::operator+(const double &val)
{
    return dVector2d(this->X + val, this->Y + val);
}

dVector2d dVector2d::operator-(const double &val)
{
    return dVector2d(this->X - val, this->Y - val);
}

dVector2d dVector2d::operator*(const double &val)
{
    return dVector2d(this->X * val, this->Y * val);
}

dVector2d dVector2d::operator/(const double &val)
{
    return dVector2d(this->X / val, this->Y / val);
}

bool dVector2d::operator==(const dVector2d &vec)
{
    return this->X == vec.X && this->Y == vec.Y;
}

bool dVector2d::operator!=(const dVector2d &vec)
{
    return this->X != vec.X || this->Y != vec.Y;
}

bool dVector2d::operator>=(const dVector2d &vec)
{
    return this->X >= vec.X && this->Y >= vec.Y;
}

bool dVector2d::operator<=(const dVector2d &vec)
{
    return this->X <= vec.X && this->Y <= vec.Y;
}

bool dVector2d::operator>(const dVector2d &vec)
{
    return this->X > vec.X && this->Y > vec.Y;
}

bool dVector2d::operator<(const dVector2d &vec)
{
    return this->X < vec.X && this->Y < vec.Y;
}
