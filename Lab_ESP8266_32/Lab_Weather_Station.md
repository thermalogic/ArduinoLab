# ESP32气象站

## 高德地图天气

###高德地图天气 API 免费版可用资源

* key: d4aa79aeab835f56274c27742bb731c
* 南京：city:32010

* https://restapi.amap.com/v3/weather/weatherInfo?key=d4aa79aeab835f56274c27742bb731cc&city=320100&extensions=all


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


##  OpenWeather weather data

* https://www.makerguides.com/simple-esp32-internet-weather-station/