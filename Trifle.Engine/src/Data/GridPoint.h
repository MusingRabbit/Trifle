#ifndef GRIDPOINT_H
#define GRIDPOINT_H
struct GridPoint
{
    unsigned int X;
    unsigned int Y;
    unsigned int Z;

    GridPoint()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    GridPoint(unsigned int x, unsigned int y, unsigned int z)
    {
        X = x;
        Y = y;
        Z = z;
    }
};
#endif // !GRIDPOINT_H
