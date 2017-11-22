#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <iostream>
#include <onion-i2c.h>
#include <ugpio/ugpio.h>//include this class!!!
//check the boost class
using namespace std;
bool checkGPIO(int pin);

bool checkGPIO(int gpioPin) {
	int checkGPIOIsUsed = gpio_is_requested(gpioPin);//check if being used and returns -1 if it is.
	int pinDirection = gpio_request(gpioPin, NULL);//returns -1 if pin value could not be set.
	if(checkGPIOIsUsed < 0){
		cerr << "GPIO pin " << gpioPin << " is being used. Please select another pin" << endl;
		return false;
	} else {
		cout << "Reading GPIO pin #" << gpioPin << endl;
		if(pinDirection < 0){
			cerr << "There was an error setting the pin value" << endl;
			return false;
		}
	}
	return true;
}

int main(){
	int gpioPin = 1;
	int value;
	int pinDirection;

	if (!checkGPIO(gpioPin)) {
		return -1;
	}
	pinDirection = gpio_direction_input(gpioPin);


	for(int index = 0; index < 10; index++){
		value = gpio_get_value(gpioPin);//gets the value of the gpiopin it reads 1 if theres voltage, zero if there is not
		cout << "Value: " << value << endl;
		sleep(0.5); //stall for one second
	}

	gpio_free(gpioPin);//unsetsthe gpio pin so tht it is off
	
	
	if (!checkGPIO(gpioPin)){
		return -1;
	}
	pinDirection = gpio_direction_output(gpioPin, 1); //et pin from input to output
	
	for (int n=0; n<10; n++){
		sleep(1);
		pinDirection=gpio_set_value(gpioPin, 1); //turns the pin on
		sleep(1);
		pinDirection=gpio_set_value(gpioPin, 0); //turns it off
	}
	gpio_free(gpioPin);//unsetsthe gpio pin so tht it is off
	return 0;
}