#ifndef __INTRUDERSENSOR_H
#define __INTRUDERSENSOR_H

#include "atomic.h"

class IntruderSensor : public Atomic {
public:
	IntruderSensor( const string &name = "IntruderSensor" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	const Port &out;
	Time preparationTime;

};

inline string IntruderSensor::className() const
{
	return "IntruderSensor" ;
}
#endif
