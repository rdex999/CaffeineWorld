#ifndef VECTOR2D_H
#define VECTOR2D_H

class vector2d
{
    public:
        int X, Y;
        
        vector2d();
        vector2d(int X, int Y);

        void operator += (const vector2d& vec);
        void operator -= (const vector2d& vec);
        void operator *= (const vector2d& vec);
        void operator /= (const vector2d& vec);

        vector2d operator + (const vector2d& vec);
        vector2d operator - (const vector2d& vec);
        vector2d operator * (const vector2d& vec);
        vector2d operator / (const vector2d& vec);

        bool operator == (const vector2d& vec);
        bool operator != (const vector2d& vec);
        bool operator >= (const vector2d& vec);
        bool operator <= (const vector2d& vec);

        bool operator > (const vector2d& vec);
        bool operator < (const vector2d& vec);
};

#endif