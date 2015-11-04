# ZeroFires
Code for a device that senses when a large scale composting pile is at a high risk of combustion and sends out a tweet through twitter account @zerofires (https://twitter.com/ZeroFires)
Arduino based
Sensors:
  humidity
  temperature
  air alcohol content
  fire sensor
Sends data to a thingspeak account (https://thingspeak.com/channels/63370) through wifi101 shield in real time. Sends a tweet when threshholds are met: high temperature, lots of methane, low humidity, FIRE.
This project is still a work in progress, functionality is not complete
