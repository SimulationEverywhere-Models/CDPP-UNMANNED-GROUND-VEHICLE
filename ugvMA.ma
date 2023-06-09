[top]
components : mc1@MainComputer
components : is1@IntruderSensor
components : hs1@HeadingSensor
components : WheelAssembly

in :  inputHeading intruder 

out : status leftWheel rightWheel

Link : inputHeading inputHeading@mc1
Link : intruder in@is1
Link : out@is1 intruder@mc1
Link : turningPort@mc1 in@hs1
Link : out@hs1 heading@mc1
Link : status@mc1 status
Link : turnLeft@mc1 leftWheel
Link : turnRight@mc1 rightWheel
Link : turnLeft@mc1 turnLeft@WheelAssembly
Link : turnRight@mc1 turnRight@WheelAssembly

[mc1]
preparation : 00:00:01:000

[is1]
preparation : 00:00:01:000

[hs1]
preparation : 00:00:01:000

[WheelAssembly]
components : ws1@WheelSet
components : ws2@WheelSet

in : turnLeft turnRight
out : leftWheel rightWheel

Link : turnLeft in@ws1
Link : turnRight in@ws2
Link : out@ws1 leftWheel
Link : out@ws2 rightWheel

[ws1]
preparation : 00:00:01:000

[ws2]
preparation : 00:00:01:000