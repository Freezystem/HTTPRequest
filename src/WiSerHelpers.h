#ifndef WISERHELPERS_h
#define WISERHELPERS_h

#ifndef WISER_DEBUG
#define WISER_DEBUG false
#endif

#include <Arduino.h>

enum class HttpMethod : unsigned int {
  OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
};

enum class HttpCode : unsigned int {
  // Informational
  CONTINUE,
  SWITCHING_PROTOCOLS,
  // Success
  OK,
  CREATED,
  ACCEPTED,
  NON_AUTHORITATIVE_INFORMATION,
  NO_CONTENT,
  RESET_CONTENT,
  PARTIAL_CONTENT,
  // Redirection
  MULTIPLE_CHOICES,
  MOVED_PERMANENTLY,
  FOUND,
  SEE_OTHER,
  NOT_MODIFIED,
  USE_PROXY,
  TEMPORARY_REDIRECT,
  // Client Error
  BAD_REQUEST,
  UNAUTHORIZED,
  PAYMENT_REQUIRED,
  FORBIDDEN,
  NOT_FOUND,
  METHOD_NOT_ALLOWED,
  NOT_ACCEPTABLE,
  PROXY_AUTHENTICATION_REQUIRED,
  REQUEST_TIME_OUT,
  CONFLICT,
  GONE,
  LENGTH_REQUIRED,
  PRECONDITION_FAILED,
  REQUEST_ENTITY_TOO_LARGE,
  REQUEST_URI_TOO_LARGE,
  UNSUPPORTED_MEDIA_TYPE,
  REQUESTED_RANGE_NOT_SATISFIABLE,
  EXPECTATION_FAILED,
  // Server Error
  INTERNAL_SERVER_ERROR,
  NOT_IMPLEMENTED,
  BAD_GATEWAY,
  SERVICE_UNAVAILABLE,
  GATEWAY_TIMED_OUT,
  HTTP_VERSION_NOT_SUPPORTED
};

class WiSerHelpers {
  public:
  static String statusToString(HttpCode code);
  static String statusToCodeString(HttpCode code);
  static String methodToString(HttpMethod method);
  static HttpCode codeStringToStatus(String code);
  static HttpMethod stringToMethod(String method);
};

#endif
