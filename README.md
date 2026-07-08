# Embedded-vehicle-control-system
Bare-metal STM32F407 smart vehicle simulation in register-level C (no HAL). Features accelerometer-based motion sensing, ambient light-controlled headlights, Bluetooth motor control, and real-time status on a 20×4 I2C LCD, demonstrating low-level embedded systems programming and peripheral interfacing.

**# Features**

- **Bluetooth (HC-06) remote control** — Start/Stop/Standby, Forward/Backward/Left/Right commands over UART2
- **Motor control** — Dual-motor differential drive via L298N H-bridge, PWM speed control on TIM2
- **Accelerometer monitoring** — SPI-based 3-axis acceleration reading with real-time magnitude calculation (integer square root, no `libm`)
- **Auto-headlight** — ADC-based LDR light sensing that automatically toggles a headlight LED
- **Status display** — 20x4 character LCD over I2C (PCF8574 backpack) showing system mode, magnitude, and headlight status
- **Turn signal LEDs** — GPIO-driven indicators tied to motor direction

  ## Software Architecture

Bare-metal, register-level C — no HAL/LL libraries. Each peripheral has its own driver file under `Core/Src`:

    File                     Responsibility 

 **main.c**             System init, main control loop, magnitude calculation, integer `sq_root()` 
 **SPI.c** |            SPI1 GPIO/peripheral init, byte send/receive, chip-select control 
 **LIS302DL_ACC.c**     Accelerometer register read/write, 3-axis data acquisition, WHO_AM_I check 
 **I2C_LCD.c**          I2C1 init, PCF8574-based 4-bit LCD driver (init, cursor, print) 
 **Uart.c**             USART2 init, RX polling, Bluetooth command handler (state machine) 
 **Timer.c**            TIM2 PWM init (dual channel), motor direction logic, motor stop 
 **ADC_LDR.c**          ADC1 single-channel init for the LDR 
 **syscalls.c**         Newlib syscall stubs (ITM-based `printf` redirection, heap management) 

 ## Build Environment

- STM32CubeIDE
- Target: STM32F407 (Discovery board)
- 
