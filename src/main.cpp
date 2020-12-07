#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define CE_TX 9
#define CSN_TX 10
RF24 TxRadio(CE_TX,CSN_TX);

const uint64_t radioAddress = 0xB00B1E5000LL;

#define TX_INPUT_PIN A2

void setup() {
	TxRadio.begin();
	TxRadio.setAutoAck(1);
	TxRadio.setRetries(5,15);
	TxRadio.openWritingPipe(radioAddress);
	TxRadio.stopListening();
	TxRadio.printDetails();

	Serial.begin(115200);
}

void loop() {
	unsigned int input = analogRead(TX_INPUT_PIN);

	Serial.print("Transmitting: ");
	Serial.println(input);

	unsigned long startTime = micros();

	if(TxRadio.write(&input,sizeof(input))){
		unsigned int elapsedTime = micros() - startTime; 

		Serial.print("Ack received for ");
		Serial.print(input);
		Serial.print(" elapsed time: ");
		Serial.println(elapsedTime);
	}else{
		Serial.print("Failed transmission of ");
		Serial.println(input);
	}


	delay(1000);
}