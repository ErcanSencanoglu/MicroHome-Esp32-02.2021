typedef struct PinModel{
  int pinNo;
  const char* description;
};

typedef struct PinConnectionModel{
  const char* description;
  PinModel* devicePin;
  PinModel* sensorPin;
  struct PinConnectionModel* next;
};
