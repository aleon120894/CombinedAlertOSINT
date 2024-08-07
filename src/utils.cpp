#include "utils.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stdexcept> // For std::runtime_error

struct MemoryStruct {
    char* memory;
    size_t size;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    
    size_t realsize = size * nmemb;
    MemoryStruct* mem = static_cast<MemoryStruct*>(userp);

    // Ensure sufficient memory
    if (mem->memory == nullptr) {
        mem->memory = static_cast<char*>(malloc(realsize + 1));
        if (mem->memory == nullptr) {
            throw std::runtime_error("Failed to allocate memory in WriteCallback");
        }
    } else {
        char* ptr = static_cast<char*>(realloc(mem->memory, mem->size + realsize + 1));
        if (ptr == nullptr) {
            throw std::runtime_error("Failed to reallocate memory in WriteCallback");
        }
        mem->memory = ptr;
    }

    memcpy(mem->memory + mem->size, contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = '\0';  // Ensure null termination

    return realsize;
}
