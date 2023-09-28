#pragma once
#include <cmath>
#include <iostream>

// almost the same as vector2d, but this one is for doubles.
// i do not recomend using this unless you have to.
class dVector2d
{
    public:
        double X, Y;
        dVector2d();
        dVector2d(double X, double Y);

        dVector2d norm();

        // returns whether this vector is in a box defined by two vectors 
        bool inBox(dVector2d point1, dVector2d point2);

        // prints the vector to the terminal
        void printVec();

        void operator += (const dVector2d& vec);
        void operator -= (const dVector2d& vec);
        void operator *= (const dVector2d& vec);
        void operator /= (const dVector2d& vec);
      
        void operator += (const double& val);
        void operator -= (const double& val);
        void operator *= (const double& val);
        void operator /= (const double& val);
       
        dVector2d operator + (const dVector2d& vec);
        dVector2d operator - (const dVector2d& vec);
        dVector2d operator * (const dVector2d& vec);
        dVector2d operator / (const dVector2d& vec);
        
        dVector2d operator + (const double& val);
        dVector2d operator - (const double& val);
        dVector2d operator * (const double& val);
        dVector2d operator / (const double& val);
        
        bool operator == (const dVector2d& vec);
        bool operator != (const dVector2d& vec);
        bool operator >= (const dVector2d& vec);
        bool operator <= (const dVector2d& vec);

        bool operator > (const dVector2d& vec);
        bool operator < (const dVector2d& vec);
};