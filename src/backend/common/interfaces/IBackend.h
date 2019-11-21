/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
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

#ifndef XMRIG_IBACKEND_H
#define XMRIG_IBACKEND_H


#include <stdint.h>


#include "rapidjson/fwd.h"


namespace xmrig {


class Algorithm;
class Hashrate;
class IWorker;
class Job;
class String;


class IBackend
{
public:
    virtual ~IBackend() = default;

    virtual bool isEnabled() const                                      = 0;
    virtual bool isEnabled(const Algorithm &algorithm) const            = 0;
    virtual const Hashrate *hashrate() const                            = 0;
    virtual const String &profileName() const                           = 0;
    virtual const String &type() const                                  = 0;
    virtual void prepare(const Job &nextJob)                            = 0;
    virtual void printHashrate(bool details)                            = 0;
    virtual void setJob(const Job &job)                                 = 0;
    virtual void start(IWorker *worker)                                 = 0;
    virtual void stop()                                                 = 0;
    virtual void tick(uint64_t ticks)                                   = 0;

#   ifdef XMRIG_FEATURE_API
    virtual rapidjson::Value toJSON(rapidjson::Document &doc) const     = 0;
#   endif
};


} // namespace xmrig


#endif // XMRIG_IBACKEND_H
