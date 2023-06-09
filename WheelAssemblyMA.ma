[top]
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