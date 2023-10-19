#pragma once
#include <cmath>
#include <iostream>

class vector2d
{
    public:
        int X, Y;
        int W, H;
        vector2d();
        vector2d(double X, double Y);
        vector2d(double X, double Y, double W, double H);

        vector2d norm();

        // returns whether this vector is in a box defined by two vectors 
        bool inBox(vector2d point1, vector2d point2);

        // prints the vector to the terminal
        void printVec();

        // returns the distance from this to 'to'
        double distance(vector2d to);
        double distance(vector2d *to);

        // @returns {vector2d} vector of X+W, Y+H
        vector2d getWH();

        void operator += (const vector2d& vec);
        void operator -= (const vector2d& vec);
        void operator *= (const vector2d& vec);
        void operator /= (const vector2d& vec);
      
        void operator += (const float& val);
        void operator -= (const float& val);
        void operator *= (const float& val);
        void operator /= (const float& val);
       
        vector2d operator + (const vector2d& vec);
        vector2d operator - (const vector2d& vec);
        vector2d operator * (const vector2d& vec);
        vector2d operator / (const vector2d& vec);
        
        vector2d operator + (const float& val);
        vector2d operator - (const float& val);
        vector2d operator * (const float& val);
        vector2d operator / (const float& val);
        
        bool operator == (const vector2d& vec);
        bool operator != (const vector2d& vec);
        bool operator >= (const vector2d& vec);
        bool operator <= (const vector2d& vec);

        bool operator > (const vector2d& vec);
        bool operator < (const vector2d& vec);
};