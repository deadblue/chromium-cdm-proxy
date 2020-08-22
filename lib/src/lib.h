#ifndef CDM_PROXY_LIB_H
#define CDM_PROXY_LIB_H

#include <memory>

#include "api/content_decryption_module.h"
#include "api/content_decryption_module_ext.h"
#include "common/log.h"
#include "proxy/lib_proxy.h"

#define INIT __attribute__((constructor))
#define FINI __attribute__((destructor))

INIT void on_init();

FINI void on_fini();

namespace lib {

    const char* ENV_CDM_LIB = "Z_CDM_LIB";

    std::shared_ptr<proxy::LibProxy> proxy_ptr;

} // namespace lib

#endif //CDM_PROXY_LIB_H
