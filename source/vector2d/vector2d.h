#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
#include <iostream>

class vector2d
{
    public:
        int X, Y;
        
        vector2d();
        vector2d(int X, int Y);

        vector2d norm();

        void operator += (const vector2d& vec);
        void operator -= (const vector2d& vec);
        void operator *= (const vector2d& vec);
        void operator /= (const vector2d& vec);
      
        void operator += (const int& val);
        void operator -= (const int& val);
        void operator *= (const int& val);
        void operator /= (const int& val);
       
        vector2d operator + (const vector2d& vec);
        vector2d operator - (const vector2d& vec);
        vector2d operator * (const vector2d& vec);
        vector2d operator / (const vector2d& vec);
        
        vector2d operator + (const int& val);
        vector2d operator - (const int& val);
        vector2d operator * (const int& val);
        vector2d operator / (const int& val);
        
        bool operator == (const vector2d& vec);
        bool operator != (const vector2d& vec);
        bool operator >= (const vector2d& vec);
        bool operator <= (const vector2d& vec);

        bool operator > (const vector2d& vec);
        bool operator < (const vector2d& vec);
};

#endif