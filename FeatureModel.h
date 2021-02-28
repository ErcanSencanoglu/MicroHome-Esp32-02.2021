typedef struct FeatureModel{
  int id;
  int value;
  int featureType_id;//struct ile değiştirilerbilir;
  int minValue;
  int maxValue;
  //int* pins;//////pinler silinebilir
  struct FeatureModel* next;
};

/*typedef struct FeatureType{
  int id;
};*/
