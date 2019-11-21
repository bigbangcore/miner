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

#ifndef XMRIG_CONFIG_DEFAULT_H
#define XMRIG_CONFIG_DEFAULT_H

namespace xmrig {

#ifdef XMRIG_FEATURE_EMBEDDED_CONFIG
const static char *default_config =
    R"===(
{
    "autosave": false,
    "background": false,
    "colors": true,
    "retries": 5,
    "retry-pause": 5,
    "syslog": false,
    "log-file": null,
    "print-time": 60,
    "av": 0,
    "safe": false,
    "max-cpu-usage": 85,
    "cpu-priority": 3,
    "pools": [
        {
            "algo": "cn/bbc",
            "url1": "18.139.37.48:3333",
            "url2": "106.14.238.184:12812",
            "url": "127.0.0.1:3333",
            "user": "1jtacnnqtrmm6g7n0tphyjrqp0rkapvr49m2qwhx8kt6x8c83mh2c19ds",
            "pass": "x",
            "rig-id": "chasanbu",
            "nicehash": true,
            "keepalive": true,
            "enabled": true,
            "tls": false,
            "tls-fingerprint": null
        }
    ],
    "threads": 1,
    "api": {
        "port": 0,
        "access-token": null,
        "worker-id": null
    }
}
)===";
#endif

} // namespace xmrig

#endif /* XMRIG_CONFIG_DEFAULT_H */
