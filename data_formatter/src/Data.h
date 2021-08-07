/**
 * @file Data.h
 * @author Juan Millan (jjmillancas@gmail.com)
 * @brief Archivo que declara clase Data para el tratado de datos recbidos desde una ECU de un vehiculo
 */
#ifndef _Data_h
#define _Data_h
#include <stdint.h>

/**
 * @brief ECU data container
 * 
 */
typedef struct ecu_data { 
    uint32_t    odometer;  /**< Odometer data [m] */
    uint32_t    hourmeter; /**< Hourmeter data [seg] */
    uint32_t    tfu;       /**< Total Fuel Used [ml] */
    uint8_t     velocity;  /**< Velocity [km/h] */
    uint8_t     fuel;      /**< Fuel percent [%] */
};

/**
 * @brief Data object 
 * 
 */
class Data {
    public:
        /**
         * @brief Construct a new Data object
         * 
         */
        Data(void);

        /**
         * @brief Destroy the Data object
         * 
         */
        ~Data();

        /**
         * @brief Construct the Message object and return it in HEX format String
         * 
         * @param id 
         * @param timestamp 
         * @param type 
         * @param odometerData 
         * @param hourMeterData 
         * @param tfuData 
         * @param velocityData 
         * @param fuelData 
         * @return char* Message to send
         */
        char* getMsg(uint32_t id, 
                    uint32_t timestamp, 
                    uint16_t type,
                    uint32_t odometerData,
                    uint32_t hourMeterData, 
                    uint32_t tfuData, 
                    uint8_t velocityData, 
                    uint8_t fuelData);

        /**
         * @brief Construct the Message object and return it in HEX format String
         * 
         * @param id 
         * @param timestamp 
         * @param type 
         * @param odometerData 
         * @param hourMeterData 
         * @param tfuData 
         * @param velocityData 
         * @param fuelData 
         * @param otherData 
         * @return char* Message to send
         */
        char* getMsg(uint32_t id, 
                    uint32_t timestamp, 
                    uint16_t type,
                    uint32_t odometerData,
                    uint32_t hourMeterData, 
                    uint32_t tfuData, 
                    uint8_t velocityData, 
                    uint8_t fuelData,
                    uint32_t otherData);

        /**
         * @brief Get the Msg C-String Length
         * 
         * @return int 
         */
        int getMsgLength(void);

        /**
         * @brief Construct and get the Byte Msg object
         * 
         * @param id 
         * @param timestamp 
         * @param type 
         * @param odometerData 
         * @param hourMeterData 
         * @param tfuData 
         * @param velocityData 
         * @param fuelData 
         * @return uint8_t* Byte msg object
         */
        uint8_t* getByteMsg(uint32_t id, 
                            uint32_t timestamp, 
                            uint16_t type,
                            uint32_t odometerData,
                            uint32_t hourMeterData, 
                            uint32_t tfuData, 
                            uint8_t velocityData, 
                            uint8_t fuelData);

        /**
         * @brief Construct and get the Byte Msg object
         * 
         * @param id 
         * @param timestamp 
         * @param type 
         * @param odometerData 
         * @param hourMeterData 
         * @param tfuData 
         * @param velocityData 
         * @param fuelData 
         * @param otherData 
         * @return uint8_t* Byte msg object
         */
        uint8_t* getByteMsg(uint32_t id, 
                            uint32_t timestamp, 
                            uint16_t type,
                            uint32_t odometerData,
                            uint32_t hourMeterData, 
                            uint32_t tfuData, 
                            uint8_t velocityData, 
                            uint8_t fuelData,
                            uint32_t otherData);

        /**
         * @brief Get the length of Byte Msg object
         * 
         * @return int Byte msg lenth
         */
        int getByteMsgLength(void);  
        
    private:
        ecu_data data; /**< ECU data container */
        uint8_t* byteMsg; /**< Message in byte format */
        int byteMsgLen; /**< Length of byteMsg in bytes */
        char* msg; /**< Message in HEX format String*/

        /**
         * @brief Save the ECU data on ECU data cointainer
         * 
         * @param odometerData 
         * @param hourMeterData 
         * @param tfuData 
         * @param velocityData 
         * @param fuelData 
         */
        void saveEcuData(uint32_t odometerData, 
                        uint32_t hourMeterData, 
                        uint32_t tfuData, 
                        uint8_t velocityData, 
                        uint8_t fuelData);

        /**
         * @brief Generate Byte format message
         * 
         * @param id 
         * @param timestamp 
         * @param type 
         * @return uint8_t* Byte array with the message
         */
        uint8_t* generateByteMsg(uint32_t id, uint32_t timestamp, uint16_t type);

        /**
         * @brief Generate Byte format message
         * 
         * @param id 
         * @param timestamp 
         * @param type 
         * @param otherData 
         * @return uint8_t* Byte array with the message
         */
        uint8_t* generateByteMsg(uint32_t id, uint32_t timestamp, uint16_t type, uint32_t otherData);

        /**
         * @brief Transform byteMsg on HEX formar String
         * 
         * @return char* C-String with the message in HEX format
         */
        char* generateMsg(void);

        /**
         * @brief Save byte value in byte array
         * 
         * @param outputArray Byte array where the value will be inserted
         * @param initIndex Position where the value will be inserted
         * @param value Value to insert on byte array
         * @return int Position of the pointer after the insertion
         */
        int saveValueOnByteArray(uint8_t* outputArray, int initIndex, uint8_t value);
        int saveValueOnByteArray(uint8_t* outputArray, int initIndex, uint16_t value);
        int saveValueOnByteArray(uint8_t* outputArray, int initIndex, uint32_t value);
};

#endif