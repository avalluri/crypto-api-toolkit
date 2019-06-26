/*
 * Copyright (C) 2019 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef ENCLAVE_HELPERS_H
#define ENCLAVE_HELPERS_H

#include <sgx_error.h>
#include <sgx_eid.h>
#include <sgx_urts.h>
#include <sgx_error.h>
#include <sgx_uae_service.h>
#include <map>

#include "p11Enclave_u.h"
#include "CryptoEnclaveDefs.h"
#include "p11Defines.h"

// Globals with file scope.
namespace P11Crypto
{
    class EnclaveHelpers
    {
    public:

        EnclaveHelpers();

        /*
        * Checks if SGX enclave is loaded.
        * @return false if SGX enclave is not loaded.
        * @return true  if SGX enclave is loaded.
        */
        inline bool isSgxEnclaveLoaded()
        {
            return (mSgxEnclaveLoadedCount > 0);
        }

        /*
        * Gets the SGX enclave ID.
        * @return The SGX enclave ID.
        */
        inline sgx_enclave_id_t getSgxEnclaveId(void)
        {
            return mSgxEnclaveId;
        }

        /*
        * Sets the SGX enclave ID.
        * @param sgxEnclaveId The SGX enclave ID.
        */
        inline void setSgxEnclaveId(const sgx_enclave_id_t sgxEnclaveId)
        {
            mSgxEnclaveId = sgxEnclaveId;
        }

        /*
        * Loads the enclave.
        * @return sgx_status_t   SGX_SUCCESS if enclave load is successful, error code otherwise.
        */
        sgx_status_t loadSgxEnclave();

        /*
        * Unloads the enclave.
        * @return sgx_status_t   SGX_SUCCESS if enclave unload is successful, error code otherwise.
        */
        sgx_status_t unloadSgxEnclave();

        /*
        * Maps the enclave return code to PKCS status code.
        * @param  enclaveStatus  The enclave return code.
        * @return CK_RV          CKR_OK if operation is successful, error code otherwise.
        */
        CK_RV enclaveStatusToPkcsStatus(const SgxCryptStatus& enclaveStatus);

        // Invalid SGX enclave ID value.
        static sgx_enclave_id_t mEnclaveInvalidId;

        // SGX enclave reference count
        static volatile long mSgxEnclaveLoadedCount;

    private:
        // SGX enclave ID global.
        static sgx_enclave_id_t mSgxEnclaveId;
    };
}
#endif //ENCLAVE_HELPERS_H

