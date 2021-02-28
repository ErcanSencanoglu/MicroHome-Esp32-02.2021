
class ControllerService{
  public:
    String Get(String path)// path alınacak
    {
      if(WiFi.status() == WL_CONNECTED)
      {
       String link = String(Config::base_url) + String(path);
       HTTPClient http;
       http.begin(link);
       http.addHeader("Content-Type", "application/json");
       http.setConnectTimeout(3000);
       int httpCode = http.GET();
       if(httpCode > 0) { 
          Serial.println(httpCode);
          if(httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              Serial.println(payload);
              http.end(); 
              return payload;
           }
           else{
            return "Error";
           }
       }
       else {
           http.end(); 
           return http.errorToString(httpCode).c_str();
       }
     }
     else 
     {
        return "Wifi Error";
     }
   }

   bool Delete(String path)
   {
      Serial.println(path);
      WiFiClient client;
      if(WiFi.status() == WL_CONNECTED)
      {
        char* withoutHtppLink = &Config::base_url[7]; 
        if (client.connect(withoutHtppLink,80))
        {
         client.print("DELETE "+ String(path) + " HTTP/1.1\r\n" +
                       "Host: " + String(withoutHtppLink) + "\r\n" +
                       "Connection: close\r\n" +
                       "\r\n"
                      );
          String line = client.readStringUntil('\n');
          //while (client.connected() || client.available())
          //{
          Serial.println(line);
             if(line.indexOf("200") > 0){
              return true;
             }
          //}
          client.stop();
        }
        else
        {
          client.stop();
        }
     }
     else 
     {
        return false;
     }
     return false;
   }
   
   bool Put(String path, String payload){
     if(WiFi.status() == WL_CONNECTED)
     {
       String link = String(Config::base_url) + String(path);
       HTTPClient http;
       http.begin(link);
       http.addHeader("Content-Type", "application/json");
       http.setConnectTimeout(3000);
        
       int httpCode = http.PUT(payload);
       Serial.println(httpCode);
       if(httpCode > 0) { 
          if(httpCode == HTTP_CODE_OK) {
              String response = http.getString();
              http.end(); 
              return true;
           }
           else{
            return false;
           }
       }
       else
       {
           Serial.println(http.errorToString(httpCode).c_str());
           http.end(); 
           return false;
       }
     }
     else 
     {
        return false;
     }
    }
  
};
