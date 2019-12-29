void grabarDatos()
{ 
  char charVal[10];               
  
  File dataFile = SD.open("Datalog.txt", O_CREAT | O_WRITE | O_APPEND);

  boolean estadoLed = digitalRead(LED);
  if (dataFile) 
  {
    digitalWrite(LED, !estadoLed);
    String dataString = "";   
    dataString += Dia;
    dataString += "/";
    dataString += Mes;
    dataString += "/";
    dataString += Ano;
    dataString += ",";
    dataString += Hora;
    dataString += ":";
    dataString += Minuto;
    dataString += ":";
    dataString += Segundo;
    dataString += ",";   
    
    for(unsigned char i=0; i<NUM_TC; i++)
    {
      dtostrf(Temp_TC[i], 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
      dataString += String(charVal);
      dataString += ",";
    }

    for(unsigned char i=0; i<NUM_IR; i++)
    {
      dtostrf(Temp_Amb_T_IR[i], 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
      dataString += String(charVal);
      dataString += ",";
    }    

    for(unsigned char i=0; i<NUM_IR; i++)
    {
      dtostrf(Temp_Obj_T_IR[i], 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
      dataString += String(charVal);
      dataString += ",";
    }   

    for(unsigned char i=0; i<NUM_DS; i++)
    {
      dtostrf(Temp_DS[i], 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
      dataString += String(charVal);
      dataString += ",";
    }    

    for(unsigned char i=0; i<NUM_LM335; i++)
    {
      dtostrf(Temp_LM335_F[i], 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
      dataString += String(charVal);
      dataString += ",";
    }
    
    for(unsigned char i=0; i<NUM_TERM; i++)
    {
      dtostrf(Temp_Term_F[i], 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
      dataString += String(charVal);
      dataString += ",";
    }    

    for(unsigned char i=0; i<NUM_PT; i++)
    {     
      dataString += String(PT100_An[i]);
      dataString += ",";
    }  

    dtostrf(humedad, 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
    dataString += String(charVal);
    dataString += ",";
    dtostrf(temperaturaHR, 4, 1, charVal);  //4 is mininum width, 3 is precision; float value is copied onto buff
    dataString += String(charVal);
    
    
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.print("\nGrabado:");
    Serial.println(dataString);
   if(SDInicializada)
      digitalWrite(LED, estadoLed);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  return;
}
