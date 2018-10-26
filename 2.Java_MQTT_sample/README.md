# Java MQTT sample
This sample demonstrates how you can create a java application with a front-end for your smart device. The sample uses the MQTT service pre-installed in NordicID's smart readers to send and recieve commands from the front end to the java backend which is connected to the RFID service. Using this app you can run simple RFID invetories to read the available tags around the device and display them back in the front end.

# Prerequisites
### MQTT configuration:
1. Make sure that the MQTT service is up and listening to the correct ports.
* Port definitions for the front end are located in `zipcontents/frontend/config.js`. The frontend decides which port to use depending on which protocol the page is using `https -> WSS (1884) | http -> WS (1885)`.
* The java backend uses TCP port 1883 by default which is the `MQTT port` in `services -> MQTT Settings`

### Nur Service:
1. Nur service should be running and not connected to any other application, you can check this by going to `services -> NUR service`

# Changelog
### v1.1.0
- The front end can now be used with both http and https, front-end will try to connect to the default  mqtt ports for ws 1885 and wss 1884.