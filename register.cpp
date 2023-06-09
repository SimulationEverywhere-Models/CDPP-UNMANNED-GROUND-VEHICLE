/*********************************
 * Register.cpp
 * Daanish Khan
 * 100621354
 *
 * This module registers all the simulation components
 */

//TODO: Add model stuff

#include "modeladm.h"
#include "mainsimu.h"
#include "HeadingSensor.h"
#include "IntruderSensor.h"
#include "MainComputer.h"
#include "WheelSet.h"
void MainSimulator::registerNewAtomics()
{
	//SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<IntruderSensor>(), "IntruderSensor" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<MainComputer>(), "MainComputer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<IntruderSensor>(), "IntruderSensor" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<HeadingSensor>(), "HeadingSensor" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<WheelSet>(), "WheelSet" ) ;
	//SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<WheelSet>(), "WheelSet" ) ;

}
