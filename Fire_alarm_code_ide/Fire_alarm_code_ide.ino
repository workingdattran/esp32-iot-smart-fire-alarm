// UNG DUNG BLYNK
#define BLYNK_TEMPLATE_ID "TMPL6L32zKbOt"
#define BLYNK_TEMPLATE_NAME "canh bao chay"
#define BLYNK_AUTH_TOKEN "Idwma_e2VzbXsg908DoQbjc-EwgPvWH0"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // THU VIEN CHO LCD

//  THONG TIN WIFI
char ssid[] = "wifi";
char pass[] = "password";

#define PIN_BUZZER  11 // COI
#define PIN_FLAME   3  // LUA 
#define PIN_GAS     8  // GAS
#define PIN_DHT     9  // NHIET DO

// CHAN I2C CHO LCD
#define I2C_SDA     4
#define I2C_SCL     5

#define DHTTYPE DHT11   
DHT dht(PIN_DHT, DHTTYPE, 15); 

// LCD 16 COT, 2 HANG
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// NGUONG BAO DONG
int GAS_THRESHOLD = 1500;        
float TEMP_THRESHOLD_C = 37.0;   

BlynkTimer timer;
bool isAlarming = false;
unsigned long lastBuzzerToggle = 0; 
bool buzzerState = LOW;

// Ham doc cam bien va hien thi (chay moi 2 giay)
void processSensors() {
  int flameState = digitalRead(PIN_FLAME);
  int gasValue = analogRead(PIN_GAS);
  float tempC = dht.readTemperature();

  // In ra Serial Monitor và gửi Blynk
  if (isnan(tempC)) {
    Serial.print("Loi doc DHT11! | ");
  } else {
    Serial.print("Nhiet do: "); Serial.print(tempC); Serial.print("C | ");
    Blynk.virtualWrite(V0, tempC); 
  }

  Serial.print("Lua: ");  Serial.print(flameState);
  Serial.print(" | Khoi: "); Serial.println(gasValue);

  
  Blynk.virtualWrite(V1, gasValue); 

  // Logic Bao Chay 
  bool isFire   = (flameState == HIGH);  
  bool isGas    = (gasValue > GAS_THRESHOLD);
  bool isHot    = (!isnan(tempC) && tempC > TEMP_THRESHOLD_C); 

  // Xử lý logic và gửi cảnh báo
  if (isFire || isGas || isHot) {
    if (!isAlarming) { //tranh spam bao hieu
      Serial.println("CANH BAO: PHAT HIEN NGUY CO CHAY NO!");
      Blynk.logEvent("cnh_bo_nguy_c_chy_n", "Cảnh báo nguy cơ cháy nổ!"); 
      isAlarming = true;
    }
  } else {
    isAlarming = false;
  }
  
  Blynk.virtualWrite(V2, isAlarming ? 1 : 0); 

  // HIEN THI LCD
  lcd.clear(); // XOA CU
  // hien thi nhiet do va gas (dong 1)
  lcd.setCursor(0, 0);
  if (!isnan(tempC)) {
    lcd.print("T:"); 
    lcd.print(tempC, 1); // In 1 số thập phân
    lcd.print("C ");
  } else {
    lcd.print("T:ERR ");
  }
  lcd.print("G:");
  lcd.print(gasValue);

  // Dòng 2: Hiển thị trạng thái an toàn / báo cháy
  lcd.setCursor(0, 1);
  if (isAlarming) {
    if (isFire) lcd.print("BAO CHAY: LUA!  ");
    else if (isGas) lcd.print("BAO CHAY: KHI GAS");
    else if (isHot) lcd.print("BAO CHAY: Nh.DO! ");
  } else {
    lcd.print("   AN TOAN     ");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW); 
  //pinMode(PIN_FLAME, INPUT_PULLUP);
  pinMode(PIN_FLAME, INPUT_PULLDOWN);

  dht.begin();

  // Khởi tạo I2C và LCD
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Khong hoat dong..");
  
  Serial.println("Dang ket noi WiFi va Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" WiFi Connected!");
  delay(1000); 

  timer.setInterval(2000, processSensors);

  Serial.println("=======================================");
  Serial.println("He thong bao chay ESP32 da san sang!");
  Serial.println("=======================================");
}

void loop() {
  Blynk.run();
  timer.run();
  
  if (isAlarming) {
    if (millis() - lastBuzzerToggle >= 150) {
      buzzerState = !buzzerState;
      digitalWrite(PIN_BUZZER, buzzerState);
      lastBuzzerToggle = millis();
    }
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }
}