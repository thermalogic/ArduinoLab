## 74hHC595扩展output

3个转8个，可以解决小车输出端口不足问题

*  https://lastminuteengineers.com/74hc595-shift-register-arduino-tutorial/

## 问题

芯片直接插在面包板上，不使用芯片座，芯片座在面包板，插不好接触不良。

## 连线

需要和Arduino 数字端口连接的有3个

* latchPin： RCLK (Register Clock / Latch) (12) -> Arduino D5
* clockPin: SRCLK (Shift Register Clock) (11)    -> Arduino D6
* dataPin: SER (Serial Input)(14)  -> Arduino D4

## 4HC595 Shift Register Pinout

* SER (Serial Input) pin is used to `send data into the shift register` one bit at a time.

* SRCLK (Shift Register Clock) is the `clock for the shift-register` and is `positive`-edge triggered. This means that the bits are pushed in on the rising edge of the clock.

* RCLK (Register Clock / Latch - 锁存器) is a very important pin. When this pin is pulled `HIGH`, the contents of the Shift Register are copied into the Storage/Latch Register, which eventually appears at the output. So, the `latch` pin can be seen as the `last` step before we see our results at the output.
