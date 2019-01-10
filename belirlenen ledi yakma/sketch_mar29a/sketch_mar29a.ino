
byte led_no=0;

boolean arttir_butonu;
boolean azalt_butonu;

void setup() 
{
 pinMode(2,INPUT);
 pinMode(4,INPUT);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(10,OUTPUT);
 Serial.begin(9600);
 

}

void loop() 

{
  arttir_butonu =digitalRead(2);
  azalt_butonu=digitalRead(4);


if (led_no ==3 && led_no<=255)
         {
              Serial.println("Başka led yok ");
              delay(1000);
              led_no=3;
              }


  if (arttir_butonu==true)
  {
//    if(led_no > 3)
//    led_no=3;
    
    led_no++;
    Serial.print("led numarası:");
    Serial.println(led_no);
//  digitalWrite(led_no, HIGH);
   
    
    
    delay(250);

    }else if (azalt_butonu==true)
            {
//              if(led_no >3 )
//              led_no=3;            
              
              led_no--;
              Serial.print("led numarası:");
              Serial.println(led_no);

             delay(250); 
             } 
//else if (led_no >3 && led_no<=255)
//             {
//              Serial.println("Başka led yok , en başa dönülüyor !!");
//              led_no=0;
//              }

              



             
switch(led_no)
{
  case 1:
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  break;
  
  case 2:
  digitalWrite(9, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  break;

  case 3:
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  break;

  default:
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  
  break;
}
}
