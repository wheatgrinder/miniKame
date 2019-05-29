#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Servo.h>
#include "minikame.h"

void parseData(String data);
MiniKame robot;
bool running=1;
String input;
int count=0;

String botMode="remote";

int demoStepCnt = 0;

int port = 80;
WiFiServer server(port);

void setup() {

    if(botMode == "remote-ap"){
        // Wifi Access Point configuration
        const char* ssid = "minikame ap";
        const char* password = "";
        
        WiFi.mode(WIFI_AP);
        WiFi.softAP(ssid, password);
       
    } else if (botMode == "remote"){
        
        const char* ssid = "DJ6ZK";
        const char* password = "51B4A1AEC7";
        
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password); //Connect to wifi
       
    }
    
    
    server.begin();
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    Serial.println("BotMode:" + botMode);

    if(botMode == "remote"){
        Serial.println("Connecting to Wifi");
        while (WiFi.status() != WL_CONNECTED) {   
            delay(500);
            Serial.print(".");
            delay(500);
        }

        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(WiFi.SSID());

        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());  
        //server.begin();
        Serial.print("Server:");
        Serial.print(WiFi.localIP());
        Serial.print(" on port ");
        Serial.println(port);
        Serial.print("ready to connect:");

    }
    


    robot.init();
    delay(2000);
    robot.home();

    
    
}

void loop() {
    if (botMode == "remote") {
        WiFiClient client = server.available();
            if (client){
                while (client.connected()) {
                    if (running){
                            Serial.println("running");
                            if (client.available()) {
                                while(client.available()) input = client.readStringUntil('+');
                                parseData(input);
                            }
                            else {
                                Serial.println("Keep Moving");
                                parseData(input);
                            }
                        }
                        else{
                            Serial.println("Normal mode");
                            if (client.available()) {
                                while(client.available()) input = client.readStringUntil('+');
                                parseData(input);
                            }
                            else robot.home();
                        }
                }
            }
    } 
    else if (botMode == "remote-AP") {
        WiFiClient client = server.available();
            if (!client) {
                IPAddress myIP = WiFi.softAPIP();
                Serial.print("AP IP address: ");
                Serial.println(myIP);
                delay(1000);

            }
            while (client.connected()) {
                if (running){
                        Serial.println("running");
                        if (client.available()) {
                            while(client.available()) input = client.readStringUntil('+');
                            parseData(input);
                        }
                        else {
                            //Serial.println("Keep Moving");
                            parseData(input);
                        }
                    }
                    else{
                        //Serial.println("Normal mode");
                        if (client.available()) {
                            while(client.available()) input = client.readStringUntil('+');
                            parseData(input);
                        }
                        else robot.home();
                    }
            }
    } 
    else if (botMode == "demo") {
        while(true){
            parseData("9");
            parseData("13");
            parseData("13");
            parseData("13");
            parseData("");
            parseData("");
            parseData("");
            parseData("");

            parseData("1");
            parseData("1");
            parseData("1");
            parseData("1");
            parseData("1");

            parseData("");
            parseData("");
            parseData("");
            parseData("");

            parseData("12");
            parseData("12");
            parseData("12");
            parseData("12");
            parseData("13");
            parseData("13");
            parseData("12");
            parseData("12");
            parseData("13");
            parseData("13");
            parseData("");

            parseData("2");
            parseData("2");
            parseData("2");
            parseData("2");

            parseData("3");
            parseData("3");
            parseData("3");
            parseData("3");
            parseData("3");
            
            parseData("13");
            parseData("13");
            parseData("13");

            parseData("6");
            parseData("6");
            
            parseData("12");
            parseData("12");
            parseData("12");

            parseData("7");
            parseData("7");
            parseData("7");

            parseData("11");
            parseData("11");
            parseData("11");

            parseData("");
            parseData("");

            parseData("10");
            parseData("10");
            parseData("10");
            parseData("10");

            parseData("");

            parseData("1");
            parseData("1");
            parseData("1");
            parseData("1");
            parseData("1");
           
        }
    }
}
void parseData(String data){
    Serial.println("Data:" + data);
    switch (data.toInt()){

        case 1: // Up
            robot.walk(1,550);
            running = 1;
            break;

        case 2: // Down
            break;

        case 3: // Left
            robot.turnL(1,550);
            running = 1;
            break;

        case 4: // Right
            robot.turnR(1,550);
            running = 1;
            break;

        case 5: // STOP
            running = 0;
            break;

        case 6: // heart
            robot.pushUp(2,2000);
            running = 1;
            break;

        case 7: // fire
            robot.upDown(4,800);
            running = 1;
            break;

        case 8: // skull
            robot.jump();
            running = 1;
            break;

        case 9: // cross
            robot.hello();
            running = 1;
            break;

        case 10: // punch
            robot.frontBack(4,800);
            running = 1;
            break;

        case 11: // mask
            robot.dance(2,1000);
            running = 1;
            break;
        
        case 12: // mask
            robot.standtall();
            running = 1;
            break;
        
        case 13: // mask
            robot.zero();
            running = 1;
            break;
        case 14: // mask
            robot.moonwalkL(2,800);
            running = 1;
            break;

        //case 15: //calibrate 


        default:
            robot.home();
            break;
    }
}
