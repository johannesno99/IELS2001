// Bibliotek
#include <Adafruit_GPS.h>

//Kobler GPS kommunikasjon til Serial2 på ESP32
//kan ha den på serial1 med mp ha RX1 og TX1 isåfall
#define GPSSerial Serial2

//variabel for å få ut GPS til serial kommunikasjon
Adafruit_GPS GPS(&GPSSerial);

void setup() {
  Serial.begin(115200);
  // Starter GPS ved 9600 baud
  GPS.begin(9600); 

  /* Denne kommandoen gjør at vi både får sendt ut RMC som står
  for (Recommended Minumum Navigation information) samt GGA som står 
  for (Global Positioning System Fix data) som NMEA - setninger */
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); 

  // Dette bestemmer oppdateringsfrekvensen til GPS'en
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
}

void loop() {
  if (!GPS.fix)
  {
    Serial.println("ingen posisjon");
    delay(2500);
  }
  /* Denne while setningen sjekker om det er kommet en ny 
  NMEA setning med informasjon som skal printes ut */
  while (!GPS.newNMEAreceived()) {
    GPS.read(); // Denne leser av for å se om det kommen noe  
  }

  /* henter ut den NMEA informasjonen som ble sist lagret på GPS'en
  og deretter parser denne, dette vil si å analysere NMEA informasjonen
  som er lagret og trekke ut den informasjonen vi ønsker å printe */
    //dekrypterer NMEA - setningen
  if (GPS.parse(GPS.lastNMEA())) {
      // fortelles oss om kvalitet, fra 1 - 6
      Serial.print("Kvalitet: ");
      Serial.println(GPS.fixquality);
      delay(2500);
      
      // sier hvor mange satelitter den er koblet til
      Serial.print("Antall satellitter: ");
      Serial.println((int)GPS.satellites);
      delay(2500);
      
    if (GPS.fix == true) {// Sjekker om GPS har en "fix", altså en posisjon å logge
      // printe ut informasjonen som er sendt: 
      Serial.print("Lokasjon: ");
      Serial.print(GPS.latitude, 4);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4);
      Serial.println(".");
    }
  }
}

