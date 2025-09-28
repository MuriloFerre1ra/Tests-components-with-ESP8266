#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(4, 3);

void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando GPS...");
  ss.begin(4800);
}

void loop() {
  // Variáveis GPS
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);

  // Satélites e HDOP
  Serial.print("Satélites: ");
  Serial.print(gps.satellites());
  Serial.print(" | HDOP: ");
  Serial.println(gps.hdop());

  // Latitude e Longitude
  if (flat == TinyGPS::GPS_INVALID_F_ANGLE || flon == TinyGPS::GPS_INVALID_F_ANGLE) {
    Serial.println("Localização: inválida");
  } else {
    Serial.print("Latitude: ");
    Serial.print(flat, 6);
    Serial.print(" | Longitude: ");
    Serial.println(flon, 6);
  }

  // Data e hora
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE) {
    Serial.println("Data/Hora: inválida");
  } else {
    Serial.print("Data: ");
    Serial.print(day); Serial.print("/");
    Serial.print(month); Serial.print("/");
    Serial.print(year);
    Serial.print(" | Hora: ");
    Serial.print(hour); Serial.print(":");
    Serial.print(minute); Serial.print(":");
    Serial.println(second);
  }

  // Altitude
  float alt = gps.f_altitude();
  if (alt == TinyGPS::GPS_INVALID_F_ALTITUDE) {
    Serial.println("Altitude: inválida");
  } else {
    Serial.print("Altitude: ");
    Serial.print(alt, 2);
    Serial.println(" m");
  }

  // Velocidade
  float speed = gps.f_speed_kmph();
  if (speed == TinyGPS::GPS_INVALID_F_SPEED) {
    Serial.println("Velocidade: inválida");
  } else {
    Serial.print("Velocidade: ");
    Serial.print(speed, 2);
    Serial.println(" km/h");
  }

  Serial.println("---------------------------------------");

  // Alimenta o GPS enquanto espera
  smartDelay(1000);
}

// Função para manter leitura do GPS enquanto espera
void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available()) {
      gps.encode(ss.read());
    }
  } while (millis() - start < ms);
}
