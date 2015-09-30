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
  rot=0.8;
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

void SpecificWorker::compute()
{
    const float threshold = 400; //millimeters
    

    try
    {
        RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data
        std::sort( ldata.begin()+15, ldata.end()-15, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
	if( (ldata.data()+15)->dist < threshold&&!giro){
	        std::cout << ldata.front().dist << std::endl;
		if((ldata.data()+15)->angle>0)
		  rot=-rot;
		differentialrobot_proxy->setSpeedBase(400, rot);
		giro=true;
 		usleep(rand()%(1000000-100000 + 1) + 100000);  //random wait between 1.5s and 0.1sec
   	}
	else if((ldata.data()+15)->dist > threshold)
    	{
		giro=false;
        	differentialrobot_proxy->setSpeedBase(500, 0);
    	}
    	else if(giro){
		
		differentialrobot_proxy->setSpeedBase((ldata.data()+15)->dist, rot);
	}
    }
    catch(const Ice::Exception &ex)
    {
        std::cout << ex << std::endl;
    }
}
