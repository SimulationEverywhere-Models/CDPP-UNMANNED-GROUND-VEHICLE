#ifndef __MAINCOMPUTER_H
#define __MAINCOMPUTER_H

#include "atomic.h"

class MainComputer : public Atomic {
public:
	MainComputer( const string &name = "MainComputer" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &turnLeft;
	Port &turnRight;
	const Port &heading;
	const Port &intruder;
	const Port &inputHeading;
	Port &turningPort;
	Port &status;
	double currentHeading;
	double setpoint;
	int turning;
	bool alarm;
	bool brakes;
	Time preparationTime;

};

inline string MainComputer::className() const
{
	return "MainComputer" ;
}

#endif
