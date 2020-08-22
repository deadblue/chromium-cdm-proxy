#ifndef CDM_PROXY_CMDPROXY_H
#define CDM_PROXY_CMDPROXY_H

#include <memory>
#include "../api/content_decryption_module.h"
#include "../common/log.h"

namespace proxy {

    // Proxy for CDM module.
    class CdmProxy_10 : public cdm::ContentDecryptionModule_10 {

        using CdmInterface = cdm::ContentDecryptionModule_10;

    public:
        explicit CdmProxy_10(void* ptr);
        ~CdmProxy_10() override =default;

        // ContentDecryptModule implementations
        void Initialize(
                bool allow_distinctive_identifier, bool allow_persistent_state,
                bool use_hw_secure_codecs) override;
        void GetStatusForPolicy(
                uint32_t promise_id, const cdm::Policy& policy) override;
        void SetServerCertificate(
                uint32_t promise_id, const uint8_t* server_certificate_data,
                uint32_t server_certificate_data_size) override;
        void CreateSessionAndGenerateRequest(
                uint32_t promise_id, cdm::SessionType session_type,
                cdm::InitDataType init_data_type,
                const uint8_t* init_data, uint32_t init_data_size) override;
        void LoadSession(
                uint32_t promise_id, cdm::SessionType session_type,
                const char* session_id, uint32_t session_id_size) override;
        void UpdateSession(
                uint32_t promise_id, const char* session_id, uint32_t session_id_size,
                const uint8_t* response, uint32_t response_size) override;
        void CloseSession(
                uint32_t promise_id, const char* session_id, uint32_t session_id_size) override;
        void RemoveSession(
                uint32_t promise_id, const char* session_id, uint32_t session_id_size) override;
        void TimerExpired(void* context) override;
        cdm::Status Decrypt(
                const cdm::InputBuffer_2& encrypted_buffer, cdm::DecryptedBlock* decrypted_buffer) override;
        cdm::Status InitializeAudioDecoder(
                const cdm::AudioDecoderConfig_2& audio_decoder_config) override;
        cdm::Status InitializeVideoDecoder(
                const cdm::VideoDecoderConfig_2& video_decoder_config) override;
        void DeinitializeDecoder(cdm::StreamType decoder_type) override;
        void ResetDecoder(cdm::StreamType decoder_type) override;
        cdm::Status DecryptAndDecodeFrame(
                const cdm::InputBuffer_2& encrypted_buffer, cdm::VideoFrame* video_frame) override;
        cdm::Status DecryptAndDecodeSamples(
                const cdm::InputBuffer_2& encrypted_buffer, cdm::AudioFrames* audio_frames) override;
        void OnPlatformChallengeResponse(
                const cdm::PlatformChallengeResponse& response) override;
        void OnQueryOutputProtectionStatus(
                cdm::QueryResult result, uint32_t link_mask, uint32_t output_protection_mask) override;
        void OnStorageId(
                uint32_t version, const uint8_t* storage_id, uint32_t storage_id_size) override;
        void Destroy() override;

    private:
        CdmInterface* up_ptr;

    };

} // namespace proxy

#endif //CDM_PROXY_CMDPROXY_H
