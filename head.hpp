#include <iostream>  
#include <queue> 
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

#define STARTING_INFECTED 5
#define TRANSMISSION_PROB 0.0295
#define INFECTIVENESS_START 5
#define INFECTIVENESS_END 13
#define MOVEMENT_RATE 0 //simulates population movement (trips per day)
                        //1 = 1 extra random cell from site gets added to cell neighborhood per day
                        //0 = lockdown = no movement
                        //any floating decimal numbers are added as a random chance (e.g. 1.5 = 1 movement plus 50% chance of one extra)
#define CURE_RATE 0.15

#define DAYS 100

#define SITE_LENGHT 5
#define SITE_WIDTH 5




class Cell
{
    private:
        float totalNonInfective;
        float totalInfective;
        float toBeCured;
        float cured;
        
        queue<float> nonInfectiveQueue;
        queue<float> infectiveQueue;

        void updateNonInfectiveQueue(float num);
        void updateInfectiveQueue(float num);

    public:
        Cell();
        Cell(float tNI, float tI, float tBC, float c): totalNonInfective(tNI), totalInfective(tI), toBeCured(tBC), cured(c) {}
        
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
        vector<float> currentlyDiseased; //current percent of diseased people per day
        vector<float> totalCured;   //current percent of cured people per day

    public:
        Cell cell[SITE_LENGHT][SITE_WIDTH]; 
        void updateSite();
        void printSite();
        int randRound(float num);
        float get_neighbourInfectives(int pos_x, int pos_y);
        Cell get_averageCell();
        vector<float> getDiseasedPerDay();
};

float discretize(float x);