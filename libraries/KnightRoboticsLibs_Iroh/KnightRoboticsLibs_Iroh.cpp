///////////////////////////////////////////////////////////////////////////////////////
//                                                                                   //
//  Copyright (c) 2023, MAURICIO CORREA (KNIGHT ROBOTICS SPA)                        //
//  All rights reserved.                                                             //
//                                                                                   //
//  Redistribution and use in source and binary forms, with or without               //
//  modification, are permitted provided that the following conditions are met:      //
//                                                                                   //
//   * Redistributions of source code must retain the above copyright notice,        //
//     this list of conditions and the following disclaimer.                         //
//   * Redistributions in binary form must reproduce the above copyright             //
//     notice, this list of conditions and the following disclaimer in the           //
//     documentation and/or other materials provided with the distribution.          //
//   * Neither the name of KNIGHT ROBOTICS SPA nor the names of its                  //
//     contributors may be used to endorse or promote products derived from          //
//     this software without specific prior written permission.                      //
//                                                                                   //
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"      //
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE        //
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE       //
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE         //
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR              //
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF             //
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS         //
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN          //
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)          //
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       //
//  POSSIBILITY OF SUCH DAMAGE.                                                      //
//                                                                                   //
//                                                                                   //
//  Last updated on 03/03/2023                                                       //
//  Compatible with the Arduino IDE 1.82 y 2.0                                       //
//  Library version: 4                                                               //
//  Robot version: Iroh                                                              //
//  Web: http://www.knightrobotics.cl/                                               //
//                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////

#include "KnightRoboticsLibs_Iroh.h"
#include <inttypes.h>
#include "Arduino.h"

#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>         
#include <LiquidCrystal_I2C.h>

#define MIN_SPEED_PWM 50
#define MAX_SPEED_PWM 200

// DATOS SONAR
#define TRIGGER_PIN  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar_(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// SERVOS
Servo Yaw;    // create servo object to control a servo 
Servo Pitch;  // create servo object to control a servo
Servo Golpe;  // create servo object to control a servo

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display - 
LiquidCrystal_I2C lcd2(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

int versionPantalla = 0;

int movement = 0; // 0: Detenido, 1: Avanza, 2: Retrocede, 3: Gira Derecha, 4: Gira Izquierda, 5: Avanza DIF, 6: Retrocede DIF
int ServoGolpeState = 0; // -1: Izquierda, 0: Centro, 1: Derecha

int sensorLineaDerecho_ = A0;
int sensorLineaCentral_ = A1;
int sensorLineaIzquierdo_ = A2;

int motorIzquierdo1 = 6; //atras
int motorIzquierdo2 = 5; //adelante
int motorDerecho1 = 3; //atras
int motorDerecho2 = 11; //adelante

int rightProximityPin = 10;
int leftProximityPin = 2;

const int startbutton = 4;
int buttonValue = 0;

void retroceder(int vel){

  if (vel>100){
	vel = 100;
	}
  vel = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*vel;

  if (movement!=2){
	detenerse();
	movement=2;
	}

  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho2, HIGH);
  analogWrite(motorIzquierdo1, 255-vel);
  analogWrite(motorDerecho1, 255-vel);

}

void retroceder(int velIzq, int velDer){

  if (velIzq>100){
	velIzq = 100;
	}
  if (velDer>100){
	velDer = 100;
	}
  velIzq = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*velIzq;
  velDer = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*velDer;

  if (movement!=6){
	detenerse();
	movement=6;
	}

  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho2, HIGH);
  analogWrite(motorIzquierdo1, 255-velIzq);
  analogWrite(motorDerecho1, 255-velDer);

}

void avanzar(int vel){

  if (vel>100){
	vel = 100;
	}
  vel = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*vel;
  
  if (movement!=1){
	detenerse();
	movement=1;
	}

  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  analogWrite(motorIzquierdo2, 255-vel);
  analogWrite(motorDerecho2, 255-vel);

}

