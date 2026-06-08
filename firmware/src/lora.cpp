#include "LoRa_E220.h"
#include "gps.h"

LoRa_E220 e220ttl(&Serial1);

void send_message(String message){
    e220ttl.sendMessage(message);
}

void send_gps(){
    e220ttl.sendMessage("LAT: " + String(getLatitude()) + " LON: " + String(getLongitude()));
}

void listen_to_message(){ //next include string library and return the string value
    unsigned long listening_start_time = millis();

    while (millis() - listening_start_time < 10000){ //Listening for 10 seconds
    if (e220ttl.available()>1) {
        // read the String message
        ResponseContainer rc = e220ttl.receiveMessage();
        // Is something goes wrong print error
        if (rc.status.code!=1){
            rc.status.getResponseDescription();
        }else{
            // Print the data received
            Serial.println(rc.data);
            }
        }
    }
}