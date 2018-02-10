#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza

  char* kodMorsa[]{".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
  char litery[]{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','v','w','x','y','z'};
  int MAX=23;
 char Porownaj(char* wejscie){
   for(int i=0;i<MAX;i++)
   {
    if(wejscie==kodMorsa[i])
    return litery[i];
   }
   return "!";
 }
  
void setup() {
  lcd.begin(16, 2); //Deklaracja typu
  
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(8, LOW); // czerwona dioda
  digitalWrite(12, LOW); // zielona dioda
  digitalWrite(13, LOW); // żółta dioda
  pinMode(14, INPUT_PULLUP); // nowy znak
  pinMode(15, INPUT_PULLUP); // nastepneSlowo
  pinMode(16, INPUT_PULLUP); // nastepnaLitera
  pinMode(17, INPUT_PULLUP); // koniecProgramu
  
  
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Maszyna Moors'a"); //Wyświetlenie tekstu
}
void loop() {
  int dotDelay = 200;
  int rozmiarWejscia;
  char* wejscie[4];
  lcd.setCursor(0, 1); //Ustawienie kursora w odpowiednim momencie
  while(digitalRead(17) == HIGH)
  {
    while(digitalRead(15) == HIGH)
    {
      while(digitalRead(16) == HIGH&&rozmiarWejscia<4 )
      {
        digitalWrite(13, HIGH);
        delay(dotDelay);
        if(digitalRead(14) == LOW)
        {
          wejscie[rozmiarWejscia]='.';
          digitalWrite(13, LOW);
          delay(dotDelay);
        }
        else
        {
          wejscie[rozmiarWejscia]='-';
          digitalWrite(13, LOW);
          delay(dotDelay);
        }
        rozmiarWejscia++;
      }
      char* temp[rozmiarWejscia];
      for(int i=0;i<rozmiarWejscia;i++)
        temp[i]=wejscie[i];
      if(Porownaj(temp)=='!')
      {
        lcd.print('!');
        digitalWrite(8, HIGH);
        delay(dotDelay);
        digitalWrite(8, LOW);
      }
      else
      {
        char tekst;
          Serial.print(Porownaj(temp));
        digitalWrite(12, HIGH);
        delay(dotDelay);
        digitalWrite(12, LOW);
      }
      rozmiarWejscia=0;
    }
    lcd.print(" ");
  }
    if (digitalRead(14) == LOW) { //Jeśli przycisk wciśnięty
    digitalWrite(8, HIGH); //Włącz diodę
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    lcd.print("Wcisniety");
  } else { //Jeśli warunek nie został spełniony (przycisk nie jest wciśnięty)
    digitalWrite(8, LOW); //Wyłącz diodę
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
     lcd.print("Wycisniety");
  }
  delay(250); //Opóźnienie
}
