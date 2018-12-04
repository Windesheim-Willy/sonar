#include <ros.h>
#include <sensor_msgs/Range.h>
#include <ros/time.h>

//define sonar signal ports for easy configuration
#define first_sonar_sensor    3
#define second_sonar_sensor   4
#define third_sonar_sensor    5
#define fourth_sonar_sensor   6
#define fifth_sonar_sensor    7

#define sixth_sonar_sensor    8
#define seventh_sonar_sensor  9
#define eight_sonar_sensor    10
#define nineth_sonar_sensor   11
#define tenth_sonar_sensor    12

//function definition
float get_measure_from(int digitalport);
void sort(float a[], float size);


//declare ros nodehandler, message and publisher
ros::NodeHandle nh;
sensor_msgs::Range message;
ros::Publisher sonar("sonar", &message);

void setup()
{
  pinMode(first_sonar_sensor, OUTPUT);
  pinMode(second_sonar_sensor, OUTPUT);
  pinMode(third_sonar_sensor, OUTPUT);
  pinMode(fourth_sonar_sensor, OUTPUT);
  pinMode(fifth_sonar_sensor, OUTPUT);
  pinMode(sixth_sonar_sensor, OUTPUT);
  pinMode(seventh_sonar_sensor, OUTPUT);
  pinMode(eight_sonar_sensor, OUTPUT);
  pinMode(nineth_sonar_sensor, OUTPUT);
  pinMode(tenth_sonar_sensor, OUTPUT);
  //init ros node and advertise the publisher
  nh.initNode();
  nh.advertise(sonar);
}

char frameid[] = "/us_ranger";

void loop()
{
  //get sonar values, we read the sonar in the following way
  //so there wont be any overlap in ultrasonic bursts
  float distance_sonar_one = get_measure_from(first_sonar_sensor);
  float distance_sonar_three = get_measure_from(third_sonar_sensor);
  float distance_sonar_five = get_measure_from(fifth_sonar_sensor);
  float distance_sonar_seven = get_measure_from(seventh_sonar_sensor);
  float distance_sonar_nine = get_measure_from(nineth_sonar_sensor);

  //delay(5);

  float distance_sonar_two = get_measure_from(second_sonar_sensor);
  float distance_sonar_four = get_measure_from(fourth_sonar_sensor);
  float distance_sonar_six = get_measure_from(sixth_sonar_sensor);
  float distance_sonar_eight = get_measure_from(eight_sonar_sensor);
  float distance_sonar_ten = get_measure_from(tenth_sonar_sensor);

  //add sonar values to message object and publish message
  float ech[10] = {1.0, 2.0, 4.8, 7.0, 6.7, 3.8, 9.0, 0.1, 8.9, 6.0};

  //float ech[10] = {distance_sonar_one ,distance_sonar_two, distance_sonar_three,
  //               distance_sonar_four, distance_sonar_five, distance_sonar_six,
  //               distance_sonar_seven, distance_sonar_eight, distance_sonar_nine,
  //               distance_sonar_ten};               
  
  sort(ech,10); //Pass in the values and the size.

  
	    message.header.stamp = nh.now();
      message.range = ech[0];
      message.radiation_type = sensor_msgs::Range::ULTRASOUND;
      message.header.frame_id =  frameid;
      message.field_of_view = 0.01;
      sonar.publish(&message);
      nh.spinOnce();
//  delay(10);
}

//return the measured distance of a connected Parallax Ping Ultrasonic Sensor in centimetres
float get_measure_from(int digitalport)
{
  //set pin as output so we can send a pulse
  pinMode(digitalport, OUTPUT);

  //set output to LOW
  digitalWrite(digitalport, LOW);
  delayMicroseconds(5);

  //send a 5uS pulse out to activate the sensor
  digitalWrite(digitalport, HIGH);
  delayMicroseconds(5);
  digitalWrite(digitalport, LOW);

  //change the digital pin to input to read the incoming pulse
  pinMode(digitalport, INPUT);

  //measure the length of the incoming pulse
  unsigned long pulseduration = pulseIn(digitalport, HIGH);

  //divide the pulse length by half
  pulseduration = pulseduration / 2;

  //convert to centimetres and return the value
  return float(pulseduration / 29);
}

void sort(float a[], float size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[o] > a[o+1]) {
                    int t = a[o];
                    a[o] = a[o+1];
                    a[o+1] = t;
                }
        }
    }
}
