#include "Arduino.h"
#include "WiSerResponse.h"

// public

WiSerResponse& WiSerResponse::setStatus(HttpCode code) {
  _status = code;
  return *this;
}

WiSerResponse& WiSerResponse::setHeader(String key, String value) {
  _headers += String( key + ":" + value + "\n");
  return *this;
}

WiSerResponse& WiSerResponse::setContent(String content) {
  _content += content;
  return *this;
}

void WiSerResponse::send() {
  String res = _protocol + " " + WiSerHelper::statusToCodeString(_status) + " " + WiSerHelper::statusToString(_status) + "\n" + _headers + "\n" + _content;
  _client.print(res);
}
