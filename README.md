# Botaneer-
The Botaneer 
Created by
Justin Mathieu Drapeau
Quang Buu (Aidan) Ha
Gregory Robin Ho
Team Number: 34

 
Overall Summary of Project
           	The Botaneer is a functional automated plant-watering system, that tracks the humidity and temperature of the plant, and waters it when the sensors read values within a certain threshold. The Botaneer utilizes an Omega2 attached to an Arduino dock to read values from a humidity and a temperature sensor, which also runs a current through a DC water pump to pour a defined volume of water onto the plant. The Botaneer will also log and append the plant conditions every minute into a file, in addition to displaying the plant’s current humidity and temperature to an OLED attached to the Omega’s GPIO pins. Finally, miscellaneous stats using functions from previous labs will be calculated and logged including min, max, avg and etc.
 
System Specifications
 
General Composition: The hardware aspect of this project comprises of an Omega 2 Linux machine attached to an Arduino dock, which enables it to use many add-ons that otherwise  would be solely available to an Arduino. The Botaneer consists of a temperature and Humidity sensor (which was purchased online separately) attached to the Arduino dock, as the dock posses’ analog pins capable of reading the sensor values to a degree of accuracy greater than the Omega. Through the humidity sensor, there is no required calculations to have a value in an usable format, falling between zero and approximately one thousand. However for temperature, a voltage value was found and converted to an actual temperature reading on the celsius scale. These sensor values are then sent to the Omega through UART (serial communication), and will then be manipulated in the software part of the project. For the pump to turn on, the C++ program will gather user input and use that value as the threshold for how low the humidity can be, and will turn on a GPIO pin for a certain amount of time to power the pump for a set duration (tested via trial and error). Refer to Appendix C for pictures.
           	
Motor: The structure of the pump made it suboptimal to work with due to the input and output valve of the pump being placed on the same side, resulting in difficulty to transfer water from a reservoir of sorts (tank, cup, or bowl) to the plant. After days of testing, it was decided to angle the pump and use plastic straws and duct tape to the reservoir to aim the nozzle of the pump towards the plant such that water would flow onto it.  Refer to Appendix C for pictures.

           	
Sensor: For the temperature and humidity sensors, it reads the corresponding values once every six seconds and through the Arduino Dock, sends the values via serial. However, once the Botaneer waters the plant, it will not water the plant for a set duration to allow the water to be absorbed by the soil. As well, the logger only logs the values of temperature and humidity every other minute to avoid cluttering the log file, while still logging what functions and classes have been opened.  Refer to Appendix C for pictures.

 
OLED: The purpose of the OLED is to take the information gathered from the sensors and output to be visible, such that the program may be functional without the presence of the ssh and the command line. In addition, it may provide some other useful information such as when the plant is to be watered, and warning messages should any errors occur or if any condition in which the plant’s growth is inhibited or threatened. Refer to Appendix C for pictures.

Classes
Botaneer Class

The biggest class that was used in this project was called “Botaneer”. This class contained many functions that was used in order to properly water the plant under specific conditions. 

Data Elements/ Instance variable: There are some elements within the class that are private. These instance variables include the current temperature/humidity of the plant, the thresholds of the humidity/temperature, and a boolean that decides whether or not the Botaneer should water the plant. These instance variables are manipulated with the functions defined above.

Functions within the class:
setHumidityCap, setTempCapMin and setTempCapMax: These functions allows the user to interact with the botaneer, and manually set a lower and upper threshold for the humidity and temperature.

getHumidityCap, getTempCapMin, getTempCapMax: functions that return an integer that represents its respective threshold value.

tempOverexceed: This function tells the main class whether the plant is in a suitable condition or not, and returns a boolean accordingly. This function is called within the main class, specifically whenever the program checks if the plant is in a suitable environment.

waterPlant : This function checks if the current humidity of the plant is below the humidity threshold, and manipulates the hardware in the main class to physically water the plant.


