/**
 * Daanish Khan
 * 100621354
 */
#include "HeadingSensor.h"
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

HeadingSensor::HeadingSensor( const string &name ) :   Atomic ( name ) ,
in( addInputPort("in")),
path( addInputPort("path")),
out( addOutputPort("out")),
preparationTime(0,0,1,0){

	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &HeadingSensor::initFunction()
{
	this->holdIn(active, Time::Zero); //Immediately activate the heading sensor
	turning = heading = 0; //The heading is zero and the setpoint is zero to begin with
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &HeadingSensor::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{
		turning = static_cast <int>(msg.value());
	}
	if (msg.port() == path)
	{
		//string temp = static_cast <string>(msg.value());
		//'*********| |**********'
	}
	holdIn(active, Time::Zero);
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &HeadingSensor::internalFunction( const InternalMessage & )
{
	if (turning == 1) {
		//We are artificially changing our heading here
		//Note: In real life, the heading sensor would sense the heading using a compass
		//Change the heading by 1 degree
		if (heading == 359.0){ heading = 0.0;}
		else {heading = heading + 1.0;}
		holdIn(active, preparationTime);
	}
	else if (turning == -1) {
		if (heading == 0.0){ heading = 359.0;}
		else {heading = heading - 1.0;}
		holdIn(active, preparationTime);
	}
	else if (turning == 0){
		heading = heading; //Don't change heading: REDUNDANT (REMOVE IN FINAL)
		holdIn(active, preparationTime);
	}
	else {
		passivate();
	}
	//NEED TO PASSIVATE OR HOLDIN
	//Time t("00:00:01:000");

	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &HeadingSensor::outputFunction( const InternalMessage &msg )
{
	//sendOutput( msg.time(), out, ) ;
	sendOutput(msg.time(), out, heading);

	return *this ;
}
