#define Sensor_TC //Termocupla
#define Sensor_IR //MLX90614
#define Sensor_DS //DS18S20
#define Sensor_LM //LM335
#define Sensor_TR //Termistor
#define Sensor_PT //PT100
#define Sensor_HR

#define MemoriaSD
#define Reloj

//#define MedirTiempoMedicion
#define LamparaAuto

#define BT_Instalado

#include <TimerOne.h>

#include "RTClib.h"

RTC_DS1307 rtc;

//libreria para las termocuplas con el módulo Maxim6675
#include <max6675.h>

//Libreria para los sensores IR por comunicacion I2C

//#define Sparkfun
#define Adafruit

#include <Wire.h>
#ifdef Adafruit
  #include <Adafruit_MLX90614.h>
#endif
#ifdef Sparkfun
  #include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library
#endif
//Libreria sensor de temperatura DS18S20

#include <OneWire.h>
#include <DallasTemperature.h>

//Libreria SD
#ifdef MemoriaSD
  #include <SPI.h>
  #include <SD.h>
#endif

const int chipSelect = 53;

#include <dht.h>

#include <HX711.h>

#include "Variables.h"
#include "mostrarInfo.h"
#ifdef MemoriaSD
  #include "grabarSD.h"
#endif
#include "comunicacion.h"



// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();    
}

