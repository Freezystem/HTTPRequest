#include "WiSerHelpers.h"

const String statuses[40] = {"100","101","200","201","202","203","204","205","206","300","301","302","303","304","305","307","400","401","402","403","404","405","406","407","408","409","410","411","412","413","414","415","416","417","500","501","502","503","504","505"};
const String methods[8] = {"OPTIONS", "GET", "HEAD", "POST", "PUT", "DELETE", "TRACE", "CONNECT"};

String WiSerHelpers::statusToString(HttpCode code){
  String statuses[40] = {
    "Continue",
    "Switching Protocols",
    "OK",
    "Created",
    "Accepted",
    "Non-Authoritative Information",
    "No Content",
    "Reset Content",
    "Partial Content",
    "Multiple Choices",
    "Moved Permanently",
    "Found",
    "See Other",
    "Not Modified",
    "Use Proxy",
    "Temporary Redirect",
    "Bad Request",
    "Unauthorized",
    "Payment Required",
    "Forbidden",
    "Not Found",
    "Method Not Allowed",
    "Not Acceptable",
    "Proxy Authentication Required",
    "Request Time-out",
    "Conflict",
    "Gone",
    "Length Required",
    "Precondition Failed",
    "Request Entity Too Large",
    "Request-URI Too Large",
    "Unsupported Media Type",
    "Requested range not satisfiable",
    "Expectation Failed",
    "Internal Server Error",
    "Not Implemented",
    "Bad Gateway",
    "Service Unavailable",
    "Gateway Time-out",
    "HTTP Version not supported"
  };
  return statuses[(int)code];
}

String WiSerHelpers::statusToCodeString(HttpCode code){
  return statuses[(int)code];
}

String WiSerHelpers::methodToString(HttpMethod method){
  return methods[(int)method];
}

HttpCode WiSerHelpers::codeStringToStatus(String code){
  int i = 40;
  bool searching = true;
  
  while(i > 0 && searching){
    searching = statuses[--i] != code;
  }
  
  return (HttpCode)i;
}

HttpMethod WiSerHelpers::stringToMethod(String method){
  int i = 8;
  bool searching = true;
  
  while(i > 0 && searching){
    searching = methods[--i] != method;
  }
  
  return (HttpMethod)i;
}
