int pinBouton;
void setup()
{
    Serial.begin(9600);
    pinBouton=10;
    pinMode(pinBouton,INPUT);
}
void loop()
{
    boolean etatBouton=digitalRead(pinBouton);
    Serial.println(etatBouton);
}
