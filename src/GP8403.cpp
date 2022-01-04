#include "GP8403.h"

GP8403::GP8403(uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}

#if defined (ESP8266) || defined(ESP32)
    bool GP8403::begin(uint8_t sda, uint8_t scl)
    {
    _wire = &Wire;
    _wire->begin(sda, scl);
    if (! isConnected()) return false;
    return true;
    }
#endif


bool GP8403::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}

bool GP8403::isConnected()
{
  _wire->beginTransmission(_address);
  return (_wire->endTransmission() == 0);
}


bool GP8403::setVoltageRange(VOLTAGE_SEL _vSel){
  return _writeRegister8(_address, VSEL_REG, _vSel);
}

bool GP8403::setOutput(OUTPUT_SEL _channel, uint16_t _lvl){
  uint8_t hibyte = ((_lvl << 4) & 0xff00) >> 8; 
  uint8_t lobyte = ((_lvl << 4) & 0xff);
  _lvl = lobyte << 8 | hibyte;
  return _writeRegister16(_address, _channel, _lvl);
}

void GP8403::setWireClock(uint32_t clockSpeed)
{
  _wire->setClock(clockSpeed);
}

bool GP8403::_writeRegister8(uint8_t address, uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(address);
  _wire->write((uint8_t)reg);
  _wire->write((uint8_t)value);
  return (_wire->endTransmission() == 0);
}

bool GP8403::_writeRegister16(uint8_t address, uint8_t reg, uint16_t value)
{
  _wire->beginTransmission(address);
  _wire->write((uint8_t)reg);
  _wire->write((uint8_t)(value >> 8));
  _wire->write((uint8_t)(value & 0xFF));
  return (_wire->endTransmission() == 0);
}

uint8_t GP8403::_readRegister8(uint8_t address, uint8_t reg)
{
  _wire->beginTransmission(address);
  _wire->write(reg);
  _wire->endTransmission();

  int rv = _wire->requestFrom(address, (uint8_t) 1);
  if (rv == 1) 
  {
    return _wire->read();
  }
  return 0x00;
}

uint16_t GP8403::_readRegister16(uint8_t address, uint8_t reg)
{
  _wire->beginTransmission(address);
  _wire->write(reg);
  _wire->endTransmission();

  int rv = _wire->requestFrom(address, (uint8_t) 2);
  if (rv == 2) 
  {
    uint16_t value = _wire->read() << 8;
    value += _wire->read();
    return value;
  }
  return 0x0000;
}

