#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

#define SDA_PIN 21
#define SCL_PIN 22

void setup(void)
{
  Serial.begin(115200);
  Serial.println("ESP32 + ADS1115 Example");

  // เริ่มต้น I2C โดยกำหนดขา SDA, SCL เอง
  Wire.begin(SDA_PIN, SCL_PIN, 400000); // 400kHz I2C speed

  // เริ่มต้น ADS1115
  if (!ads.begin(0x48, &Wire)) {  // 0x48 คือ I2C address ปกติ
    Serial.println("❌ Failed to initialize ADS1115!");
    while (1);
  }

  // ตั้งค่า gain (ช่วงแรงดันอินพุต)
  ads.setGain(GAIN_TWOTHIRDS); 

  Serial.println("ADS1115 Initialized!");
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  // อ่านค่า 4 ช่องของ ADS1115
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  // แปลงค่าเป็นโวลต์
  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

  // แสดงผล
  Serial.println("-----------------------------------------------------------");
  Serial.printf("AIN0: %6d  %7.5f V\n", adc0, volts0);
  Serial.printf("AIN1: %6d  %7.5f V\n", adc1, volts1);
  Serial.printf("AIN2: %6d  %7.5f V\n", adc2, volts2);
  Serial.printf("AIN3: %6d  %7.5f V\n", adc3, volts3);
  
  delay(1000);
}