GPIO class

To making working and manipulating the GPIO pins easier, our group made a custom class specifically for the GPIO. This allows us to call a “GPIO” object within the main function, and lets us easily manipulate the components of that specific gpio pin via the functions in the class.

Data Elements/ Instance variable: There is only one instance variable in the class which is the gpio pin number of the GPIO object (which ever gpio pin that is being used). The constructor takes in an integer, which represent which gpio pin the user would like to use.

Functions within the class:
initializePin: This function allocates a desired pin, and sets its direction (intput, output). Setting the direction of the pin is done by taking in an enum parameter called “stream”, where the only 2 components of that enum is “INPUT” and “OUTPUT”. This function returns false if it unable to allocate the pin.

getPinNumber: Returns the pin number that is used. This function was mainly used in the testing stage of the project.

getPin : Returns the pin’s current logic level. Return -1 if the function is unable to return the pin’s logic level. Mainly used for testing.

setPin : Sets the pin’s logic level. Return true if successful, and false if otherwise.

cleanPin: Deallocates the pin and makes it available the next time it is requested to be used.

OLED class

Data Elements/ Instance variable: There are two member variables in this class, humidity and temperature. These two private variables hold the current values of humidity and temperature for use in other functions within the class. They can be modified only through the setHumidity() and setTemperature() functions.

Functions within the class:
setTemperature, setHumidity: These two functions take one parameter which will be data from the humidity and temperature sensors. The two functions modify the member variables of the OLED class and return nothing.

getTemperature, getHumidity: These two functions take no parameters and return the values of humidity and temperature respectively.

initialize: This function takes no parameters and return nothing. The functions performs the necessary function calls for the initial setup of the oled display. This function also prints out the basic messages onto the display.

updateHumidity, updateTemperature: These two functions take no parameters and return nothing. The functions simply modify the oled display and update the values that are shown.

lastWatered: This function takes a string which should represent a timeStamp. The function will display when the last time the plant was watered according to the Omega’s system time. This function should be used with the timeStamp() function.

temperatureStatus: This function takes a boolean variable and displays the corresponding message according the the variable’s value. True would mean indicating the soil’s temperature is within the defined bounds. False would mean outside of the temperature bounds.

systemStatus: This function displays the current state of the system. The system can be in 3 different states: awake, watering, and sleeping.

External Function specifics

System Dependent: 

Reading the sensor: Due to development of many sensors being around the same microcontroller as a standard (Arduino and Raspberry Pi) it is absolutely crucial to have the interface to use these devices, which was solved through having an Arduino Dock to emulate a fully functional Arduino Uno. In addition, an effective means of receiving values was required (as the Omega cannot read the sensor), so the Arduino Dock was used to be able to do either UART or I2C communication to send data to be processed.
 
Turning on the pump: Requires GPIO Pins and capable voltage and current supply in order to power the motor and push the water against gravity in order to reach the plant. To support this action, a strong and consistent voltage must be provided, and unlike the controllable input pins present on the Omega which output 3.3V but not consistently. If one wanted to use the constant power pins of 3.3V or 5V a switch system (using transistors) can be used, but through testing was shown to not work with the Omega. The Omega’s pins apply a voltage but not consistent or powerful enough to be used as a pump, thus either Pulse Width Modulation (PWM), Relay Expansion, or an Arduino dock must be used to have a successful project. 
 
System Independent: 

Utilization of Input and Output: The GPIO class mentioned above is used to turn the pins on, general implementation similar across the Linux and Arduino platforms using GPIO pins.
Processing Data: Once data has been received from the Arduino dock, processing, parsing and calculating data remains rather consistent across a multitude of programming languages, and as such is independent of the parts acquired for the project.

Displaying Data: Two main methods of displaying data, both with use of I2C, in which the display is controlled to display values, refresh and clear the display to update as time goes on. Both equally valid options for this project include the OLED display, and also a 16x2 LCD display.
 
