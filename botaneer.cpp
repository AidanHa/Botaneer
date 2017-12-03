#include <stdio.h>
#include<math.h>
#include<limits.h>
#include <unistd.h>
#include <fcntl.h>    
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <ugpio/ugpio.h>

using namespace std;
//struct declaration
struct Statistics {
	int   minimumHum;
	float averageHum;
	int   maximumHum;
	float popStdDevHum;
	float smplStdDevHum;
	
	int   minimumTemp;
	float averageTemp;
	int   maximumTemp;
	float popStdDevTemp;
	float smplStdDevTemp;
};
struct Dataset {
	int* humArray;
	int* tempArray;
};
//funciton declaration
bool logInfo(char* string);
bool logInt(int value);
bool logFloat(float value);
bool stringToInt(const char input[], int& value);
int computeStatistics(float datasetHum[], int datasetHum1[], float datasetTemp[], int datasetTemp1[], Statistics& stats, int SWconstant);
int minimum(int dataset[], int size);
float average(float dataset[], int size);
int maximum(int dataset[], int size);
float popStdDev(float dataset[], int size);
float smplStdDev(float dataset[], int size);
//enum declaration
enum stream {INPUT, OUTPUT};

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
int computeStatistics(float datasetHum[], int datasetHum1[], float datasetTemp[], int datasetTemp1[], Statistics& stats, int SWconstant) {
	//sets the values of the stats here using objects!!!!
	stats.minimumHum = minimum(datasetHum1, SWconstant);
	stats.minimumTemp = minimum(datasetTemp1, SWconstant);
	stats.maximumHum = maximum(datasetHum1, SWconstant);
	stats.maximumTemp = maximum(datasetTemp1, SWconstant);
	stats.averageHum = average(datasetHum, SWconstant);
	stats.averageTemp = average(datasetTemp, SWconstant);
	stats.popStdDevHum = popStdDev(datasetHum, SWconstant);
	stats.popStdDevTemp = popStdDev(datasetTemp, SWconstant);
	stats.smplStdDevHum = smplStdDev(datasetHum, SWconstant);
	stats.smplStdDevTemp = smplStdDev(datasetTemp, SWconstant);
	return 0;
}
int minimum(int dataset[], int size) {
	int minimum;
	for (int i = 0; i < size; i++ ) {
		if (i == 0){
			minimum = dataset[i];
		}
		if (dataset[i] < minimum) {
			minimum = dataset[i];
		}
	}
	return minimum;
}
float average(float dataset[], int size) {
	float average = 0;
	for (int i = 0; i < size; i++) {
		average += dataset[i];
	}
	return (average/size);
}
int maximum(int dataset[], int size) {
	int maximum;
	for (int i = 0; i < size; i++ ) {
		if (i == 0) {
			maximum = dataset[i];
		} 
		if (dataset[i] > maximum) {
			maximum = dataset[i];
		}
	}
	return maximum;
}
float popStdDev(float dataset[], int size) {
	float avg = average(dataset, size);
	float dev = 0;
	for (int i = 0; i < size; i++) {
			dev += (dataset[i]-avg) * (dataset[i]-avg);
		}
	return (sqrt(dev / size));
}
float smplStdDev(float dataset[], int size) {
	float avg = average(dataset, size);
	float dev = 0;
	for (int i = 0; i < size; i++) {
			dev += (dataset[i]-avg) * (dataset[i]-avg);
		}
	return (sqrt(dev / (size - 1)));
}
class Botaneer {	
	public:
		bool waterPlant(int humidity, int humidityCap);
		bool tempOverexceed(int temperature, int temperatureCapMin, int temperatureCapMax);
		void setHumiditycap(int newCap);
		void setTempCapMin(int newCap);
		void setTempCapMax(int newCap);
		int getHumidityCap();
		int getTempCapMin();
		int getTempCapMax();
		Botaneer();//constructors
		Botaneer(int, int, int);
		
