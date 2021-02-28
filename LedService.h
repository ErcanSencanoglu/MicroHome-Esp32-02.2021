

class LedService : public IFeature
{
 private:
   
   int pin1 = -1,pin2 = -1;
   virtual void AttachPins()
   {
    PinConnectionService pinConnectionService;
    /*while(pin1 == -1 || pin2 == -1){
     pin1=-1;pin2=-1;
     PinConnectionModel* p = pinConnectionService.getPinConnectionsByFeatureID(feature_id);
     PinConnectionModel* head = p;
     while(p != NULL){
       if(p->sensorPin->pinNo == 1){
        pin1 = p->devicePin->pinNo;
       }
       else if (p->sensorPin->pinNo == 2){
        pin2 = p->devicePin->pinNo;
       }
       p = p->next;
      }/**************Bu pin metodu coklu pini olan servisler için kullanılacak. Tekli pin olanlar için kısa olanı kullanılacak ve ledservice teki burası degısecek************
      free(head);
      }  */
       while(pin1 == -1){
       pin1=-1;
       PinConnectionModel* p = pinConnectionService.getPinConnectionsByFeatureID(feature_id);
       pin1 = p->devicePin->pinNo;
       free(p);
     }
    pinMode(pin1,OUTPUT);
   }

public:
  LedService(){featureType_id = 29;}
  LedService(int feature_id):IFeature(feature_id)
  { 
     AttachPins();
  }
 

  virtual IFeature* create(int feature_id){
        return new LedService(feature_id);
  }

  virtual size_t getSize(){
    return sizeof(LedService);
  }
  virtual void Set(){
   FeatureModel *fModel = featureService->Get(feature_id);
   if(fModel == NULL)return;
   if(fModel->value == 1)
   {
      digitalWrite(pin1,HIGH);
      if(digitalRead(pin1)== HIGH){
         DeleteOrder();
      }      
    }
    else if(fModel->value == 0)
    {
      digitalWrite(pin1,LOW);
      if(digitalRead(pin1) == LOW){
        DeleteOrder();
      }    
    }
    free(fModel);
  }

 bool UpdateFt(){
    //FeatureModel * fModel = (FeatureModel *)(malloc(sizeof(FeatureModel)));//String ataması yapmıyor.
    FeatureModel fModel;
    fModel.id = feature_id; 
    if(digitalRead(pin1) == HIGH){fModel.value = 1;}
    else{fModel.value = 0;}
    bool response = featureService->Put(&fModel);
    return response;   
  }

  bool DeleteOrder(){
    bool response =  featureService->DeleteOrder(feature_id);
    return response;
  }
};
