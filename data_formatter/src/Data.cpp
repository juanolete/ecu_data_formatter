/**
 * @file Data.cpp
 * @author Juan Millan (jjmillancas@gmail.com)
 * @brief Codigo fuente de Data.h
 */

#include "Data.h"

const char* hex_chars = "0123456789ABCDEF";

Data::Data() {
    byteMsg = nullptr;
    byteMsgLen = 0;
    msg = nullptr;
}

Data::~Data() {
    delete[] byteMsg;
    delete[] msg;
}

char* Data::getMsg(uint32_t id, uint32_t timestamp, uint16_t type, uint32_t odometerData, uint32_t hourMeterData, uint32_t tfuData, uint8_t velocityData, uint8_t fuelData) {
    saveEcuData(odometerData, hourMeterData, tfuData, velocityData, fuelData);
    generateByteMsg(id, timestamp, type);
    return generateMsg();
}

char* Data::getMsg(uint32_t id, uint32_t timestamp, uint16_t type, uint32_t odometerData, uint32_t hourMeterData, uint32_t tfuData, uint8_t velocityData, uint8_t fuelData, uint32_t otherData) {
    saveEcuData(odometerData, hourMeterData, tfuData, velocityData, fuelData);
    generateByteMsg(id, timestamp, type, otherData);
    return generateMsg();
}

int Data::getMsgLength() {
    return byteMsgLen*2;
}

uint8_t* Data::getByteMsg(uint32_t id, uint32_t timestamp, uint16_t type, uint32_t odometerData, uint32_t hourMeterData, uint32_t tfuData, uint8_t velocityData, uint8_t fuelData) {
    saveEcuData(odometerData, hourMeterData, tfuData, velocityData, fuelData);
    return generateByteMsg(id, timestamp, type);
}

uint8_t* Data::getByteMsg(uint32_t id, uint32_t timestamp, uint16_t type, uint32_t odometerData, uint32_t hourMeterData, uint32_t tfuData, uint8_t velocityData, uint8_t fuelData, uint32_t otherData) {
    saveEcuData(odometerData, hourMeterData, tfuData, velocityData, fuelData);
    return generateByteMsg(id, timestamp, type);
}

int Data::getByteMsgLength() {
    return byteMsgLen;
}

void Data::saveEcuData(uint32_t odometerData, uint32_t hourMeterData, uint32_t tfuData, uint8_t velocityData, uint8_t fuelData) {
    data.odometer = odometerData;
    data.hourmeter = hourMeterData;
    data.tfu = tfuData;
    data.velocity = velocityData;
    data.fuel = fuelData;
}

char* Data::generateMsg() {
    int msgLen = byteMsgLen*2 + 1;
    if (msg != nullptr) {
        delete[] msg;
    }
    msg = new char[msgLen];
    int byteMsgIndex = 0;
    int charMsgIndex = 0;
    while (byteMsgIndex < byteMsgLen) {
        msg[charMsgIndex] = hex_chars[(byteMsg[byteMsgIndex] & 0xf0) >> 4];
        charMsgIndex++;
        msg[charMsgIndex] = hex_chars[(byteMsg[byteMsgIndex] & 0x0f)];
        charMsgIndex++;
        byteMsgIndex++;
    }
    msg[charMsgIndex] = 0;
    return msg;
}

uint8_t* Data::generateByteMsg(uint32_t id, uint32_t timestamp, uint16_t type) {
    if (byteMsg != nullptr) {
        delete[] byteMsg;
    }

    uint8_t headerLenBytes = 10; /**< Header data len */
    uint8_t dataLenBytes = 14; /**< Default data len */
    byteMsgLen = headerLenBytes + dataLenBytes;
    byteMsg = new uint8_t[byteMsgLen];

    int index = 0;
    // Header 
    index = saveValueOnByteArray(byteMsg, index, id);
    index = saveValueOnByteArray(byteMsg, index, timestamp);
    index = saveValueOnByteArray(byteMsg, index, type);
    // Data
    index = saveValueOnByteArray(byteMsg, index, data.odometer);
    index = saveValueOnByteArray(byteMsg, index, data.hourmeter);
    index = saveValueOnByteArray(byteMsg, index, data.tfu);
    index = saveValueOnByteArray(byteMsg, index, data.velocity);
    index = saveValueOnByteArray(byteMsg, index, data.fuel);
}

uint8_t* Data::generateByteMsg(uint32_t id, uint32_t timestamp, uint16_t type, uint32_t otherData) {
    if (byteMsg != nullptr) {
        delete[] byteMsg;
    }

    uint8_t headerLenBytes = 10;
    uint8_t dataLenBytes = 14 + 4;
    byteMsgLen = headerLenBytes + dataLenBytes;
    byteMsg = new uint8_t[headerLenBytes];

    int index = 0;
    // Header 
    index = saveValueOnByteArray(byteMsg, index, id);
    index = saveValueOnByteArray(byteMsg, index, timestamp);
    index = saveValueOnByteArray(byteMsg, index, type);
    // ECU Data
    index = saveValueOnByteArray(byteMsg, index, data.odometer);
    index = saveValueOnByteArray(byteMsg, index, data.hourmeter);
    index = saveValueOnByteArray(byteMsg, index, data.tfu);
    index = saveValueOnByteArray(byteMsg, index, data.velocity);
    index = saveValueOnByteArray(byteMsg, index, data.fuel);
    // Other Data
    index = saveValueOnByteArray(byteMsg, index, otherData);
}

int Data::saveValueOnByteArray(uint8_t* outputArray, int initIndex, uint8_t value) {
    outputArray[initIndex] = value;
    return initIndex+1;
}

int Data::saveValueOnByteArray(uint8_t* outputArray, int initIndex, uint16_t value) {
    int index = initIndex;
    outputArray[index] = (value & 0xff00) >> 8;
    outputArray[index + 1] = (value & 0x00ff);
    return index + 2;
}

int Data::saveValueOnByteArray(uint8_t* outputArray, int initIndex, uint32_t value) {
    int index = initIndex;
    outputArray[index] = (value & 0xff000000) >> 24;
    outputArray[index + 1] = (value & 0x00ff0000) >> 16;
    outputArray[index + 2] = (value & 0x0000ff00) >> 8;
    outputArray[index + 3] = (value & 0x000000ff);
    return index + 4;
}