Logging infrastructure

Logging and File Writing: There are 3 logging functions, and they all write a specific variable type to a file called “log.log”. logInfo writes a string (character array), logInt writes an integer, and logFloat writes a float. Each log function takes in that specific variable that they write as a parameter. All functions return false if it is unable to open the desired file.
The log function is called several times:
Once at the start of the program to write that the program has started.
Whenever the user changes the humidity/temperature caps.
After every minute, to log the current Humidity and temperature.
After every minute, to log the statistics calculated in the program.

Statistics

Stats: The statistics component of this project was very simple, and mirrors off the previous assignments that was done in ECE 150. The botaneer calculates the minimum, maximum average, population SD and sample SD for both the humidity and the temperature. Each of these statistics were calculated via a specific function (listed below). Furthermore, the calculated values were then placed in a Struct called “Statistics”, which contained the statistics from both Humidity and Temperature. In addition, the main function contains a method similar to SlidingWindowsStats, where every time a new humidity/temperature was calculated, it would replace the 10th oldest value of the humidity temperature. This means that the average/minimum/maximum/popSD/smplSD of the humidity/temperature would only consider the values found within the last minute prior to the calculation. 

Note: Each function listed below takes in a integer array (dataset) and an integer (size) as parameters.

Minimum: Uses a bubble sort algorithm to return the smallest number within the array. 

Maximum: Uses a bubble sort algorithm to return the largest number within the array.

Average: Returns the sum of all of the data in the dataset divided by the size of the dataset.

PopStdDev: Returns the value of the population standard deviation of the dataset.

SmplStdDev: Returns the value of the sample standard deviation of the dataset.

ComputeStatistics: Function that calls all of the functions above, and store the values received into a “Statistics” struct.

Main Function

Initializes variables:  When the program begins, it initializes all variables with a numeric value (eg: int, float) to zero. This reduces any potential memory space errors. The Botaneer and GPIO objects are also created in this part of the main function

Change Humidity/Temperature Threshold: The program will then prompt the user whether or not they want to change the humidity/temperature threshold. It will then change the values of the temperature/humidity threshold to what the user wants. Note, there is a certain that these values can be. For example, the program will not let the user enter a value of 1000 for the minimum temperature threshold.

Loop: The program then goes into a while loop where after every 6 seconds, it would read the sensors. The arduino dock sequentially turns on the sensors for a short period of time, gathering the value and depending on the time (if 6 seconds have elapsed since last transmission), more data is taken, or the current data is written to the Serial Port.  In order to have consistency and uniformity in transmission, the two data values together are written to the serial port, parsed with an ampersand (&), as an identifier to split the two values, where the values are then processed and converted to integer values. From this, other classes and methods may make use of the values to display the data, compute statistics, decide if conditions are optimal for the plant, and whether or not to water the plant.

waterPlant: After it reads the values received from the sensors, the program will use the functions from the Botaneer class to determine whether or not the plant needs to be watered. It will then perform actions if required (eg: turn on the motor to water the plant). If the plants needs to be watered, the program will turn on a GPIO pin for three seconds, which connects to the Arduino dock, where the Arduino is in a constant loop checking for a voltage (input), such that it can then output a voltage to power the motor. Once the signal is received, the pump will turn on for three more seconds and remain off for the remaining three, to remain synchronized with Omega for sending and receiving values. The Arduino is the source for the motor as for reasons mentioned above, the Omega’s GPIO are simply not powerful enough to power the motor.

Log and compute statistics: A counter variable was placed within the loop so that every minute (count % 10 == 0; count++ which increment every six seconds), it would log the values of temperature and humidity of the plant using the functions described above.


