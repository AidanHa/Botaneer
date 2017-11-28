#include <stdio.h>
#include<math.h>
#include<limits.h>
#include <unistd.h>
#include <fcntl.h>    
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ugpio/ugpio.h>
using namespace std;


enum stream {INPUT, OUTPUT};
enum Plant{CACTUS = 1, EVERGREEN = 2, SHRUB = 3, ORIENTAL = 4, LEAF = 5, FRUIT = 6,  MOSS = 7, TROPICAL = 8};
bool logInfo(int fatal, int start) {//FILEWRITE need timestap, severity tag, description
    ofstream ofile;
    ofile.open("log.txt", std::ios_base::app | std::ios_base::out);
    ofile <<endl;
    if (!ofile.is_open()){
        return -1;
    }
    if (start == 1) {//writes this at the begining of the file
        ofile << "Start of botaneer.cpp" << endl;
    }
    if (fatal == 1) { // writes this if theres an error;
        ofile << "A fatal error occurred." << endl;
    } else {
        ofile << "No Error" << endl;   
    }
    ofile.close();
    return true;
}
bool stringToInt(const char input[], int& value) {
	int sign = 0;
	int digits = 0;
	value = 0;
	
	for (int i = 0; input[i] != 0 ; i++){
		digits++;
	}
	
	if (input[0] == 43 || input[0] == 45){
		sign = 1;
	}
	
	if(digits - sign > 10){	// digits = index - sign Too many digits, will overflow.
		return false;
	}
	
	for (int i = sign; input[i] != 0 && i < digits + sign ; i++){
		switch (input[i]){
		case 48:
			if (0 * pow(10,digits - i - 1)- sign > INT_MAX - value){
				return false;
			}
			value += 0 * pow(10,digits - i - 1);
			break;
		case 49:
			if (1 * pow(10,digits - i - 1) - sign > INT_MAX - value){
				return false;
			}
			value += 1 * pow(10,digits - i - 1);
			break;
		case 50:
			if (2 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 2 * pow(10,digits - i - 1);
			break;
		case 51:
			if (3 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 3 * pow(10,digits - i - 1);
			break;
		case 52:
			if (4 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 4 * pow(10,digits - i - 1);
			break;
		case 53:
			if (5 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 5 * pow(10,digits - i - 1);
			break;
		case 54:
			if (6 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 6 * pow(10,digits - i - 1);
			break;
		case 55:
			if (7 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 7 * pow(10,digits - i - 1);
			break;
		case 56:
			if (8 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 8 * pow(10,digits - i - 1);
			break;
		case 57:
			if (9 * pow(10,digits - i - 1) - sign> INT_MAX - value ){
				return false;
			}
			value += 9 * pow(10,digits - i - 1);
			break;	
		default:
			return false;
			break;
		}
	}

	if (sign == 1 && input[0] == 45){
		value *= (-1);
	}
	return true;
}
//Allocate pin to be used +set its stream, return true if successful, false if unable to allocate.
bool initializePin(int pinNumber, stream direction ){
    
    gpio_request(pinNumber, NULL);                              // Allocate the pin.
    int checkGPIOIsUsed = gpio_is_requested(pinNumber);//check if being used and returns -1 if it is.
    if(checkGPIOIsUsed < 0){
        cerr << "GPIO pin " << pinNumber << " is being used. Please select another pin" << endl;
        logInfo(1,0);
        return false;
    }
    if (direction == INPUT){                            // Set direction of the pin.
        gpio_direction_input(pinNumber);
    }
    else if (direction == OUTPUT){
        gpio_direction_output(pinNumber,0);
    }
    
    return true;
}
// Gets the pin's current logic level. Returns: 1 - High, Returns: 0 - Low, Returns: -1 - Error
int getPin(int pinNumber){

    return gpio_get_value(pinNumber);   
}
// Sets the logic level of a pin. Returns: True if successful, Returns: False if unable to set logic level. 
bool setPin(int pinNumber, int state){
    
    if (gpio_get_direction(pinNumber) != GPIOF_DIR_OUT || gpio_get_direction(pinNumber) == -1){
        return false;   // Pin is not an output pin. Or had trouble getting direction.
    }
    
    gpio_set_value(pinNumber, state);
    
    return true;
}

// Deallocates the pin and makes it available for other use.
void cleanPin(int pinNumber){

    gpio_free(pinNumber);                               // Deallocate the pin.
}



bool waterPlant(int humidity, int temperature, const int humidityCap, const int temperatureCap) {
    return true;
}


int main() {
    int gpioPin = 1;
    int value;
    int pinDirection;
    int humidity;
    int typeOfPlant;
    int humidityCap;
    int temperatureCap;
    Plant chosenPlant = CACTUS;

    cout << "Please enter a number according to the plant you wish to use the botaneer on:"  << endl;
    cout << "1 for a cactus" << endl;
    cout << "2 for an evergreen plant" << endl;
    cout << "3 for a shrub" << endl;
    cout << "4 for an oriental plant" << endl;
    cout << "5 for a leaf plant" << endl;
    cout << "6 for a  fruit plant" << endl;
    cout << "7 for a moss plant" << endl;
    cout << "8 for a tropical plant" << endl;
    
    cin >> typeOfPlant;
    
    switch(typeOfPlant) {
        case 1:
            chosenPlant = CACTUS;
            break;
        case 2:
            chosenPlant = EVERGREEN;
            break;
        case 3:
            chosenPlant = SHRUB;
            break;
        case 4:
            chosenPlant = ORIENTAL;
            break;
        case 5:
            chosenPlant = LEAF;
            break;
        case 6:
            chosenPlant = FRUIT;
            break;
        case 7:
            chosenPlant = MOSS;
            break;
        case8:
            chosenPlant = TROPICAL;
            break;
        default:
            cout << "Not a valid input! The program will now exit." << endl;
            logInfo(1,0);
            return -1;  

    }
  //  int tmp=0;	
    while (true){
        initializePin(gpioPin,OUTPUT); // try setting buffer array size to 3/4 
        char buffer[10];
        int fd=open("/dev/ttyS1", O_RDONLY);
        int bytes_read;
        int k = 0;
        //read reads up to count bytes (1 in this case) from file descriptor fd into buffer starting at buff.
        // read byte by byte (1 char = 1 byte) - 0 - 255 can be read
        for (int n=0;n<3;n++){
        char t = 0;
        bytes_read = read(fd, &t, 2);  
   //	cout<<t<<endl;
        buffer[k++] = t; 
   //	cout<<buffer[n]<<endl;   
        if(t == '\n' || t == '\0') {
            n=3;
        }
	}
	   bytes_read=0;
	   int close(fd);
        //buffer[3]=0; .//maybe append an end
        stringToInt(buffer,humidity);
//	if (humidity ==0 && tmp != 0){
//	    humidity=tmp;
//	}
        cout <<humidity<<endl;
        if (humidity<400 && humidity!=0){
            setPin(gpioPin,1);
         //   cout << getPin(1) << endl; //ON
            sleep(3);
            setPin(1,0);
         //   cout << getPin(1) << endl; //OFF
            sleep(3);
            cleanPin(1);
        }
	else{
	sleep(6);
	}
//    tmp=humidity;
    }
    return 0;
}


/**
    pinDirection = gpio_direction_input(gpioPin);

    for(int index = 0; index < 10; index++){
        value = gpio_get_value(gpioPin);//gets the value of the gpiopin it reads 1 if theres voltage, zero if there is not
        cout << "Value: " << value << endl;
        sleep(1); //stall for one second
    }
    gpio_free(gpioPin);//unsetsthe gpio pin so tht it is off

   pinDirection = gpio_direction_output(gpioPin, 1); //et pin from input to output
    
    for (int n=0; n<10; n++){
        sleep(1);
        pinDirection=gpio_set_value(gpioPin, 1); //turns the pin on
        sleep(1);
        pinDirection=gpio_set_value(gpioPin, 0); //turns it off
    }
    if (!logInfo(0, 1)) {
        return -1;
    }
    gpio_free(gpioPin);//unsetsthe gpio pin so tht it is off
    return 0;
*/
