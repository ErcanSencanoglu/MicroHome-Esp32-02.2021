class FeatureController
{

private:
  ControllerService *controlService;
public:
    FeatureController() 
    {
      controlService = new ControllerService();
    }
   /* ~FeatureController()
    {
      delete controlService;
    }*/
    String getAllFeatures(){
      String path = String("/feature/device/"+String(Config::device_id));
      String payload = controlService->Get(path);
      return payload;
    }
    bool Put(String payload){
      String path = String("/feature/device/"+String(Config::device_id));
      bool response = controlService->Put(path,payload);
      return response;
    }
 
};
