# Esp8266 Websocket with Arduino/


客户端数据更新，客户端请求，不然，数据到达后服务器端

* 目前客户端请求，程序简单

但目前，有客户端数据不稳定现象，有时没有数据，原因不明

* 可能的原因是， 这个web服务不是异步的，在客户端get请求时，服务的主循环在读串口数据，冲突

Websocket相关库，不少都已经很长时间没有维护了,不确定性大，`暂时不做websocket`

## 库：

* https://github.com/Links2004/arduinoWebSockets

* https://github.com/me-no-dev/ESPAsyncTCP

* https://github.com/me-no-dev/ESPAsyncWebServer

## 参考

* https://randomnerdtutorials.com/esp8266-nodemcu-websocket-server-arduino/#:~:text=Using%20the%20WebSockets%20protocol%2C%20the,browser%20when%20a%20change%20occurs.

* https://tttapa.github.io/ESP8266/Chap14%20-%20WebSocket.html

* http://www.martyncurrey.com/esp8266-and-the-arduino-ide-part-9-websockets/