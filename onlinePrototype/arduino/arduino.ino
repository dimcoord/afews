#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
String data; // Variabel yang akan digunakan sebagai input
char c; // Variabel yang akan digunakan untuk parsing input

// Mendefinisikan pin yang akan digunakan
const int trigPin = 9;
const int echoPin = 10;
// Mendefinisikan variabel yang diperlukan
long duration;
int distance;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(trigPin, OUTPUT); // trigPin sebagai output
  pinMode(echoPin, INPUT); // echoPin sebagai input
  delay(10);
}

void loop() {
  // Parsing input dari user lewat Telegram
  while(mySerial.available()>0){
    delay(10);
    c = mySerial.read();
    data += c;
  }
  
  if (data.length()>0) {
    Serial.println(data);
    if (data == "CEK") {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Menyalakan trigPin selama 10 microsekon
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Membaca echoPin, hasilnya adalah pantulan gelombang suara dari trigPin
      duration = pulseIn(echoPin, HIGH);
      // Menghitung jarak
      distance = duration * 0.034 / 2;
      // Memperlihatkan hasil perhitungan di Serial Monitor
      Serial.print("Distance: ");
      Serial.println(distance);
      mySerial.print(distance);
    }
    data = "";
  }
}
