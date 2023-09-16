#include "vector2d.h"

vector2d::vector2d()
{
    X = 0;
    Y = 0;
}

vector2d::vector2d(int X, int Y)
{
    this->X = X;
    this->Y = Y;
}

vector2d vector2d::norm()
{
    float mag = std::sqrt(this->X * this->X + this->Y * this->Y);
    return vector2d(this->X/mag, this->Y/mag);
}

void vector2d::operator+=(const vector2d &vec)
{
    this->X += vec.X;
    this->Y += vec.Y;
}

void vector2d::operator-=(const vector2d &vec)
{
    this->X -= vec.X;
    this->Y -= vec.Y;
}

void vector2d::operator*=(const vector2d &vec)
{
    this->X *= vec.X;
    this->Y *= vec.Y;
}

void vector2d::operator/=(const vector2d &vec)
{
    this->X /= vec.X;
    this->Y /= vec.Y;
}

void vector2d::operator+=(const int &val)
{
    this->X += val;
    this->Y += val;
}

void vector2d::operator-=(const int &val)
{
    this->X -= val;
    this->Y -= val;
}

void vector2d::operator*=(const int &val)
{
    this->X *= val;
    this->Y *= val;
}

void vector2d::operator/=(const int &val)
{
    this->X /= val;
    this->Y /= val;
}

vector2d vector2d::operator+(const vector2d &vec)
{
    return vector2d(this->X + vec.X, this->Y + vec.Y);
}

vector2d vector2d::operator-(const vector2d &vec)
{
    return vector2d(this->X - vec.X, this->Y - vec.Y);
}

vector2d vector2d::operator*(const vector2d &vec)
{
    return vector2d(this->X * vec.X, this->Y * vec.Y);
}

vector2d vector2d::operator/(const vector2d &vec)
{
    return vector2d(this->X / vec.X, this->Y / vec.Y);
}

vector2d vector2d::operator+(const int &val)
{
    return vector2d(this->X + val, this->Y + val);
}

vector2d vector2d::operator-(const int &val)
{
    return vector2d(this->X - val, this->Y - val);
}

vector2d vector2d::operator*(const int &val)
{
    return vector2d(this->X * val, this->Y * val);
}

vector2d vector2d::operator/(const int &val)
{
    return vector2d(this->X / val, this->Y / val);
}

bool vector2d::operator==(const vector2d &vec)
{
    return this->X == vec.X && this->Y == vec.Y;
}

bool vector2d::operator!=(const vector2d &vec)
{
    return this->X != vec.X || this->Y != vec.Y;
}

bool vector2d::operator>=(const vector2d &vec)
{
    return this->X >= vec.X && this->Y >= vec.Y;
}

bool vector2d::operator<=(const vector2d &vec)
{
    return this->X <= vec.X && this->Y <= vec.Y;
}

bool vector2d::operator>(const vector2d &vec)
{
    return this->X > vec.X && this->Y > vec.Y;
}

bool vector2d::operator<(const vector2d &vec)
{
    return this->X < vec.X && this->Y < vec.Y;
}