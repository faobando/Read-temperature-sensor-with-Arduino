#ifdef BT_Instalado
  //Comunicación módulo Bluetooth
  void serialEvent2() {
    while (Serial2.available()) 
    {
      // get the new byte:
      char inChar = (char)Serial2.read();
      // add it to the inputString:
      inputStringBT += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n') {
        stringCompleteBT = true;
      }
    } 
  
    if (stringCompleteBT)
    {
      Serial2.println(inputStringBT);         
      if (inputStringBT.indexOf("m")>=0)
      {
        mostrarInfoBT = true;
      } 
      if (inputStringBT.indexOf("n")>=0)
      {      
        mostrarInfoBT = false;
      }        
      stringCompleteBT = false;
      inputStringBT = "";
    }  
    return;
  }
#endif
