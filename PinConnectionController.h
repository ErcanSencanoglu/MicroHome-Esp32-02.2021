class PinConnectionController
{

private:
  ControllerService *controlService;
public:
    PinConnectionController() 
    {
      controlService = new ControllerService();
    }
   /* ~PinConnectionController()
    {
      delete controlService;
    }*/
    String getPinConnectionsByFeatureID(int feature_id){
       String link = String("/pinconnection/feature/"+String(feature_id));
       String payload = controlService->Get(link);
       return payload;
    }
};
