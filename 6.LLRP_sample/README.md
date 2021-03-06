# Norma LLRP sample
This application (Norma) provides access to the RFID module through LLRP protocol. The current version provides the mandatory features from the LLRP specifications without custom LLRP commands. for more details on this application and how to use it read [this](../docs/AN007_AR8x_LLRP_Norma.docx).

The `NormaConfig` project depends on the Newtonsoft json library to build, restore the nugget package for the project to build before creating a new package.

# Changelog

### v1.1.1
- Fix SET_READER_CONFIG for antenna IDs over 15
- Restart norma in case of abnormal termination

### v1.1.0
- Write logs to stdout instead of flash
- Update nurapi library

### v1.0.9
- Updated Nurlibrary to latest 

### v1.0.8
- Call the backend with correct protocol https/http

### v1.0.7
- RxSensitivity uses RSSI filter on AR82/AR85/AR62/Sampo S2 if using newer chip. Range is the same as for other chip versions i.e. -70 to -50. Highest sensitivity allowing lower RSSI also.

### v1.0.6
- GetRospecs returns now StatusCode_M_Success also when no ROSpecs available

### v1.0.5
- Removed reporting of all available HopTables since reader is anyway locked to a specific region
- Default reader configuration correctly fills now ROSpec AntennaConfiguration if its only partial(i.e has only RFTransmitter properties but others are absent)

### v1.0.4
- ChannelIndex used from RFTransmitter settings if available
- HoptableIDs changed to match NurApi.Region setting
- ReceiverSensitivity now in DeviceCapabilities, used also from Spec/ReaderConfig when performing Spec
- Added option for reader configuration(in web view) to disable sensors from device i.e. Norma does not list the tap/light sensors from Sampo S1 as one of its GPIOs. 
- GPOPortNumber indexing changed from 5-8 to 1-4. 
- C1G2SingulationControl parameters used properly also when TagInventoryStateAware is 0

### v1.0.3
- AntennaProperties/AntennaConnected now utilized for active ROSpecs => if AISpec antennaID(s) == 0 and new antennas connected/disconnected(AntennaConnected state changed via SET_READER_CONFIG) => internal antenna array updated for running ROSpecs

### v1.0.2
- AISpec AntennaID 0 now utilizing all enabled antennas(check AntennaProperties "connected"-state)
- Add_ROSpec now replaces correctly the previous entry
- KeepAliveSpec now closes the connection if periodic keepalive is used and missed ACKs > 5
- Connection overriding now allowed from "previous" client i.e. same client can reconnect if connection dropped due to network loss or similar. Peridioc keep alive recommended even with this.

### v1.0.1
- Fixes issue where AISpec AntennaID 0 did not use all antennas defined in AntennaProperties which had AntennaConnected set to 1
