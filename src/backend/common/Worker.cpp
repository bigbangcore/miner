/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018      Lee Clagett <https://github.com/vtnerd>
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


#include "backend/common/Worker.h"
#include "base/kernel/Platform.h"
#include "base/tools/Chrono.h"
#include "crypto/common/VirtualMemory.h"


xmrig::Worker::Worker(size_t id, int64_t affinity, int priority) :
    m_affinity(affinity),
    m_id(id),
    m_hashCount(0),
    m_timestamp(0),
    m_count(0)
{
    m_node = VirtualMemory::bindToNUMANode(affinity);

    Platform::trySetThreadAffinity(affinity);
    Platform::setThreadPriority(priority);
}


void xmrig::Worker::storeStats()
{
    m_hashCount.store(m_count, std::memory_order_relaxed);
    m_timestamp.store(Chrono::highResolutionMSecs(), std::memory_order_relaxed);
}
