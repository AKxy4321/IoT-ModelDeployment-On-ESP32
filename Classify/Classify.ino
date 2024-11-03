# Course: IoT and Edge Computing: Oct 2024
# This is a follow up Lab after based on the theory covered in the Session 7A about classification
# Models and the steps to make them run on ESP32

# This code is explained in the Lab8a based on the theory covered in Ses 7A
# Students are expected to identify similar datasets and port them to ESP32 based on 
# what is learnt here. Sample Examples are: IRIS dataset, Cactus, etc. as part of CP3 Project
# evaluation component.
# For other datasets that can be classified and ported on to ESP32
# Ref:https://archive.ics.uci.edu/datasets 

#include <EloquentTinyML.h>
// This file has the TFlite model generated by the Cars_Classify_Tflite_hex.ipynb 
// Done on Sep 2024
#include "cars_model_esp32.h"

// The car attribute details are given below
// These values were got on Spyder, by introducing the 
// following in the code, by accessing .head() of each labels

// Datal cols = ['price', 'maint', 'doors', 'persons', 'lug_capacity', 'safety','output']
// Individual attribute values are given as below: (from the file: car.names)
//  buying price  high, low, med, vhigh
//  maint         high, low, med, vhigh
//  doors         2, 3, 4, 5-more
//  persons       2, 4, more
//  lug_capacity  big, med, small
//  safety        high, low, med
// Output Categories are: acc, good, unacc, v-good

// Some sample input data and expected output from the file: car_dataset.csv
// Line no. 1226: med low 3 4  small med acc        : Input1
// Line no. 1236: med  low 3 more  small high       : Input2
// Line no.    1: vhigh vhigh 2 2 small low unacc   : Input3
// Line no. 1134: med med 3 more  big high  vgood   : Input4

#define NUMBER_OF_INPUTS 94  
#define NUMBER_OF_OUTPUTS 2 
// in future projects you may need to tweek this value: it's a trial and error process
//#define TENSOR_ARENA_SIZE 3*1024  // Since the size is 2960 here, this needs to be 
// changed from 2*1024 to 3*1024

#define TENSOR_ARENA_SIZE 5*1024  // Since the size is 3836 for more improved Sine model

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(115200);
   
    ml.begin(salary_model_esp32);
}

float fResult[NUMBER_OF_OUTPUTS] = {0};
float fRes = NULL;

void loop() {

//['price', 'maint', 'doors', 'persons', 'lug_capacity', 'safety']
// Line no. 1226: med low 3 4  small med acc        : Input1
    float input1[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.232876710f, 0.397959180f}

// Expected output1: 1.0f, 0.0f

//['price', 'maint', 'doors', 'persons', 'lug_capacity', 'safety']
// Line no. 1236: med  low 3 more  small high       : Input2
    float input2[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.260273970f, 0.193877550f};
// Expected output2: 1.0f, 0.0f

//['price', 'maint', 'doors', 'persons', 'lug_capacity', 'safety']
// Line no.    1: vhigh vhigh 2 2 small low unacc   : Input3
    float input3[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.575342470f, 0.244897960f};
// Expected output3: 1.0f, 0.0f

// Earlier tried 1131 which should have been vgood, but it gave 0.48 for 
// acc and vgood, the difference between 1131 and 1134 is in lug_capacity
// which is med in 1131 whereas it big in 1134, so the result for 1134 was correct
//['price', 'maint', 'doors', 'persons', 'lug_capacity', 'safety']
// Line no. 1134: med med 3 more  big high  vgood   : Input4
    float input4[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.575342470f, 0.357142860f};
// Expected output4: 0.0f, 1.0f

    initfResult(fResult);
    fRes = ml.predict(input1, fResult);
    Serial.print("\nThe output value returned for input1 is:\n");
    Serial.println(fRes);
    displayOutput(fResult);  

    initfResult(fResult);
    fRes = ml.predict(input2, fResult);
    Serial.print("\nThe output value returned for input2 is:\n");
    Serial.println(fRes);
    displayOutput(fResult);      
    Serial.println();

    initfResult(fResult);
    fRes = ml.predict(input3, fResult);
    Serial.print("\nThe output value returned for input3 is:\n");
    Serial.println(fRes);
    displayOutput(fResult);    
  
    initfResult(fResult);
    fRes = ml.predict(input4, fResult);
    Serial.print("\nThe output value returned for input4 is:\n");
    Serial.println(fRes);
    displayOutput(fResult);  

    delay(5000); // 5 milliseconds of delay between two plots
}

void initfResult(float *fResult){
  
    for(int i = 0; i < NUMBER_OF_OUTPUTS; i++){
       fResult[i] = 0.0f;
    }
} // end of displayOutput()

void displayOutput(float *fResult){
  
    for(int i = 0; i < NUMBER_OF_OUTPUTS; i++){
        Serial.print(fResult[i]);
        Serial.print(" ");
    }
} // end of displayOutput()
