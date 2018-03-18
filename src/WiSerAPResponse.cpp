#include "Arduino.h"
#include "WiSerAPResponse.h"

// public

WiSerAPResponse& WiSerAPResponse::setStatus(HttpCode code) {
  _status = code;
  return *this;
}

WiSerAPResponse& WiSerAPResponse::setHeader(String key, String value) {
  _headers += String( key + ": " + value + "\n");
  return *this;
}

WiSerAPResponse& WiSerAPResponse::setContent(String content) {
  _content += content;
  return *this;
}

void WiSerAPResponse::send() {
  String res = _protocol + " " + WiSerHelpers::statusToCodeString(_status) + " " + WiSerHelpers::statusToString(_status) + "\n" + _headers + "\n" + _content;
  _client.print(res);
}
