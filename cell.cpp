#include "head.hpp"

/** constructor**/
Cell::Cell()
{
    this->cured=0;
    this->toBeCured=0;
    this->totalInfective=0;
    this->totalNonInfective=0;
    for(int i=0;i<INFECTIVENESS_START;i++)
    {
        this->nonInfectiveQueue.push(0);
    }
    for(int i=INFECTIVENESS_START;i<INFECTIVENESS_END;i++)
    {
        this->infectiveQueue.push(0);
    }
}

float Cell::get_currentDiseased()
{
    return this->totalNonInfective + this->totalInfective + this->toBeCured;
}
float Cell::get_toBeCured()
{
    return this->toBeCured;
}
float Cell::get_totalInfective()
{
    return this->totalInfective;
}
float Cell::get_totalNonInfective()
{
    return this->totalNonInfective;
}
float Cell::get_cured()
{
    return this->cured;
}

/** add infected to nonInfectiveQueue **/
void Cell::addInfected(float num)
{
    this->totalNonInfective+=num;
    this->updateNonInfectiveQueue(num);
}

/** move nonInfectiveQueue **/
void Cell::updateNonInfectiveQueue(float num)
{
    auto toInfective=this->nonInfectiveQueue.front();
    this->totalNonInfective -= toInfective;
    this->nonInfectiveQueue.pop();
    this->nonInfectiveQueue.push(num);
    this->updateInfectiveQueue(toInfective);
}

/** move infectiveQueue **/
void Cell::updateInfectiveQueue(float num)
{
    this->totalInfective+= num-this->infectiveQueue.front();
    this->toBeCured += this->infectiveQueue.front();
    this->infectiveQueue.pop();
    this->infectiveQueue.push(num);
}

/** do spread of the disease in one cell by one day **/
void Cell::nextDay(float neighInfect)
{
    if(this->toBeCured!=0.0)
    {
        float newCured=CURE_RATE * this->toBeCured;
        //in order to avoid to stuck in rounding to 0 when toBeCured is low
        if(newCured<0.005 && newCured > 0.000)
        {
            if(rand()%101 < (CURE_RATE*100))
            {     
                newCured=0.01;
            }
            else
            {
                newCured=0.0;
            }    
        }

        this->toBeCured-=newCured;
        this->cured+=newCured;

        this->toBeCured=discretize(this->toBeCured);
        this->cured=discretize(this->cured);
        this->totalInfective=discretize(this->totalInfective);
        this->totalNonInfective=discretize(this->totalNonInfective);
    }

    float toBeDiseased= 1 - this->totalNonInfective - this->totalInfective - this->toBeCured - this->cured;
    float newDiseased = toBeDiseased * (TRANSMISSION_PROB*this->totalInfective + neighInfect);
    // some unnecessery shit chance to spread in low infective numbers
    if(newDiseased<0.005 && newDiseased > 0.000)
        {
            if(rand()%101 < (TRANSMISSION_PROB*100))
            {
                newDiseased=0.01;
            }
            else
            {
                newDiseased=0.0;
            }
        }
    newDiseased = discretize(newDiseased);
    this->addInfected(newDiseased);  
}