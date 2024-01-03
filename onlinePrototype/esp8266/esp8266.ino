#include "CTBot.h"
#include "Servo.h"

CTBot myBot;
String ssid = "(ssid wifi)";
String pass = "(pass wifi)";
String token = "(token dari telegram)";
const int id = 1537275575;

// KONFIG SERVO
Servo myServo;

// KONFIG SENSOR ULTRASONIK
// Mendefinisikan pin yang akan digunakan
const int trigPin = 14;
const int echoPin = 12;
// Mendefinisikan variabel yang diperlukan
long duration;
int distance, level;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }

  myBot.sendMessage(id, "Terhubung\n");
  Serial.println("Pesan Terkirim\n");

  // SERVO
  myServo.attach(15);

  // SENSOR ULTRASONIK
  pinMode(trigPin, OUTPUT); // trigPin sebagai output
  pinMode(echoPin, INPUT); // echoPin sebagai input
  delay(10);
}

/*
void sensorPing() {
  // SENSOR ULTRASONIK
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Menyalakan trigPin selama 10 microsekon
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Membaca echoPin, hasilnya adalah pantulan gelombang suara dari trigPin
      duration = pulseIn(echoPin, HIGH);
      // Menghitung jarak
      distance = (duration/2) / 29.1;
      level = 65 - distance;
      // Memperlihatkan hasil perhitungan di Serial Monitor
      Serial.print("Distance: ");
      Serial.println(distance);

    if (distance > 300 || distance <= 0){
      Serial.print("Di luar jangkauan");
    } else {
      Serial.print("Ketinggian: ");
      Serial.println(level);
    }

  delay(500);
} */

void loop() {
  TBMessage msg;

  //sensorPing;

	if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("CEK")) {
      Serial.print("CEK");
      String replyCek;
      level = 65 - distance;
      replyCek = (String)"Ketinggian air saat ini: " + level + (String)" cm";
      myBot.sendMessage(id, replyCek);
    }
		else { 
			// membalas pesan selain kode diatas
			String reply;
			reply = (String)"Selamat datang, " + msg.sender.username + (String)". Ketik CEK untuk melihat ketinggian air.";
			myBot.sendMessage(id, reply);         
		}
	}

  // Jika air berada di ketinggian kritis
  if (distance >= 1 && distance <= 45){
    myBot.sendMessage(id, "BAHAYA");
    myServo.write(90);
    delay(1000);
  } else if (distance > 45){
    myServo.write(0);
  }


// SENSOR ULTRASONIK
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Menyalakan trigPin selama 10 microsekon
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Membaca echoPin, hasilnya adalah pantulan gelombang suara dari trigPin
      duration = pulseIn(echoPin, HIGH);
      // Menghitung jarak
      //distance = 65 - (duration/2) / 29.1);
      distance = (duration/2) / 29.1;
      // Memperlihatkan hasil perhitungan di Serial Monitor
      //Serial.print("Distance: ");
      //Serial.println(distance);

    if (distance > 300 || distance <= 0){
      Serial.print("Di luar jangkauan");
    } else {
      Serial.print("Ketinggian: ");
      Serial.println(distance);
    }

  //delay(1000);

}