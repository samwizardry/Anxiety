#pragma once

#include <iostream>

#define ANX_TRACE(message) ::std::cout << "[TRACE]: " << message;
#define ANX_DEBUG(message) ::std::cout << "[DEBUG]: " << message;
#define ANX_INFO(message) ::std::cout << "[INFO]: " << message;
#define ANX_WARN(message) ::std::cout << "[WARNING]: " << message;
#define ANX_ERROR(message) ::std::cout << "[ERROR]: " << message;
#define ANX_FATAL(message) ::std::cout << "[FATAL]: " << message;
