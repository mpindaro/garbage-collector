/************************************************************************************************************
 * DistanceGP2Y0A02YK0F.h - Arduino library for retrieving data from the analog GP2Y IR Distance sensor *
 * Copyright 2011 Jeroen Doggen (jeroendoggen@gmail.com)                                                    *
 * For more information: variable declaration, changelog,... see DistanceGP2Y0A02YK0F.h                       *
 ************************************************************************************************************
 * This library is free software; you can redistribute it and/or                                            *
 * modify it under the terms of the GNU Lesser General Public                                               *
 * License as published by the Free Software Foundation; either                                             *
 * version 2.1 of the License, or (at your option) any later version.                                       *
 *                                                                                                          *
 * This library is distributed in the hope that it will be useful,                                          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                                           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                                        *
 * Lesser General Public License for more details.                                                          *
 *                                                                                                          *
 * You should have received a copy of the GNU Lesser General Public                                         *
 * License along with this library; if not, write to the Free Software                                      *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA                               *
 ***********************************************************************************************************/

/// <summary>
/// DistanceGP2Y0A02YK0F.cpp - Library for retrieving data from the GP2Y IR Distance sensor.
/// For more information: variable declaration, changelog,... see DistanceGP2Y0A41SK.h
/// </summary>

#include <Arduino.h>
#include <DistanceGP2Y0A02YK0F.h>

/// <summary>
/// Constructor
/// </summary>
DistanceGP2Y0A02YK0F::DistanceGP2Y0A02YK0F()
{
}
/// <summary>
/// Multimap comes from http://playground.arduino.cc/Main/MultiMap
/// and provides a way to linearize by segments a function
/// val is the input value _in and _out are the arrays of corresponding
/// measured points (for input and ground truth), size is the size of the 
/// arrays.
/// The arrays for GP2Y0A02YK0F are below.
/// </summary>
int multiMap(int val, int* _in, int* _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return map(val, _in[pos-1], _in[pos], _out[pos-1], _out[pos]);
}

int out[] = {150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20, 15};
int in[]  = {74, 82, 91, 99, 107, 128, 138, 158, 180, 209, 250, 308, 400, 496, 520};


/// <summary>
/// getDistanceCentimeter(): Returns the distance in centimeters: between 20-150cm (20 & 150 are boundary values)
/// </summary>
int DistanceGP2Y0A02YK0F::getDistanceCentimeter()
{
	int adcValue=getDistanceRaw();
/*
  Serial.print("Distance in ADC Values: ");
  Serial.println(adcValue); 
  delay(100);
*/
	if (adcValue > 520){  // lower boundary: 15 cm (0 cm means under the boundary)
		return (0);
	}
	
	if (adcValue < 74){  //upper boundary: 150 cm (returning 1000 means over the boundary)
		return (1000);
	}
	
	else{ //distance= 9462/(adcValue - 16.92);
	      //return (1 / (0.000413153 * adcValue - 0.0055266887));
	      return (multiMap(adcValue, in, out, 15));
	}
}
