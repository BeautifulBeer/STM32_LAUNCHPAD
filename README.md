# 2017_stm310_launchpad

MCU Number : STM32F107VHTx
System Clock = 72MHz

## Used Open Source Library


## Interrupt Priority(PreemptionPriority/SubPriority)
### LCD Refresher 0
### PWM - 1
## Port Specification
### PE0, PB6, PB7 - MPR121
### PA7 - NeoPixel
### PA2, PA3 - Bluetooth
### * Bluetooth Module - Used Model : FB755AC
- Putty Commnad Line - STM32(Board) Data transmission : USART1
    - Configuration
        - BaudRate = 9600
        - WordLength = 8bit
        - Stopbits = 1bit
        - Parity = No
    - USART1 Port(used)
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

- 
### * TFT LCD Module
### * MPR121 Module
### * NeoPixel LED Module