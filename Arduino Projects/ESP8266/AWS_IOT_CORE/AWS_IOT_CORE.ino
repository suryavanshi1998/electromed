#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "emedwifi.h"
const char AWS_PUBLIC_CERT[] = "-----BEGIN CERTIFICATE-----\n"\
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsFADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTELMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJvb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXjca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qwIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQmjgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUAA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDIU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUsN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vvo/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpyrqXRfboQnoZsG4q5WTP468SQvvG5\n"\
"-----END CERTIFICATE-----\n";
const char AWS_PRIVATE_KEY[] = "-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpgIBAAKCAQEAyTBmp4oqtajsn1YFJvWohU6oAnvo15TvtT/Zw8Euvc+YgoLYBntTGwsP2VzigO2UUtrbmOgOh4uFc1BptyFAGbljY6j9CMyzlmprfEBv3YrWwW13CAGWksoXEV3OAXy9gMlDFBwvkYqpxkTjBPB4VnzvwabtIbCs7i0LT64+q+oM0/vGcMtp3kOpF3WXNCLe6KdMFJCbosKPy4kMdHl97X1gTxbajJMtZIz9fd8mbZ7ZFSgV9rtWLcrmXK4gL2VX5HMDzsXSdbTcJ9Qp73/AUGFEbkGT2emrDElWT3VYcuWsElaOZa5EPuqIpFT72G9i7SBp87rbZSi7uNgyk77BGQIDAQABAoIBAQCmU+p6VmLq3mYJcI8/31ZcJ2QE8bXVDN+EA+6fxMVEzSyzsUKxUSGquOF4fS8REdlPCnsEFc11R+ajJ/bOHKIm4jqF+P6AWOOb1g1YotkY2iCjt0DyEIYQgxzBEcEvP5ZXs4xOQuMcuvuS2/6nZbrHHfEFM2DWOn8tRXYVgON1McgIbn/hBV+X9uaGW+j7oHUb4Z4PVg/KDrE11/XkSb2qU+/Cnn5v1pXeU0YE9APbAtNnstYaUcfryQEI086Qp51BWF00OjlfbUD0/6BiaL5jS+83DO46at1ACWM05j6hrLWG+cRZnp4Ttk7xWnrdRlF/Dotoax7RlBoojwDxTB11AoGBAPtJ8//EjhaQry5nFkvZg2Iz3YMhUpWL6NpDwTFw9d9idJYmKpaKeb8SO9h87N9e88lbUoaMQyNP20Mz0SWjbfgh6wKcPTRZMP4kV900kjZC0oZeu/Oh3mOkJACpJ0J8/mxoQUJmsxuR5bjvZ1ljGm/z0Q2b37X9PF0T7/UsPzzTAoGBAMz1/yMxg4LNCCz3wQg3HjSgTptkksAKwJ0m7vvTtspM1ACtilFxutSPNzBjv6pRZRHIkySn7UkP1g2HBswF7ey31zI5lMlAXChHSP/oZlZNB8mNOjNuXHHkxFJa4kx8gAIzGWpaCOyJJT/b0SM/Bd6Wv5H8NZWZpz7gIhH/+abjAoGBAOMp1n7XxA8YGpVbMae96WykMFJzlEGGqiht6b71PAAF9BksRYGzix20sQ8i18uR/daATNk/AQ5yCWf19tMMq8QNfXLtpNKm8og8eIWLGcYdoE1CZKx5Hx56auWCBPCxKBr+IEiTqMR6nu4Q1h/TXDnqcojX6WOOmrwV4u2DY2NrAoGBAIxTqFkqH0ZApmZTQmAjjJSvZOJTW34MXo+6Bkl4TF/5dfT43Aii+y1o2HpS8PjlPXONheDE8FrjcsRUPD0XmixGOhny/oFDhVU2aS58qQRRPRGrlbt8xeJcpGVWQDXpz6Kx5abA+fcods5f67JcBeK+B28l5HIGf1E3F1yHix/NAoGBANugYLEDw2FhqJCpBgWMqfGazJdAYMfEvTfL+lFXR5fle0zLtYjXmy5Qjh6F8IODW+/hw/8Pw9Wiq4672v95558KMtDuZbQ+nj412C97ytZexIB9TAU4U/cE/H2T4oKZUs+CfVCv86pYbIw3TNogrHP1Bmptrf/UjasYErPNnga4\n" \
"-----END RSA PRIVATE KEY-----\n";
const char AWS_DEVICE_CERT[] = "-----BEGIN CERTIFICATE-----\n"\
"MIIDWjCCAkKgAwIBAgIVAJbG6bVv5gG6IVQDUzBK710kZFLAMA0GCSqGSIb3DQEBCwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29tIEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMTAxMTkwOTEwMjVaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNhdGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDJMGaniiq1qOyfVgUm9aiFTqgCe+jXlO+1P9nDwS69z5iCgtgGe1MbCw/ZXOKA7ZRS2tuY6A6Hi4VzUGm3IUAZuWNjqP0IzLOWamt8QG/ditbBbXcIAZaSyhcRXc4BfL2AyUMUHC+RiqnGROME8HhWfO/Bpu0hsKzuLQtPrj6r6gzT+8Zwy2neQ6kXdZc0It7op0wUkJuiwo/LiQx0eX3tfWBPFtqMky1kjP193yZtntkVKBX2u1YtyuZcriAvZVfkcwPOxdJ1tNwn1Cnvf8BQYURuQZPZ6asMSVZPdVhy5awSVo5lrkQ+6oikVPvYb2LtIGnzuttlKLu42DKTvsEZAgMBAAGjYDBeMB8GA1UdIwQYMBaAFJRt9v5LXuDzCybpuraIZK+FbywYMB0GA1UdDgQWBBQe0w5M++cdr15dDBtntWVxhp34GjAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAcuSUYsOfcG/BswuzQebVmvkr3xyLwk9P4tmc1SGhIaKllMv2MysV+cAALk4Fj724gpbj6KeNnIaGjexODjFsNLLukBkNwqsWDL/dMTNirLKc6H1PaEQlUJs8gJ6bG+7S4CC6ylIlYkyxL9YRo2bcOuORs/mrCfXuvoR091hSeefEFwQHbKIRE0PSvC1F47y5qdgKOuag4hgb0HKEHS0/u9bffMkwCGDqqoW9dJbkn6X1tN2YwRiVp/6I8MbYyaaFFRbPFXOeHA2Wb6p4msV+TRCGfEW15HhjXYW1VojAEdCZ5G9Mo6+viRI8OA6vPTa29lyyfehAUk0H3qAcr0xoOA==\n"\
"-----END CERTIFICATE-----\n"; 
WiFiClientSecure secureClient = WiFiClientSecure();
PubSubClient mqttClient(secureClient);
void connectToWiFi() {
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void connectToAWS() {
  mqttClient.setServer("a3irubq5su94at-ats.iot.ap-south-1.amazonaws.com", 8883);
  secureClient.setCACert(AWS_PUBLIC_CERT);
  secureClient.setCertificate(AWS_DEVICE_CERT);
  secureClient.setPrivateKey(AWS_PRIVATE_KEY);
  Serial.println("Connecting to MQTT....");
  mqttClient.connect(DEVICE_NAME);
  
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT....Retry");
    mqttClient.connect(DEVICE_NAME);
    delay(5000);
  }
  Serial.println("MQTT Connected");
}
void setup() {
  Serial.begin(9600);
  connectToWiFi();
  connectToAWS();
}
