/*
 * EBYTE LoRa E22
 *
 * Send a string message to the all devices of channel 23
 *
 * Write a string on serial monitor or reset to resend default value.
 *
 * Send a fixed message, you must check that the transmitter and receiver have different
 * CHANNEL ADDL or ADDH, check the configuration down
 *
 * Pai attention e22 support RSSI, if you want use that functionality you must enable RSSI on configuration
 * configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;
 *
 * and uncomment #define ENABLE_RSSI true in this sketch
 *
 * You must select 3 devices, and you must use the configuration
 * BROADCAST MESSAGE 1
 * BROADCAST MESSAGE 2
 * BROADCAST MESSAGE 3
 *
 * Renzo Mischianti <https://www.mischianti.org>
 * https://www.mischianti.org/category/my-libraries/ebyte-lora-e22-devices/
 */

// If you want use RSSI uncomment //#define ENABLE_RSSI true
// and use relative configuration with RSSI enabled
//#define ENABLE_RSSI true

#include "Arduino.h"
#include "LoRa_E22.h"



LoRa_E22 e22ttl(13, 14, &Serial2, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 TX, RX, Serial, AUX, M0, M1
// -------------------------------------

void setup() {
  Serial.begin(9600);
  delay(500);

  // Startup all pins and UART
  e22ttl.begin();

  Serial.println("Hi, I'm going to send message!");

  // Send message
  ResponseStatus rs = e22ttl.sendBroadcastFixedMessage(23, "Hello, world?");
  // Check If there is some problem of succesfully send
  Serial.println(rs.getResponseDescription());
}

void loop() {
	// If something available
  if (e22ttl.available()>1) {
	  // read the String message
#ifdef ENABLE_RSSI
	ResponseContainer rc = e22ttl.receiveMessageRSSI();
#else
	ResponseContainer rc = e22ttl.receiveMessage();
#endif
	// Is something goes wrong print error
	if (rc.status.code!=1){
		Serial.println(rc.status.getResponseDescription());
	}else{
		// Print the data received
		Serial.println(rc.status.getResponseDescription());
		Serial.println(rc.data);
#ifdef ENABLE_RSSI
		Serial.print("RSSI: "); Serial.println(rc.rssi, DEC);
#endif
	}
  }
  if (Serial.available()) {
	  String input = Serial.readString();
	  ResponseStatus rs = e22ttl.sendBroadcastFixedMessage(23, input);
	  // Check If there is some problem of succesfully send
	  Serial.println(rs.getResponseDescription());

  }
}

