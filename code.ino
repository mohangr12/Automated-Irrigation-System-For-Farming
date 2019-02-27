#include <SoftwareSerial.h>
SoftwareSerial BTserial(6, 7); //RX | TX

int sensor_pin = A0;
//define the analog pin to which the soil moisture sensor is connected
int motor = 13;
//define the digital pin to which dc water pump is to be connected
int tx = 7;
//define the transmitter pin
int rx = 6;
//define the receiver pin
int output_value ;
char output_value_str ;
//integer to store the output value of soil moiture sensor
const int analogOutPin = 1; 
//set analog output pin to pin 1
int threshold = 800;
//set the threshold value = 800
int current_value;
//integer to store current value of soil moisture sensor reading
int ones; int tens;
void setup() 
//void setup runs once
{
   Serial.begin(9600);
   //begin serial communication at baud rate 9600
   Serial.println("Reading From the Sensor ...");
   //print that readin from soil moisture sensor has begun
   pinMode(motor, OUTPUT);
   //set motor pin as OUPUT
   pinMode(tx, OUTPUT);
   //set transmitter pin as OUTPUT
   pinMode(rx, INPUT);
   //set receiver pin as OUTPUT
   delay(2000);
   //create a delay of 2s
   BTserial.begin(9600);
   }

void loop() 
//void loop runs continuously
{
   output_value= analogRead(sensor_pin);
   //read the value of soil moisture sensor and store it in output_value 
   current_value = output_value;
   //set current_value equal to output_value
   output_value= constrain(output_value,10,1023); 
   //set the contrain on output_value. Minimum = 10 Maximum = 1023 
   output_value= map(output_value,10,1023,150,0); 
   //map the output_value
   analogWrite(analogOutPin, output_value); 
   //send the output_value to transmitter pin
   BTserial.write("Moisture : ");
   //print Moisture:
   ones = output_value%10;
   tens = output_value/10;
   ones = ones + 48;
   tens = tens + 48;
   BTserial.write(tens);
   BTserial.write(ones);
   //print the output_value
   BTserial.write("%");
   //print %
   if(current_value >=threshold)
   //check if current_value >= 800
   {
    //if yes then
    BTserial.println("water level low... turning water pump on..");
    //print water level low.. turning water pump on..
    digitalWrite(motor,HIGH);
    //turn on the dc water pump
   }
   else
   {
    //if no then
    BTserial.println("Water level high... turning water pump off");
    //print water leve high.. turning water pump off..
    digitalWrite(motor,LOW);
    //turn off the dc water pump
   }
   delay(3000);
   //create a delay of 3 second
}
