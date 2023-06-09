/**
 * Daanish Khan
 * 100621354
 */
#include "MainComputer.h"
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

MainComputer::MainComputer( const string &name ) :   Atomic ( name ) ,
turnLeft(addOutputPort("turnLeft")),
turnRight(addOutputPort("turnRight")),
heading(addInputPort("heading")),
intruder(addInputPort("intruder")),
status(addOutputPort("status")),
inputHeading(addInputPort("inputHeading")),
turningPort(addOutputPort("turningPort")),
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
Model &MainComputer::initFunction()
{
	this-> passivate();
	alarm=false;
	brakes= false;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &MainComputer::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == heading )
	{
		currentHeading = static_cast <double>(msg.value());

	}
	if ( msg.port() == inputHeading)
	{
		if (static_cast <double>(msg.value()) == 9999) {
			//stop!
			brakes = true;
		}else if (static_cast <double>(msg.value()) >= 0 && static_cast <double>(msg.value()) <= 360){
			setpoint = static_cast <double>(msg.value());
			brakes = false;
		}

	}
	if ( msg.port() == intruder ) {
		alarm = true;

	}
	if (currentHeading != setpoint) {
		double cldist;//= setpoint - currentHeading; //Clockwise & counter clockwise distances
		double ccldist;// = currentHeading - setpoint + 360;
		cldist = currentHeading - setpoint;
		if (cldist >= 360) { cldist -= 360;}
		if (cldist <= -360) {cldist += 360;}
		if (cldist < 0) {
			ccldist = -1 * cldist;
			cldist = 360 - ccldist;
		}
		else {
			ccldist = 360 - cldist;
		}

		if (cldist <= ccldist) {
			//i.e setpoint @ 179 current @ 0
			//i.e. setpoint @ 5 current @ 359
			// turn clockwise
			turning = -1;
		}
		else {
			//turn counterclockwise
			turning = 1;
		}
	}
	else {
		turning = 0; //Not turning
	}
	holdIn(active, preparationTime);
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &MainComputer::internalFunction( const InternalMessage & )
{

	passivate();
	//holdIn(active, preparationTime);
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &MainComputer::outputFunction( const InternalMessage &msg )
{
	//sendOutput( msg.time(), out, "IntruderDetected") ;
	if (alarm) {
		sendOutput(msg.time(), status, 9999);
	}
	else {
		sendOutput(msg.time(), status, currentHeading);
	}
	sendOutput(msg.time(), turningPort, turning);
	if (turning == 1 && !brakes) {
		sendOutput(msg.time(), turnRight, 1);
		sendOutput(msg.time(), turnLeft, 0);
	}
	else if (turning == -1 && !brakes) {
		sendOutput(msg.time(), turnLeft, 1);
		sendOutput(msg.time(), turnRight, 0);
	}
	else if (!brakes) {
		sendOutput(msg.time(), turnLeft, 1);
		sendOutput(msg.time(), turnRight, 1);
	}
	else {
		sendOutput(msg.time(), turnLeft, 0);
		sendOutput(msg.time(), turnRight, 0);
	}


	return *this ;
}
