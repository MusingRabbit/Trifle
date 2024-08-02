#ifndef DISTANCEMEASURE_H
#define DISTANCEMEASURE_H

#include "KDTreeTypes.h"

namespace tfl 
{

    class DistanceMeasure
    {
        public :
        DistanceMeasure() {}
        virtual ~DistanceMeasure() {}
        virtual double Distance(const CoordPos& lhs, const CoordPos& rhs) = 0;
        virtual double CoordinateDistance(double x, double y, size_t dim) = 0;
    };

    // Maximum Distance (Linfinite norm)
    class DistanceL0 : virtual public DistanceMeasure
    {
        std::vector<double> w;

        public :
        DistanceL0(const std::vector<double>& weights = {})
        {
            w = weights;
        }

        double Distance(const CoordPos& lhs, const CoordPos& rhs)
        {
            size_t i;
            double dist, test;

            if (w.size() > 0)
            {
                dist = w[0] * fabs(lhs[0] - rhs[0]);

                for (i = 1; i < lhs.size(); i++)
                {
                    test = w[i] * fabs(lhs[i] - rhs[i]);
                    
                    if (test > dist)
                    {
                        dist = test;
                    }
                }
            }
            else 
            {
                dist = fabs(lhs[0] - rhs[0]);

                for (i = 1; i < lhs.size(); i++)
                {
                    test = fabs(lhs[i] - rhs[i]);
                    
                    if (test > dist)
                    {
                        dist = test;
                    }
                }
            }

            return dist;
        }

        double CoordinateDistance(double x, double y, size_t dim)
        {

            if (w.size() > 0)
            {
                return w[dim] * fabs(x - y);
            }

            return fabs(x - y);
        }
    };

    // Manhatten distance (L1 norm)
    class DistanceL1 : virtual public DistanceMeasure
    {
        std::vector<double> w;
        
        public :
        DistanceL1(const std::vector<double>& weights = {})
        {
            w = weights;
        }

        ~DistanceL1()
        {

        }

        double Distance(const CoordPos& lhs, const CoordPos& rhs)
        {
            size_t i;
            double dist = 0.0;

            if (w.size() > 0)
            {
                for (i = 0; i < lhs.size(); i ++)
                {
                    dist += w[i] * fabs(lhs[i] - rhs[i]);
                }
            }
            else 
            {
                for (i = 0; i < lhs.size(); i ++)
                {
                    dist += fabs(lhs[i] - rhs[i]);
                }
            }

            return dist;
        }

        double CoordinateDistance(double x, double y, size_t dim)
        {
            if (w.size() > 0)
            {
                return w[dim] * fabs(x - y);
            }

            return fabs(x - y);
        }
    };

    // Euclidian distance (L2 norm) - squared
    class DistanceL2 : virtual public DistanceMeasure 
    {
        std::vector<double> w;

        public :
        DistanceL2(const std::vector<double>& weights)
        {
            w = weights;
        }

        ~DistanceL2() 
        {

        }

        double Distance(const CoordPos& lhs, const CoordPos& rhs)
        {
            size_t i;
            double dist = 0.0f;

            if (w.size() > 0)
            {
                for (i = 0; i < lhs.size(); i++)
                {
                    dist += w[i] * (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
                }
            }
            else 
            {
                for (i = 0; i < lhs.size(); i++)
                {
                    dist += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
                }
            }

            return dist;
        }

        double CoordinateDistance(double x, double y, size_t dim)
        {
            if (w.size() > 0)
            {
                return w[dim] * (x - y) * (x - y);
            }

            return (x - y) * (x - y);
        } 
    };

}


#endif