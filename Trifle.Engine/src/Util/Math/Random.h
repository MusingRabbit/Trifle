#include <random>
#include <climits>



namespace tfl 
{
    class Random
    {
        public :
        static void Seed(unsigned long n)
        {
             srand (static_cast <unsigned> (n));
        }


        static float GetFloat()
        {
            return (float)rand() / (float)RAND_MAX;
        }

        static int GetInt()
        {
            return rand();
        }

        static int GetInt(int max)
        {
            return GetInt() % max;
        }

        static int GetInt(int min, int max)
        {
            return GetInt(max) + min;
        }
    };
}

