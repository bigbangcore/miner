/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2019 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018      Lee Clagett <https://github.com/vtnerd>
 * Copyright 2018-2019 tevador     <tevador@gmail.com>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
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

#ifndef XMRIG_RX_CACHE_H
#define XMRIG_RX_CACHE_H


#include <stdint.h>


#include "crypto/randomx/configuration.h"


struct randomx_cache;


namespace xmrig
{


class RxCache
{
public:
    RxCache(bool hugePages = true);
    ~RxCache();

    inline bool isHugePages() const         { return m_flags & 1; }
    inline bool isJIT() const               { return m_flags & 8; }
    inline const uint8_t *seed() const      { return m_seed; }
    inline randomx_cache *get() const       { return m_cache; }
    inline uint64_t initCount() const       { return m_initCount; }

    bool init(const uint8_t *seed);

    static inline constexpr size_t size() { return RANDOMX_CACHE_MAX_SIZE; }

private:
    bool isReady(const uint8_t *seed) const;

    int m_flags            = 0;
    randomx_cache *m_cache = nullptr;
    uint64_t m_initCount   = 0;
    uint8_t m_seed[32];
};


} /* namespace xmrig */


#endif /* XMRIG_RX_CACHE_H */