		~Botaneer();
	private:
		int temperature;
		int humidity;
		int temperatureCapMin;
		int temperatureCapMax;
		int humidityCap;
};
Botaneer::Botaneer() {//constructor
	temperature = 25;
	humidity = 850;
	temperatureCapMin = 20;
	temperatureCapMax = 40;
	humidityCap = 800;
}
Botaneer::Botaneer(int humCap, int tempCapMin, int tempCapMax) {//constructor
	temperature = 25;
	humidity = 850;
	temperatureCapMin = tempCapMin;
	temperatureCapMax = tempCapMax;
	humidityCap = humCap;
}
Botaneer::~Botaneer() {
	logInfo((char*)"end of Botaneer program");
}
bool Botaneer::waterPlant(int humidity, int humidityCap) {
	if (humidity < humidityCap) {
		return true;
	}
	return false;
}
bool Botaneer::tempOverexceed(int temperature, int temperatureCapMin, int temperatureCapMax) {
	if (temperature < temperatureCapMax && temperature > temperatureCapMin) {
		return true;
	}
	return false;
}
void Botaneer::setHumiditycap(int newCap) {
	humidityCap = newCap;
}
void Botaneer::setTempCapMin(int newCap) {
	temperature = newCap;
}
void Botaneer::setTempCapMax(int newCap) {
	
	temperature = newCap;
}
int Botaneer::getHumidityCap() {
	return humidityCap;
}
int Botaneer::getTempCapMin() {
	return temperatureCapMin;
}
int Botaneer::getTempCapMax() {
	return temperatureCapMax;
}

class GPIOPIN {
	public:
		bool initializePin(stream direction); //instance functions
		int getPin();
		int getPinNumber(); // retuena pinNumber;
		bool setPin(int state);
		void cleanPin();
		
		GPIOPIN();//constructor
		GPIOPIN(int);
		
		~GPIOPIN();//destructor
	
