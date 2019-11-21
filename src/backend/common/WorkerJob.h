/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>,
 * <https://github.com/psychocrypt> Copyright 2018-2019 SChernykh
 * <https://github.com/SChernykh> Copyright 2016-2019 XMRig
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

#ifndef XMRIG_WORKERJOB_H
#define XMRIG_WORKERJOB_H

#include <string.h>

#include "base/net/stratum/Job.h"
#include "crypto/common/Nonce.h"

namespace xmrig {

template <size_t N> class WorkerJob {
public:
  inline const Job &currentJob() const { return m_jobs[index()]; }
  inline uint32_t *nonce(size_t i = 0) {
    return reinterpret_cast<uint32_t *>(blob() + (i * currentJob().size()) +
                                        109);
  }
  inline uint32_t *time(size_t i = 0) {
    return reinterpret_cast<uint32_t *>(blob() + (i * currentJob().size()) + 4);
  }
  inline uint64_t sequence() const { return m_sequence; }
  inline uint8_t *blob() { return m_blobs[index()]; }
  inline uint8_t index() const { return m_index; }

  inline void add(const Job &job, uint64_t sequence, uint32_t reserveCount) {
    m_sequence = sequence;

    if (currentJob() == job) {
      return;
    }

    if (index() == 1 && job.index() == 0 && job == m_jobs[0]) {
      m_index = 0;
      return;
    }

    save(job, reserveCount);
  }

  inline void nextRound(uint32_t reserveCount) {
    m_rounds[index()]++;

    if ((m_rounds[index()] % reserveCount) == 0) {
      for (size_t i = 0; i < N; ++i) {
        *nonce(i) = Nonce::next(index(), *nonce(i), reserveCount,
                                currentJob().isNicehash());
      }
    } else {
      for (size_t i = 0; i < N; ++i) {
        *nonce(i) += 1;
      }
    }
  }

  inline void nextTime() {
    for (size_t i = 0; i < N; ++i) {
      *time(i) += 1;
    }
  }

  inline void setTime(uint32_t val) {
    for (size_t i = 0; i < N; ++i) {
      *time(i) = val;
    }
  }

private:
  inline void save(const Job &job, uint32_t reserveCount) {
    m_index = job.index();
    const size_t size = job.size();
    m_jobs[index()] = job;
    m_rounds[index()] = 0;

    for (size_t i = 0; i < N; ++i) {
      memcpy(m_blobs[index()] + (i * size), job.blob(), size);
      *nonce(i) =
          Nonce::next(index(), *nonce(i), reserveCount, job.isNicehash());
    }
  }

  alignas(16) uint8_t m_blobs[2][Job::kMaxBlobSize * N];
  Job m_jobs[2];
  uint32_t m_rounds[2] = {0, 0};
  uint64_t m_sequence = 0;
  uint8_t m_index = 0;
};

template <> inline uint32_t *xmrig::WorkerJob<1>::nonce(size_t) {
  return reinterpret_cast<uint32_t *>(blob() + 109);
}

template <> inline void xmrig::WorkerJob<1>::nextRound(uint32_t reserveCount) {
  m_rounds[index()]++;

  if ((m_rounds[index()] % reserveCount) == 0) {
    *nonce() =
        Nonce::next(index(), *nonce(), reserveCount, currentJob().isNicehash());
  } else {
    *nonce() += 1;
  }
}

template <>
inline void xmrig::WorkerJob<1>::save(const Job &job, uint32_t reserveCount) {
  m_index = job.index();
  m_jobs[index()] = job;
  m_rounds[index()] = 0;

  memcpy(blob(), job.blob(), job.size());
  *nonce() =
      Nonce::next(index(), *nonce(), reserveCount, currentJob().isNicehash());
}

} // namespace xmrig

#endif /* XMRIG_WORKERJOB_H */
