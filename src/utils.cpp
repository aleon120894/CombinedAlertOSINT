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
    auto* mem = (MemoryStruct*)userp;
    char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);

    if (ptr == NULL) {
        // out of memory!
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    std::memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}
