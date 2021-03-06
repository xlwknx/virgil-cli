/**
 * Copyright (C) 2015-2017 Virgil Security Inc.
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VIRGIL_CLI_FILE_DATA_SOURCE_H
#define VIRGIL_CLI_FILE_DATA_SOURCE_H

#include <virgil/crypto/VirgilDataSource.h>

#include <functional>
#include <istream>
#include <memory>
#include <vector>


namespace cli { namespace model {

class FileDataSource : public virgil::crypto::VirgilDataSource {
public:
    static constexpr const size_t kChunkSize_Default = 1024 * 1024; // 1MB
public:
    /**
     * @param chunkSize - size of the data that will be returned by @link read() @endlink method.
     * @brief Create source from the standard input
     */
    FileDataSource(size_t chunkSize = kChunkSize_Default);
    /**
     * @brief Create source from the given file.
     * @param fileName - path to the source file to be read.
     * @param chunkSize - size of the data that will be returned by @link read() @endlink method.
     * @throw ArgumentFileNotFound, if IO errors occurred.
     */
    FileDataSource(const std::string& fileName, size_t chunkSize = kChunkSize_Default);
public:
    virtual bool hasData() override;
    virtual virgil::crypto::VirgilByteArray read() override;
    virtual virgil::crypto::VirgilByteArray readAll();
    virtual std::string readText();
    virtual std::string readLine();
    virtual std::vector<std::string> readMultiLine();
private:
    using istream_deleter = std::function<void(std::istream*)>;
    using istream_ptr = std::unique_ptr<std::istream, istream_deleter>;
    istream_ptr in_;
    size_t chunkSize_;
};

}}

#endif //VIRGIL_CLI_FILE_DATA_SOURCE_H
