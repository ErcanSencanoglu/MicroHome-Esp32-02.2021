

class OrderController
{

private:
  ControllerService *controlService;
public:
    OrderController() 
    {
      controlService = new ControllerService();//çalısmıyor sebebini bilmiyorum
    }
    /*~OrderController()
    {
      delete controlService;
    }*/
    String GetOrderByFeatureID(int feature_id){
       ControllerService *controlS = new ControllerService();// diğer şekilde hata verdiği için kısa bir çözüm olarak ayarlandı.
       String path = String("/order/feature/"+String(feature_id)+"/device/"+String(Config::device_id));
       String payload = controlS->Get(path);
       delete controlS;
       return payload;
    }
    /*
    void Put(int feature_id, String payload){
      String link = String("http://micro19.herokuapp.com/order/feature"+String(feature_id));
      bool response = controlService->Put(link,payload);
    }*/
    bool Delete(int feature_id){
      ControllerService *controlS = new ControllerService();
      String path = "/order/feature/"+String(feature_id)+"/device/"+String(Config::device_id);
      bool response = controlS->Delete(path);
      delete controlS;
      return response;
    }

   
};