void setup() 
{

  for (unsigned char j=0; j<2; j++)
  {
    pinMode(pinLamp[j],OUTPUT);
    digitalWrite(pinLamp[j],HIGH);        
  }
  Serial.begin(115200);
  Serial.println("Modulo sensores de temperatura de globo negro");
  #ifdef Ajuste
    Serial.println("Temperaturas con ajuste");
  #endif

  #ifdef BT_Instalado
    Serial2.begin(9600);
  #endif

  pinMode(LED, OUTPUT);
/**************************************************************************************/
  //Inicio libreria sensores IR
  #ifdef Adafruit
    T_IR_1.begin();  
    T_IR_2.begin();  
    T_IR_3.begin();  
  #endif
  #ifdef Sparkfun
    T_IR_1.begin(0x70);  
    T_IR_2.begin(0x71);  
    T_IR_3.begin(0x72);  
    T_IR_1.setEmissivity(newEmissivity);
    T_IR_2.setEmissivity(newEmissivity);
    T_IR_3.setEmissivity(newEmissivity);
    T_IR_1.setUnit(TEMP_C);
    T_IR_2.setUnit(TEMP_C);
    T_IR_3.setUnit(TEMP_C);
  #endif
  
/**************************************************************************************/

/**************************************************************************************/
  //Inicio configuración sensores de temperatura DS18S20

  #ifdef Sensor_DS
    sensors.begin();
  
    // locate devices on the bus
    Serial.print("Locating devices...");
    Serial.print("Found ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" devices.");
  
    // report parasite power requirements
    Serial.print("Parasite power is: "); 
    if (sensors.isParasitePowerMode()) Serial.println("ON");
    else Serial.println("OFF");
  
    // Assign address manually. The addresses below will beed to be changed
    // to valid device addresses on your bus. Device address can be retrieved
    // by using either oneWire.search(deviceAddress) or individually via
    // sensors.getAddress(deviceAddress, index)
    
    // Search for devices on the bus and assign based on an index. Ideally,
    // you would do this to initially discover addresses on the bus and then 
    // use those addresses and manually assign them (see above) once you know 
    // the devices on your bus (and assuming they don't change).
    // 
    // method 1: by index
    if (!sensors.getAddress(T_DS_1, 0)) Serial.println("Unable to find address for Device 0"); 
    if (!sensors.getAddress(T_DS_2, 1)) Serial.println("Unable to find address for Device 1"); 
    if (!sensors.getAddress(T_DS_3, 2)) Serial.println("Unable to find address for Device 2"); 
    if (!sensors.getAddress(T_DS_4, 3)) Serial.println("Unable to find address for Device 3"); 
    //T_DS_1 = {0x28, 0x41, 0x8D, 0x9D, 0x05, 0x00, 0x00, 0x32}; //Esfera metálica grande
    //T_DS_2 = {0x28, 0xAB, 0x37, 0x9D, 0x05, 0x00, 0x00, 0x26}; //Esfera metálica pequeña
    //T_DS_3 = {0x28, 0xEB, 0x24, 0x9D, 0x05, 0x00, 0x00, 0x61}; //Esfera plástica
  
    // method 2: search()
    // search() looks for the next device. Returns 1 if a new address has been
    // returned. A zero might mean that the bus is shorted, there are no devices, 
    // or you have already retrieved all of them. It might be a good idea to 
    // check the CRC to make sure you didn't get garbage. The order is 
    // deterministic. You will always get the same devices in the same order
    //
    // Must be called before search()
    //oneWire.reset_search();
    // assigns the first address found to insideThermometer
    //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");
    // assigns the seconds address found to outsideThermometer
    //if (!oneWire.search(outsideThermometer)) Serial.println("Unable to find address for outsideThermometer");
  
    // show the addresses we found on the bus
    Serial.print("Device 0 Address: ");
    printAddress(T_DS_1);
    Serial.println();
  
    Serial.print("Device 1 Address: ");
    printAddress(T_DS_2);
    Serial.println();

    Serial.print("Device 2 Address: ");
    printAddress(T_DS_3);
    Serial.println();

    Serial.print("Device 2 Address: ");
    printAddress(T_DS_4);
    Serial.println();
  
    // set the resolution to 9 bit per device
    sensors.setResolution(T_DS_1, TEMPERATURE_PRECISION);
    sensors.setResolution(T_DS_2, TEMPERATURE_PRECISION);
    sensors.setResolution(T_DS_3, TEMPERATURE_PRECISION);
    sensors.setResolution(T_DS_4, TEMPERATURE_PRECISION);
    
    Serial.print("Device 0 Resolution: ");
    Serial.print(sensors.getResolution(T_DS_1), DEC); 
    Serial.println();
  
    Serial.print("Device 1 Resolution: ");
    Serial.print(sensors.getResolution(T_DS_2), DEC); 
    Serial.println();
    
    Serial.print("Device 2 Resolution: ");
    Serial.print(sensors.getResolution(T_DS_3), DEC); 
    Serial.println();

    Serial.print("Device 3 Resolution: ");
    Serial.print(sensors.getResolution(T_DS_4), DEC); 
    Serial.println();
    
  #endif
/**************************************************************************************/  

/**************************************************************************************/  
  #ifdef MemoriaSD
    Serial.print("Initializing SD card...");

    if (!SD.begin(chipSelect))
    {
      Serial.println("Card failed, or not present");      
      SDInicializada = false;    
      digitalWrite(LED,HIGH);        
    }
    else
    {
      Serial.println("card initialized.");
      SDInicializada = true;    
      digitalWrite(LED,LOW);        
    }
  #endif
/**************************************************************************************/  

/**************************************************************************************/  
  #ifdef Reloj
    Serial.println("RTC test");  
    rtc.begin();
  
  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    if (! rtc.isrunning()) {
      Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
  #endif
/**************************************************************************************/  

  Timer1.initialize(1000000);  // Se activa la interrupción cada 1 segundo
  Timer1.attachInterrupt(Tiempo);
}


void loop() {
  
  t_inicio = millis();   
  #ifdef MemoriaSD 
    if (grabarSD_Now)
    {
      leerReloj();
      grabarDatos();
      grabarSD_Now = false;
    }
  #endif
  switch (leerSensor)
  {
    case 1:       
      //Lee la temperatura de las termocuplas
      for (unsigned char i= 0; i<NUM_TC; i++)
      {
        for (unsigned char j=0; j<NUM_MEDICIONES; j++)
        {     
          switch(i)
          {
          case 0:
            Mediciones[j] = thermocouple1.readCelsius(); 
            if (Mediciones[j] < 10)
              Mediciones[j] = thermocouple1.readCelsius(); 
            break;
          case 1:
            Mediciones[j] = thermocouple2.readCelsius();
            if (Mediciones[j] < 10)
              Mediciones[j] = thermocouple2.readCelsius(); 
            break;
          case 2:
            Mediciones[j] = thermocouple3.readCelsius();
            if (Mediciones[j] < 10)
              Mediciones[j] = thermocouple3.readCelsius(); 
            break;        
          } 
          /*               
          if (isnan(Mediciones[j]))
            Mediciones[j] = 0;
          delay(10);
          */
        }  
        
        organizarVector(Mediciones);
        
        Temp_TC[i] = medicionTotal;
        #ifdef Ajuste
          Temp_TC[i] = TCp1[i]*Temp_TC[i]+TCp2[i];
        #endif
      }
      #ifdef MedirTiempoMedicion
        Serial.print("Termocuplas ");
      #endif          
      break;
    case 2:
      //Lee las temperaturas de los sensores IR
      for (unsigned char i=0; i<NUM_IR; i++)
      {
        for (unsigned char j=0; j<NUM_MEDICIONES; j++)
        {      
          switch(i)
          {
          case 0:
            #ifdef Adafruit            
              Mediciones1[j] = T_IR_1.readObjectTempC();
              Mediciones2[j] = T_IR_1.readAmbientTempC();
            #endif
            #ifdef Sparkfun
              T_IR_1.read();
              Mediciones1[j]= T_IR_1.object();
              Mediciones2[j]= T_IR_1.ambient();
            #endif
            break;
          case 1:
            #ifdef Adafruit            
              Mediciones1[j] = T_IR_2.readObjectTempC();
              Mediciones2[j] = T_IR_2.readAmbientTempC();
            #endif
            #ifdef Sparkfun
              T_IR_2.read();
              Mediciones1[j]= T_IR_2.object();
              Mediciones2[j]= T_IR_2.ambient();
            #endif
            break;
          case 2:
            #ifdef Adafruit            
              Mediciones1[j] = T_IR_3.readObjectTempC();
              Mediciones2[j] = T_IR_3.readAmbientTempC();
            #endif
            #ifdef Sparkfun
              T_IR_3.read();
              Mediciones1[j]= T_IR_3.object();
              Mediciones2[j]= T_IR_3.ambient();
            #endif
            break;
          }
       
          organizarVector(Mediciones1);
        
          Temp_Obj_T_IR[i] = medicionTotal;
                  
          #ifdef Ajuste
            Temp_Obj_T_IR[i] = TIROp1[i]*Temp_Obj_T_IR[i]+TIROp2[i];
          #endif
                
          organizarVector(Mediciones2);
                        
          Temp_Amb_T_IR[i] = medicionTotal;
          #ifdef Ajuste
            Temp_Amb_T_IR[i] = TIRAp1[i]*Temp_Amb_T_IR[i]+TIRAp2[i];
          #endif      
        }
      }     
      #ifdef MedirTiempoMedicion
        Serial.print("IR ");
      #endif      
      break;
    case 3:
      //Leer sensores de temperatura DS18S20      
      for (unsigned char j=0; j<NUM_MEDICIONES_DS; j++)
      { 
        sensors.requestTemperatures();             
        for (unsigned char i=0; i<NUM_DS; i++)
        {              
          switch(i)
          {
          case 0:
            MedicionesDS[i][j] = sensors.getTempC(T_DS_1); 
            break;
          case 1:
            MedicionesDS[i][j] = sensors.getTempC(T_DS_2);
            break;
          case 2:
            MedicionesDS[i][j] = sensors.getTempC(T_DS_3);
            break;
          case 3:
            MedicionesDS[i][j] = sensors.getTempC(T_DS_4);        
          }
        }
      }    
      for (unsigned char i=0; i<NUM_DS; i++)
      {
        for (unsigned char j=0; j<NUM_MEDICIONES; j++)
        {
          Mediciones[j] = MedicionesDS[i][j];
        }
        organizarVector(Mediciones);      
        Temp_DS[i] = medicionTotal;      
        #ifdef Ajuste
          Temp_DS[i] = TDSp1[i]*Temp_DS[i]+TDSp2[i];
        #endif    
      } 
      #ifdef MedirTiempoMedicion                             
        Serial.print("DS ");
      #endif    
      break;
    case 4:
      //Lee los sensores de temperatura LM335
      for (unsigned char i=0; i<NUM_LM335; i++)
      {      
        for (unsigned char j=0; j<NUM_MEDICIONES; j++)
        {       
          Mediciones[j]= analogRead(pin_LM335[i]);        
        }
  
        organizarVector(Mediciones);       
                        
        Temp_LM335_AN[i] =  medicionTotal;     
              
        Temp_LM335_F[i] = a_LM335[i]*Temp_LM335_AN[i]+b_LM335[i]-273.15; 
        
        #ifdef Ajuste
          Temp_LM335_F[i] = TLMp1[i]*Temp_LM335_F[i]+TLMp2[i];
        #endif                   
      }
      #ifdef MedirTiempoMedicion
        Serial.print("LM ");
      #endif    
      break;
    case 5:
      //Lee los termistores de temperatura      
      for (unsigned char i=0; i<NUM_TERM; i++)
      {
        for (unsigned char j=0; j<NUM_MEDICIONES; j++)
        {       
          Mediciones[j]= analogRead(pin_Term[i]);        
        }
  
        organizarVector(Mediciones);       
                        
        Temp_Term_AN[i] =  medicionTotal;
        
        RT[i] = R[i]*((1024.0/Temp_Term_AN[i]) - 1.0);
        Temp_Term_F[i] = (float(beta)*T0)/(float(beta)+T0*log(RT[i]/R0))-273.15; 
        #ifdef Ajuste
          Temp_Term_F[i] = TTermp1[i]*Temp_Term_F[i]+TTermp2[i];
        #endif            
      }       
      #ifdef MedirTiempoMedicion
        Serial.print("Term ");
      #endif    
      break;
    case 6:
      //Lee los sensores PT100
      for (unsigned char i=0; i<NUM_PT; i++)
      {
        for (unsigned char j=0; j<NUM_MEDICIONES; j++)
        { 
          switch (i)
          {
          case 0:
            Mediciones[j]= float(PT1.read());
            break;
          case 1:
            Mediciones[j]= float(PT2.read());
            break;
          case 2:
            Mediciones[j]= float(PT3.read());
            break;               
          }                  
        }        
  
        organizarVector(Mediciones);       
                        
        PT100_An[i] =  medicionTotal;                
      }       
      #ifdef MedirTiempoMedicion
        Serial.print("PT ");
      #endif    
      break;     
    case 7:
      //Lee el sensor de humedad relativa y su temperatura
      for (unsigned char j=0; j<NUM_MEDICIONES; j++)
      {       
        DHT.read22(DHT22_PIN);
        Mediciones1[j]= DHT.humidity;              
        Mediciones2[j]= DHT.temperature;              
      }    
      
      organizarVector(Mediciones1);       
                        
      humedad =  medicionTotal;
      
      organizarVector(Mediciones2);       
  
      temperaturaHR =  medicionTotal;     
      #ifdef MedirTiempoMedicion
        Serial.print("HR ");
      #endif    
      break;
    }
    if(leerSensor<7)
      leerSensor ++;
    else
      leerSensor = 1;
    #ifdef MedirTiempoMedicion  
      Tiempo_t();
    #endif  
    
    /**************************************************************************************/

  #ifdef MemoriaSD 
    if (grabarSD_Now)
    {
      leerReloj();
      grabarDatos();
      grabarSD_Now = false;
    }
  #endif
    
    /**************************************************************************************/     
     if((millis()-tiempoInfo) > T_INFO)
     {
       leerReloj();
       MostrarInfo();
       #ifdef BT_Instalado
        if (mostrarInfoBT)
          InfoBT();
       #endif
       tiempoInfo = millis();       
     }     
    
    /**************************************************************************************/    
    #ifdef MemoriaSD 
      if (grabarSD_Now)
      {
      leerReloj();
      grabarDatos();
      grabarSD_Now = false;
      }
    #endif
    /**************************************************************************************/    
    #ifdef LamparaAuto
      #ifdef Reloj
        if((millis()-t_CheckTime) > T_CHECK_TIME)
        {
          //Serial.println("Check time");
          verificar_tiempos();
          t_CheckTime = millis();
        }
      #endif
    #endif
    /**************************************************************************************/
}

void organizarVector(float Med[NUM_MEDICIONES])
{
  float aux;
  for (int i=0; i<(NUM_MEDICIONES-1);i++)
  {
    for(int j=0; j<(NUM_MEDICIONES-1-i);j++)
    {
      if (Med[j] > Med[j+1])
      {
        aux = Med[j+1];
        Med[j+1] = Med[j];
        Med[j] = aux;
      }
    }
  }
  
  float totalSum=0;
  for (int i=2; i<NUM_MEDICIONES-2; i++)
  {
    totalSum += Med[i];
  }
   
  medicionTotal =  totalSum / (NUM_MEDICIONES-4); 
  return;
}

void organizarVectorDS(float Med[NUM_MEDICIONES_DS])
{
  float aux;
  for (int i=0; i<(NUM_MEDICIONES_DS-1);i++)
  {
    for(int j=0; j<(NUM_MEDICIONES_DS-1-i);j++)
    {
      if (Med[j] > Med[j+1])
      {
        aux = Med[j+1];
        Med[j+1] = Med[j];
        Med[j] = aux;
      }
    }
  }
  
  float totalSum=0;
  for (int i=1; i<NUM_MEDICIONES-1; i++)
  {
    totalSum += Med[i];
  }
   
  medicionTotal =  totalSum / (NUM_MEDICIONES-2); 
  return;
}


void Tiempo_t()
{
  Serial.print("t=");
  Serial.println(millis()-t_inicio);
  return;
}


void Tiempo(void)
{  
  seg ++;  // incrementa el contador de seg  
  if (seg>=15)
  {
    seg=0;    
    #ifdef MemoriaSD      
      grabarSD_Now = true;
    #endif    
  }      
}

void verificar_tiempos()
{
  DateTime now = rtc.now();
  unsigned int tHora = now.hour();
  //unsigned int tHora = now.minute();
  for (int i=0; i < sizeof(HORA_ON); i++)
  {             
    if (tHora == HORA_ON[i] && tHora != tHoraOldOn)
    {
      encendido = true;
      tHoraOldOn = tHora;
      for (unsigned char j=0; j<2; j++)
      {
        digitalWrite(pinLamp[j],LOW);        
        digitalWrite(LED, HIGH);
      }
    }     
    if (tHora == HORA_OFF[i] && tHora != tHoraOldOff)
    {
      encendido = false;
      tHoraOldOff = tHora;
      for (unsigned char j=0; j<2; j++)
      {
        digitalWrite(pinLamp[j],HIGH);        
        digitalWrite(LED, LOW);
      }
    }
  }   
  return;
}

