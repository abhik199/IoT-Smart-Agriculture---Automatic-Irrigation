
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h> // Including library for dht

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

#define DHTPIN D4 // pin where the dht11 is connected
    DHT dht(DHTPIN, DHT11);

String apiKey = "C25ICK6FHOR7PST4"; // Enter your Write API key from ThingSpeak
const char *ssid = "MySmartHome";   // replace with your wifi ssid and wpa2 key
const char *pass = "nRF52840";
const char *server = "api.thingspeak.com";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int AirValue = 790;   // you need to replace this value with Value_1
const int WaterValue = 390; // you need to replace this value with Value_2
const int SensorPin = A0;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
int relaypin = D5;

WiFiClient client;

void setup()
{
    Serial.begin(115200);                      // open serial port, set the baud rate to 9600 bps
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (128x64)
    display.clearDisplay();
    pinMode(relaypin, OUTPUT);

    dht.begin();

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    delay(4000);
}

void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Temperature: ");
    Serial.println(t);

    soilMoistureValue = analogRead(SensorPin); // put Sensor insert into soil
    Serial.println(soilMoistureValue);

    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

    if (soilmoisturepercent > 100)
    {
        Serial.println("100 %");

        display.setCursor(0, 0); // oled display
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.print("Soil RH:");
        display.setTextSize(1);
        display.print("100");
        display.println(" %");
        display.setCursor(0, 20); // oled display
        display.setTextSize(2);
        display.print("Air RH:");
        display.setTextSize(1);
        display.print(h);
        display.println(" %");
        display.setCursor(0, 40); // oled display
        display.setTextSize(2);
        display.print("Temp:");
        display.setTextSize(1);
        display.print(t);
        display.println(" C");
        display.display();

        delay(250);
        display.clearDisplay();
    }

    else if (soilmoisturepercent < 0)
    {
        Serial.println("0 %");

        display.setCursor(0, 0); // oled display
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.print("Soil RH:");
        display.setTextSize(1);
        display.print("0");
        display.println(" %");
        display.setCursor(0, 20); // oled display
        display.setTextSize(2);
        display.print("Air RH:");
        display.setTextSize(1);
        display.print(h);
        display.println(" %");
        display.setCursor(0, 40); // oled display
        display.setTextSize(2);
        display.print("Temp:");
        display.setTextSize(1);
        display.print(t);
        display.println(" C");
        display.display();

        delay(250);
        display.clearDisplay();
    }

    else if (soilmoisturepercent >= 0 && soilmoisturepercent <= 100)
    {
        Serial.print(soilmoisturepercent);
        Serial.println("%");

        display.setCursor(0, 0); // oled display
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.print("Soil RH:");
        display.setTextSize(1);
        display.print(soilmoisturepercent);
        display.println(" %");
        display.setCursor(0, 20); // oled display
        display.setTextSize(2);
        display.print("Air RH:");
        display.setTextSize(1);
        display.print(h);
        display.println(" %");
        display.setCursor(0, 40); // oled display
        display.setTextSize(2);
        display.print("Temp:");
        display.setTextSize(1);
        display.print(t);
        display.println(" C");
        display.display();

        delay(250);
        display.clearDisplay();
    }

    if (soilmoisturepercent >= 0 && soilmoisturepercent <= 30)
    {
        digitalWrite(relaypin, HIGH);
        Serial.println("Motor is ON");
    }
    else if (soilmoisturepercent > 30 && soilmoisturepercent <= 100)
    {
        digitalWrite(relaypin, LOW);
        Serial.println("Motor is OFF");
    }

    if (client.connect(server, 80)) // "184.106.153.149" or api.thingspeak.com
    {
        String postStr = apiKey;
        postStr += "&field1=";
        postStr += String(soilmoisturepercent);
        postStr += "&field2=";
        postStr += String(h);
        postStr += "&field3=";
        postStr += String(t);
        postStr += "&field4=";
        postStr += String(relaypin);
        postStr += "\r\n\r\n\r\n\r\n";

        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
    }
    client.stop();
}
