#include <NTPClient.h>
// change next line to use with another board/shield
#include <WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid = "TP-LINK_3DB3";     // type your ssid
const char *password = "chengmaohua";  // type your password

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
// NTPClient(UDP& udp, const char* poolServerName, long timeOffset, unsigned long updateInterval);
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 28800, 60000);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getDay());

  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}
