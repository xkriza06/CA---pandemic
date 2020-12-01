#include "head.hpp"

/** round to 2 decimals **/
float discretize(float x)
{
    if(x>=1.0)
    {
        return 1.0;
    }
    else if(x<=0.0)
    {
        return 0.0;
    }
    else
    {
        return roundf(x*100)/100;
    } 
}




int main(int argc, char *argv[])
{
    srand(time(NULL));

    Site mapa;
    mapa.cell[1][1].addInfected(0.2);
    mapa.cell[4][1].addInfected(0.15);
  //  mapa.cell[8][3].addInfected(0.31);
    mapa.cell[4][3].addInfected(0.18);
//    mapa.cell[9][7].addInfected(0.22);
 //   mapa.cell[9][4].addInfected(0.19);
    mapa.cell[0][0].addInfected(0.29);
    mapa.cell[1][0].addInfected(0.05);

    mapa.updateSite();

    return 0;  
}
