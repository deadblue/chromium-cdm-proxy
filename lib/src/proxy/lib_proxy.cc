#include "lib_proxy.h"

#include <dlfcn.h>
#include <cstdio>

namespace proxy {

    void* GetCdmHostProxy(int version, void* user_data) {
        ZLOG("version=%d", version);

        // Call original GetCdmHostFunc
        auto data = static_cast<CmdHostProxyData *>(user_data);
        auto ptr = data->up_get_host_func(version, data->up_user_data);
        // Store original host
        data->host_proxy->SetUpstreamPtr(ptr);
        return data->host_proxy;
    }

    std::shared_ptr<LibProxy> LibProxy::Hijack(const char *lib_path) {
        std::shared_ptr<LibProxy> ptr;

        ZLOG("Loading CDM lib: %s", lib_path);
        auto hdl = dlopen(lib_path, RTLD_LAZY);
        if(hdl != nullptr) {
            auto f1 = (VoidFunc) dlsym(hdl, "InitializeCdmModule_4");
            auto f2 = (VoidFunc) dlsym(hdl, "DeinitializeCdmModule");
            auto f3 = (CreateInstanceFunc) dlsym(hdl, "CreateCdmInstance");
            auto f4 = (GetVersionFunc) dlsym(hdl, "GetCdmVersion");
            if(f1 == nullptr || f2 == nullptr || f3 == nullptr || f4 == nullptr) {
                ZLOG("Get upstream API function error: %s", dlerror());
            } else {
                ZLOG("Upsteam InitializeCdmModule_4 => %p", f1);
                ZLOG("Upsteam DeinitializeCdmModule => %p", f2);
                ZLOG("Upsteam CreateCdmInstance => %p", f3);
                ZLOG("Upsteam GetCdmVersion => %p", f4);
                ptr.reset(new LibProxy(hdl, f1, f2, f3, f4));
            }
        } else {
            ZLOG("Load upstream lib error: %s", dlerror());
        }
        return ptr;
    }

    void LibProxy::InitializeCmdModule() {
        ZLOG("");
        this->func_init();
    }
    void LibProxy::DeinitializeCmdModule() {
        ZLOG("");
        this->func_deinit();
    }

    void* LibProxy::CreateCdmInstance(int interface_version,
                                      const char* key_system, uint32_t key_system_size,
                                      GetCdmHostFunc get_cdm_host_func, void* user_data) {
        ZLOG("interface_version=%d, key_system=%s", interface_version, key_system);
        CmdHostProxyData proxy_data = {
                .up_get_host_func = get_cdm_host_func,
                .up_user_data = user_data,
                .host_proxy = cmd_host_proxy.get()
        };
        auto ptr = this->func_create_inst(interface_version,
                                          key_system, key_system_size,
                                          // Hijack CDM host
                                          GetCdmHostProxy, &proxy_data);
        // Hijack CDM instance
        cdm_proxy = std::make_shared<CdmProxy_10>(ptr);
        return cdm_proxy.get();
    }

    const char* LibProxy::GetCdmVersion() {
        auto version = this->func_get_ver();
        ZLOG("result => %s", version);
        return version;
    }

    LibProxy::~LibProxy() {
        if (hdl != nullptr) {
            dlclose(hdl);
        }
    }

} // namespace proxy
