#include "lib.h"

#include <iostream>
#include <cstring>

void on_init() {
    ZLOG("Proxy initializing ...");
    char* lib_path = getenv(lib::ENV_CDM_LIB);
    if(lib_path == nullptr || strlen(lib_path) == 0) {
        ZLOG("Please set environment variable: %s", lib::ENV_CDM_LIB);
    } else {
        lib::proxy_ptr = proxy::LibProxy::Hijack(lib_path);
    }
}

void on_fini() {
    ZLOG("Proxy finalizing ...");
    // Release proxy instance
    if(lib::proxy_ptr) {
        lib::proxy_ptr.reset();
    }
}

void INITIALIZE_CDM_MODULE() {
    if(lib::proxy_ptr) {
        lib::proxy_ptr->InitializeCmdModule();
    }
}

void DeinitializeCdmModule() {
    if(lib::proxy_ptr) {
        lib::proxy_ptr->DeinitializeCmdModule();
    }
}

void* CreateCdmInstance(int cdm_interface_version,
                        const char* key_system,
                        uint32_t key_system_size,
                        GetCdmHostFunc get_cdm_host_func,
                        void* user_data) {
    if(lib::proxy_ptr) {
        return lib::proxy_ptr->CreateCdmInstance(
                cdm_interface_version, key_system, key_system_size,
                get_cdm_host_func, user_data );
    } else {
        return nullptr;
    }
}

const char* GetCdmVersion() {
    if(lib::proxy_ptr) {
        return lib::proxy_ptr->GetCdmVersion();;
    } else {
        return "";
    }
}

bool VerifyCdmHost_0(const cdm::HostFile* host_files,
                     uint32_t num_files) {
    return true;
}
