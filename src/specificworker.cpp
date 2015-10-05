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
#include <qt4/QtGui/qplaintextedit.h>

/**
* \brief Default constructor
*/
SpecificWorker::SpecificWorker(MapPrx& mprx) : GenericWorker(mprx)
{
  
  connect(Start, SIGNAL(clicked()), this, SLOT(iniciar()));
  connect(Stop, SIGNAL(clicked()), this, SLOT(parar()));
  connect(&clk, SIGNAL(senal()), this, SLOT(reloj()));
  clk.setseg(1000);
  scene =  new QGraphicsScene();
  Grafico->setScene(scene);
  cont=0;
  startbutton=false;
  giro=false;
  rot=1.2;
  clk.start();

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

int SpecificWorker::getvelocidadl(float distmin,int velomax, float dist){
  	if(dist<distmin){
	      return velomax*tanh(dist/distmin);
	}
	else
	      return velomax;
}
float SpecificWorker::getvelocidadg(float velmaxg, float angle, int dismax, int dis){
	if(dis<dismax)
	{
	    float resul;
	    float aux=M_PI*angle*angle;
	    resul = 1+velmaxg*(pow(EulerC,-(aux)));	      
	    if (angle>0&&!giro)
	      resul=-resul;
	    return resul;
	}
	else return 0;
}
int SpecificWorker::getdistmin(int dismax,float angle){
	float aux=M_PI*angle*angle;
	return 350+dismax*(pow(EulerC,-(aux)));
}

void SpecificWorker::compute()
{
    if(startbutton){
	const float threshold = 400; //millimeters
	const int velmax=350;	//velocidad maxima del robot
	const int cota=16;  //cota de vision
	const float velmaxg=2.2;
	const int distsecurity=440;
	int sentido=M_PI-0.6;
	try
	{
	    RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data
	    if((ldata.data()+cota)->dist<distsecurity&&((ldata.data())+100-cota)->dist<distsecurity){
	      writeinfo("¡¡¡Esquina!!!");
	      differentialrobot_proxy->setSpeedBase(-400, 0); 
	      usleep(1000000);
	      RoboCompLaser::TLaserData ldata2 = laser_proxy->getLaserData();  //read laser data
	      if(ldata2.data()->dist>(ldata2.data()+99)->dist)
		sentido=-sentido;
	      differentialrobot_proxy->setSpeedBase(0, (sentido));
	      usleep(1000000);
	      giro=false;
	    }
	    else{
		  std::sort( ldata.begin()+cota, ldata.end()-cota, [](RoboCompLaser::TData a, RoboCompLaser::TData b){ return (a.dist < b.dist); }) ;  //sort laser data from small to $
		  
		  float distaux=(ldata.data()+cota)->dist;
		  float angle=(ldata.data()+cota)->angle;
		  
		  int distmax=getdistmin(threshold,angle);
		  rot=getvelocidadg(velmaxg,angle,distmax,distaux);
		  int vel=getvelocidadl(distmax,velmax,distaux);
		  if(rot<0)
			giro=false;
		  if((ldata.data()+cota)->dist<distmax)
			differentialrobot_proxy->setSpeedBase(vel, rot);
		  else{
		      cont++;
		      if (cont==200){
			  rot=rand()%100 -6;
			  differentialrobot_proxy->setSpeedBase(vel, rot/10);
			  usleep(rand()%(250000));
			  cont=0;
		      }
		      else
			differentialrobot_proxy->setSpeedBase(vel, 0);
			
		  }
		  writeinfo("Velocidad lineal = "+to_string(vel));
		  writeinfo("Velocidad de rotacion = "+to_string(rot));
	    }
	TBaseState state;
	differentialrobot_proxy->getBaseState(state);
	
	scene->addRect(state.z/10,state.x/10,40,40,QPen(Qt::black),QBrush(Qt::black));
	}
	catch(const Ice::Exception &ex)
	{
	    writeinfo("ex");
	}
    }
}
void SpecificWorker::reloj()
{
  static int seg=1;
  static int min=1;
  static int hor=1;
  if(startbutton){
    if(seg<60){
      LCDseg->display(seg++);
    }
    else if(seg==60&&min<60){
      seg=0;
      LCDseg->display(seg);
      LCDmin->display(min++);
    }
    else {
      seg=0;
      min=0;
      LCDseg->display(seg);
      LCDmin->display(min);
      LCDhor->display(hor++);
      
    }
  }
}

void SpecificWorker::iniciar()
{
    startbutton=true;
}
void SpecificWorker::parar()
{
    startbutton=false;
    differentialrobot_proxy->setSpeedBase(0, 0);
}
void SpecificWorker::writeinfo(string _info)
{	
    QString *text=new QString(_info.c_str());
    InfoText->append(*text);
    
}



