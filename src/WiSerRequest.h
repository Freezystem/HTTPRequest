#ifndef HTTPREQUEST_h
#define HTTPREQUEST_h

#include <Arduino.h>
#include <WiFi101.h>

#include "WiSerHelper.h"

class WiSerRequest {
  typedef void (RequestCallback)(WiSerRequest& request);
  
  public:
    WiSerRequest(WiFiClient& client) : _client(client) {
      _request = "";
      _headers = "";
      _route = "";
      _protocol = "";
      _params = "";
      _form = "";
    };
    void catchRequest(RequestCallback& func);
    void printRequest();
    WiFiClient& getClient();
    String getHeader(String key);
    String getQueryParam(String key);
    String getFormData(String key);
    HttpMethod getMethod();
    String getRoute();
    String getProtocol();
    String getHeaders();
    String getQueryParams();
    String getForm();
    HttpCode getCode();
    
  private:
    WiFiClient& _client;
    String _request;
    String _headers;
    String _payload;
    HttpMethod _method;
    String _route;
    String _protocol;
    String _params;
    String _form;
    HttpCode _code;

    void parseRequest(String request);
    String getValueFromString(String data, String key, String startDelimiter, String endDelimiter, bool caseSensitive = true);
    int getContentLength(String headers);
};

#endif