	private:
		int pinNumber;//instance variable
};
GPIOPIN::GPIOPIN() {//constructor
	pinNumber = 1;
}
GPIOPIN::GPIOPIN(int pin) {//constructor
	pinNumber = pin;
}
GPIOPIN::~GPIOPIN() {
	pinNumber = 0;
}
//Allocate pin to be used +set its stream, return true if successful, false if unable to allocate.
int GPIOPIN::getPinNumber() {
	return pinNumber;
}
bool GPIOPIN::initializePin(stream direction) {
    
    gpio_request(pinNumber, NULL);                              // Allocate the pin.
    int checkGPIOIsUsed = gpio_is_requested(pinNumber);//check if being used and returns -1 if it is.
    if(checkGPIOIsUsed < 0){
        cerr << "GPIO pin " << pinNumber << " is being used. Please select another pin" << endl;
        logInfo((char *)"fatal error, exiting");
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
int GPIOPIN::getPin() {
    return gpio_get_value(pinNumber);  
}
// Sets the logic level of a pin. Returns: True if successful, Returns: False if unable to set logic level. 
bool GPIOPIN::setPin(int state) {
    if (gpio_get_direction(pinNumber) != GPIOF_DIR_OUT || gpio_get_direction(pinNumber) == -1){
        return false;   // Pin is not an output pin. Or had trouble getting direction.
    } 
    gpio_set_value(pinNumber, state);
    return true;
}
// Deallocates the pin and makes it available for other use.
void GPIOPIN::cleanPin() {
	    gpio_free(pinNumber);                               // Deallocate the pin.
}
bool logInfo(char* string) {//FILEWRITE need timestap, severity tag, description
    ofstream ofile;
    ofile.open("log.txt", std::ios_base::app | std::ios_base::out);
    ofile <<endl;
    if (!ofile.is_open()){
        return -1;
    }
	ofile << string << endl;
	ofile << "\n" << endl;
	ofile.close();
    return true;
}
bool logInt(int value) {
    ofstream ofile;
    ofile.open("log.txt", std::ios_base::app | std::ios_base::out);
    ofile <<endl;
    if (!ofile.is_open()){
        return -1;
    }
	ofile << value << endl;
	ofile << "\n" << endl;
	ofile.close();
    return true;
}
bool logFloat(float value) {
    ofstream ofile;
    ofile.open("log.txt", std::ios_base::app | std::ios_base::out);
    ofile <<endl;
    if (!ofile.is_open()){
        return -1;
    }
	ofile << value << endl;
	ofile << "\n" << endl;
	ofile.close();
    return true;
}

int main() {
    int humidity;
	char yesNo;
	char yesNo2;
	char yesNo3;
    int humidityCap;
    int temperature;
	int minTemperatureCap;
	int maxTemperatureCap;
	Botaneer theBotaneer(800, 20, 35);//humidity cap, min temperature cap, max temperature cap.
	GPIOPIN gpioPin(1); //declared GPIOPIN object, the parameter is the pin that the main reader is attached too.
	int counter = 0;
	int sleepTime = 3;
	int SWconstant = 10;
	float datasetHum[SWconstant];
	float datasetTemp[SWconstant];
	int datasetHum1[SWconstant];
	int datasetTemp1[SWconstant];
	Dataset data = {0};
	Statistics stats = {0};

	
	for (int x = 0; x < SWconstant; x++) {
		datasetHum[x] = 0;
		datasetTemp[x] = 0;
		datasetHum1[x] = 0;
		datasetTemp1[x] = 0;
	}
	
	cout << "Start of Botaneer..." << endl;
	logInfo((char *)"Start of Botaneer...");
/////////////////////////////////////////////////CHANGE OF THRESHOLF FOR HUMIDITY AND TEMPERATURE + ERROR CHECKING//////////////////////////////////////////////////
	cout << "Would you like to change the minimum humidity cap? Enter 'y' for yes or 'n' for no" << endl;
	cin >> yesNo;
	if (yesNo == 'y') {
		cout << "Enter a Humidty value from 750 to 1000" << endl;
		while (!(cin >> humidityCap) || humidityCap < 750 || humidityCap > 1000) {
			cout << "Bad input. Please re-enter a proper input from 750 to 1000: " << endl;
			cin.clear();//clear input buffer
		}
		theBotaneer.setHumiditycap(humidityCap);
	}
	cout << "Would you like to change the minimum temperature cap? Enter 'y' for yes or 'n' for no" << endl;
	cin >> yesNo2;
	if (yesNo2 == 'y') {
		cout << "Enter a minimum temperature value from 15 to 25" << endl;
		while (!(cin >> minTemperatureCap) || minTemperatureCap < 15 || minTemperatureCap > 25) {
			cout << "Bad input. Please re-enter a proper input from 15 to 25: " << endl;
			cin.clear();//clear input buffer
		}
		theBotaneer.setTempCapMin(minTemperatureCap);
	}
	cout << "Would you like to change the maximum humidity cap? Enter 'y' for yes or 'n' for no" << endl;
	cin >> yesNo3;
	if (yesNo3 == 'y') {
		cout << "Enter a Humidty value from 30 to 45" << endl;
		while (!(cin >> maxTemperatureCap) || maxTemperatureCap < 30 || maxTemperatureCap > 45) {
			cout << "Bad input. Please re-enter a proper input: " << endl;
			cin.clear();//clear input buffer
		}
		theBotaneer.setTempCapMax(maxTemperatureCap);
	}
	cout << "Humidity lower Threshold: " << theBotaneer.getHumidityCap() << endl;
	logInfo ((char*)"Humidity lower Threshold: ");
	logInt(theBotaneer.getHumidityCap());
	cout << "Temperature lower Threshold: " << theBotaneer.getTempCapMin() << endl;
	logInfo ((char*)"Temperature lower Threshold: ");
	logInt(theBotaneer.getTempCapMin());
	cout << "Temperature upper Threshold: " << theBotaneer.getTempCapMax() << endl;
	logInfo ((char*)"Temperature upper Threshold: ");
	logInt(theBotaneer.getTempCapMax());
	/////////////////////////////////////////////////////////////////////////BOTANEER RUNNING//////////////////////////////////////////////////////////////////////
    while (true) {
        gpioPin.initializePin(OUTPUT); // try setting buffer array size to 3/4 
        char bufferH[3];
        char bufferT[5];
        int fd=open("/dev/ttyS1", O_RDONLY);
        int bytes_read;
        int k = 0;
        //read reads up to count bytes (1 in this case) from file descriptor fd into buffer starting at buff.
        // read byte by byte (1 char = 1 byte) - 0 - 255 can be read
        for (int n = 0; n < 3; n++){
			char t = 0;
			bytes_read = read(fd, &t, 1);  
			bufferH[k++] = t; 
			if(t == '\n' || t == '\0' || t=='.') {
				n = 3;
			}
		}
		int kount = 0;
		for (int n = 0; n < 5; n++) {
			char x = 0;
			bytes_read = read(fd, &x, 1);  
			bufferT[kount++] = x; 
			if(x == '\n' || x == '\0') {
				n=5;
			}
		}
		bytes_read=0;
		int close(fd);
		stringToInt(bufferH, humidity);//'humidity' is the value for hum
		stringToInt(bufferT, temperature); //'temperature' is the value for temp'
		
		cout << "The humidity of the plant is: " << humidity << endl;
		cout << "The temperature of the plant is: " << temperature << endl;
		
		for(int x = 0; x < (SWconstant - 1); x++) {
			datasetHum[x] = datasetHum[x + 1];//float
			datasetTemp[x] = datasetTemp[x + 1];
			datasetHum1[x] = datasetHum1[x + 1];
			datasetTemp1[x] = datasetTemp1[x + 1];
		}
		//add data to sliding windows
		datasetHum[SWconstant - 1] = (float)humidity;
		datasetTemp[SWconstant - 1] = (float)temperature;
		datasetHum1[SWconstant - 1] = humidity;
		datasetTemp1[SWconstant - 1] = temperature;
		
		//update statistics struct
		int computeTheStatsHere = computeStatistics(datasetHum, datasetHum1, datasetTemp, datasetTemp1, stats, SWconstant);
		if (computeTheStatsHere < 0) {
			cout << "Fatal error with the botaneer occured while computing statistics, exiting" << endl;
			logInfo((char *) "Fatal error with the botaneer occured while computing statistics, exiting");
			break;
			//break;
		}
		
		if (theBotaneer.waterPlant(humidity, theBotaneer.getHumidityCap)) {
			gpioPin.setPin(1);//truns on motor
			
			//PUMP THE FUCKING MOTOR HERE, PUT IT INTO A FUNCTION OR SOME SHIT
			
			sleep(3);//pumps around 50 bl of water if the pump is on for 3 seconds
			gpioPin.setPin(0); //turns it off
			sleep(3);
			logInfo((char *) "The plant was watered at this time. The humidity of the plant was: "); //PUT SOME FUCKING TIME OF DAY FUNCTIONS
			logInt(humidity);
			//PRINT SOMETHING ON THE OLED HERE FOR WHEN THE FUCKING WATER IS PUMPED
			gpioPin.cleanPin();
		} else {
			sleep(6);
		}
		
		if (!theBotaneer.tempOverexceed(temperature, theBotaneer.getTempCapMin(), theBotaneer.getTempCapMax())) {
			//PUT SOME FUCKIGN SHIT ON AN OLED HERE
			//LIGHT A FUCKING LED OR SOME SHIT? WE CAN MAKE ANOTHER gpiopin OBJECT
			
			cout << "Warning! Plant is not placed within a suitable temperature! Please change the location of the plant." << endl;
			cout << "The temperature right now is: " << temperature << " degrees." << endl;
			
		}
		if (counter % 10 == 0) {//logs the humidty and temperature after every minute
			//prints the values of temperature and humidity to the ofile.
			//logs current temp/hum
			logInfo((char *)"The humidity of the plant is: ");//ADD THE FUCKING TIME OF DAYS
			logInt(humidity);
			logInfo((char *)"The temperature of the plant is: "); // ADD TIME OF DAY TO THIS FUCKER
			logInt(temperature);
			//log stats
			logInfo((char*) "Computing stats...");
			logInfo((char*) "Minimum Humidity:");
			logInt(stats.minimumHum);
			logInfo((char*) "Minimum Temperature: ");
			logInt(stats.minimumTemp);		
			logInfo((char*)"Maximum Humidity: ");
			logInt(stats.maximumHum);	
			logInfo((char*)"Maximum Temperature: ");
			logInt(stats.maximumTemp);
			logInfo((char*)"Average Humidity: ");
			logFloat(stats.averageHum);				
			logInfo((char*)"Average Temperature: ");
			logFloat(stats.averageTemp);
			logInfo((char*)"Population Standard Deviation of Humidity: ");
			logFloat(stats.popStdDevHum);
			logInfo((char*)"Population Standard Deviation of Temperature: ");
			logFloat(stats.popStdDevTemp);
			logInfo((char*)"Sample Standard Deviation of Humidity: ");
			logFloat(stats.smplStdDevHum);
			logInfo((char*)"Sample Standard Deviation of Temperature: ");
			logFloat(stats.smplStdDevTemp);

			if (!theBotaneer.tempOverexceed(temperature, theBotaneer.getTempCapMin(), theBotaneer.getTempCapMax())) {
				logInfo((char *) "The plant is currently not placed in a suitable environment due to the temeprature being to low/high");
			}	
		}
		counter++;
		if ((temperature < minTemperatureCap && temperature !=0) || (temperature > maxTemperatureCap && temperature != 0)) {
			//PRINT SOME SHIT ON THE OLED HERE THIS PART JUST DISPLAYS THE TEMP AND HUMIDITY SENSOR HERE
		}
    }
    return 0;
}
