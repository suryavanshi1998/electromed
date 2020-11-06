// This example shows the different ways you can use String with ArduinoJson.
//
// Use String objects sparingly, because ArduinoJson duplicates them in the
// JsonBuffer. Prefer plain old char[], as they are more efficient in term of
// code size, speed, and memory usage.

#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  DynamicJsonBuffer jsonBuffer;

  // You can use a String as your JSON input.
  // WARNING: the content of the String will be duplicated in the JsonBuffer.
  String input =
        "{\"status\":success\",\"msg\":null,\"data\":{\"text\":Poor,\"alert\":\"Poor air quality index in this location. It may cause breathing discomfort to people on prolonged exposure, and discomfort to people with heart disease.\",\"color\":\"#FF9A00;\",\"value\":300,\"index\":4,\"updated\":\"Wed Oct 28 08:45:00 +0000 2020\",\"temp\":\"31\",\"content\":null,\"country\":\"India\",\"clouds\":\"description = haze, image = https://airpollutionapi.com/images/icons/50d.png\",\"coordinates\":{\"latitude\":26.8718431,\"longitude\":80.9459051},\"source\":{\"name\":\"CPCB, Lalbagh, Lucknow  CPCB\",\"coordinates\":{\"latitude\":26.8458805,\"longitude\":80.9365541}},\"accuracy\":\"3.03 Km\",\"dominating\":\"PM2.5\",\"aqiParams\":[{\"name\":\"NO2\",\"value\":\"26.23 µg/m³, AQI 32\",\"aqi\":32,\"color\":\"#79bc6a;\",\"text\":\"Good\",\"updated\":\"Wed Oct 28 08:47wQbNPTDJp9hMYdvogK2hAUiHsGeiybwaWe36bwtRQ3UTpYV7YuZ8FV5j9nauFCWwcjM6dTzpL5s2N79Rp5unwdMvc8ZKU\":\"Satisfactory\",\"updated\":\"Wed Oct 28 08:45:00 +0000 2020\"},{\"name\":\"PM2.5\",\"value\":\"125.41 µg/m³, AQI 300\",\"aqi\":300,\"color\":\"#A52A2A;\",\"text\":\"Severe\",\"updated\":\"Wed Oct 28 08:45:00 +0000 2020\"},{\"name\":\"SO2\",\"value\":\"4.33 µg/m³, AQI 4\",\"aqi\":4,\"color\":\"#79bc6a;\",\"text\":\"Good\",\"updated\":\"Wed Oct 28 08:45:00 +0000 2020\"},{\"name\":\"CO\",\"value\":\"390.0 µg/m³, AQI 19\",\"aqi\":19,\"color\":\"red\",\"text\":\"Very poor\",\"updated\":\"Wed Oct 28 08:45:00 +0000 2020\"},{\"name\":\"Humidity\",\"value\":\"38.0 %\",\"aqi\":null,\"color\":null,\"text\":null,\"updated\":null},{\"name\":\"Barometric Pressure\",\"value\":\"1011.0 hPa\",\"aqi\":null,\"color\":null,\"text\":null,\"updated\":null},{\"name\":\"Wind Speed\",\"value\":\" 4.7 m/s\",\"aqi\":null,\"color\":null,\"text\":null,\"updated\":null},{\"name\":\"Wind Direction\",\"value\":\"340.0 degrees\",\"aqi\":null,\"color\":null,\"text\":null,\"updated\":null}]}}";

  JsonObject& root = jsonBuffer.parseObject(input);

  // You can use a String to get an element of a JsonObject
  // No duplication is done.
  String status = root[String("status")];//[String("msg")][String("data")][String("text")];

  // You can use a String to set an element of a JsonObject
  // WARNING: the content of the String will be duplicated in the JsonBuffer.
  root[String("status")] = status;

  // You can get a String from a JsonObject or JsonArray:
  // No duplication is done, at least not in the JsonBuffer.
  
//  String text = root["text"];
 status = root["text"].as<String>();

  // You can set a String to a JsonObject or JsonArray:
  // WARNING: the content of the String will be duplicated in the JsonBuffer.
  //root["text"] = text;
  Serial.print("\n");
  //Serial.print("text:");
//  Serial.print(text);
  Serial.print("\n");
  Serial.print("Status:");
  Serial.print(status);
  Serial.print("\n");
  

  // Lastly, you can print the resulting JSON to a String
  String output;
  root.printTo(output);
  //Serial.println(output);
}

void loop() {
  // not used in this example
}
