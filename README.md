# Basic HTTP Server for WiFi101 Library

The main goal of this library is to create a simple way to handle HTTP1.1 requests between an Arduino and a device or server.  
As the Arduino can be the client or the server it should be able de handle requesting dialog both ways, so the library will be devided in two major parts.

## Disclaimer

This library is still under **heavy development** and **does not fit for production** use.  
A lot of **breaking changes** may occur until this library hits the `v1` stable release.

> Until this time none or few documentation will be written.

## Arduino as a Server (Access Point)

In this case the Arduino is the server that receive and dispatch requests to a unique device connected to it.
This mode can be used to get or set board configuration like sensors or WiFi.

### Access Point request handler

The `WiSerAPRequest` class allows the handling of requests sent to your Arduino from the client.

### Access Point response handler

The `WiSerAPResponse` class allows the dispatch of responses from the Arduino to the client.

## Arduino as a Client

In this case the Arduino is the client connected to internet through the WiFi that send and receive requests to one or more specific endpoints.

### Client request handler

The `WiSerCRequest` class allows the dispatch of message to specific endpoints.

### Client response handler

The `WiSerCResponse` class allows the handling of responses from endpoints the Arduino is sending request to.

## Helpers

The `WiSerHelpers` class provides a set of static functions to help code simplification and readability.

## Roadmap to v1 :
To acknowledge all the features and changes planned before the release of v1 see [here](https://github.com/Freezystem/WiSer/projects/1)