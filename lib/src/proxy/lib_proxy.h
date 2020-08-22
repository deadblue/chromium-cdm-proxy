#ifndef CDM_PROXY_LIB_PROXY_H
#define CDM_PROXY_LIB_PROXY_H

#include <memory>
#include <cstdint>

#include "../common/log.h"
#include "../api/content_decryption_module.h"
#include "cdm_proxy.h"
#include "cdm_host_proxy_data.h"
#include "cdm_host_proxy.h"

namespace proxy {

    void* GetCdmHostProxy(int version, void* user_data);

    typedef void (* VoidFunc)();
    typedef void* (* CreateInstanceFunc)(int, const char*, uint32_t, GetCdmHostFunc, void*);
    typedef char* (* GetVersionFunc)();

    // Proxy for libwidevinecdm APIs
    class LibProxy {

    public:
        static std::shared_ptr<LibProxy> Hijack(const char* lib_path);

        void InitializeCmdModule();
        void DeinitializeCmdModule();
        void* CreateCdmInstance(int interface_version,
                                const char* key_system, uint32_t key_system_size,
                                GetCdmHostFunc get_cdm_host_func, void* user_data);
        const char* GetCdmVersion();

        ~LibProxy();

    private:
        LibProxy(void* hdl,
                 VoidFunc func_init,
                 VoidFunc func_deinit,
                 CreateInstanceFunc func_create_inst,
                 GetVersionFunc func_get_ver) {
            this->hdl = hdl;
            this->func_init = func_init;
            this->func_deinit = func_deinit;
            this->func_create_inst = func_create_inst;
            this->func_get_ver = func_get_ver;

            this->cmd_host_proxy = std::make_shared<CdmHostProxy_10>();
        }

    private:
        // Upstream lib
        void* hdl;
        VoidFunc func_init;
        VoidFunc func_deinit;
        CreateInstanceFunc func_create_inst;
        GetVersionFunc func_get_ver;

        // Proxies
        std::shared_ptr<CdmProxy_10> cdm_proxy;
        std::shared_ptr<CdmHostProxy_10> cmd_host_proxy;

    };
}

#endif //CDM_PROXY_LIB_PROXY_H
