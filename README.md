# GP8403 Arduino
An easy to use library for using the Guestgood GP8403 I2C 0-5v/0-10v DAC.
This IC simplifies the generation of industrial 0-10v outputs.

[LCSC Link](url=https://lcsc.com/product-detail/ADC-DAC-Specialized_Guestgood-GP8403-TC50-EW_C2856292.html)

# NOTE
This library should still be considered as in development and should not be relied upon for critical systems.
Any improvements / suggestions welcome in PRs

# Usage
- Include the library 
    ```
    <#include "GP8403.h">
    ```
- Declare an instance or many 
    ```
    GP8403 _gp8403 = GP8403(0x58);
    ```
- Initiliase Library and Set IC 
    ```
    _gp8403.begin(15,16);
    _gp8403.setVoltageRange(GP8403::V_5); //0-5V Output
    _gp8403.setVoltageRange(GP8403::V_10); //0-10V Output
    ``` 
- Setting the output
  ```
  _gp8403.setOutput(GP8403::OUT_0, 0); // 0 out_0
  _gp8403.setOutput(GP8403::OUT_1, 0); // 0 out_1

  _gp8403.setOutput(GP8403::OUT_0, 4095); // 100% out_0
  _gp8403.setOutput(GP8403::OUT_1, 4095); // 100% out_1
  ```