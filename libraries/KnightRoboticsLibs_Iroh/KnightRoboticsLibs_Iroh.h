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

#ifndef KnightRoboticsLibs_Iroh_h
#define KnightRoboticsLibs_Iroh_h

void retroceder(int vel);

void retroceder(int velIzq, int velDer);

void avanzar(int vel);

void avanzar(int velIzq, int velDer);

void detenerse();

void girarDerecha(int vel);

void girarIzquierda(int vel);

void inicializarMovimientoRobot();

void inicializarCabezaRobot();

void inicializarGolpeRobot();

void inicializarSensoresRobot();

void inicializarPantallaRobot();

void apagarCabezaRobot();

void inicializarMovimiento();

void inicializarCabeza();

void inicializarGolpe();

void inicializarSensores();

void inicializarPantalla();

void apagarCabeza();

void moverServoYaw(int pos);

void moverServoPitch(int pos);

void moverServoGolpe(int pos);

int leerBoton();

void botonInicio();

int leerDistanciaSonar();

int leerSensorLineaIzquierdo();

int leerSensorLineaCentral();

int leerSensorLineaDerecho();

int leerSensorObstaculoIzquierdo();

int leerSensorObstaculoDerecho();

void escribirPantalla(int col, int fil, const char Text[]);

void escribirPantalla(int col, int fil, int Number);

void apagarPantalla();

void prenderPantalla();

void borrarPantalla();

void finPrograma();

void pausa(int tiempo);

#endif
