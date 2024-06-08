// DistanceAlert.ino
// This code connects to a WiFi network and uses an ultrasonic sensor to measure distance. 
// If the distance is below a specified threshold, it sends data to a Blynk server.

// Include necessary libraries
#include <WiFi.h>

// Blynk credentials
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

// Network settings
const char ssid[] = ""; // Your network SSID (name)
const char pass[] = ""; // Your network password

// Blynk cloud server settings
const char* host = "blynk.cloud";
unsigned int port = 80;

// Create WiFi client instance
WiFiClient client;

// Define ultrasonic sensor pins
const int trigPin = 5;
const int echoPin = 18;

// Define sound speed in cm/µs
#define SOUND_SPEED 0.034

long duration; // Time taken for the pulse to return
float distance; // Calculated distance in cm

// Function to start the WiFi connection
void connectNetwork() {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    // Wait until the WiFi is connected
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");
}

// Function to perform an HTTP request
bool httpRequest(const String& method, const String& url, const String& request, String& response) {
    Serial.print(F("Connecting to "));
    Serial.print(host);
    Serial.print(":");
    Serial.print(port);
    Serial.print("... ");
    if (client.connect(host, port)) {
        Serial.println("OK");
    } else {
        Serial.println("failed");
        return false;
    }

    // Send HTTP request
    Serial.print(method); 
    Serial.print(" "); 
    Serial.println(url);

    client.print(method); 
    client.print(" ");
    client.print(url); 
    client.println(F(" HTTP/1.1"));
    client.print(F("Host: ")); 
    client.println(host);
    client.println(F("Connection: close"));

    if (request.length()) {
        client.println(F("Content-Type: application/json"));
        client.print(F("Content-Length: ")); 
        client.println(request.length());
        client.println();
        client.print(request);
    } else {
        client.println();
    }

    // Wait for response
    int timeout = millis() + 5000;
    while (client.available() == 0) {
        if (timeout - millis() < 0) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return false;
        }
    }

    // Read response headers
    int contentLength = -1;
    while (client.available()) {
        String line = client.readStringUntil('\n');
        line.trim();
        line.toLowerCase();
        if (line.startsWith("content-length:")) {
            contentLength = line.substring(line.lastIndexOf(':') + 1).toInt();
        } else if (line.length() == 0) {
            break;
        }
    }

    // Read response body
    response = "";
    response.reserve(contentLength + 1);
    while (response.length() < contentLength) {
        if (client.available()) {
            char c = client.read();
            response += c;
        } else if (!client.connected()) {
            break;
        }
    }
    client.stop();
    return true;
}

// Arduino setup function
void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT); 
    delay(10);
    Serial.println();
    Serial.println();

    // Connect to WiFi network
    connectNetwork();
}

// Arduino main loop function
void loop() {
    String response;

    // Send a 10µs pulse to trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the time for echo to return
    duration = pulseIn(echoPin, HIGH);
    distance = duration * SOUND_SPEED / 2;

    // Print the distance to the serial monitor
    Serial.println(distance);

    // If the distance is less than 50 cm, send an alert to Blynk
    if (distance < 50) {
        if (httpRequest("GET", String("/external/api/update?token=") + BLYNK_AUTH_TOKEN + "&pin=V0&value=" + distance, "", response)) {
            if (response.length() != 0) {
                Serial.print("WARNING: ");
                Serial.println(response);
            }
        }
        delay(1000); // Wait for 1 second before the next measurement
    }
    delay(50); // Wait for 50ms before the next loop
}
