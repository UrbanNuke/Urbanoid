#pragma once
#include <string>
#include <string_view>
#include <Windows.h>

/*
 * This class was taken from https://mklimenko.github.io/english/2018/06/23/embed-resources-msvc/
 * It's aiming to embed resource into executable
 */

class Resource {
public:
    struct Parameters {
        std::size_t size_bytes = 0;
        void* ptr = nullptr;
    };

private:
    HRSRC hResource = nullptr;
    HGLOBAL hMemory = nullptr;

    Parameters p;

public:
    Resource(int resource_id, const std::string& resource_class);

    std::string_view GetResourceString() const;
};
