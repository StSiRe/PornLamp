IPAddress apIP(192, 168, 1, 1);
const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer wserver(80);

//************Vars*************************

String titleHTML = ""
"<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Hooli Smart Lamp</title>";
String styleStartHTML = "<style>";
String styleBodyHTML = ""
"body {"
"  background: #76b852;"
"  background: -webkit-linear-gradient(right, #76b852, #8DC26F);"
"  background: -moz-linear-gradient(right, #76b852, #8DC26F);"
"  background: -o-linear-gradient(right, #76b852, #8DC26F);"
"  background: linear-gradient(to left, #76b852, #8DC26F);"
"  font-family: 'Roboto', sans-serif;"
"  -webkit-font-smoothing: antialiased;"
"  -moz-osx-font-smoothing: grayscale;"
"}";
String styleFormHTML = ""
".form {"
"  position: relative;"
"  z-index: 1;"
"  background: #FFFFFF;"
"  max-width: 360px;"
"  margin: 0 auto 100px;"
"  padding: 45px;"
"  text-align: center;"
"  box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);"
"}";
String styleLoginPageHTML = ""
".login-page {"
"  width: 360px;"
"  padding: 8% 0 0;"
"  margin: auto;"
"}";
String styleInputHTML = ""
".form input {"
"  outline: 0;"
"  background: #f2f2f2;"
"  width: 100%;"
"  border: 0;"
"  margin: 0 0 15px;"
"  padding: 15px;"
"  box-sizing: border-box;"
"  font-size: 14px;"
"}";
String styleButtonHTML = ""
".form button {"
"  text-transform: uppercase;"
"  outline: 0;"
"  background: #4CAF50;"
"  width: 100%;"
"  border: 0;"
"  padding: 15px;"
"  color: #FFFFFF;"
"  font-size: 14px;"
"  -webkit-transition: all 0.3 ease;"
"  transition: all 0.3 ease;"
"  cursor: pointer;"
"}"
".form button:hover,.form button:active,.form button:focus {"
"  background: #43A047;"
"}";
String styleEndHTML = "</style>";
String bodyStartHTML = ""
"</head>"
"<body>";
String loginPageHTML = ""
"<div class='login-page'>"
"  <div class='form'>"
"    <form class='login-form' action='/ssid'>"
"      <p>"
"         Please enter the name and password of your WiFi router:"
"      </p>"
"      <input name=ssid type='text' required placeholder='ssid'/>"
"      <input name=passwd type='password' required placeholder='password'/>"
"      <button>Save</button>"
"    </form>"
"  </div>"
"</div>";
String bodyEndHTML = ""
"</body>"
"</html>";
String registationOkHTML = ""
"<div class='login-page'>"
"  <div class='form'>"
"    <form class='login-form'>"
"      <p>Please connect your device to your WiFi Access Point</p>"
"        <p>And open in your browser <a href = 'www.lamp.com'>this site</a></p>"
"</form>"
"</div>"
"</div>";

//**********Methods***********************************
void initWiFiManager()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  //WiFi.softAP("SMW Lamp","12345678");
  WiFi.softAP("Free WiFi(1-8)","12345678");
  dnsServer.start(DNS_PORT, "*", apIP);
  wserver.on("/hotspot-detect.html", handleAppleCaptivePortal);
  wserver.on("/generate_204", handleAndroidCaptivePortal);
  wserver.on("/", handleRoot);
  wserver.on("/ssid",handleData);
  wserver.begin();
}

void checkWiFiManager()
{
  dnsServer.processNextRequest();
  wserver.handleClient();
  delay(1);
}
//*************Handles*********************
void handleRoot()
{
  wserver.send(200,"text/html",loginPage());
}
void handleAppleCaptivePortal() 
{
    wserver.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    wserver.sendHeader("Pragma", "no-cache");
    wserver.sendHeader("Expires", "-1");
    wserver.send(200, "text/html", loginPage());
    return;
}
void handleAndroidCaptivePortal() 
{
    wserver.send(200, "text/html", loginPage());
    return;
}
void handleData()
{
  Serial.println("Start parsing data");
  ssidName = wserver.arg("ssid");
  ssidPassword = wserver.arg("passwd");
  Serial.println(ssidName);
  Serial.println(ssidPassword);
  isFirstStart = 1;
  saveConfig();
  wserver.send(200,"text/html",registrOkPage());
  delay(2000);
  ESP.restart();
}
//*****************Pages****************************
String loginPage()
{
  String page = "";
  page+=titleHTML;
  page+=styleStartHTML;
  page+=styleBodyHTML;
  page+=styleFormHTML;
  page+=styleLoginPageHTML;
  page+=styleInputHTML;
  page+=styleButtonHTML;
  page+=styleEndHTML;
  page+=bodyStartHTML;
  page+=loginPageHTML;
  page+=bodyEndHTML;
  return page;
}
String registrOkPage()
{
  String page = "";
  page+=titleHTML;
  page+=styleStartHTML;
  page+=styleBodyHTML;
  page+=styleFormHTML;
  page+=styleLoginPageHTML;
  page+=styleInputHTML;
  page+=styleButtonHTML;
  page+=styleEndHTML;
  page+=bodyStartHTML;
  page+=registationOkHTML;
  page+=bodyEndHTML;
  return page;
}
