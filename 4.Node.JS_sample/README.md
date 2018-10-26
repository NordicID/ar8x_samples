# Netdata package
This sample demonstrates how you can create a Node.js application. The back end node app located in `bin/server.js` listens to port **10126** waiting for an Inventory or single tag read command, executes it and sends it back to the front end. the back end relies on the provided nurcon executable to perform the RFID operations, the source code for that can be found in `nurcon_src` with needed makefiles. 

# Changelog
## v1.1.0
- Update the front end to use the correct protocol while querying the nodejs app.