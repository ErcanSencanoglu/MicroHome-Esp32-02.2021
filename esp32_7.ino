#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h> 
#include <string>

#include "Config.cpp"
#include "Const.cpp"
#include "WifiBluetoothService.h"
#include "FeatureModel.h"
#include "PinConnectionModel.h"
#include "ControllerService.h"
#include "FeatureController.h"
#include "PinConnectionController.h"
#include "OrderController.h"
#include "FeatureService.h"
#include "PinConnectionService.h"
#include "IFeature.h"
#include "LedService.h"
#include "RelayService.h"


std::vector<IFeature*> usedServices;

void setup() {
  LedService led;
  RelayService relay;
  IFeature* services[] = {&led,&relay};  
 
  //IFeature* services[] = CreatedFeatures::services;
  Serial.begin(115200);
  Serial.println("Starting");
  WifiBluetoothService::connectWifi();
  Serial.println("Started");
  delay(2000);
  
   FeatureService featureService;
   FeatureModel* f = featureService.getAllFeatures();
   FeatureModel *head = f;
   while(f != NULL){
     int lengthOfServices = sizeof(services)/sizeof(services[0]); 
     for(int j=0; j<lengthOfServices;j++)//size değişeecek
     {
      if(services[j]->getFeatureType_id() == f->featureType_id){ 
        IFeature* feature = services[j]->create(f->id); 
        usedServices.push_back(feature);
      }
     }
     f = f->next;
   }
   free(head);
}


void loop() {
 Serial.println("***************************");
 for(int i = 0; i<usedServices.size();i++){
    usedServices.at(i)->Set();
    usedServices.at(i)->UpdateFt();
  }
  delay(200);
}

void restart(){
   for(uint8_t t = 2; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }
}
