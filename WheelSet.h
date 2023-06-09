#ifndef __WHEELSET_H
#define __WHEELSET_H

#include "atomic.h"

class WheelSet : public Atomic {
public:
	WheelSet( const string &name = "WheelSet" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	Time preparationTime;
	int acti;
	double velocity;

};

inline string WheelSet::className() const
{
	return "WheelSet" ;
}

#endif
