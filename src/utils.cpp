#include "utils.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>


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
            // Handle allocation failure (e.g., print error)
            return 0;
        }
    } else {
        char* ptr = static_cast<char*>(realloc(mem->memory, mem->size + realsize + 1));
        if (ptr == nullptr) {
            // Handle reallocation failure (e.g., print error)
            return 0;
        }
        mem->memory = ptr;
    }

    memcpy(mem->memory + mem->size, contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = '\0';  // Ensure null termination

    return realsize;
}
