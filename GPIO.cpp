#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <ugpio/ugpio.h>//include this class!!!
//check the boost class
using namespace std;

int main(){

	int gpioPin = 1;
	int value;
	int checkGPIOIsUsed = gpio_is_requested(gpioPin);//check if being used and returns -1 if it is.
	int pinDirection = gpio_request(gpioPin, NULL);//returns -1 if pin value could not be set.



//starts reading the GPIO pin
	if(checkGPIOIsUsed < 0){
		cerr << "GPIO pin " << gpioPin << " is being used. Please select another pin" << endl;
		return -1;
	}
	else{
		cout << "Reading GPIO pin #" << gpioPin << endl;
		if(pinDirection < 0){
			cerr << "There was an error setting the pin value" << endl;
			return -1;
		}
	}

	pinDirection = gpio_direction_input(gpioPin);


	for(int index = 0; index < 20; index++){
		value = gpio_get_value(gpioPin);//gets the value of the gpiopin it reads 1 if theres voltage, zero if there is not
		cout << "Value: " << value << endl;
		sleep(1); //stall for one second
	}

	gpio_free(gpioPin);//unsetsthe gpio pin so tht it is off
	return 0;
}