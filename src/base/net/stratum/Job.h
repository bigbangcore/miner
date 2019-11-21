/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>,
 * <https://github.com/psychocrypt> Copyright 2018      Lee Clagett
 * <https://github.com/vtnerd> Copyright 2018-2019 SChernykh
 * <https://github.com/SChernykh> Copyright 2019      Howard Chu
 * <https://github.com/hyc> Copyright 2016-2019 XMRig
 * <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef XMRIG_JOB_H
#define XMRIG_JOB_H

#include <iostream>
#include <stddef.h>
#include <stdint.h>

#include "base/tools/String.h"
#include "crypto/common/Algorithm.h"
#include <cmath>

using namespace std;
namespace xmrig {

class Job {
public:
  // Max blob size is 84 (75 fixed + 9 variable), aligned to 96.
  // https://github.com/xmrig/xmrig/issues/1 Thanks fireice-uk. SECOR increase
  // requirements for blob size: https://github.com/xmrig/xmrig/issues/913
  static constexpr const size_t kMaxBlobSize = 128;

  Job();
  Job(bool nicehash, const Algorithm &algorithm, const String &clientId);
  ~Job();

  bool isEqual(const Job &other) const;
  bool setBlob(const char *blob);
  bool setSeedHash(const char *hash);
  bool setTarget(const char *target);
  void setDiff(uint64_t diff);

  inline bool isNicehash() const { return m_nicehash; }
  inline bool isValid() const { return m_size > 0 && m_diff > 0; }
  inline bool setId(const char *id) { return m_id = id; }
  inline const Algorithm &algorithm() const { return m_algorithm; }
  inline const String &clientId() const { return m_clientId; }
  inline const String &id() const { return m_id; }
  inline const uint32_t *nonce() const {
    return reinterpret_cast<const uint32_t *>(m_blob + 109);
  }
  inline const uint8_t *blob() const { return m_blob; }
  inline const uint8_t *seedHash() const { return m_seedHash; }
  inline size_t size() const { return m_size; }
  inline uint32_t *nonce() {
    return reinterpret_cast<uint32_t *>(m_blob + 109);
  }
  inline uint64_t diff() const { return m_diff; }
  inline uint64_t height() const { return m_height; }
  inline uint64_t target() const { return m_target; }
  inline uint32_t *time() { return reinterpret_cast<uint32_t *>(m_blob + 4); }
  inline const uint32_t *time() const{ return reinterpret_cast<const uint32_t *>(m_blob + 4); }
  inline uint8_t fixedByte() const { return *(m_blob + 42); }
  inline uint8_t index() const { return m_index; }
  inline void reset() {
    m_size = 0;
    m_diff = 0;
  }
  inline void setAlgorithm(const char *algo) { m_algorithm = algo; }
  inline void setClientId(const String &id) { m_clientId = id; }
  inline void setHeight(uint64_t height) { m_height = height; }
  inline void setIndex(uint8_t index) { m_index = index; }

#ifdef XMRIG_PROXY_PROJECT
  inline char *rawBlob() { return m_rawBlob; }
  inline const char *rawBlob() const { return m_rawBlob; }
  inline const char *rawTarget() const { return m_rawTarget; }
  inline const String &rawSeedHash() const { return m_rawSeedHash; }
#endif

  static inline uint32_t *nonce(uint8_t *blob) {
    return reinterpret_cast<uint32_t *>(blob + 109);
  }
  static inline uint64_t toDiff(uint64_t target) {
    // std::cout << "target:" << target << std::endl;
    // std::cout << "targetHex:" << std::hex << target << std::endl;
    int i;
    for (i = 0; i < 64; i++) {
      if (target & 0x8000000000000000) {
        break;
      }
      target <<= 1;
    }
    // std::cout << "i:" << i << std::endl;
    return i;
  }

  inline bool operator==(const Job &other) const { return isEqual(other); }
  inline bool operator!=(const Job &other) const { return !isEqual(other); }
  inline Job &operator=(const Job &other) {
    copy(other);
    return *this;
  }

private:
  void copy(const Job &other);

  Algorithm m_algorithm;
  bool m_nicehash = false;
  size_t m_size = 0;
  String m_clientId;
  String m_id;
  uint64_t m_diff = 0;
  uint64_t m_height = 0;
  uint64_t m_target = 0;
  uint8_t m_blob[kMaxBlobSize];
  uint8_t m_index = 0;
  uint8_t m_seedHash[32];

#ifdef XMRIG_PROXY_PROJECT
  char m_rawBlob[kMaxBlobSize * 2 + 8];
  char m_rawTarget[24];
  String m_rawSeedHash;
#endif
};

} /* namespace xmrig */

#endif /* XMRIG_JOB_H */
