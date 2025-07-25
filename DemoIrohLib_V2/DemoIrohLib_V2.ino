///////////////////////////////////////////////////////////////////////////////////////
//                                                                                   //
//  Copyright (c) 2022, MAURICIO CORREA (KNIGHT ROBOTICS SPA)                        //
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
//  Last updated on 13/08/2022                                                       //
//  Compatible with the Arduino IDE 1.8                                             //
//  Library version: 4.0                                                             //
//  Robot version: Iroh                                                              //
//  Web: http://www.knightrobotics.cl/                                               //
//                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////
/*
 Movimientos básicos de robot modelo Iroh.
 */

#include <KnightRoboticsLibs_Iroh.h>


int sensorValue_I = 0;  // variable to store the value coming from the sensor 1
int sensorValue_C = 0;  // variable to store the value coming from the sensor 2
int sensorValue_D = 0;  // variable to store the value coming from the sensor 3

unsigned int DistSonar = 0;

int leftProximityPValue = 0;
int rightProximityPValue = 0;

int buttonState = 0;

void setup() {
  
  Serial.begin (115200);
  
  inicializarMovimientoRobot();
  inicializarSensoresRobot();
  inicializarPantallaRobot();
  inicializarCabezaRobot();
  inicializarGolpe();
  //apagarCabezaRobot();
}

void loop() {
  
  DistSonar  = leerDistanciaSonar();
  
  sensorValue_I = leerSensorLineaIzquierdo();
  sensorValue_C = leerSensorLineaCentral();
  sensorValue_D = leerSensorLineaDerecho();
  
  leftProximityPValue = leerSensorObstaculoIzquierdo();
  rightProximityPValue = leerSensorObstaculoDerecho();
  
  buttonState = leerBoton();

  int power = 100;
  
  if (buttonState==1){
  
    apagarPantalla(); 
    avanzar(power);
    delay(1000);
    retroceder(power);
    delay(1000);
    girarDerecha(power);
    delay(1000);
    girarIzquierda(power);
    delay(1000);
    detenerse();
    prenderPantalla(); 
    
  }
  
  Serial.print("sensors =" );
  Serial.print("\t");  
  Serial.print(sensorValue_I);      
  Serial.print("\t");
  Serial.print(sensorValue_C);      
  Serial.print("\t");    
  Serial.print(sensorValue_D);
  Serial.print("\t");
  Serial.print(DistSonar);
  Serial.print("\t");
  
  if ( buttonState == 1) {         
    Serial.print("TOUCH \t");

  }
  
  if (DistSonar>99){
      escribirPantalla(6, 1, DistSonar);
  }
  else if (DistSonar<=99 && DistSonar>=10){
    
      escribirPantalla(6, 1, 0);
      escribirPantalla(7, 1, DistSonar);
  }
  else{
      escribirPantalla(6, 1, "00");
      escribirPantalla(8, 1, DistSonar);
  }
  
  if (rightProximityPValue == HIGH && leftProximityPValue == HIGH) {         
    Serial.println("");
    moverServoYaw(90);
    moverServoPitch(40);
  }
  else if (rightProximityPValue == LOW && leftProximityPValue == HIGH) {            
    Serial.println("RIGHT"); 
    moverServoYaw(60);
    moverServoPitch(40);
  } 
  else if (leftProximityPValue == LOW && rightProximityPValue == HIGH){   
    Serial.println("LEFT");
    moverServoYaw(120);
    moverServoPitch(40);
  }
  else if (leftProximityPValue == LOW && rightProximityPValue == LOW){   
    Serial.println("RIGHT\tLEFT");
    moverServoYaw(90);
    moverServoPitch(90);
    moverServoGolpe(-1);
    delay(500);
    moverServoGolpe(0);
    delay(500);
    moverServoGolpe(1);
    delay(500);
    moverServoGolpe(0);
    delay(500);
  }
  else {
    Serial.println("");
  }

  delay(200);    
               
}