void avanzar(int velIzq, int velDer){

  if (velIzq>100){
	velIzq = 100;
	}
  if (velDer>100){
	velDer = 100;
	}
  velIzq = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*velIzq;
  velDer = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*velDer;

  if (movement!=5){
	detenerse();
	movement=5;
	}

  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  analogWrite(motorIzquierdo2, 255-velIzq);
  analogWrite(motorDerecho2, 255-velDer);
 
}

void detenerse(){

  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho2, HIGH);
  
  delay(70);
  movement=0;

}

void girarDerecha(int vel){

  if (vel>100){
	vel = 100;
	}
  vel = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*vel;
  
  if (movement!=3){
	detenerse();
	movement=3;
	}
	
  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorDerecho2, HIGH);
  analogWrite(motorIzquierdo2, 255-vel);
  analogWrite(motorDerecho1, 255-vel);

}

void girarIzquierda(int vel){

  if (vel>100){
	vel = 100;
	}
  vel = MIN_SPEED_PWM + (MAX_SPEED_PWM-MIN_SPEED_PWM)/100*vel;

  if (movement!=4){
	detenerse();
	movement=4;
	}
	
  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  analogWrite(motorIzquierdo1, 255-vel);
  analogWrite(motorDerecho2, 255-vel);

}

void inicializarMovimientoRobot(){

  // PH
  pinMode(motorIzquierdo1, OUTPUT);
  pinMode(motorIzquierdo2, OUTPUT);
  pinMode(motorDerecho1, OUTPUT);
  pinMode(motorDerecho2, OUTPUT);
  
  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  digitalWrite(motorDerecho2, HIGH);

}

void inicializarMovimiento(){

  // PH
  pinMode(motorIzquierdo1, OUTPUT);
  pinMode(motorIzquierdo2, OUTPUT);
  pinMode(motorDerecho1, OUTPUT);
  pinMode(motorDerecho2, OUTPUT);
  
  digitalWrite(motorIzquierdo1, HIGH);
  digitalWrite(motorIzquierdo2, HIGH);
  digitalWrite(motorDerecho1, HIGH);
  digitalWrite(motorDerecho2, HIGH);

}

void inicializarSensoresRobot(){

//Sensores
  pinMode(rightProximityPin, INPUT);
  pinMode(leftProximityPin, INPUT);
  
  pinMode(startbutton, INPUT);

}

void inicializarSensores(){

//Sensores
  pinMode(rightProximityPin, INPUT);
  pinMode(leftProximityPin, INPUT);
  
  pinMode(startbutton, INPUT);

}

void inicializarCabezaRobot(){

  Yaw.attach(7);  
  Pitch.attach(8);
  
  moverServoYaw(90);
  moverServoPitch(40);

}

void inicializarCabeza(){

  Yaw.attach(7);  
  Pitch.attach(8);
  
  moverServoYaw(90);
  moverServoPitch(40);

}

void apagarCabezaRobot(){

  Yaw.detach();  
  Pitch.detach();

}

void apagarCabeza(){

  Yaw.detach();  
  Pitch.detach();

}

void inicializarGolpeRobot(){

  Golpe.attach(9);
  
  moverServoGolpe(0);

}
void inicializarGolpe(){

  Golpe.attach(9);
  
  moverServoGolpe(0);

}

void inicializarPantallaRobot(){

  Wire.begin();
  
  Wire.beginTransmission (39);
  if (Wire.endTransmission () == 0)
    {
    //Serial.print ("Pantalla V1: (0x27)");
    versionPantalla = 1;
  } 

  Wire.beginTransmission (63);
  if (Wire.endTransmission () == 0)
    {
    //Serial.print ("Pantalla V2: (0x3F)");
    versionPantalla = 2;
  }
  
  //delay(2000);

  //LCD
  if (versionPantalla == 1){
     lcd.init();               
     lcd.backlight(); 
     escribirPantalla(1, 0, "KnightRobotics");
     }
  else if(versionPantalla == 2){
     lcd2.init();               
     lcd2.backlight(); 
     escribirPantalla(1, 0, "KnightRobotics");
     }
  
  //delay(1000);
  
  //lcd.noBacklight();
  
}

