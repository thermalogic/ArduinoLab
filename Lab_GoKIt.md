# Gokit 实验板

GoKit扩展板载有：

* Chainable RGB
* DHT11
* Motor
# Gokit实验本


## Chainable RGB


使用在线的Groove RGB库

需要修改

```c
ChainableLED leds(7,8, NUM_LEDS);
```
和GoKit扩展板的接口一致
```c
ChainableLED leds(SCL,SDA, NUM_LEDS);
```

## DHT11

使用在线的DFRobot的库,修改
```c
#define DHT11_PIN 10
```
和GoKit扩展板的接口一致
```c
#define DHT11_PIN 3 
```

## 电机


## 红外


