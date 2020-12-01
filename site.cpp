#include "head.hpp"

/** get number of infective from neighbourhood multiplyed by infection rate **/
float Site::get_neighbourInfectives(int pos_x, int pos_y)
{
    float res=0.0;
    for(int x=pos_x-1;x<=pos_x+1;++x)
    {
        for(int y=pos_y-1;y<=pos_y+1;++y)
        {
            if(x<0 || y<0 || x==SITE_LENGHT || y==SITE_WIDTH)
            {
                continue;
            }
            else if(x==pos_x && y==pos_y)
            {
                continue;
            }
            else
            {
                res+= TRANSMISSION_PROB * this->cell[x][y].get_totalInfective();
            }   
        }
    }
    return res;
}

/** makespread for whole site by DAYS days **/
void Site::updateSite()
{
    Site mapaZal;
    for(int i=0;i<DAYS;++i)
    {
        mapaZal=*this;
        for(int x=0;x<SITE_LENGHT;++x)
        {
            for(int y=0;y<SITE_WIDTH;++y)
            {
                this->cell[x][y].nextDay(mapaZal.get_neighbourInfectives(x,y));
            }
        }
        this->printSite();
    }
}

/** print number of currently diseased **/
void Site::printSite()
{
    cout<<"diseased \n";
    for(int x=0;x<SITE_LENGHT;++x)
    {
        for(int y=0;y<SITE_WIDTH;++y)
        {
            cout<< this->cell[x][y].get_currentDiseased()<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
