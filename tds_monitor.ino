#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4   // DS18B20 cam chan D4
#define TDS_PIN A1       // TDS module cam chan A1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 28);
  display.println("  Dang khoi dong...");
  display.display();
  delay(3000);
}

void loop() {
  // Buoc 1: doc nhiet do
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  // Buoc 2: doc TDS 10 lan, lay trung binh giam nhieu
  int rawSum = 0;
  for (int i = 0; i < 10; i++) {
    rawSum += analogRead(TDS_PIN);
    delay(10);
  }
  float voltage = (rawSum / 10.0) * 5.0 / 1024.0;

  // Buoc 3: bu nhiet do vao dien ap truoc (theo DFRobot, ISO 7888)
  float compensatedV = voltage / (1.0 + 0.02 * (temp - 25.0));

  // Buoc 4: tinh TDS tu dien ap da bu nhiet do
  float tds = (133.42 * compensatedV * compensatedV * compensatedV
             - 255.86 * compensatedV * compensatedV
             + 857.39 * compensatedV) * 0.5;

  // Buoc 5: xac dinh trang thai rieng le cho TDS va nhiet do
  bool tdsOK  = (tds <= 1000);
  bool tempOK = (temp <= 30);

  String statusLine;
  if (tdsOK && tempOK) {
    statusLine = "DAT QCVN";
  } else if (!tdsOK && tempOK) {
    statusLine = "VUOT QCVN: TDS CAO";
  } else if (tdsOK && !tempOK) {
    statusLine = "NUOC NONG (TDS OK)";
  } else {
    statusLine = "VUOT QCVN: TDS+NHIET";
  }

  // Buoc 6: in ra Serial Monitor de kiem tra
  Serial.print("Nhiet do: "); Serial.print(temp, 1);
  Serial.print("C | TDS: "); Serial.print(tds, 0);
  Serial.print(" ppm | "); Serial.println(statusLine);

  // Buoc 7: hien thi len OLED
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("DO CHAT LUONG NUOC");
  display.drawLine(0, 10, 127, 10, WHITE);
  display.setTextSize(2);
  display.setCursor(0, 14);
  display.print("T:"); display.print(temp, 1); display.println("C");
  display.setCursor(0, 34);
  display.print("TDS:"); display.print((int)tds); display.println("ppm");
  display.setTextSize(1);
  display.setCursor(0, 56);
  display.println(statusLine);
  display.display();

  delay(1000);
}

