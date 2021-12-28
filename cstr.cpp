#include "cstr.h"

char intTo_StringOutput[128];

const char* to_string(uint64_t value){
   uint8_t size;
   uint64_t sizeTest = value;
   
   while(sizeTest / 10 > 0){
       sizeTest /= 10;
       size++;
   }

    uint8_t index = 0;

    while(value / 10 > 0)
    {
        uint8_t remainder = value % 10;
        value /= 10;   
        intTo_StringOutput[size - index] = remainder + '0';
        index++; 
    }

    uint8_t remainder = value % 10;
    intTo_StringOutput[size - index] = remainder + '0';
    intTo_StringOutput[size + 1] = 0;    
    return intTo_StringOutput;
}

const char* to_string(int64_t value){

   uint8_t isNegative = 0;
   
    if(value < 0){
        isNegative = 1;
        value *= -1;
        intTo_StringOutput[0] = '-';
    }

   uint8_t size;
   uint64_t sizeTest = value;
   
   while(sizeTest / 10 > 0){
       sizeTest /= 10;
       size++;
   }

    uint8_t index = 0;

    while(value / 10 > 0)
    {
        uint8_t remainder = value % 10;
        value /= 10;   
        intTo_StringOutput[isNegative + size - index] = remainder + '0';
        index++; 
    }

    uint8_t remainder = value % 10;
    intTo_StringOutput[isNegative + size - index] = remainder + '0';
    intTo_StringOutput[isNegative + size + 1] = 0;    
    return intTo_StringOutput;
}

char doubleTo_StringOutput [128];
const char* to_string(double value, uint8_t decimal){
    char* intPtr = (char*)to_string((int64_t)value);
    char* doublePtr = doubleTo_StringOutput;

    if(decimal > 20) decimal=20;

    if(value < 0){
        value *= -1;
    }

    while(*intPtr != 0){
        *doublePtr = *intPtr;
        intPtr++;
        doublePtr++;
    }

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value;

    for(uint8_t i = 0; i < decimal; i++){
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }

    *doublePtr = 0;
    return doubleTo_StringOutput;
}    

char Hex_toStringOutput64[128];
const char* to_hstring(uint64_t value){
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t temp;
    uint8_t size = 8 * 2 - 1;
    
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xF0) >> 4);
        Hex_toStringOutput64[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
        temp = ((*ptr & 0x0F));
        Hex_toStringOutput64[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
    }
    Hex_toStringOutput64[size + 1] = 0;
    return Hex_toStringOutput64;

}
char Hex_toStringOutput32[128];
const char* to_hstring(uint32_t value){
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t temp;
    uint8_t size = 4 * 2 - 1;
    
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xF0) >> 4);
        Hex_toStringOutput32[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
        temp = ((*ptr & 0x0F));
        Hex_toStringOutput32[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
    }
    Hex_toStringOutput32[size + 1] = 0;
    return Hex_toStringOutput32;

}
char Hex_toStringOutput16[128];
const char* to_hstring(uint16_t value){
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t temp;
    uint8_t size = 2 * 2 - 1;
    
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xF0) >> 4);
        Hex_toStringOutput16[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
        temp = ((*ptr & 0x0F));
        Hex_toStringOutput16[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
    }
    Hex_toStringOutput16[size + 1] = 0;
    return Hex_toStringOutput16;

}
char Hex_toStringOutput8[128];
const char* to_hstring(uint8_t value){
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t temp;
    uint8_t size = 1 * 2 - 1;
    
    for(uint8_t i = 0; i < size; i++){
        ptr = ((uint8_t*)valPtr + i);
        temp = ((*ptr & 0xF0) >> 4);
        Hex_toStringOutput8[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
        temp = ((*ptr & 0x0F));
        Hex_toStringOutput8[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
    }
    Hex_toStringOutput8[size + 1] = 0;
    return Hex_toStringOutput8;

}