Project Testing Stage 
For the first round of testing, we tested how much water was pumped per second when the motor was on from both the 5V and 3.3V source, then trying to apply an output pin to see how much water would be pumped. However, during testing we noticed that the Omega’s GPIO pins supplied so little power that when the pin was turned on, the water had great difficulty climbing a small incline. This demonstrated the requirement of a more powerful or consistent source (through a relay expansion + power supply or the Arduino Dock). We chose to use the arduino dock which was able to provide enough power to water the plant. Nextly, came the step of testing the fine control of the system, seeing how we would be able to send data, and control the duration of the pump being on. To do this, simple arduino sketches were written in conjunction with a simple C++ program which turned on and off the pump within a certain interval. The next step of testing was to successfully be able to parse the datastream sent, and interpret it in a way to be able to control the pump and use the data. Once the data could successfully be obtained, we did a test on how the humidity of the soil would change after excess water was pumped to the soil. With excess water, the sensor values increased past the threshold of 900, which was the maximum value one can attain by pressing one’s fingers against the sensor, providing a good basis for understanding what values are to be expected for a plant watering system. 

The position of the pump relative to the humidity was also tested, and it was found that the position of the pump had no effect based on the speed of the change of humidity. For the second test, we tested different types of plumbing and connections to the plant due to there not being an easy access between the plant and the pump. After using several models, it was found that the most optimal model was when the pump was angled approaching 45 degrees and was connected to a straw that would follow a small arc to water the plant.



Proof of Concept: We are able to confirm the values we read by running cat /dev/ttyS1 from the command line which displays both sensor values on a set interval split by an ampersand (&). The temperature value was checked by simply confirming the temperature of the room, and for the humidity, the linear trend of how much contact put onto ensured that the proper readings were made. For no skin/plant contact, the reading was 0 and eventually with more moisture or pressure applied to the sensor the value would increase all the way to a maximum of 900. Thus, we were able to interpolate for which data value could be considered to be not watered enough, and turn on the pump at that certain instance. To confirm the pump worked only a certain conditions, we first ensured that the pump would only turn on for a set interval, which it does through a simple pumpTest program, and then we ensured that it functioned by changing the values of the humidity sensor and seeing what would occur. When the sensor was not touching anything, the pump would not pump, and for values within an acceptable and defined range the pump would pump.

Limitations:
The shortfall of our project stems from the fact that the motor is severely weak due to it not having its own dedicated and consistent power supply, which could be mitigated through a relay expansion, but alas, our group did not have the parts to convert a DC power supply to both a positive and negative terminal, thus we settled for the Arduino’s weaker but still functional pump speed. 
Significant lessons learned:
 
Compiler: From the beginning, even though we did not have the parts to actually build the project, we now know that more time should have been dedicated to properly setting up the compiler and by extension the cross compiler in order to have more time to be able to test the code written. Large amounts of time was used to setup the cross compiler, which could have been dealt with at an earlier time to be able to add more to the project. Specifically, the use of multiple libraries in compiling command line took a lengthily period of time to figure out how do to. In all, there was difficulty in properly implementing multiple libraries to compile, having easily setup the ugpio library but being unable to combine that with an I2C library. In all, the I2C library managed to be incorporated, but large amounts of that time could have potentially worked towards solving the power issue through incorporation of a Relay Expansion (and work with its corresponding C++ library). Should this project be repeated, more time will be dedicated to starting up the compiler and actually booting up the omega2.
 
 
Time management: Overall, our group underestimated the amount of time required to complete the project. Specifically, we overestimated our ability to learn the material in a short amount of time. For example, the compiler took 2 out of the 5 weeks to get it to a functional state. The other classes we implemented such as the OLED also took a decent amount of time to learn due to having to find out how to include a method to compile with I2C. Finally, a realization that we couldn’t get the project done with 3-4 meetings a week was made. All of the group members realized that we must work on this project every single day in order to meet such a strict deadline, while producing something that would impress the professors and TA’s. For the future, it would be best to having a system where all of the group is applied towards solving differing issues then coming together to pseudo code for the project while trying to set-up the compiler that it is functional, instead of waiting for one part to finish before working on the other.
 
