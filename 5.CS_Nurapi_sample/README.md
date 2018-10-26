# NUR Api sample
This sample demonstrates how you can create a C# backend service using NUR api to perform RFID operations, MQTT to publish events and message. A front end that connects to the MQTT broker using websockets and listens for events published.

# Changelog

### v1.1.0
- Connect to the default MQTT service ports depending on which protocol is used (https/http)
- Call the backend with correct protocol https/http
