class WifiBluetoothService{
  public:
  static void connectWifi(){
    /*IPAddress ip =WiFi.localIP();//WiFi.localIP();// WiFi.softAPIP();
    IPAddress gateway(192,168,1,1);   
    IPAddress subnet(255,255,255,0);  */
    //IPAddress dns(8,8,8,8);
    WiFi.begin(Config::ssid,Config::password);
    //WiFi.config(ip,gateway, subnet);
    while(WiFi.status() != WL_CONNECTED){
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
    Serial.println(WiFi.localIP());
  }
};
