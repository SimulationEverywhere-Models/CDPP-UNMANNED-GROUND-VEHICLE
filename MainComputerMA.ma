[top]
components : mc1@MainComputer
in : heading inputHeading intruder

out : status turningPort turnLeft turnRight


Link : heading heading@mc1
Link : inputHeading inputHeading@mc1
Link : intruder intruder@mc1

Link : status@mc1 status
Link : turningPort@mc1 turningPort
Link : turnLeft@mc1 turnLeft
Link : turnRight@mc1 turnRight




[mc1]
preparation : 00:00:01:000