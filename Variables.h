/**************************************************************************************/
//Variables sensor de temperatura termocupla con módulo MAX6675

const unsigned char NUM_TC = 3; // Número de termocuplas

//Puertos donde estan conectados los modulos de las termocuplas
/*
const unsigned char thermoCLK[NUM_TC]  = {2, 5, 8};
const unsigned char thermoCS[NUM_TC] = {3, 6, 9}; //Pines CS (chip select)
const unsigned char thermoDO[NUM_TC]  = {4, 7, 10};
*/

const unsigned char thermoCLK[NUM_TC]  = {2, 5, 22};
const unsigned char thermoCS[NUM_TC] = {3, 6, 23}; //Pines CS (chip select)
const unsigned char thermoDO[NUM_TC]  = {4, 7, 24};


MAX6675 thermocouple1(thermoCLK[0] , thermoCS[0], thermoDO[0] );  //Esfera plástica
MAX6675 thermocouple2(thermoCLK[1] , thermoCS[1], thermoDO[1] );  //Esfera metálica pequeña
MAX6675 thermocouple3(thermoCLK[2] , thermoCS[2], thermoDO[2] );  //Esfera metálica grande

float Temp_TC[NUM_TC]= {0.0, 0.0, 0.0};

/**************************************************************************************/

/**************************************************************************************/
//Variables sensor de temperatura IR MLX90614

//Puertos donde estan conectados los sensores de temperatura IR
//I2C arduino mega 2560
//SDA: 20
//SCL: 21

#ifdef Adafruit
  Adafruit_MLX90614 T_IR_1 = Adafruit_MLX90614(0x70); //Esfera plástica
  Adafruit_MLX90614 T_IR_2 = Adafruit_MLX90614(0x71); //Esfera metálica pequeña
  Adafruit_MLX90614 T_IR_3 = Adafruit_MLX90614(0x72); //Esfera metálica grande
#endif

#ifdef Sparkfun
  IRTherm T_IR_1; // Create an IRTherm object to interact with throughout
  IRTherm T_IR_2;
  IRTherm T_IR_3;
#endif

const unsigned char NUM_IR = 3;
float Temp_Amb_T_IR[NUM_IR] = {0.0, 0.0, 0.0};
float Temp_Obj_T_IR[NUM_IR] = {0.0, 0.0, 0.0};
float newEmissivity = 0.97;
/**************************************************************************************/

/**************************************************************************************/
//Variables e inicialización sensor digital de temperatura DS18S20

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 11
#define TEMPERATURE_PRECISION 12

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
DeviceAddress T_DS_1, T_DS_2, T_DS_3, T_DS_4; 
// DS1: Esfera metálica grande
// DS2: Esfera metálica pequeña
// DS3: Esfera de plástico
// DS4: Ambiente

const unsigned char NUM_DS = 4;
float Temp_DS[NUM_DS] = {0.0, 0.0, 0.0, 0.0};
/**************************************************************************************/

/**************************************************************************************/
//Variables sensores de temperatura LM335
const unsigned char NUM_LM335 = 3;
float Temp_LM335_AN[NUM_LM335] = {0.0, 0.0, 0.0};
float Temp_LM335_F[NUM_LM335] = {0.0, 0.0, 0.0};
unsigned char pin_LM335[NUM_LM335] = {A0, A2, A4}; //A0: Esfera pequeña, A2: Esfera grande, A4: Esfera plástica
const float a_LM335[NUM_LM335] = {(5.0*100.0)/1024.0, (5.0*100.0)/1024.0, (5.0*100.0)/1024.0};
const float b_LM335[NUM_LM335] = {0.0, 0.0, 0.0};
/**************************************************************************************/

/**************************************************************************************/  
//Variables sensores de temperatura termistor
const unsigned char NUM_TERM = 3;
float Temp_Term_AN[NUM_TERM] = {0.0, 0.0, 0.0};
float Temp_Term_F[NUM_TERM] = {0.0, 0.0, 0.0};
unsigned char pin_Term[NUM_TERM] = {A6, A9, A11}; //A6: Esfera metálica pequeña, A9: Esfera metálica grande , A11: Esfera plástica
const unsigned int R0 = 10000;
const float T0 = 298.15; //25°C
const unsigned int beta = 3435;
float RT[NUM_TERM] = {R0, R0, R0};
float R[NUM_TERM] = {5600, 5600, 5600};
/**************************************************************************************/

/**************************************************************************************/

HX711 PT1(39, 38, 64);     // parameter "gain" is 64; the default value 128 is used by the library
HX711 PT2(41, 40, 64);    // parameter "gain" is 64; the default value 128 is used by the library
HX711 PT3(43, 42, 64);  // parameter "gain" is 64; the default value 128 is used by the library

//Variables sensores de temperatura PT100
const unsigned char NUM_PT = 3;
unsigned long PT100_An[NUM_PT] = {0, 0, 0};

/**************************************************************************************/


