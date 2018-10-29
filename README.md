# ar8x_samples

This repository contains the samples and demo applications for NordicID's smart readers. Each sample contains the necessary scripts to build it and package it for installation and a pre-packaged signed zip ready to install on your device.
Should you ever need to modify a sample to test or make things work your way, you can find the necessary files for the application package in `zipcontents` more details about the contents of that folder in the [documentation](docs/AN002_AR8x_appinterface.docx). in case the application has binaries that need to be compiled you can find the source code in a `src` folder e.g **nurapisample_src**. each of these will contain scripts or make files to build the binaries.

use the `make` script to compile any necessary binaries and package the application files, this will generate a signed zip file in the sample folder.

## Sample applications

[C# WCF webservice sample](1.CS_WCF_sample)

[Java MQTT sample](2.Java_MQTT_sample)

[Netdata device monitoring app](3.Netdata_package)

[Node.js sample](4.Node.JS_sample)

[C# Nurapi sample](5.CS_Nurapi_sample)

[Nurapi LLRP demo](6.LLRP_sample)

## Documentation

Find all the NordicID smart readers documentation [here](docs), documents in that folder go through different aspects of the smart readers

### [AN001_AR8x_Getting started](docs/AN001_AR8x_Getting started)

Your first glance over the smart reader dashboard, details on each view what it can do and what to expect. This is bound to change as the development is ongoing new features will be added or changed along the way.

### [AN002_AR8x_appinterface.docx](docs/AN002_AR8x_appinterface.docx)

An overview on the smart reader application api and packages, how to create your own application package and what it should contain.

### [AN003_AR8x_webservice.docx](docs/AN003_AR8x_webservice.docx)

A guide on how to use the reader API offering all the necessary means to control, monitor and configure your device. also shows how to use the Swagger doc provided to generate client for any environment.

### [AN004_AR8x_RemoteDebug_C_C++.docx](docs/AN004_AR8x_RemoteDebug_C_C++.docx)

Provides details about remotely debugging your C or C++ applications running on the smart reader.

### [AN005_AR8x_RemoteDebug_Python.docx](docs/AN005_AR8x_RemoteDebug_Python.docx)

Provides details about remotely debugging your Python application running on the smart reader.

### [AN006_AR8x_NurSvc.docx](docs/AN006_AR8x_NurSvc.docx)

Documents the purpose and use of NUR service running on the smart reader which handles the RFID operations of the device.

### [AN007_AR8x_LLRP_Norma.docx](docs/AN007_AR8x_LLRP_Norma.docx)

more details about the [Nurapi LLRP demo](6.LLRP_sample); how to install, run and configure.

## License
All source files in this repository is provided under terms specified in [LICENSE](LICENSE) file.