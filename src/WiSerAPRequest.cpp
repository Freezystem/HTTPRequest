#include "WiSerAPRequest.h"

// private

void WiSerAPRequest::parseRequest(String request){
  int routeIdx = request.indexOf(" ");
  int protocolIdx = request.indexOf(" ", routeIdx + 1);
  
  _method = WiSerHelpers::stringToMethod(request.substring(0, routeIdx));
  _route = request.substring(routeIdx + 1, protocolIdx);

  int queryIdx = _route.indexOf("?");
  
  if (queryIdx){
    _params = _route.substring(queryIdx + 1);
    _route = _route.substring(0, queryIdx);
  }
  
  _protocol = request.substring(protocolIdx + 1);
}

String WiSerAPRequest::getValueFromString(String data, String key, String startDelimiter, String endDelimiter, bool caseSensitive){
  String dataSensitive = data;
  if (!caseSensitive) { 
    dataSensitive.toLowerCase();
    key.toLowerCase();
    startDelimiter.toLowerCase();
    endDelimiter.toLowerCase();
  }
  
  int keyIndex = dataSensitive.indexOf(key);
  if (keyIndex == -1) {
    return "";
  }
  
  int startIndex = data.indexOf(startDelimiter, keyIndex);
  int endIndex = data.indexOf(endDelimiter, keyIndex);

  return data.substring(startIndex + startDelimiter.length(), endIndex);
}

int WiSerAPRequest::getContentLength(String headers) {
  String contentLength = getValueFromString(headers, "content-length", ": ", "\n", false);
  return contentLength == "" ? 0 : contentLength.toInt();
}

// public

void WiSerAPRequest::catchRequest(RequestCallback& func) {
  String currentLine = "";
  int lineNumber = 0;
  char previousChar;
  bool pendingRequest = true;
  int contentLength = 0;

  while (_client.connected() && pendingRequest) {
    if (_client.available()) {
      char currentChar = _client.read();

      if(WISER_DEBUG){Serial.print(currentChar);}
      
      if (currentChar != '\r'){
        currentLine += currentChar;
        
        if (_request == "" && currentChar == '\n') {
          if (currentLine.endsWith("HTTP/1.1\n")){
            _request = currentLine;
            parseRequest(_request);
            
            currentLine = "";
          }
          else {
            pendingRequest = false;
            _code = HttpCode::HTTP_VERSION_NOT_SUPPORTED;
            func(*this);
          }
        }
        else if (_headers == "" && currentChar == '\n' && previousChar == '\n') {
          _headers = currentLine;
          contentLength = getContentLength(_headers);

          if(!contentLength){
            _code = HttpCode::OK;
            func(*this);
            pendingRequest = false;
          }
          
          currentLine = "";
        }
        else if (_headers != "" && currentLine.length() == contentLength) {
          _form = currentLine;
          _code = HttpCode::OK;

          func(*this);
          
          pendingRequest = false;
          currentLine = "";
        }

        previousChar = currentChar;
      }
    }
  }
}

WiFiClient& WiSerAPRequest::getClient(){
  return _client;
}

String WiSerAPRequest::getHeader(String key){
  return getValueFromString(_headers, key, ": ", "\n", false);
}

String WiSerAPRequest::getQueryParam(String key){
  return getValueFromString(_params, key, "=", "&");
}

String WiSerAPRequest::getFormData(String key){
  return getValueFromString(_form, key, "=", "&");
}

HttpMethod WiSerAPRequest::getMethod(){
  return _method;
}

String WiSerAPRequest::getRoute(){
  return _route;
}

String WiSerAPRequest::getProtocol(){
  return _protocol;
}

String WiSerAPRequest::getHeaders(){
  return _headers;
}

String WiSerAPRequest::getQueryParams(){
  return _params;
}

String WiSerAPRequest::getForm(){
  return _form;
}

HttpCode WiSerAPRequest::getCode(){
  return _code;
}
