/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-ble-server-client/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#ifndef BLE_H
#define BLE_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Wire.h>

//BLE server name
#define bleServerName "ESP32-DHT11"

bool deviceConnected = false;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"

BLECharacteristic TemperatureCharacteristics("f78ebbff-c8b7-4107-93de-889a6a06d408", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor TemperatureDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic HumidityCharacteristics("ca73b3ba-39f6-4ab3-91ae-186dc9577d99", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor HumidityDescriptor(BLEUUID((uint16_t)0x2903));

//Setup callbacks onConnect and onDisconnect
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

void setup() {
  // Create the BLE Device
  BLEDevice::init(bleServerName);

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *dht11Service = pServer->createService(SERVICE_UUID);

  // Create BLE Characteristics and Create a BLE Descriptor
  // Temperature
  dht11Service->addCharacteristic(&TemperatureCharacteristics);
  dht11TemperatureDescriptor.setValue("temperature");
  dht11TemperatureCharacteristics.addDescriptor(&TemperatureDescriptor);

  // Humidity
  dht11Service->addCharacteristic(&HumidityCharacteristics);
  dht11HumidityDescriptor.setValue("humidity");
  dht11HumidityCharacteristics.addDescriptor(new BLE2902());
  
  // Start the service
  dht11Service->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void loop_ble() {
    //Notify temperature reading from BME sensor
    static char temperatureFTemp[6];
    dtostrf(t, 6, 2, temperatureFTemp);
    //Set temperature Characteristic value and notify connected client
    TemperatureCharacteristics.setValue(temperatureFTemp);
    TemperatureCharacteristics.notify();
      
    //Notify humidity reading from BME
    static char humidityTemp[6];
    dtostrf(h, 6, 2, humidityTemp);
    //Set humidity Characteristic value and notify connected client
    bmeHumidityCharacteristics.setValue(humidityTemp);
    bmeHumidityCharacteristics.notify();    
}

#endif /* BLE_H */
