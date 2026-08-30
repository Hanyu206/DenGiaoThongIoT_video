#define BLYNK_TEMPLATE_ID "TMPL6vGjltW6r"
#define BLYNK_TEMPLATE_NAME "DenGiaoThongIoT"
#define BLYNK_AUTH_TOKEN "hvB5c9asX26FPTdPBU2de2YlcM1S3TbF"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define LED_GREEN  16
#define LED_YELLOW 17
#define LED_RED    19

LiquidCrystal_I2C lcd(0x27, 16, 2);

int thoiGianXanh = 8;
bool cheDoUuTien = false;
int soXeNhanDuoc = 0;   

BLYNK_WRITE(V0) {
  soXeNhanDuoc = param.asInt();
}

BLYNK_WRITE(V2) {
  cheDoUuTien = param.asInt();
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V2);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dang khoi dong..");

  Blynk.begin(auth, ssid, pass);
  lcd.clear();
}

void loop() {
  Blynk.run();

  if (cheDoUuTien) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);

    Blynk.virtualWrite(V3, "UU TIEN");
    Blynk.virtualWrite(V4, 99);

    lcd.setCursor(0, 0);
    lcd.print("CHEDO: UU TIEN! ");
    lcd.setCursor(0, 1);
    lcd.print("XE CAP CUU PASS ");
    delay(500);
    return;
  }

 int soXe = soXeNhanDuoc;
const char* matDo;
if (soXe >= 12) {
  thoiGianXanh = 15;
  matDo = "CAO!    ";
} else if (soXe >= 6) {
  thoiGianXanh = 8;
  matDo = "TR.BINH ";
} else {
  thoiGianXanh = 5;
  matDo = "THAP    ";
}
  Blynk.virtualWrite(V1, thoiGianXanh);

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  Blynk.virtualWrite(V3, "XANH");

  for (int i = thoiGianXanh; i > 0; i--) {
    Blynk.run();
    if (cheDoUuTien) break;

    Blynk.virtualWrite(V4, i);

    char line0[17];
    snprintf(line0, sizeof(line0), "XANH:%-2ds Xe:%-3d", i, soXe);
    lcd.setCursor(0, 0);
    lcd.print(line0);
    lcd.setCursor(0, 1);
    lcd.print("MAT DO: ");
    lcd.print(matDo);

    delay(1000);
  }

  if (cheDoUuTien) return;

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED, LOW);
  Blynk.virtualWrite(V3, "VANG");

  for (int i = 2; i > 0; i--) {
    Blynk.run();
    if (cheDoUuTien) break;

    Blynk.virtualWrite(V4, i);

    char line0[17];
    snprintf(line0, sizeof(line0), "VANG:%-2ds Xe:%-3d", i, soXe);
    lcd.setCursor(0, 0);
    lcd.print(line0);
    lcd.setCursor(0, 1);
    lcd.print("CHUAN BI DUNG   ");
    delay(1000);
  }

  if (cheDoUuTien) return;

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, HIGH);
  Blynk.virtualWrite(V3, "DO");

  for (int i = 5; i > 0; i--) {
    Blynk.run();
    if (cheDoUuTien) break;

    Blynk.virtualWrite(V4, i);

    char line0[17];
    snprintf(line0, sizeof(line0), "DO:%-2ds Xe:%-3d  ", i, soXe);
    lcd.setCursor(0, 0);
    lcd.print(line0);

    lcd.setCursor(0, 1);
    lcd.print("DUNG XE LAI     ");
    delay(1000);
  }
}
