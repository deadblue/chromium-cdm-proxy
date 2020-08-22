#include <iostream>
#include <dlfcn.h>

#include "log.h"

typedef char *(* get_ver_func)();

int main(int argc, char * argv[]) {
    if(argc <= 1) {
        std::cout << "Usage: "
            << argv[0] << " <proxy-so-file>" << std::endl;
        return 0;
    }

    ZLOG("Loading proxy lib: %s ...", argv[1]);
    auto hdr = dlopen(argv[1], RTLD_LAZY);
    if(hdr == nullptr) {
        ZLOG("Load error: %s", dlerror());
    } else {
        // Call function on proxy
        auto func = (get_ver_func)dlsym(hdr, "GetCdmVersion");
        auto version = func();
        ZLOG("GetCdmVersion: %s", version);

        ZLOG("Unloading proxy ...");
        dlclose(hdr);
    }
    return 0;
}