Team infrastructure: One of the most important lessons learned when working on this project was how necessary a team infrastructure was in this project. First off, a team lead was almost mandatory to establish. This person would make crucial decisions, micromanage the other group members, and organize the priorities for the project. The lead would also have to know which group member specializes in what aspect of the project and would oversee the overall work done of the team. Next, it was also important to establish which group member will work on which part of the project. In this case, each group member would prioritize the tasks that they have prior experience in, and will work specifically on that part. The way our group divided the task is as followed: Justin on the hardware components, Gregory on software, and Aidan on the infrastructure of the project and linking the hardware and the software components. Since each group member had their own specialty, the group would work at max efficiency if each member focused on what they do best.
 
Theoretical Planning: In hindsight, it would be easy to say that our group should have not trusted the GPIO pins to be consistent enough to power a motor, and pushed for a power supply, meaning that we should have planned for worst case scenario (GPIO being next to useless and getting something for PWM or the relay)

 
 

Appendix A: Peer Contributions
During the course of the project, each member worked towards writing and testing their own code, and giving feedback and ideas to others All group members participated in writing, editing and researching information both for the report and proposal, with more specific areas of focus listed below:
Quang Buu (Aidan) Ha:
-        Responsible for the getting the Compiler up and running 
-        Created the infrastructure system for both the software and hardware components.
-	Created the Botaneer and GPIO class.
-        Combined the functions created by the other group member into one single functional file
-	Responsible for the logging and statistics infrastructure.
-        Relayed the hardware component with the software component of the Project
- 	 Assisted with the breadboarding, and implementing solutions for the motor to properly  provide water
-        Responsible for purchasing external parts.
Justin Drapeau:
-        Mainly responsible for the hardware of the project.
-        Also responsible for setting up the functional compiler.
-        Researched which hardware components were needed for the project.
-        Primarily focused on the Arduino dock, flashing the dock to be compatible with the Omega
-      Wiring of the breadboard, and establishing connections between components, deciding how pins were to be laid out and how pump was to be used and powered
-       Worked on getting the sensors to pass integer values from temperature and humidity sensors on the Arduino dock passed through use of UART (serial communication) 
-    Utilized StringToInt and knowledge from StringToFloat to properly parse the serial stream in order to get two separate values from serial communication.	
-    Worked on turning on the Pump at a power strong enough to water the plant.
Gregory Ho:
-        Mainly responsible for the software component of the project.
-        Responsible for researching which classes and functions we needed to implement in our project.
-     Created the OLED class.
-        Created the stringToInt function.
-	Created the timeStamp function.
-      Assisted with reading serial data in C++ and converting it into usable integer values
-        Enhanced the infrastructure of the code by implementing the use of structs and functions.
-        Worked on the OLED and the compilation of the I2C library.
-        Also assisted with the hardware component of the project when necessary.




Appendix B: Source code

Please refer to https://github.com/AidanHa/Botaneer/blob/master/botaneer.cpp  for the source code.

Makefile

The makefile used was extremely similar to the default one provided, with the exception of changing the second line to compile in C++, adding a -w to compile with warnings, and appending -std=c++0x to the seventh line, in order to make use of the C++ 11 standard (for use of to_String)


Compiling with I2C
Library Name/Source, way of installation what it allows you to do.
	
Structs + Enums
 
 struct Statistics {
	//stats for humidity
	int   minimumHum;
	float averageHum;
	int   maximumHum;
	float popStdDevHum;
	float smplStdDevHum;
	
	//stats for temperature
	int   minimumTemp;
	float averageTemp;
	int   maximumTemp;
	float popStdDevTemp;
	float smplStdDevTemp;
};
enum stream {INPUT, OUTPUT};

CLASSES
Botaneer

bool waterPlant(int humidity, int humidityCap); //decides if plant needs to be watered

bool tempOverexceed(int temperature, int temperatureCapMin, int temperatureCapMax); //check if temperature is within range

