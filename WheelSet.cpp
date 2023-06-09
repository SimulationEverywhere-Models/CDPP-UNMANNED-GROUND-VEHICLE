/**
 * Daanish Khan
 * 100621354
 */
#include "WheelSet.h"
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

WheelSet::WheelSet( const string &name ) :   Atomic ( name ) ,
in( addInputPort("in")),
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
Model &WheelSet::initFunction()
{
	this-> passivate();
	acti = 0; //Disable the wheels and set velocity to 0
	velocity = 0.0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description:
********************************************************************/
Model &WheelSet::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{

		double tvel = static_cast < double > (msg.value());
		if (tvel == 0.0) {
			acti = 0;
			velocity = 0.0;
		}
		else {
			acti = 1;
			velocity = tvel;
		}
		holdIn( active, preparationTime );
	}

	return *this;
}
/*******************************************************************
* Function Name: internalFunction
* Description:
********************************************************************/
Model &WheelSet::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description:
********************************************************************/
Model &WheelSet::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), out, velocity) ;
	return *this ;
}
