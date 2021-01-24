#pragma once
#include <iostream>
#define LOG(x) std::cout << x << std::endl
#define LOGINFO(x) std::cout << "INFO: " << x << std::endl
#define LOGWARN(x) std::cout << "WARNING: " << x << std::endl
#define LOGERR(x) std::cerr << "ERROR: " << x << std::endl
#define NEWLINE() std::cout << std::endl