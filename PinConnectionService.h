class PinConnectionService
{
private:
PinConnectionController* pinConnectionController;
public:
    PinConnectionService(){
      pinConnectionController = new PinConnectionController();
    }
    /* ~PinConnectionService()
    {
      delete pinConnectionController;
    }*/
   PinConnectionModel* getPinConnectionsByFeatureID(int featureID){
      String payload = pinConnectionController->getPinConnectionsByFeatureID(featureID);
      PinConnectionModel* pinConnectionModel = ConvertToModelArray(payload);
      return pinConnectionModel;
   }

  private:
    
    PinConnectionModel* ConvertToModelArray(String payload){
      const size_t oneConnectionSize = Const::one_pin_connection_size;
      const size_t capacity = oneConnectionSize*6;//6 değişmeli dinamik olarak ayarlanmalı
      DynamicJsonDocument doc(capacity);
      DeserializationError error = deserializeJson(doc, payload);
      if (error) 
      {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return NULL;
      }
     PinConnectionModel* head = NULL;
     PinConnectionModel* previous = head;
     bool control = true;
     int i = 0;
     while(control){
        JsonObject root = doc[i++];
        if(root == NULL){return head;}
        const char* pinConnection_description = root["description"];
        
        JsonObject root_devicePin = root["devicePin"];
        int devicePin_pinNo = root_devicePin["pinNo"];
        const char* devicePin_description = root_devicePin["description"];
        PinModel* devicePin = (PinModel*)malloc(sizeof(PinModel));
        devicePin->pinNo = devicePin_pinNo;
        devicePin->description = devicePin_description;
  
        JsonObject root_sensorPin = root["serPinpin"];
        int sensorPin_pinNo = root_sensorPin["pinNo"]; // 1
        const char* sensorPin_description = root_sensorPin["pinDescription"];
        PinModel* sensorPin = (PinModel*)malloc(sizeof(PinModel)); 
        sensorPin->pinNo = sensorPin_pinNo;
        sensorPin->description = sensorPin_description;
        
  
        PinConnectionModel *node = (PinConnectionModel*)malloc(sizeof(PinConnectionModel)); 
        node->description = pinConnection_description;
        node->devicePin = devicePin;
        node->sensorPin = sensorPin;
        node->next = NULL;
        if(head != NULL){
          previous->next = node;
          previous = node;
        }else{
          head = node;
          previous = node;
        }
      }
  
    
      return head;

}

 
};
