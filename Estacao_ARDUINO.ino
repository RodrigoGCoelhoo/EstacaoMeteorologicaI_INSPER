#include <LiquidCrystal.h> 

// Inicialização do Display

const int rs = 12, en =11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Criacao de um caracter customizado

byte customChar[] = {
  B01110,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup()
{

  analogReference(INTERNAL); // Define a referência analógica
  
  // Inicia o display
  
  lcd.begin(16,2);            
  lcd.print("Estacao INSPER");
  lcd.setCursor(0,1);
  lcd.print("de Meteorologia");
  delay(3000);
  
  // Apresenta os integrantes
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Integrantes: Pedro     Victor   Rodrigo ");
  lcd.setCursor(0,1);
  lcd.print("             Sant'Ana  Assis    Coelho  ");
  delay(1000);
  for (int positionCounter = 0; positionCounter < 24; positionCounter++){
  	lcd.setCursor(0,0);
  	lcd.scrollDisplayLeft();
  	delay(200);
  }
  delay(500);
  
  // Inicia a rotina de printar as medições
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    MEDICOES    ");
  lcd.createChar(1, customChar); 
  
  delay(2000);
}


//Função de simulação do DHT22

float dht_lerUmidade()
{
  float umidade = analogRead(A2)/1.023;
  umidade -= 20 + random(41);            //Incerteza do DHT22
  if (umidade < 0) umidade = 0;
  if (umidade > 1000) umidade = 1000;
  return umidade/10.0;
}


//Função TMP36

float ler_voltagem_tmp36()
{
  int adc = analogRead(A0);
  float v = adc * (1.1/1023.0);
  return v;
}

void loop()
{
  
  //DHT 22
  
  float umid = dht_lerUmidade();
  
  umid = 0.926 * umid + 1.88;    //Calibração DHT22
  
  // Print da umidade
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Umidade:");
  lcd.setCursor(0,1);
  lcd.print(umid);
  lcd.print("% +/-2%");
  
  delay(2500);
  
  // Sensor de Luz
  
  int bin;
  double tensao, res, lum;
  
  bin = analogRead(A1);
  tensao = bin * 1.1 / 1023;
  res = 330 * (5.0 / tensao + 1);
  lum = pow(10, 5 - log10(res));
  
  // Print da luminosidade
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Luminosidade:");
  lcd.setCursor(0,1);
  lcd.print(lum, 3);
  lcd.print(" Lux");
  
  delay(2500);
  
  //TMP36
  
  float voltagem = ler_voltagem_tmp36();
  float temp;
  temp = 99.86 * voltagem - 50.28;       //Calibração TMP36
    
  // Print da Temperatura
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.print(" ");
  lcd.write(1);         
  lcd.print("C +/-0.1");
  
  delay(2500);
}

