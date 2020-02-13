# BinaryLEDClock
This project runs on an arduino uno
The Clock works with 15 leds representing the second, minute, and hour in binary.
"On" represents 1 and "Off" represents 0.
6 LEDs Represent the seconds
6 LEDs Represent the minutes
3 LEDs Represent the hours
The hour is represented by 3 LEDs which means we can represent hours 0 through 7. Thus, the 24 hour day is divided into three, eight-hour periods. The user must infer what "third" of the day it is. For example, if the sun is setting and the hour LEDs are reading 001, chances are that the day is in the last three hour period. Thus, the hour is 17 or 5 PM.