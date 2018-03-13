#ifndef WISERRESPONSE_h
#define WISERRESPONSE_h

#include <Arduino.h>
#include <WiFi101.h>

#include "WiSerHelper.h"

class WiSerResponse {
  public:
    WiSerResponse(WiFiClient& client) : _client(client) {
      _protocol = "HTTP/1.1";
      _status = HttpCode::OK;
      _content = "";
      _headers = "";
    };
    WiSerResponse& setStatus(HttpCode code);
    WiSerResponse& setHeader(String key, String value);
    WiSerResponse& setContent(String content);
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
