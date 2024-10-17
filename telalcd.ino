#include <SPFD5408_Adafruit_GFX.h>     // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h>  // Hardware-specific library
#include <SPFD5408_TouchScreen.h>

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 6   // can be a digital pin
#define XP 7   // can be a digital pin
#define LCD_CS A3
#define LCD_RS A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define WHITE 0x0000   //Black->White
#define YELLOW 0x001F  //Blue->Yellow
#define CYAN 0xF800    //Red->Cyan
#define PINK 0x07E0    //Green-> Pink
#define RED 0x07FF     //Cyan -> Red
#define GREEN 0xF81F   //Pink -> Green
#define BLUE 0xFFE0    //Yellow->Blue
#define BLACK 0xFFFF   //White-> Black
#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define TS_MINX 190
#define TS_MINY 150
#define TS_MAXX 880
#define TS_MAXY 890

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);               //300 is the sensitivity
Adafruit_TFTLCD tft(LCD_CS, LCD_RS, LCD_WR, LCD_RD, LCD_RESET);  //Start communication with LCD


void setup() {
  Serial.begin(9600);  //Use serial monitor for debugging
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.reset();         //Always reset at start
  tft.begin(0x9341);   // My LCD uses LIL9341 Interface driver IC
  tft.setRotation(2);  // I just roated so that the power jack faces up - optional
  tft.fillScreen(BLACK);


  // IntroScreen();
  // delay(3000);
  // DisplayResult();
  // delay(3000);
  // mostrarTelaRFID();
  // delay(3000);
  // telaErro();
  // delay(3000);
  // telaMenu();
  // delay(3000);
  // adicionarPonto();
  // delay(3000);
  // removerPonto();
  delay(3000);
  telaConfirmaResert();
}

void loop() {
}

TSPoint waitTouch() {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE));
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
  ;
  return p;
}

void DisplayResult() {
  tft.setCursor(10, 20);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
}

void IntroScreen() {
  tft.setCursor(70, 70);
  tft.setTextSize(5);
  tft.setTextColor(WHITE);
  tft.println("SEJA");

  tft.setCursor(80, 140);
  tft.println("BEM");

  tft.setCursor(30, 210);
  tft.setTextSize(4.5);
  tft.println("VINDO(A)");

  delay(3000);
}
void mostrarTelaRFID() {
  tft.fillScreen(BLACK);

  tft.setCursor(10, 50);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("APROXIME TAG");


  tft.fillCircle(120, 170, 20, WHITE);
  tft.drawCircle(120, 170, 40, WHITE);
  tft.drawCircle(120, 170, 60, WHITE);

  tft.setCursor(90, 260);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("RFID");
}

void telaErro() {
  tft.fillScreen(BLACK);

  tft.fillCircle(120, 90, 80, BLUE);

  tft.setCursor(85, 40);
  tft.setTextSize(15);
  tft.setTextColor(WHITE);
  tft.println("!");

  tft.setCursor(90, 190);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("ERRO:");
  tft.setCursor(15, 220);
  tft.println("CODIGO NAO EXISTE");

  tft.fillRect(80, 250, 90, 45, WHITE);
  tft.drawRoundRect(80, 250, 90, 45, 0, BLACK);
  tft.setCursor(105, 265);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("MENU");
}

void telaMenu() {
  tft.fillScreen(BLACK);

  tft.setCursor(60, 30);
  tft.setTextSize(5);
  tft.setTextColor(WHITE);
  tft.println("MENU");

  tft.fillRect(20, 100, 200, 45, WHITE);
  tft.setCursor(30, 115);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("ADICIONAR PONTO");

  tft.fillRect(20, 150, 200, 45, WHITE);
  tft.setCursor(80, 165);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("NOVO ID");

  tft.fillRect(20, 200, 200, 45, WHITE);
  tft.setCursor(50, 215);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("TROCAR NOME");

  tft.fillRect(20, 250, 200, 45, WHITE);
  tft.setCursor(30, 265);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("RESERTAR MODULO");
}

