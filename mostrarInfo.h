void leerReloj()
{
      #ifdef Reloj
      DateTime now = rtc.now(); 
      DD = now.day();
      Dia = String(DD);
      MM = now.month();
      Mes = String(MM);
      YY = now.year();
      Ano = String(YY);
      hh = now.hour();
      Hora = String(hh);
      mm = now.minute();
      Minuto = String(mm);
      ss = now.second();
      Segundo = String(ss);       
    #else
      DD = 0;
      Dia = "00";
      MM = 0;
      Mes = "00";
      YY = 0;
      Ano = "0000";
      hh = 0;
      Hora = "00";
      mm = 0;
      Minuto = "00";
      ss = 0;
      Segundo = "00";   
    #endif   
}

/**************************************************************************************/
void MostrarInfo()
{
  Serial.print(Dia);
  Serial.print('/');
  Serial.print(Mes);
  Serial.print('/');
  Serial.print(Ano);
  Serial.print(' ');
  Serial.print(Hora);
  Serial.print(':');
  Serial.print(Minuto);
  Serial.print(':');
  Serial.print(Segundo);
  Serial.println();
  
  #ifdef Sensor_TC
    Serial.println("Termocuplas");
    for (unsigned char i=0; i<NUM_TC; i++)
    {
      Serial.print(Temp_TC[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');      
  #endif

  #ifdef Sensor_IR
    Serial.println("Infrarrojos");
    Serial.println("Ambiente");
    for (unsigned char i=0; i<NUM_IR; i++)
    {
      Serial.print(Temp_Amb_T_IR[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');
    Serial.println("Objeto");
    for (unsigned char i=0; i<NUM_IR; i++)
    {
      Serial.print(Temp_Obj_T_IR[i]);
      Serial.print('\t');      
    }    
    Serial.print('\n');          
  #endif

  #ifdef Sensor_DS
    Serial.println("DS18S20");
    for (unsigned char i=0; i<NUM_DS; i++)
    {
      Serial.print(Temp_DS[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');     
  #endif

  #ifdef Sensor_LM
    Serial.println("LM335");
    Serial.println("Analogo");
    for (unsigned char i=0; i<NUM_LM335; i++)
    {
      Serial.print(Temp_LM335_AN[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');        
    Serial.println("Convertido");
    for (unsigned char i=0; i<NUM_LM335; i++)
    {
      Serial.print(Temp_LM335_F[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');     
  #endif

  #ifdef Sensor_TR
    Serial.println("Termistor");
    Serial.println("Analogo");
    for (unsigned char i=0; i<NUM_TERM; i++)
    {
      Serial.print(Temp_Term_AN[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');        
    Serial.println("Convertido");
    for (unsigned char i=0; i<NUM_TERM; i++)
    {
      Serial.print(Temp_Term_F[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');          
    Serial.println("Resistencias RT");
    for (unsigned char i=0; i<NUM_TERM; i++)
    {
      Serial.print(RT[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');        
  #endif   

  #ifdef Sensor_PT
    Serial.println("PT100");
    Serial.println("Analogo");
    for (unsigned char i=0; i<NUM_PT; i++)
    {
      Serial.print(PT100_An[i]);
      Serial.print('\t');      
    }
    Serial.print('\n');       
  #endif

  #ifdef Sensor_HR
    Serial.println("Sensor de humedad relativa");
    Serial.print("HR=");
    Serial.print(humedad);
    Serial.print('\t'); 
    Serial.print("Temp_HR=");
    Serial.println(temperaturaHR);    
  #endif  
}
/**************************************************************************************/

/**************************************************************************************/
void InfoBT()
{
  Serial2.write('\n');
  Serial2.write('\n');
  Serial2.print(Dia);
  Serial2.print('/');
  Serial2.print(Mes);
  Serial2.print('/');
  Serial2.print(Ano);
  Serial2.print(' ');
  Serial2.print(Hora);
  Serial2.print(':');
  Serial2.print(Minuto);
  Serial2.print(':');
  Serial2.println(Segundo);  
  Serial2.write('\n');
  Serial2.write('\r');
  
  #ifdef Sensor_TC
    Serial2.println("Termocuplas");
    for (unsigned char i=0; i<NUM_TC; i++)
    {
      Serial2.print(Temp_TC[i]);
      Serial2.write('\t');      
    }
    Serial2.write('\n');      
    Serial2.write('\n');      
    Serial2.write('\r');
  #endif

  #ifdef Sensor_IR
    Serial2.println("Infrarrojos");
    Serial2.println("Ambiente");
    for (unsigned char i=0; i<NUM_IR; i++)
    {
      Serial2.print(Temp_Amb_T_IR[i]);
      Serial2.write('\t');      
    }
    Serial2.write('\n');      
    Serial2.write('\n');          
    Serial2.write('\r');
    Serial2.println("Objeto");
    for (unsigned char i=0; i<NUM_IR; i++)
    {
      Serial2.print(Temp_Obj_T_IR[i]);
      Serial2.write('\t');      
    }    
    Serial2.write('\n');      
    Serial2.write('\n');      
    Serial2.write('\r');    
  #endif

  #ifdef Sensor_DS
    Serial2.println("DS18S20");
    for (unsigned char i=0; i<NUM_DS; i++)
    {
      Serial2.print(Temp_DS[i]);
      Serial2.write('\t');      
    }
    Serial2.write('\n');          
    Serial2.write('\n');      
    Serial2.write('\r');
  #endif

  #ifdef Sensor_LM
    Serial2.println("LM335");
    /*
    Serial2.println("Analogo");
    for (unsigned char i=0; i<NUM_LM335; i++)
    {
      Serial2.print(Temp_LM335_AN[i]);
      Serial2.print('\t');      
    }
    Serial2.write('\n');      
    Serial2.write('\r');       
    Serial2.println("Convertido");
    */
    for (unsigned char i=0; i<NUM_LM335; i++)
    {
      Serial2.print(Temp_LM335_F[i]);
      Serial2.write('\t');      
    }
    Serial2.write('\n');          
    Serial2.write('\n');      
    Serial2.write('\r');    
  #endif

  #ifdef Sensor_TR
    Serial2.println("Termistor");
    /*
    Serial2.println("Analogo");
    for (unsigned char i=0; i<NUM_TERM; i++)
    {
      Serial2.print(Temp_Term_AN[i]);
      Serial2.print('\t');      
    }
    Serial2.print('\n');        
    Serial2.println("Convertido");
    */
    for (unsigned char i=0; i<NUM_TERM; i++)
    {
      Serial2.print(Temp_Term_F[i]);
      Serial2.write('\t');      
    }
    Serial2.write('\n');          
    Serial2.write('\n');      
    Serial2.write('\r');    
    /*
    Serial2.println("Resistencias RT");
    for (unsigned char i=0; i<NUM_TERM; i++)
    {
      Serial2.print(RT[i]);
      Serial2.print('\t');      
    }
    Serial2.write('\n');      
    Serial2.write('\r');    
    */
  #endif   

  #ifdef Sensor_PT
    Serial2.println("PT100");
    for (unsigned char i=0; i<NUM_PT; i++)
    {
      Serial2.print(PT100_An[i]);
      Serial2.write('\t');      
    }
    Serial2.write('\n');  
    Serial2.write('\n');      
    Serial2.write('\r');       
  #endif

  #ifdef SensorHR
    Serial2.println("Sensor de humedad relativa");
    Serial2.print("HR=");
    Serial2.print(humedad);
    Serial2.write('\t'); 
    Serial2.print("   Temp_HR=");
    Serial2.println(temperaturaHR);        
    Serial2.write('\n');      
    Serial2.write('\r');    
  #endif  
}
/**************************************************************************************/
