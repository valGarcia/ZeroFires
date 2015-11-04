# ZeroFires
Code for a device that senses when a large scale composting pile is at a high risk of combustion and sends out a tweet through twitter account @zerofires
Arduino based
Sensors:
  humidity
  temperature
  air alcohol content
  fire sensor
Sends data to a thingspeak account through wifi101 shield in real time. Sends a tweet when threshholds are met: high temperature, lots of methane, low humidity, FIRE.
