class FeatureService
{
private:
FeatureController* featureController;
OrderController* orderController;
public:
    FeatureService(){
      featureController = new FeatureController();
      orderController = new OrderController();
    }
   /* ~FeatureService()
    {
      delete featureController;
      delete orderController;
    }*/
   FeatureModel* Get(int feature_id)//bu static
   {     
      String payload = orderController->GetOrderByFeatureID(feature_id);
      if(payload == "")return NULL;
      FeatureModel *fModel = ConvertToModel(payload);
      return fModel;
   }
 
   bool Put(FeatureModel *fModel)
   {
      String payload = ConvertToText(fModel);
      bool response = featureController->Put(payload); 
      return response; 
   }

   bool DeleteOrder(int feature_id)
   {
      bool response = orderController->Delete(feature_id);
      return response;
   }
   
   FeatureModel* getAllFeatures(){
      String payload = featureController->getAllFeatures();
      FeatureModel* fModel = ConvertToModelArray(payload);
      return fModel;
   }

  private:  
  FeatureModel* ConvertToModel(String payload)
  {
     DynamicJsonDocument doc(Const::one_order_model_size);
     DeserializationError error = deserializeJson(doc, payload);
     if (error) 
     {
       Serial.print(F("deserializeJson() failed: "));
       Serial.println(error.c_str());
       return NULL;
    }
   
    //FeatureModel *fModel = (FeatureModel *)(malloc(sizeof(FeatureModel))); //String ataması yapmıyor.
    //FeatureModel fModel = {doc[0]["ID"], doc[0]["Value"]};
    FeatureModel* fModel = new FeatureModel();
    int id = doc["id"];
    int value = doc["value"]; 
    fModel->id = id;
    fModel->value = value;
    return fModel;
  }

  FeatureModel* ConvertToModelArray(String payload){
    const size_t capacity = (Const::one_feature_model_ize)*Const::feature_count;
    DynamicJsonDocument doc(capacity);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) 
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return NULL;
    }
   FeatureModel* head = NULL;
   FeatureModel* previous = head;
   bool control = true;
   int i = 0;
   while(control){
      JsonObject root = doc[i++];
      if(root == NULL){return head;}
      JsonObject root_featureType = root["featureType"];
      int root_id = root["id"];
      int root_value = root["value"];
      int root_featureType_id = root_featureType["id"];
      int root_min_input_value = 99999999;
      int root_max_input_value = -1;
      //int* root_pins = (int*)malloc(sizeof(int));//pin degerleri farklı bir controllerdan alındı


      /****************Input degerleri farklı bir controller ile alınabilir******************/
      bool controlInput = true;
      int j = 0;
      while(controlInput){
        JsonObject root_featureType_ioValue = root_featureType["ioValues"][j++];
        if(root_featureType_ioValue == NULL){break;}
            int root_featureType_ioValue_input = root_featureType_ioValue["input"]; 
            if(root_min_input_value>root_featureType_ioValue_input){root_min_input_value =root_featureType_ioValue_input;}
            if(root_max_input_value < root_featureType_ioValue_input){root_max_input_value = root_featureType_ioValue_input;}
      }
      /********************************************************************************/
      /*********Pinler farklı bir controllerdan alındı************/
      /*int k = 0;
      while(controlInput){
             JsonObject root_pinConnections = root["pinConnections"][k++];
             if(root_pinConnections == NULL){break;}
             JsonObject root_pinConnections_devicePin = root_pinConnections["devicePin"];
             int root_pinConnections_devicePin_pinNo = root_pinConnections_devicePin["pinNo"];
             root_pins =(int*)realloc(root_pins,k*sizeof(int));//hata olursa kontrol edilmeli
             root_pins[k-1] = root_pinConnections_devicePin_pinNo;
      }*/
      /********************************/
      FeatureModel *node = (FeatureModel*)malloc(sizeof(FeatureModel)); 
      node->id = root_id;  
      node->value = root_value;
      node->featureType_id = root_featureType_id;
      node->minValue = root_min_input_value;
      node->maxValue = root_max_input_value;
      //node->pins = root_pins;//pinlere modelde gerek yok
      
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

  String ConvertToText(FeatureModel* fModel)
  {
    const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3);//size config dosyasından alınabilirdi fakat buyuk bir featureModel gerekmediğinden burdan alındı.
    DynamicJsonDocument doc(capacity);
    String payload;
    JsonObject doc_0 = doc.createNestedObject();
    doc_0["id"] = fModel->id;
    doc_0["value"] = fModel->value;
    serializeJson(doc, payload);
    payload = payload.substring(1,payload.length()-1);
    return payload;
  }
  
 
};