void inicializarPantalla(){

  Wire.begin();
  
  Wire.beginTransmission (39);
  if (Wire.endTransmission () == 0)
    {
    //Serial.print ("Pantalla V1: (0x27)");
    versionPantalla = 1;
  } 

  Wire.beginTransmission (63);
  if (Wire.endTransmission () == 0)
    {
    //Serial.print ("Pantalla V2: (0x3F)");
    versionPantalla = 2;
  }
  
  //delay(2000);

  //LCD
  if (versionPantalla == 1){
     lcd.init();               
     lcd.backlight(); 
     escribirPantalla(1, 0, "KnightRobotics");
     }
  else if(versionPantalla == 2){
     lcd2.init();               
     lcd2.backlight(); 
     escribirPantalla(1, 0, "KnightRobotics");
     }
  
  //delay(1000);
  
  //lcd.noBacklight();
  
}

void escribirPantalla(int col, int fil, const char Text[]){

  if (versionPantalla == 1){
     lcd.setCursor(col,fil);
     lcd.print(Text);
  }
  else if(versionPantalla == 2){
     lcd2.setCursor(col,fil);
     lcd2.print(Text);
  }
	

}

void escribirPantalla(int col, int fil, int Number){
    
  if (versionPantalla == 1){
     lcd.setCursor(col,fil);
     lcd.print(Number);
  }
  else if(versionPantalla == 2){
     lcd2.setCursor(col,fil);
     lcd2.print(Number);
  }
	

}

void apagarPantalla(){

  if (versionPantalla == 1){
     lcd.noBacklight();;
  }
  else if(versionPantalla == 2){
     lcd2.noBacklight();
  }
  
	
}

void prenderPantalla(){

  if (versionPantalla == 1){
     lcd.backlight();;
  }
  else if(versionPantalla == 2){
     lcd2.backlight();
  }
}

void borrarPantalla(){

  if (versionPantalla == 1){
     lcd.clear();;
  }
  else if(versionPantalla == 2){
     lcd2.clear();
  }
}

int leerBoton(){

	return digitalRead(startbutton);
	
}

void botonInicio(){
  while(1){
  
    buttonValue = digitalRead(startbutton);
    if (buttonValue==1)
       break;
  }
}

int leerDistanciaSonar(){

    int dist =  sonar_.ping_cm();
    
    if (dist>5)
	   return dist;

    return 0;
}

int leerSensorLineaIzquierdo(){

	return analogRead(sensorLineaIzquierdo_);
}

int leerSensorLineaCentral(){

	return analogRead(sensorLineaCentral_);
}

int leerSensorLineaDerecho(){

	return analogRead(sensorLineaDerecho_);
}

int leerSensorObstaculoIzquierdo(){

	return digitalRead(leftProximityPin);
}

int leerSensorObstaculoDerecho(){

	return digitalRead(rightProximityPin);
}

void moverServoYaw(int pos){

	Yaw.write(pos);
}

void moverServoPitch(int pos){

	Pitch.write(pos);
}

void moverServoGolpe(int pos){

	if(ServoGolpeState==0){
		if (pos==-1){
			Golpe.write(165);
			ServoGolpeState = -1;
		}
		else if (pos==1){
			Golpe.write(15);
			ServoGolpeState = 1;
		}	
	}
	else if(ServoGolpeState==-1){
		if (pos==0){
			Golpe.write(90);
			ServoGolpeState = 0;
		}
		else if (pos==1){
			Golpe.write(15);
			ServoGolpeState = 1;
		}	
	}
	else if(ServoGolpeState==1){
		if (pos==0){
			Golpe.write(90);
			ServoGolpeState = 0;
		}
		else if (pos==-1){
			Golpe.write(165);
			ServoGolpeState = -1;
		}	
	}
}

void finPrograma(){

	detenerse();
	borrarPantalla();
	apagarPantalla();

	while(1){
	
	}

}

void pausa(int tiempo){

	delay(tiempo);

};


	