void tarefaConcluida() {
  tft.fillScreen(BLACK);

  tft.setCursor(70, 30);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("TAREFA");
  tft.setCursor(35, 60);
  tft.println("CONCLUIDA?");

  tft.fillRect(20, 120, 200, 45, WHITE);
  tft.setCursor(30, 130);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("ADICIONAR PONTO");

  tft.fillRect(20, 200, 200, 45, WHITE);
  tft.setCursor(40, 210);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("REMOVER PONTO");
}

void adicionarPonto() {
  tft.fillScreen(BLACK);

  tft.fillCircle(120, 90, 80, PINK);

  for (int i = 0; i < 8; i++) {
    tft.drawLine(85 + i, 75, 110 + i, 120, WHITE);
    tft.drawLine(110 + i, 120, 155 + i, 50, WHITE);
  }

  tft.setCursor(30, 190);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("PONTO ADICIONADO");

  tft.fillRect(80, 250, 90, 45, WHITE);
  tft.drawRoundRect(80, 250, 90, 45, 0, BLACK);
  tft.setCursor(100, 265);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("MENU");
}


void removerPonto() {
  tft.fillScreen(BLACK);

  tft.fillCircle(120, 90, 80, CYAN);

  tft.setCursor(85, 40);
  tft.setTextSize(15);
  tft.setTextColor(WHITE);
  tft.println("X");

  tft.setCursor(45, 190);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("PONTO REMOVIDO");

  tft.fillRect(80, 250, 90, 45, WHITE);
  tft.drawRoundRect(80, 250, 90, 45, 0, BLACK);
  tft.setCursor(100, 265);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("MENU");
}

void codigoAdicionado() {
  tft.fillScreen(BLACK);

  tft.fillCircle(120, 90, 80, PINK);

  for (int i = 0; i < 8; i++) {
    tft.drawLine(85 + i, 75, 110 + i, 120, WHITE);
    tft.drawLine(110 + i, 120, 155 + i, 50, WHITE);
  }

  tft.setCursor(30, 190);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("CODIGO ADICIONADO");

  tft.fillRect(80, 250, 90, 45, WHITE);
  tft.drawRoundRect(80, 250, 90, 45, 0, BLACK);
  tft.setCursor(100, 265);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("MENU");
}

void telaConfirmaResert() {
  tft.fillScreen(BLACK);

  tft.setCursor(65, 60);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("DESEJA");
  tft.setCursor(40, 100);
  tft.println("FORMATAR?");

  tft.fillRect(20, 150, 200, 45, WHITE);
  tft.setCursor(30, 160);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("RESERTAR MODULO");

  if ("resertar" == "errado") {
    tft.fillScreen(BLACK);

    tft.fillCircle(120, 90, 80, BLUE);

    tft.setCursor(85, 40);
    tft.setTextSize(15);
    tft.setTextColor(WHITE);
    tft.println("!");

    tft.setCursor(90, 190);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.println("ERRO:");
    tft.setCursor(15, 220);
    tft.println("NAO FOI POSSIVEL RESERTAR");

    tft.fillRect(80, 250, 90, 45, WHITE);
    tft.drawRoundRect(80, 250, 90, 45, 0, BLACK);
    tft.setCursor(105, 265);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("MENU");
  } else {
    tft.fillScreen(BLACK);

    tft.fillCircle(120, 90, 80, PINK);

    for (int i = 0; i < 8; i++) {
      tft.drawLine(85 + i, 75, 110 + i, 120, WHITE);
      tft.drawLine(110 + i, 120, 155 + i, 50, WHITE);
    }

    tft.setCursor(30, 190);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.println("RESETADO COM SUCESSO");

    tft.fillRect(80, 250, 90, 45, WHITE);
    tft.drawRoundRect(80, 250, 90, 45, 0, BLACK);
    tft.setCursor(100, 265);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("MENU");
  }
}