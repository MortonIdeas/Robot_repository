const int LED_PIN = 13;

int getVelocity(char symbol)
{
  if(symbol == '1')
  {
    return 100;
  }
  else if(symbol == '2')
  {
    return 120;
  }
  else if(symbol == '3')
  {
    return 140;
  }
  else if(symbol == '4')
  {
    return 160;
  }
  else if(symbol == '5')
  {
    return 180;
  }
  else if(symbol == '6')
  {
    return 200;
  }
  else if(symbol == '7')
  {
    return 220;
  }
  else if(symbol == '8')
  {
    return 240;
  }
  else if(symbol == '9')
  {
    return 255;
  }
  else
  {
    return 0;
  }
}

bool isNumber(char symbol)
{
  if(symbol=='0'||symbol=='1'||symbol=='2'||symbol=='3'||symbol=='4'||symbol=='5'||symbol=='6'||symbol=='7'||symbol=='8'||symbol=='9')
  {
    return true;
  }
  else
  {
    return false;
  }

}
void setup() 
{
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() 
{ 
  if (Serial.available() >= 2) 
  {
    // Odczytanie dwóch bajtów
    char byte1 = Serial.read();
    char byte2 = Serial.read();
    

    //Czasami wysyła sie w odwrotnej kolejnosci
    if(isNumber(byte1))
    {
      char buf = byte1;
      byte1 = byte2;
      byte2 = buf;
    }
  
    if (byte1 == 'A') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, val);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
    if (byte1 == 'B') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, 9*val/10);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
  if (byte1 == 'C') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, 8*val/10);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
  if (byte1 == 'D') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, 7*val/10);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
    if (byte1 == 'E')     {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, 6*val/10);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
    if (byte1 == 'F') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, 6*val/10);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'G') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, 7*val/10);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'H') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, 8*val/10);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'I') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val/5);
      analogWrite(5, 9*val/10);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'J') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, val);
      analogWrite(5, val);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'K') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, 9*val/10);
      analogWrite(5, val);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'L') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, 8*val/10);
      analogWrite(5, val);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'M') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, 7*val/10);
      analogWrite(5, val);

      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'N') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, 6*val/10);
      analogWrite(5, val);

      digitalWrite(7, HIGH); 
      digitalWrite(8, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }
    if (byte1 == 'O') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, 6*val/10);
      analogWrite(5, val);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
    if (byte1 == 'P')
    {
      int val = getVelocity(byte2);
      analogWrite(6, 7*val/10);
      analogWrite(5, val);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
    if (byte1 == 'R') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, 8*val/10);
      analogWrite(5, val);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
    if (byte1 == 'S') 
    {
      int val = getVelocity(byte2);
      analogWrite(6, 9*val/10);
      analogWrite(5, val);

      digitalWrite(7, LOW); 
      digitalWrite(8, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
    }
    
    if (byte1 == 'Z') 
    {
      digitalWrite(7, HIGH); 
      digitalWrite(8, HIGH);
      digitalWrite(4, HIGH); 
      digitalWrite(3, HIGH);
    }
  }
}
