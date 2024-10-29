# ESP32气象站

## How to use ArduinoJson with HTTPClient?

* https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/

## 天气数据

高德地图天气 API 免费版可用资源

* key: d4aa79aeab835f56274c27742bb731c
* 南京：city:32010

* https://restapi.amap.com/v3/weather/weatherInfo?key=d4aa79aeab835f56274c27742bb731cc&city=320100&extensions=all

extensions: 气象类型, 可选值：base/all

* base:返回实况天气
* all:返回预报天气

* base:返回实况天气
```c
  String weather = doc["lives"][0]["weather"];
  int temperature = doc["lives"][0]["temperature"];
  int humidity = doc["lives"][0]["humidity"];
  String winddirection = doc["lives"][0]["winddirection"];
  String windpower= doc["lives"][0]["windpower"];
```
```json
{
    "status": "1",
    "count": "1",
    "info": "OK",
    "infocode": "10000",
    "lives": [
        {
            "province": "江苏",
            "city": "南京市",
            "adcode": "320100",
            "weather": "多云",
            "temperature": "13",
            "winddirection": "北",
            "windpower": "≤3",
            "humidity": "75",
            "reporttime": "2024-10-29 20:01:42",
            "temperature_float": "13.0",
            "humidity_float": "75.0"
        }
    ]
}
```

* all:返回预报天气

```c
 // Extract weather information
      String date = doc["forecasts"][0]["casts"][0]["date"];
      String week = doc["forecasts"][0]["casts"][0]["week"];
      String dayweather = doc["forecasts"][0]["casts"][0]["dayweather"];
      float temperature = doc["forecasts"][0]["casts"][0]["daytemp"];
```
```json
{
    "status": "1",
    "count": "1",
    "info": "OK",
    "infocode": "10000",
    "forecasts": [
        {
            "city": "南京市",
            "adcode": "320100",
            "province": "江苏",
            "reporttime": "2024-10-29 19:34:38",
            "casts": [
                {
                    "date": "2024-10-29",
                    "week": "2",
                    "dayweather": "晴",
                    "nightweather": "晴",
                    "daytemp": "20",
                    "nighttemp": "10",
                    "daywind": "东北",
                    "nightwind": "东北",
                    "daypower": "1-3",
                    "nightpower": "1-3",
                    "daytemp_float": "20.0",
                    "nighttemp_float": "10.0"
                },
                {
                    "date": "2024-10-30",
                    "week": "3",
                    "dayweather": "晴",
                    "nightweather": "晴",
                    "daytemp": "21",
                    "nighttemp": "12",
                    "daywind": "东北",
                    "nightwind": "东北",
                    "daypower": "4",
                    "nightpower": "4",
                    "daytemp_float": "21.0",
                    "nighttemp_float": "12.0"
                },
                {
                    "date": "2024-10-31",
                    "week": "4",
                    "dayweather": "多云",
                    "nightweather": "小雨",
                    "daytemp": "21",
                    "nighttemp": "15",
                    "daywind": "东",
                    "nightwind": "东",
                    "daypower": "4",
                    "nightpower": "4",
                    "daytemp_float": "21.0",
                    "nighttemp_float": "15.0"
                },
                {
                    "date": "2024-11-01",
                    "week": "5",
                    "dayweather": "小雨",
                    "nightweather": "多云",
                    "daytemp": "19",
                    "nighttemp": "15",
                    "daywind": "北",
                    "nightwind": "北",
                    "daypower": "4",
                    "nightpower": "4",
                    "daytemp_float": "19.0",
                    "nighttemp_float": "15.0"
                }
            ]
        }
    ]
}
```

##  其他参考天气

### 和风天气

已经要求付费，请求返回：`402` Payment Required

```js
//天气部分 -和风天气: cmh@seu.edu.cn,ps: hftq123456
    function TodayWeather(){
        var NowWeather = new XMLHttpRequest();
            NowWeather.open("GET","https://devapi.qweather.com/v7/weather/now?location=101190101&key=2d9a2cb5bf004272acf4b854fd55c398",true);
            
```json
{
    "code": "200",
    "updateTime": "2024-10-29T13:12+08:00",
    "fxLink": "https://www.qweather.com/weather/nanjing-101190101.html",
    "now": {
        "obsTime": "2024-10-29T13:10+08:00",
        "temp": "20",
        "feelsLike": "18",
        "icon": "100",
        "text": "晴",
        "wind360": "0",
        "windDir": "北风",
        "windScale": "3",
        "windSpeed": "13",
        "humidity": "42",
        "precip": "0.0",
        "pressure": "1016",
        "vis": "23",
        "cloud": "0",
        "dew": "10"
    },
    "refer": {
        "sources": [
            "QWeather"
        ],
        "license": [
            "CC BY-SA 4.0"
        ]
    }
}
```

###  OpenWeather weather data

* https://www.makerguides.com/simple-esp32-internet-weather-station/

