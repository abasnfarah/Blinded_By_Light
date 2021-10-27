# Blinded By The Light


This is the code base for our project Blinded By the Light. 
We are using a Pic24fjga002 microcontroller to display a signal from a photodiode.
The Photodiode signal is a current source. To convert this current source we are utilizing a transresistant op-amp
with a gain of 1M. The input source is on order of 0 to 4 microAmps. Our ouput from our op-amp is on 
order of 0 to 4 volts. The input from the op-amp is fed into a analog to digial converter to send a digital signal 
to our microcontroller. The microcontroller ouputs the value on a display.