/**************************************************************************************/
const int numReadings = 20;
float readings_TC[NUM_TC][numReadings];      // the readings from the analog input
int readIndex_TC = 0;              // the index of the current reading
float readings_IR_O[NUM_IR][numReadings];      // the readings from the analog input
int readIndex_IR_O = 0;              // the index of the current reading
float readings_IR_A[NUM_IR][numReadings];      // the readings from the analog input
int readIndex_IR_A = 0;              // the index of the current reading
float readings_DS[NUM_DS][numReadings];      // the readings from the analog input
int readIndex_DS = 0;              // the index of the current reading
int readings_LM[NUM_LM335][numReadings];      // the readings from the analog input
int readIndex_LM = 0;              // the index of the current reading
int readings_Term[NUM_TERM][numReadings];      // the readings from the analog input
int readIndex_Term = 0;              // the index of the current reading
int readings_HR[numReadings];      // the readings from the analog input
int readIndex_HR= 0;              // the index of the current reading
int readings_T_HR[numReadings];      // the readings from the analog input
int readIndex_T_HR= 0;              // the index of the current reading


float sumaTotal_TC[NUM_TC] = {0.0, 0.0, 0.0};
float sumaTotal_IR_O[NUM_IR] = {0.0, 0.0, 0.0};
float sumaTotal_IR_A[NUM_IR] = {0.0, 0.0, 0.0};
float sumaTotal_DS[NUM_DS] = {0.0, 0.0, 0.0, 0.0};
float sumaTotal_LM[NUM_LM335] = {0.0, 0.0, 0.0};
float sumaTotal_Term[NUM_TERM] = {0.0, 0.0, 0.0};
float sumaTotal_HR = 0.0;
float sumaTotal_T_HR = 0.0;
/**************************************************************************************/

/**************************************************************************************/
const unsigned long T_GRABAR_SD = 15000;
unsigned long tiempoPasSD = millis();

const unsigned long T_TOMA_DATOS = 0;
unsigned long tiempoPasToma = millis();
/**************************************************************************************/

/**************************************************************************************/
//Variables sensor de humedad relativa

dht DHT;

#define DHT22_PIN 12

float humedad = 0.0;
float temperaturaHR = 0.0;

const unsigned int LED = 13;

/**************************************************************************************/

/**************************************************************************************/
//Parámetros ajustes de curvas

float TCp1[NUM_TC] = {0.895, 0.9124, 0.9061};
float TCp2[NUM_TC] = {2.6904, 3.6329, 5.0189};

float TIRAp1[NUM_IR] = {0.9110, 0.8878, 0.8877};
float TIRAp2[NUM_IR] = {1.6653, 3.1952, 3.1957};

float TIROp1[NUM_IR] = {1.0024, 1.0703, 1.0704};
float TIROp2[NUM_IR] = {-1.2121, -2.0310, -2.0325};

float TDSp1[NUM_DS] = {0.8832, 0.9057, 0.9026, 0.9098};
float TDSp2[NUM_DS] = {3.1463, 2.5449, 2.6123, 2.4352};

float TLMp1[NUM_LM335] = {0.9545, 0.9855, 0.9227};
float TLMp2[NUM_LM335] = {2.2291, 1.5758, 2.8307};

float TTermp1[NUM_TERM] = {0.8587, 0.9235, 0.8796};
float TTermp2[NUM_TERM] = {3.6470, 1.6468, 2.5571};

float THRp1 = 0.8737;
float THRp2 = 2.7552;

String Dia = "00";
String Mes = "00";
String Ano = "0000";
String Hora = "00";
String Minuto = "00";
String Segundo = "00";

boolean mostrarInfoBT = false;
String inputStringBT = "";
boolean stringCompleteBT = false;

const unsigned int NUM_MEDICIONES = 10;
float Mediciones[NUM_MEDICIONES];
float Mediciones1[NUM_MEDICIONES];
float Mediciones2[NUM_MEDICIONES];
const unsigned char NUM_MEDICIONES_DS = 4;
float MedicionesDS[NUM_DS][NUM_MEDICIONES_DS];
float medicionTotal;

unsigned long t_inicio = millis();  

unsigned long T_INFO = 20000;
unsigned long tiempoInfo = millis();

volatile unsigned long seg = 0;
boolean SDInicializada = false;

const unsigned char pinLamp[2] = {14, 15};

//unsigned char HORA_OFF[12] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
//unsigned char HORA_ON[12] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};

unsigned char HORA_OFF[3] = {3, 6, 19};
unsigned char HORA_ON[3] = {2, 5, 18};


//unsigned char HORA_OFF[15] = {2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58};
//unsigned char HORA_ON[15] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56};

//unsigned char HORA_OFF[6] = {2, 6, 10, 14, 18, 22};
//unsigned char HORA_ON[6] = {0, 4, 8, 12, 16, 20};
boolean encendido = false;
unsigned char tHoraOldOn = 100;
unsigned char tHoraOldOff = 100;
unsigned long T_CHECK_TIME = 15000;
unsigned long t_CheckTime = millis();

unsigned int leerSensor = 1;

volatile boolean grabarSD_Now = false;

volatile unsigned int DD, MM, YY, hh, mm, ss;


