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

    //MOVEMENT_RATE amount of extra cells per day
    int total_moves = randRound(MOVEMENT_RATE);
    for(int i = 0; i < total_moves; i++) {
        //res += TRANSMISSION_PROB * this->cell[x][y].get_totalInfective();
        int rand_x;
        int rand_y;
        do {
            rand_x = rand()%SITE_LENGHT;
            rand_y = rand()%SITE_WIDTH;
        } while(rand_x==pos_x && rand_y==pos_y);

        res+= TRANSMISSION_PROB * this->cell[rand_x][rand_y].get_totalInfective();
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
    Cell avgCell = this->get_averageCell();
    cout<<"currentDeceased="<< avgCell.get_currentDiseased()<<"\n";
    cout<<"totalNonInfective="<< avgCell.get_totalNonInfective()<<"\n";
    cout<<"totalInfective="<< avgCell.get_totalInfective()<<"\n";
    cout<<"toBeCured="<< avgCell.get_toBeCured()<<"\n";
    cout<<"cured="<< avgCell.get_cured()<<"\n";
    cout<<"\n";
}

int Site::randRound(float num) {
    int count = int(num);
    float plus_one = rand() / (float)RAND_MAX;
    return plus_one < num-int(num) ? ++count : count;
}

/** return Cell with average attributes of all Cells of site **/
Cell Site::get_averageCell()
{
    float totalNonInfective= 0.0, totalInfective= 0.0, toBeCured= 0.0, cured= 0.0;
    int sizeOfSite = SITE_LENGHT * SITE_WIDTH;
    for(int x=0;x<SITE_LENGHT;++x)
    {
        for(int y=0;y<SITE_WIDTH;++y)
        {
            totalNonInfective+=this->cell[x][y].get_totalNonInfective();
            totalInfective+=this->cell[x][y].get_totalInfective();
            toBeCured+=this->cell[x][y].get_toBeCured();
            cured+=this->cell[x][y].get_cured();
        }
    }

    totalNonInfective/=sizeOfSite;
    totalInfective/=sizeOfSite;
    toBeCured/=sizeOfSite;
    cured/=sizeOfSite;
    return {discretize(totalNonInfective), discretize(totalInfective), discretize(toBeCured), discretize(cured)};
}