# Launchpad using STM32F107
* MCU Number : STM32F107VHTx
* System Clock = 40MHz

## Project Directory Description
### BluetoothApp
- Bluetooth : Bluetooth SPP is implemented.
- MusicPlay : Playing music with `MediaPlayer` and Adjusting android's audio volume with `AudioManager`. This class is triggered by STM32F107 signal during bluetooth communication.

### Project
- Libraries : _STM32F10x_StdPeriph_Driver_v3.5_ is used
- init : _STM32F107_ System Configuration is implemented
- LCD : _TFT LCD_ Part is implemented
- PWM : _NeoPixel SK6812_ Part is implemented
- MPR121 : **SHOULD NOT USE**
- bluetooth : _BLUETOOTH_ Part is implemeneted

## Used Module Description
### Bluetooth Module - Used Model : [FB755AC](http://www.funnykit.co.kr/bemarket/datasheet/FB755_UserGuide_Kor.pdf)
- **STM32** - **ANDROID** Transmission : `USART2`
    - Configuration
        - BaudRate = `9600`
        - WordLength = `8bit`
        - Stopbits = `1bit`
        - Parity = `No`
    - USART2 Port(used)
        - TX = `PA2`
        - RX = `PA3`
- **PUTTY(COM)** - **STM32** Transmission : `USART1`
    - Configuration
        - BaudRate = `9600`
        - WordLength = `8bit`
        - Stopbits = `1bit`
        - Parity = `No`
    - USART1 Port(used)
        - TX = `PC10`
        - RX = `PC11`

### TFT LCD Module 
- Port Configuration
	- RD = `PD15`
	- RS = `PD13`
	- CS = `PC6`
	- WR = `PD14`
	- TFT LCD PIN = `DB00 - DB16`

### NeoPixel LED Module - Used Model : [NeoPixel SK6812](https://cdn-shop.adafruit.com/product-files/1138/SK6812+LED+datasheet+.pdf)
- Port Configuration
	- PWM = `PA7`