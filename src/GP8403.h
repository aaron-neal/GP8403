#pragma once

#include "Arduino.h"
#include "Wire.h"

#define GP8403_LIB_VERSION               (F("1.0.0"))

#ifndef GP8403_ADDRESS
#define GP8403_ADDRESS             0x58
#endif

// REGISTERS
const uint8_t VSEL_REG  = 0x01; //Voltage level reg 0x00 5v / 0x11 10v
const uint8_t VOUT_0_REG  =  0x02; //V_OUT_0  Register
const uint8_t VOUT_1_REG  =  0x04; //V_OUT_1  Register
const uint8_t V_5_SEL     =  0x00; // 5V output
const uint8_t V_10_SEL    =  0x11; // 10V output

class GP8403
{
  
public:
  enum VOLTAGE_SEL {
    V_5 = V_5_SEL,
    V_10 = V_10_SEL,
  };

  enum OUTPUT_SEL {
    OUT_0 = VOUT_0_REG,
    OUT_1 = VOUT_1_REG,
  };

  GP8403(uint8_t Address = GP8403_ADDRESS, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool     begin(uint8_t sda, uint8_t scl);
#endif
  bool     begin();
  bool     isConnected();
  bool     setVoltageRange(VOLTAGE_SEL _vSel);
  bool     setOutput(OUTPUT_SEL _channel, uint16_t _lvl);
  void     setWireClock(uint32_t clockSpeed);
  uint8_t  address(){ return _address; };

protected:
  uint8_t  _address;
  TwoWire*  _wire;
  bool _writeRegister8(uint8_t address, uint8_t reg, uint8_t value);
  bool _writeRegister16(uint8_t address, uint8_t reg, uint16_t value);
  uint8_t _readRegister8(uint8_t address, uint8_t reg);
  uint16_t _readRegister16(uint8_t address, uint8_t reg);
};
