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

bool vector2d::inBox(vector2d point1, vector2d point2)
{
    return (this->X >= point1.X && this->X <= point2.X) && 
        (this->Y >= point1.Y && this->Y <= point2.Y);
}

void vector2d::printVec()
{
    std::cout << "Vector: (" << this->X << ", " << this->Y << ")" << std::endl;
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

void vector2d::operator+=(const float &val)
{
    this->X += val;
    this->Y += val;
}

void vector2d::operator-=(const float &val)
{
    this->X -= val;
    this->Y -= val;
}

void vector2d::operator*=(const float &val)
{
    this->X *= val;
    this->Y *= val;
}

void vector2d::operator/=(const float &val)
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

vector2d vector2d::operator+(const float &val)
{
    return vector2d(this->X + val, this->Y + val);
}

vector2d vector2d::operator-(const float &val)
{
    return vector2d(this->X - val, this->Y - val);
}

vector2d vector2d::operator*(const float &val)
{
    return vector2d(this->X * val, this->Y * val);
}

vector2d vector2d::operator/(const float &val)
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
