class RelayService : public IFeature
{
  private:
   int pin1 = -1;
   virtual void AttachPins()//Parent classda tanımlanacak
   {
     PinConnectionService pinConnectionService;
     while(pin1 == -1){
       pin1=-1;
       PinConnectionModel* p = pinConnectionService.getPinConnectionsByFeatureID(feature_id);
       pin1 = p->devicePin->pinNo;
       free(p);
     }
     pinMode(pin1,OUTPUT);
   }
  public:
  RelayService(){featureType_id = 37;}
  RelayService(int feature_id):IFeature(feature_id)
  { 
     AttachPins();
  }
 
  virtual IFeature* create(int feature_id){
        return new RelayService(feature_id);//parametre alınacak
  }

  virtual size_t getSize(){
    return sizeof(RelayService);
  }
  
  virtual void Set(){
   FeatureModel *fModel = featureService->Get(feature_id);
   if(fModel == NULL)return;
   
   if(fModel->value == 1)
    {
      digitalWrite(pin1,LOW);
      if(digitalRead(pin1)== LOW){
        DeleteOrder();
      }      
    }
    else if(fModel->value == 0)
    {
      digitalWrite(pin1,HIGH);
      if(digitalRead(pin1) == HIGH){
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
