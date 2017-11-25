# 2017_stm310_launchpad

MCU Number : STM32F107VHTx
System Clock =    

## Used Open Source Library
- akexorcist/Android-BluetoothSPPLibrary


## Interrupt Priority(PreemptionPriority/SubPriority)
- Bluetooth Interrupt
    - USART2 : 0/0
    - USART3 : 0/0
## Port Specification
### * Bluetooth Module - Used Model : FB755AC
- Module - STM32(Board) Data transmission : USART3
    - Configuration
        - BaudRate = 9600
        - WordLength = 8bit
        - Stopbits = 1bit
        - Parity = No
    - USART3 Port(used)
        - TX = PC10
        - RX = PC11

- Module - Android(Smartphone) Data transmission : USART2
    - Configuration
        - BaudRate = 9600
        - WordLength = 8bit
        - Stopbits = 1bit
        - Parity = No
    - USART2 Port(used)
        - TX = PA2
        - RX = PA3

### * TFT LCD Module
### * MPR121 Module
### * NeoPixel LED Module