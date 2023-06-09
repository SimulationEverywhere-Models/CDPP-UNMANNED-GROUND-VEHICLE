#ifndef __HEADINGSENSOR_H
#define __HEADINGSENSOR_H

#include "atomic.h"

class HeadingSensor : public Atomic {
public:
	HeadingSensor( const string &name = "HeadingSensor" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	const Port &path;
	Port &out;
	Time preparationTime;
	int turning; //-1 turn left 0 don't turn 1 turn right
	double heading;
};

inline string HeadingSensor::className() const
{
	return "HeadingSensor" ;
}

#endif
