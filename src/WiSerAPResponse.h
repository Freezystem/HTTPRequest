#ifndef WISERAPRESPONSE_h
#define WISERAPRESPONSE_h

#include <Arduino.h>
#include <WiFi101.h>

#include "WiSerHelpers.h"

class WiSerAPResponse {
  public:
    WiSerAPResponse(WiFiClient& client) : _client(client) {
      _protocol = "HTTP/1.1";
      _status = HttpCode::OK;
      _content = "";
      _headers = "";
    };
    WiSerAPResponse& setStatus(HttpCode code);
    WiSerAPResponse& setHeader(String key, String value);
    WiSerAPResponse& setContent(String content);
    void send();
    
  private:
    WiFiClient& _client;
    String _headers;
    String _protocol;
    HttpCode _status;
    String _statusString;
    String _content;
};

#endif
