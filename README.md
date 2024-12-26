IoT Smart Agriculture & Automatic Irrigation System with ESP8266 


![image](https://github.com/user-attachments/assets/2a7b0b0c-6b6f-46ff-b54e-a1019d156713)  



Overview: IoT Based Smart Agriculture & Automatic Irrigation System
In this project, we will learn about the IoT Based Smart Agriculture & Automatic Irrigation System with Nodemcu ESP8266. Agriculture plays a vital role in the development of agricultural countries. Some issues concerning agriculture have been always hindering the development of the country. Consequently, the only solution to this problem is smart agriculture by modernizing the current traditional methods of agriculture.

Hence the method is making agriculture smart using automation and IoT technologies. Internet of Things (IoT) enables various applications of crop growth monitoring and selection, automatic irrigation decision support, etc. We proposed ESP8266 IoT Automatic irrigation system to modernize and improve the productivity of the crop.


This post explains how to make IoT Smart Agriculture with Automatic Irrigation System using some simple sensors that are available in the market. We will use Capacitive Soil Moisture Sensor to measure moisture content present in the soil. Similarly to measure Air Temperature and Humidity, we prefer DHT11 Humidity Temperature Sensor. Using a 5V Power relay we will control the Water Pump. Whenever the sensor detects a low quantity of moisture in the soil, the motor turns on automatically. Hence, will automatically irrigate the field. Once the soil becomes wet, the motor turns off. You can monitor all this happening remotely via Thingspeak Server online from any part of the world.

Bill of Materials
We will need the fllowing electronics components for making this project.You can purchase all the components online from Amazon. The component purchase link is given below.


1	NodeMCU ESP8266 Board
2	Capacitive Soil Moisture Sensor	
3	0.96" I2C OLED Displa
4	DHT11 Sensor	
5	1 Channel 5V Relay Module	
6	5V DC Motor Pump	
7	Connecting Wires	
8	Breadboard	

Capacitive Soil Moisture Sensor
This is an analog capacitive soil moisture sensor which measures soil moisture levels by capacitive sensing. This means the capacitance is varied on the basis of water content present in the soil. You can convert the capacitance into voltage level basically from 1.2V minimum to 3.0V maximum. The advantage of Capacitive Soil Moisture Sensor is that they are made of a corrosion-resistant material giving it a long service life. The sensor can be used to make Automatic Plant Watering System.

Capacitive Soil Moisture Sensor v1.2

Features & Specifications
Supports 3-Pin Sensor interface
Analog output
Operating Voltage: DC 3.3-5.5V
Output Voltage: DC 0-3.0V
Interface: PH2.0-3P
Size: 99x16mm/3.9×0.63″
To learn more about Capacitive Soil Moisture Sensor you can follow this post: Capacitive Soil Moisture Sensor Basic Interfacing Guide





DHT11 Humidity Temperature Sensor
The DHT11 is a basic, ultra low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air. It spits out a digital signal on the data pin.

DHT11 Humidity Temperature Sensor

It’s fairly simple to use, but requires careful timing to grab data. The only real downside of this sensor is you can only get new data from it once every 2 seconds. So when using the library, sensor readings can be up to 2 seconds old. In this project, we will use this sensor to measure the air temperature and humidity.

To learn more about DHT11 Humidity/Temperature Sensor you can follow this post: DHT11 Basic Interfacing Guide

DC 3-6V Micro Submersible Mini Water Pump
The DC 3-6 V Mini Micro Submersible Water Pump is a low cost, small size Submersible Pump Motor. It operates from a 2.5 ~ 6V power supply. It can take up to 120 liters per hour with a very low current consumption of 220mA. Just connect the tube pipe to the motor outlet, submerge it in water, and power it.



Features & Specifications
Operating Voltage : 2.5 ~ 6V
Operating Current : 130 ~ 220mA
Flow Rate : 80 ~ 120 L/H
Maximum Lift : 40 ~ 110 mm
Outlet Outside Diameter: 7.5 mm
Outlet Inside Diameter: 5 mm





Circuit Diagram & Connection
Let us see the schematic of the IoT Smart Agriculture & Automatic Irrigation System project. I use Fritzing to make an schematic for most of my projects. All you need is to place and connect a component that is super easy.

IoT Smart Agriculture & Automatic Irrigation System

Connect the soil moisture sensor to A0 of Nodemcu and DHT11 to D4 Pin. The motor connects to Relay. To control the relay, we use the D5 Pin of NodeMCU. Connect the OLED display to the I2C pin of NodeMCU. You can power the Motor and Relay using the 5V pin of NodeMCU. The DHT11 Sensor, Capacitive Soil Moisture Sensor, and OLED Display require a 3.3V Supply only.

IoT Automatic Irrigation System ESP8266

Project PCB Gerber File & PCB Ordering Online
If you don’t want to assemble the circuit on breadboard and you want PCB for the project, then here is the PCB for you. The PCB Board for the Smart Agriculture & Automatic Irrigation System is designed using EasyEDA online Circuit Schematics & PCB designing tool. The front side and back side of the PCB looks something like this.


Front View of PCB

Back View of PCB
The Gerber File for the PCB is given below. You can simply download the Gerber File and order the PCB from ALLPCB at 1$ only.

Download Gerber File: Smart Agriculture + Automatic Irrigation System PCB
You can use this Gerber file to order high quality PCB for this project. To do that visit the ALLPCB official website by clicking here: https://www.allpcb.com/.



You can now upload the Gerber File by choosing the Quote Now option. From these options, you can choose the Material Type, Dimensions, Quantity, Thickness, Solder Mask Color and other required parameters.



After filling all details, select your country and shipping method. Finally you can place the order.

Setting Up Thingspeak Server
Now we need to setup the Thingspeak Account. To set up Thingspeak follow the following Steps:



Step 1: Visit https://thingspeak.com/ and create your account by filling up the details.

Step 2: Create a New Channel by Clicking on “Channel” & fill up the following details as shown in the image below.


Step 3: Click on API Key, you will see the “Write API Key“. Copy the API Key. This is very important, it will be required in Code Part.


Step 4: You can click on the “Private View” & customize the display window as you want.

So, that’s all from the Thingspeak Setup Part. Now let us move to the programming Part.





Source Code/Program
The Source Code for IoT Smart Agriculture & Automatic Irrigation System with ESP8266 is very simple. The code can be directly uploaded to the NOdeMCU Board. But before that make sure to add OLED Display Library from the below link.

Adafruit GFX Library: Download
SSD1306 Library: Download
In the below code part, change the Thingspeak API Key, WiFi SSID & Password.

The most important part of this code is the calibration of the Soil Moisture Sensor Value like AirValue and WaterValue. To learn how to calibrate and get the correct reading follow this post: Calibrating Soil Moisture Sensor Value. Please!, do not skip this step. This may result in getting the wrong soil moisture value and sometimes may result in continuous turning ON of the motor.
