# v3.1.3
- [#1180](https://github.com/xmrig/xmrig/issues/1180) Fixed possible duplicated shares after algorithm switching.
- Fixed wrong config file permissions after write (only gcc builds on recent Windows 10 affected).

# v3.1.2
- Many RandomX optimizations and fixes.
  - [#1132](https://github.com/xmrig/xmrig/issues/1132) Fixed build on CentOS 7.
  - [#1163](https://github.com/xmrig/xmrig/pull/1163) Optimized soft AES code, up to +30% hashrate on CPU without AES support and other optimizations.
  - [#1166](https://github.com/xmrig/xmrig/pull/1166) Fixed crash when initialize dataset with big threads count (eg 272).
  - [#1168](https://github.com/xmrig/xmrig/pull/1168) Optimized loading from scratchpad.
- [#1128](https://github.com/xmrig/xmrig/issues/1128) Fixed CMake 2.8 compatibility.

# v3.1.1
- [#1133](https://github.com/xmrig/xmrig/issues/1133) Fixed syslog regression.
- [#1138](https://github.com/xmrig/xmrig/issues/1138) Fixed multiple network bugs.
- [#1141](https://github.com/xmrig/xmrig/issues/1141) Fixed log in background mode.
- [#1142](https://github.com/xmrig/xmrig/pull/1142) RandomX hashrate improved by 0.5-1.5% depending on variant and CPU.
- [#1146](https://github.com/xmrig/xmrig/pull/1146) Fixed race condition in RandomX thread init.
- [#1148](https://github.com/xmrig/xmrig/pull/1148) Fixed, on Linux linker marking entire executable as having an executable stack.
- Fixed, for Argon2 algorithms command line options like `--threads` was ignored.
- Fixed command line options for single pool, free order allowed again.

# v3.1.0
- [#1107](https://github.com/xmrig/xmrig/issues/1107#issuecomment-522235892) Added Argon2 algorithm family: `argon2/chukwa` and `argon2/wrkz`.

# v3.0.0
- **[#1111](https://github.com/xmrig/xmrig/pull/1111) Added RandomX (`rx/test`) algorithm for testing and benchmarking.**
- **[#1036](https://github.com/xmrig/xmrig/pull/1036) Added RandomWOW (`rx/wow`) algorithm for [Wownero](http://wownero.org/).**
- **[#1050](https://github.com/xmrig/xmrig/pull/1050) Added RandomXL (`rx/loki`) algorithm for [Loki](https://loki.network/).**
- **[#1077](https://github.com/xmrig/xmrig/issues/1077) Added NUMA support via hwloc**.
- **Added flexible [multi algorithm](doc/CPU.md) configuration.**
- **Added unlimited switching between incompatible algorithms, all mining options can be changed in runtime.**
- [#257](https://github.com/xmrig/xmrig-nvidia/pull/257) New logging subsystem, file and syslog now always without colors.
- [#314](https://github.com/xmrig/xmrig-proxy/issues/314) Added donate over proxy feature.
- [#1007](https://github.com/xmrig/xmrig/issues/1007) Old HTTP API backend based on libmicrohttpd, replaced to custom HTTP server (libuv + http_parser).
- [#1010](https://github.com/xmrig/xmrig/pull/1010#issuecomment-482632107) Added daemon support (solo mining).
- [#1066](https://github.com/xmrig/xmrig/issues/1066#issuecomment-518080529) Added error message if pool not ready for RandomX.
- [#1105](https://github.com/xmrig/xmrig/issues/1105) Improved auto configuration for `cn-pico` algorithm.
- Added commands `pause` and `resume` via JSON RPC 2.0 API (`POST /json_rpc`).
- Added command line option `--export-topology` for export hwloc topology to a XML file.
- Breaked backward compatibility with previous configs and command line, `variant` option replaced to `algo`, global option `algo` removed, all CPU related settings moved to `cpu` object.
- Options `av`, `safe` and `max-cpu-usage` removed.
- Algorithm `cn/msr` renamed to `cn/fast`.
- Algorithm `cn/xtl` removed.
- API endpoint `GET /1/threads` replaced to `GET /2/backends`.
- Added global uptime and extended connection information in API.
- API now return current algorithm.

# Previous versions
[doc/CHANGELOG_OLD.md](doc/CHANGELOG_OLD.md)
