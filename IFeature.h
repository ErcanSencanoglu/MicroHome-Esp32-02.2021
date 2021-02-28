class IFeature{
  public:
  virtual IFeature* create(int feature_id) =0;
  virtual size_t getSize() =0;
  virtual void Set() = 0;
  virtual bool UpdateFt() =0;
  virtual bool DeleteOrder() = 0;//putorderstatus olmalı
  
  int getFeatureType_id(){
    return featureType_id;
  }
  IFeature(){};
  IFeature(int feature_id){
    this->feature_id = feature_id;
    featureService = (FeatureService*)malloc(sizeof(FeatureService));
  }
  /*~IFeature(){
    delete featureService;
  }*/
  private:
  virtual void AttachPins() = 0;
  protected:
  int featureType_id;
  int feature_id;
  FeatureService* featureService;
};
