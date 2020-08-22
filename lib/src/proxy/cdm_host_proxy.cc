#include "cdm_host_proxy.h"
#include "../common/log.h"

namespace proxy {

    void CdmHostProxy_10::SetUpstreamPtr(void *ptr) {
        ZLOG("Original CDM host => %p", ptr);
        up_ptr = static_cast<CdmHostInterface*>(ptr);
    }

    cdm::Buffer * CdmHostProxy_10::Allocate(uint32_t capacity) {
        ZLOG("capacity=%d", capacity);
        return up_ptr->Allocate(capacity);
    }

    void CdmHostProxy_10::SetTimer(int64_t delay_ms, void *context) {
        ZLOG("delay_ms=%ld, context=%p", delay_ms, context);
        up_ptr->SetTimer(delay_ms, context);
    }

    cdm::Time CdmHostProxy_10::GetCurrentWallTime() {
        auto result = up_ptr->GetCurrentWallTime();
        ZLOG("result => %f", result);
        return result;
    }

    void CdmHostProxy_10::OnInitialized(bool success) {
        ZLOG("success=%d", success);
        up_ptr->OnInitialized(success);
    }

    void CdmHostProxy_10::OnResolveKeyStatusPromise(uint32_t promise_id, cdm::KeyStatus key_status) {
        ZLOG("promise_id=%d, key_status=%d", promise_id, key_status);
        up_ptr->OnResolveKeyStatusPromise(promise_id, key_status);
    }

    void CdmHostProxy_10::OnResolveNewSessionPromise(uint32_t promise_id, const char *session_id,
                                                     uint32_t session_id_size) {
        ZLOG("promise_id=%d, session_id=%s", promise_id, session_id);
        up_ptr->OnResolveNewSessionPromise(promise_id, session_id, session_id_size);
    }

    void CdmHostProxy_10::OnResolvePromise(uint32_t promise_id) {
        ZLOG("promise_id=%d", promise_id);
        up_ptr->OnResolvePromise(promise_id);
    }

    void CdmHostProxy_10::OnRejectPromise(uint32_t promise_id, cdm::Exception exception, uint32_t system_code,
                                          const char *error_message, uint32_t error_message_size) {
        ZLOG("promise_id=%d, exception=%d, system_code=%d, error_message=%s",
             promise_id, exception, system_code, error_message);
        up_ptr->OnRejectPromise(promise_id, exception, system_code, error_message, error_message_size);
    }

    void CdmHostProxy_10::OnSessionMessage(const char *session_id, uint32_t session_id_size,
                                           cdm::MessageType message_type, const char *message, uint32_t message_size) {
        ZLOG("session_id=%s, message_type=%d, message_size=%d", session_id, message_type, message_size);
        up_ptr->OnSessionMessage(session_id, session_id_size, message_type, message, message_size);
    }

    void CdmHostProxy_10::OnSessionKeysChange(const char *session_id, uint32_t session_id_size,
                                              bool has_additional_usable_key, const cdm::KeyInformation *keys_info,
                                              uint32_t keys_info_count) {
        ZLOG("session_id=%s, has_additional_usable_key=%d, keys_info_count=%d",
             session_id, has_additional_usable_key, keys_info_count);
        up_ptr->OnSessionKeysChange(session_id, session_id_size, has_additional_usable_key, keys_info, keys_info_count);
    }

    void CdmHostProxy_10::OnExpirationChange(const char *session_id, uint32_t session_id_size,
                                             cdm::Time new_expiry_time) {
        ZLOG("session_id=%s, new_expiry_time=%f", session_id, new_expiry_time);
        up_ptr->OnExpirationChange(session_id, session_id_size, new_expiry_time);
    }

    void CdmHostProxy_10::OnSessionClosed(const char *session_id, uint32_t session_id_size) {
        ZLOG("session_id=%s", session_id);
        up_ptr->OnSessionClosed(session_id, session_id_size);
    }

    void CdmHostProxy_10::SendPlatformChallenge(const char *service_id, uint32_t service_id_size,
                                                const char *challenge, uint32_t challenge_size) {
        ZLOG("service_id=%s, challenge_size=%d", service_id, challenge_size);
        up_ptr->SendPlatformChallenge(service_id, service_id_size, challenge, challenge_size);
    }

    void CdmHostProxy_10::EnableOutputProtection(uint32_t desired_protection_mask) {
        ZLOG("desired_protection_mask=%d", desired_protection_mask);
        up_ptr->EnableOutputProtection(desired_protection_mask);
    }

    void CdmHostProxy_10::QueryOutputProtectionStatus() {
        ZLOG("");
        up_ptr->QueryOutputProtectionStatus();
    }

    void CdmHostProxy_10::OnDeferredInitializationDone(cdm::StreamType stream_type, cdm::Status decoder_status) {
        ZLOG("stream_type=%d, decoder_status=%d", stream_type, decoder_status);
        up_ptr->OnDeferredInitializationDone(stream_type, decoder_status);
    }

    cdm::FileIO * CdmHostProxy_10::CreateFileIO(cdm::FileIOClient *client) {
        ZLOG("");
        return up_ptr->CreateFileIO(client);
    }

    void CdmHostProxy_10::RequestStorageId(uint32_t version) {
        ZLOG("version=%d", version);
        up_ptr->RequestStorageId(version);
    }

}