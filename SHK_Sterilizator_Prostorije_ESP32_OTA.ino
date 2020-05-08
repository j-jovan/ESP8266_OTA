<<<<<<< HEAD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "PMS.h"
#include <mySD.h>

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);
PMS::DATA data;

// PMS7003 pinovi
#define RXD2 34
#define TXD2 35

// Vreme
unsigned long timeNow = 0;
unsigned long timeLast = 0;

int startingHour = 0;

int seconds = 0;
int minutes = 0;
//

File root;

const char* host = "esp32";
const char* ssid = "Zmaj i Ala";
const char* password = "88888888";

WebServer server(80);

const char* loginIndex =
  "<form name='loginForm'>"
  "<table width='20%' bgcolor='A09F9F' align='center'>"
  "<tr>"
  "<td colspan=2>"
  "<center><font size=4><b>ESP32 Login Page</b></font></center>"
  "<br>"
  "</td>"
  "<br>"
  "<br>"
  "</tr>"
  "<td>Username:</td>"
  "<td><input type='text' size=25 name='userid'><br></td>"
  "</tr>"
  "<br>"
  "<br>"
  "<tr>"
  "<td>Password:</td>"
  "<td><input type='Password' size=25 name='pwd'><br></td>"
  "<br>"
  "<br>"
  "</tr>"
  "<tr>"
  "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
  "</tr>"
  "</table>"
  "</form>"
  "<script>"
  "function check(form)"
  "{"
  "if(form.userid.value=='admin' && form.pwd.value=='admin')"
  "{"
  "window.open('/serverIndex')"
  "}"
  "else"
  "{"
  " alert('Error Password or Username')/*displays error message*/"
  "}"
  "}"
  "</script>";

//  Server Index Page

const char* serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>"
  "<div id='prg'>progress: 0%</div>"
  "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>";

void setup(void) {
  //https://9gag.com/gag/a9nbgyW
  Wire.begin(33, 32);
  Serial.begin(115200);


  SerialPMS.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pms.passiveMode();
  initKarticu();

  OTA();
  //pocetnaPoruka();

  //procitajFajl();
}

void loop(void) {
  server.handleClient();
  delay(1);

  timeNow = millis() / 1000;
  seconds = timeNow - timeLast;

  if (seconds == 60) {
    timeLast = timeNow;
    minutes = minutes + 1;

  }

  Serial.print("Vreme je: ");
  Serial.print(minutes);
  Serial.print(" minuta i ");
  Serial.print(seconds);
  Serial.println(" sekundi");

  if (seconds == 0) {
    pms.wakeUp();
    Serial.println("Budjenje");
  }
  if (seconds == 30) {
    pms.requestRead();
    //Serial.println("Zahtevaj citanje");
    if (pms.readUntil(data))  {
      Serial.print("PM 1.0 (ug/m3): ");
      Serial.println(data.PM_AE_UG_1_0);
      Serial.print("PM 2.5 (ug/m3): ");
      Serial.println(data.PM_AE_UG_2_5);
      Serial.print("PM 10.0 (ug/m3): ");
      Serial.println(data.PM_AE_UG_10_0);
      pmsSenzorDisplej();
    }
    else
      Serial.println("No data.");
  }
  pms.sleep();
  if (seconds == 60) {
    upisiNaKarticu(minutes);
  }
  delay(500);


}
=======
#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

void setup(void) {
  //https://9gag.com/gag/a9nbgyW

  Serial.begin(115200);
  LCDSetup();
  pms7003Setup();
  OTASetup();

  pocetnaPoruka();
  inicijalizacijaIPisanje();
  procitajFajl();
}

void loop(void) {
  PMS::DATA data;
  OTAHandleClient();
  delay(1);
  pms7003ReadData(data);
  pmsSenzorDisplej(data);
}
>>>>>>> 0d615caecf7a0b03f917186cdef9e8a53c229823
