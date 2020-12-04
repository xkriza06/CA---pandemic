#include <iostream> 
#include <map>
#include <vector> 
#include <queue> 
#include <math.h>
#include <time.h>

#define TRANSMISSION_PROB 0.0295
#define INFECTIVENESS_START 5
#define INFECTIVENESS_END 13
#define MOVEMENT_RATE 2.5 //simulates population movement (trips per day)
                        //1 = 1 extra random cell from site gets added to cell neighborhood per day
                        //0 = lockdown = no movement
                        //any floating decimal numbers are added as a random chance (e.g. 1.5 = 1 movement plus 50% chance of one extra)
#define CURE_RATE 0.15

#define DAYS 200

#define SITE_LENGHT 5
#define SITE_WIDTH 5



using namespace std;

class Cell
{
    private:
        float toBeCured;
        float cured;
        float totalInfective;
        float totalNonInfective;
        queue<float> nonInfectiveQueue;
        queue<float> infectiveQueue;
        void updateNonInfectiveQueue(float num);
        void updateInfectiveQueue(float num);

    public:
        Cell();
        
        void nextDay(float neighInfect);
        void addInfected(float num); 

        float get_currentDiseased();
        float get_toBeCured();
        float get_cured();
        float get_totalInfective();
        float get_totalNonInfective();
};

class Site
{
    private:
        
    public:
        Cell cell[SITE_LENGHT][SITE_WIDTH];
        float get_neighbourInfectives(int pos_x, int pos_y);
        void updateSite();
        void printSite();
        int randRound(float num);
};

float discretize(float x);