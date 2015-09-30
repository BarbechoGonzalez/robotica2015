/*
 *    Copyright (C) 2015 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
  giro=false;
  rot=1.2;
}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{



	
	timer.start(Period);

	return true;
}

int getvelocidadl(float distmin,int velomax, float dist){
  	if(dist<distmin){
// 	  std::cout << velomax*tanh(dist/distmin) << std::endl;
	      return velomax*tanh(dist/distmin);
	}
	else
	      return velomax;
}
float getvelocidadg(float velmaxg, float anglemax, float angle){
	if(angle<anglemax&& angle>(-anglemax)){
	      float aux=M_PI*angle*angle/2;
	      std::cout <<  velmaxg*(pow(EulerC,-(aux))) << std::endl;
	      return velmaxg*(pow(EulerC,-(aux)));
	}
	else return 0;
	
}
void SpecificWorker::compute()
{
    const float threshold = 400; //millimeters
    const int velmax=300;	//velocidad maxima del robot
    const int cota=10;  //cota de vision
    const float velmaxg=1.2;
   // const float anglemax=(100-2*cota)*100/180;
    const float anglemax=0.7854;
    
    try
    {
        RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data
        std::sort( ldata.begin()+cota, ldata.end()-cota, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
	float distaux=(ldata.data()+cota)->dist;
	rot=getvelocidadg(velmaxg,anglemax,distaux);
	if( distaux < threshold&&!giro){
		differentialrobot_proxy->setSpeedBase(getvelocidadl(threshold,velmax,distaux), rot);
		giro=true;
//   		usleep(rand()%(1000000-100000 + 1) + 100000);  //random wait between 1.5s and 0.1sec
   	}
	else if(distaux > threshold)
    	{
		giro=false;
        	differentialrobot_proxy->setSpeedBase(getvelocidadl(threshold,velmax,distaux), 0);
    	}
    	if(giro){
		differentialrobot_proxy->setSpeedBase(getvelocidadl(threshold,velmax,distaux), rot);
	}
    }
    catch(const Ice::Exception &ex)
    {
        std::cout << ex << std::endl;
    }
}