void setHumiditycap(int newCap); //sets caps
void setTempCapMin(int newCap);
void setTempCapMax(int newCap);

int getHumidityCap(); //gets caps
int getTempCapMin();
int getTempCapMax();

Botaneer();//constructors
Botaneer(int, int, int);
		
	~Botaneer(); //destructor
private:
	int temperature;
	int humidity;
	int temperatureCapMin;
	int temperatureCapMax;
	int humidityCap;
	
OLED
public:
	void setHumidity(int value);		// Assigns values to the member variables
	void setTemperature(int value);		
int getHumidity();			// Retrieves values from the member variables
	int getTemperature()	
	void initialize();			// Initializes the display
	void updateHumidity();		// Updates the values currently shown on the oled
	void updateTemperature();
	void lastWatered(string timeStamp);	// Displays a timeStamp of the last time of watering
	void temperatureStatus(bool ok);	// Displays the temperature’s status
	void systemStatus(int status);		// Displays what the system is doing
	OLED();	// Initialize member variables
	~OLED();	// Deconstructor
private:	
	int humidity;	// Holds respective values
	int temperature;

GPIO 

public:
	bool initializePin(stream direction); //Allocates pin to use
	int getPin();//returns pins logic
	int getPinNumber(); // returns pinNumber;
	bool setPin(int state); // set pin logc
	void cleanPin(); // clean for use next time, sets logic to 0
	
	GPIOPIN();//constructor
	GPIOPIN(int);
	
	~GPIOPIN();//destructor
	
private:
	int pinNumber;//the gio pin being used

External functions

bool logInfo(char* string); //logs a string to the log file

bool logInt(int value); // logs an int to the log file

bool logFloat(float value); //log a float to the log file

string timeStamp() //gets the time of day

bool stringToInt(const char input[], int& value); //converts a char array to an int

int computeStatistics(float datasetHum[], int datasetHum1[], float datasetTemp[], int datasetTemp1[], Statistics& stats, int SWconstant); // calculates stats, and stores them in a statistics struct.

int minimum(int dataset[], int size); //calculate minimum of dataset
float average(float dataset[], int size); //calculate average of dataset
int maximum(int dataset[], int size); //calculates maximum of dataset
float popStdDev(float dataset[], int size); //calculates popStdDev of dataset
float smplStdDev(float dataset[], int size); //calculates smplStdDev of dataset

Main (pseudo code)
//starts program.
//Declares a botaneer object called “theBotaneer”.
//Declare a GPIO object called “gpioPin”.

//asks if user wants to change temp/humidity caps.
//Uses theBotaneer.setHumidityCap(inputted value), theBotaneer.setTempCapMin(inputted value) and theBotaneer.setTempCapMax( inputted value) to change the caps.

// While loop runs infinitely (up to the point where long long int overflow occurs on the timing mechanism of the Arduino Dock), 

//Every iteration, the program will consistently gather Serial Input, process it into temperature and humidity strings, and convert those strings into integer values.

// Those values will be then used to compute various statistics, such as the minimum, maximum average and standard deviation of the temperature and humidity.

// The OLED will then display the current temperature/humidity of the plant.

// The program then uses the waterPlant() functions to decide whether or not the plant is to be watered. If it needs to be watered, the Omega will run a voltage through the Arduino port to turn on the motor. The OLED and the command line will also signal the user that the plant is being watered. The program will also log that the plant has been watered.

//The program will then use the  tempOverexceel() function to decide whether or not the plant is in a suitable environment in terms of temperature. If it isn’t, a warning is to be displayed on the OLED and on the command line. The program will also log this in the log.log file.

//The program will then see how much time has passed since statistics were last logged, and if it had been a minute, will log the statistics with timestamps using the TimeOfDay function.

//The program will then finally sleep for 6 seconds and loop again.




Links to Libraries Used
https://github.com/mhei/libugpio/blob/master/src/ugpio.h




