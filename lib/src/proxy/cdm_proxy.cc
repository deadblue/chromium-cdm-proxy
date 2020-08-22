#include "cdm_proxy.h"

namespace proxy {

    CdmProxy_10::CdmProxy_10(void* ptr) {
        this->up_ptr =static_cast<CdmInterface*>(ptr);
    }

    void CdmProxy_10::Initialize(bool allow_distinctive_identifier,
                                 bool allow_persistent_state, bool use_hw_secure_codecs) {
        ZLOG("allow_distinctive_identifier=%d, allow_persistent_state=%d, use_hw_secure_codecs=%d",
             allow_distinctive_identifier, allow_persistent_state, use_hw_secure_codecs);
        up_ptr->Initialize(allow_distinctive_identifier, allow_persistent_state, use_hw_secure_codecs);
    }

    void CdmProxy_10::GetStatusForPolicy(uint32_t promise_id, const cdm::Policy &policy) {
        ZLOG("promise_id=%d", promise_id);
        up_ptr->GetStatusForPolicy(promise_id, policy);
    }

    void CdmProxy_10::SetServerCertificate(uint32_t promise_id, const uint8_t *server_certificate_data,
                                           uint32_t server_certificate_data_size) {
        ZLOG("promise_id=%d, server_certificate_data_size=%d", promise_id, server_certificate_data_size);
        up_ptr->SetServerCertificate(promise_id,
                                     server_certificate_data, server_certificate_data_size);
    }

    void CdmProxy_10::CreateSessionAndGenerateRequest(uint32_t promise_id, cdm::SessionType session_type,
                                                      cdm::InitDataType init_data_type, const uint8_t *init_data,
                                                      uint32_t init_data_size) {
        ZLOG("promise_id=%d, session_tpye=%d, init_data_type=%d, init_data_size=%d",
             promise_id, session_type, init_data_type, init_data_size);
        up_ptr->CreateSessionAndGenerateRequest(promise_id, session_type,
                                                init_data_type, init_data, init_data_size);
    }

    void CdmProxy_10::LoadSession(uint32_t promise_id, cdm::SessionType session_type, const char *session_id,
                                  uint32_t session_id_size) {
        ZLOG("promise_id=%d, session_tpye=%d, session_id=%s", promise_id, session_type, session_id);
        up_ptr->LoadSession(promise_id, session_type, session_id, session_id_size);
    }

    void CdmProxy_10::UpdateSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size,
                                    const uint8_t *response, uint32_t response_size) {
        ZLOG("promise_id=%d, session_id=%s, response_size=%d", promise_id, session_id, response_size);
        up_ptr->UpdateSession(promise_id, session_id, session_id_size,
                              response, response_size);
    }

    void CdmProxy_10::CloseSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size) {
        ZLOG("promise_id=%d, session_id=%s", promise_id, session_id);
        up_ptr->CloseSession(promise_id, session_id, session_id_size);
    }

    void CdmProxy_10::RemoveSession(uint32_t promise_id, const char *session_id, uint32_t session_id_size) {
        ZLOG("promise_id=%d, session_id=%s", promise_id, session_id);
        up_ptr->RemoveSession(promise_id, session_id, session_id_size);
    }

    void CdmProxy_10::TimerExpired(void *context) {
        ZLOG("context=%p", context);
        up_ptr->TimerExpired(context);
    }

    cdm::Status CdmProxy_10::Decrypt(const cdm::InputBuffer_2 &encrypted_buffer,
                                     cdm::DecryptedBlock *decrypted_buffer) {
        auto result = up_ptr->Decrypt(encrypted_buffer, decrypted_buffer);
        ZLOG("result => %d", result);
        return result;
    }

    cdm::Status CdmProxy_10::InitializeAudioDecoder(const cdm::AudioDecoderConfig_2 &audio_decoder_config) {
        auto result = up_ptr->InitializeAudioDecoder(audio_decoder_config);
        ZLOG("result => %d", result);
        return result;
    }

    cdm::Status CdmProxy_10::InitializeVideoDecoder(const cdm::VideoDecoderConfig_2 &video_decoder_config) {
        auto result = up_ptr->InitializeVideoDecoder(video_decoder_config);
        ZLOG("result => %d", result);
        return result;
    }

    void CdmProxy_10::DeinitializeDecoder(cdm::StreamType decoder_type) {
        ZLOG("decoder_type=%d", decoder_type);
        up_ptr->DeinitializeDecoder(decoder_type);
    }

    void CdmProxy_10::ResetDecoder(cdm::StreamType decoder_type) {
        ZLOG("decoder_type=%d", decoder_type);
        up_ptr->ResetDecoder(decoder_type);
    }

    cdm::Status CdmProxy_10::DecryptAndDecodeFrame(const cdm::InputBuffer_2 &encrypted_buffer,
                                                   cdm::VideoFrame *video_frame) {
        auto result = up_ptr->DecryptAndDecodeFrame(encrypted_buffer, video_frame);
        ZLOG("result => %d", result);
        return result;
    }

    cdm::Status CdmProxy_10::DecryptAndDecodeSamples(const cdm::InputBuffer_2 &encrypted_buffer,
                                                     cdm::AudioFrames *audio_frames) {
        auto result = up_ptr->DecryptAndDecodeSamples(encrypted_buffer, audio_frames);
        ZLOG("result => %d", result);
        return result;
    }

    void CdmProxy_10::OnPlatformChallengeResponse(const cdm::PlatformChallengeResponse &response) {
        ZLOG("");
        up_ptr->OnPlatformChallengeResponse(response);
    }

    void CdmProxy_10::OnQueryOutputProtectionStatus(cdm::QueryResult result, uint32_t link_mask,
                                                    uint32_t output_protection_mask) {
        ZLOG("result=%d", result);
        up_ptr->OnQueryOutputProtectionStatus(result, link_mask, output_protection_mask);
    }

    void CdmProxy_10::OnStorageId(uint32_t version, const uint8_t *storage_id, uint32_t storage_id_size) {
        ZLOG("version=%d, storage_id_size=%d", version, storage_id_size);
        up_ptr->OnStorageId(version, storage_id, storage_id_size);
    }

    void CdmProxy_10::Destroy() {
        ZLOG("");
        up_ptr->Destroy();
    }

} // namespace proxy