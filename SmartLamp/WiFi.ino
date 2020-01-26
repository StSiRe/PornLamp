void initWiFi()
{
  if(isFirstStart == 1)//==0
  {
    initWiFiManager();
    while(true)
    {
      checkWiFiManager();
    }
  }
  else
  {
    connectWiFi();
    //Matrix
  }
}
bool connectWiFi()
{
  char ssid[ssidName.length()+1];
  char password[ssidPassword.length()+1];
  ssidName.toCharArray(ssid,ssidName.length()+1);
  ssidPassword.toCharArray(password,ssidPassword.length()+1);
  Serial.println(ssid);
  Serial.println(password);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {      
     delay(500);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}
