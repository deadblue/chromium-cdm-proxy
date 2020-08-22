#ifndef CDM_PROXY_CDM_HOST_WRAPPER_H
#define CDM_PROXY_CDM_HOST_WRAPPER_H

#include "../api/content_decryption_module.h"
#include "cdm_host_proxy.h"

namespace proxy {

    struct CmdHostProxyData {
        GetCdmHostFunc up_get_host_func;
        void* up_user_data;
        CdmHostProxy_10* host_proxy;
    };

}

#endif //CDM_PROXY_CDM_HOST_WRAPPER_H
