/**
 * Daanish Khan
 * 100621354
 */
#include "IntruderSensor.h"
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

IntruderSensor::IntruderSensor( const string &name ) :   Atomic ( name ) ,
in( addInputPort("in")), //An intruder is sensed on port in
out( addOutputPort("out")),
preparationTime(0,0,10,0){

	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &IntruderSensor::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &IntruderSensor::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{
		if (static_cast <double>(msg.value()) <= 360 && static_cast <double>(msg.value()) >= 0) {
			holdIn( active, preparationTime );
		}
		else {
				passivate();
			}
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &IntruderSensor::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &IntruderSensor::outputFunction( const InternalMessage &msg )
{
	//if ((double)rand() / (double) RAND_MAX  < 0.95) {
		//TODO:  RECODE THIS
	//}
	 sendOutput(msg.time(), out, 1);
	return *this ;
}
