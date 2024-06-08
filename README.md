
# Smart Belt Notifications

## Stay Safe and Connected with the Smart Belt: The Solution for Phone Addicts on the Go

Attention all smartphone addicts! Do you find yourself constantly glued to your phone screen, even when walking in public? You're not alone. Unfortunately, this behavior can lead to serious safety issues, including road rage incidents, collisions, and other accidents.

Fortunately, there's a new solution: the Smart Belt. This innovative device is designed specifically for people who are constantly on their phones and have no sense of their surroundings while walking in public.

### How It Works

The Smart Belt uses advanced sensors and algorithms to detect when someone is within a certain distance in front of you. When this happens, it sends a push notification to your phone, reminding you to look up and be aware of your surroundings.

This simple yet effective solution could be a game-changer for anyone who struggles with phone addiction while walking. By using the Smart Belt, you can stay connected to your phone while also staying aware of your surroundings, reducing the risk of accidents and other safety issues.

### Why Choose the Smart Belt?

- **Safety**: Stay aware of your surroundings while walking.
- **Connectivity**: Stay connected to your phone without compromising safety.
- **Peace of Mind**: Reduce the risk of accidents and collisions.

If you're a frequent pedestrian and want to stay safe while staying connected, consider investing in a Smart Belt today. Your future self (and fellow pedestrians) will thank you!



### Circuit Diagram

![circuit_diagram](https://github.com/arya2004/smart-belt-notifications/assets/72350136/b02fe34d-79f4-4552-af8a-3058d4f9eab9)



## Getting Started

### Prerequisites

- Arduino IDE
- ESP32 or similar microcontroller
- Ultrasonic sensor
- Blynk app

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/arya2004/smart-belt-notifications.git
   cd smart-belt-notifications
   ```

2. **Open the project in Arduino IDE**:
   - Open `src/DistanceAlert.ino` in the Arduino IDE.

3. **Configure WiFi and Blynk settings**:
   - Update the WiFi credentials and Blynk authentication token in `config/wifi_config.h`.

4. **Upload the code to the microcontroller**:
   - Connect your microcontroller to your computer and upload the code using the Arduino IDE.

### Usage

- Monitor the serial output for distance measurements.
- If the distance is below the threshold (50 cm), an alert will be sent to the Blynk server.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

