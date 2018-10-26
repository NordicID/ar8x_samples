# C# App sample
This sample shows how you can create a simple WCF RESTful service and consume it in a simple web application. The webservice exposes one method `Ping` which will respond with `Pong` the front end offers a simple button that calls `Ping` and writes the answer on the page.

# Changelog
### v1.1.0
- The front end can now be used with both http and https, front-end will try to connect to the default  mqtt ports for ws 1885 and wss 1884.