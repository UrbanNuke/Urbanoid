#pragma once
#include <string>

unsigned int compileShader(unsigned int type, const std::string& source);

int createShader(const std::string& vertexShader, const std::string& fragmentShader);
