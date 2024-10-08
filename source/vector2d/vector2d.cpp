#include "vector2d.h"

vector2d::vector2d()
{
    X = 0;
    Y = 0;
}

vector2d::vector2d(double X, double Y)
{
    this->X = X;
    this->Y = Y;
}

vector2d::vector2d(double X, double Y, double W, double H)
{
    this->X = X;
    this->Y = Y;
    this->W = W;
    this->H = H;
}

vector2d vector2d::norm()
{
    double mag = std::sqrt(this->X * this->X + this->Y * this->Y);
    return vector2d(this->X/mag, this->Y/mag);
}

bool vector2d::inBox(vector2d point1, vector2d point2)
{
    return (this->X >= point1.X && this->X <= point2.X) && 
        (this->Y >= point1.Y && this->Y <= point2.Y);
}

bool vector2d::inBoxRel(vector2d p)
{
    return (this->X >= p.X && this->X <= (p.X + p.W)) &&
        (this->Y >= p.Y && this->Y <= (p.Y + p.H));
}

bool vector2d::inBoxRel(vector2d *p)
{
    return (this->X >= p->X && this->X <= (p->X + p->W)) &&
        (this->Y >= p->Y && this->Y <= (p->Y + p->H));
}

bool vector2d::inBoxRel(vector2d p1, vector2d p2)
{
    return (this->X >= p1.X && this->X <= (p1.X + p2.X)) &&
        (this->Y >= p1.Y && this->Y <= (p1.Y + p2.Y));
}

void vector2d::printVec()
{
    std::cout << "Vector: (" << this->X << ", " << this->Y << ")" << std::endl;
}

double vector2d::distance(vector2d to)
{
    return std::sqrt(std::pow(this->X - to.X, 2) + std::pow(this->Y - to.Y, 2));
}

double vector2d::distance(vector2d *to)
{
    return std::sqrt(std::pow(this->X - to->X, 2) + std::pow(this->Y - to->Y, 2));
}

vector2d vector2d::getWH()
{
    return vector2d(X+W, Y+H);
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
