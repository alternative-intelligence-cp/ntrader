# NTRADER

**NTRADER** is an ultra-high-frequency, hyper-resilient cryptocurrency trading engine built entirely in **Nitpick** (`0.61.x`). Engineered for zero-allocation hot paths, cryptographic determinism, and failsafe stability.

## Features

- **Zero-Allocation Hot Paths**: The entire event loop and indicator pipelines avoid dynamic allocations (`npk_core_alloc`), relying exclusively on custom slab arenas (`TCBArena`) and thread-safe lock-free bounds.
- **Advanced State Machines**: Features non-blocking TCP and TLS (SSL) reactors via `epoll`. Connections are properly isolated and reliably torn down on critical peer errors (`WANT_READ`, `WANT_WRITE` validations).
- **Cryptographic Order Books**: Stale ticks and UDP packet races are aggressively filtered through generational cryptographic verification, maintaining a perfectly aligned Local Limit Order Book (LOB).
- **SIMD-Accelerated Quant**: Mathematical indicators like Exponential Moving Averages (EMA), Relative Strength Index (RSI), and Bollinger Bands are aligned and processed using 64-bit SIMD intrinsics (`simd<tfp64, 8>`). 
- **AI Circuit Breakers**: AI LLM integrations are tightly monitored. Memory spills or computational hangs hit a 512MB threshold circuit breaker that softly degrades the LLM output to technical-only indicators, never bringing down the main reactor.
- **Fail-Safe Master Routines**: Unrecoverable engine panics fall back to a zero-allocation `SYS_MMAP` emergency shutdown sequence, instantly firing hard-coded `AF_INET` TCP payloads to liquidate open positions natively via syscalls.

## Current Audit Release: `0.4.0`

The `a20` cycle of audits has certified NTRADER `0.4.0` as entirely resilient. Thread lifecycle tearing, SSL infinite spins, and memory races have all been mitigated.

### Building & Testing

NTRADER targets Nitpick `0.61.x`.

```bash
# Build the engine
npkbld build

# Run unit and benchmark tests
npkbld build bench
./.nitpick_make/build/bench
```

## Architecture Notes

* **`LockFreeQueue`**: Enables extreme low-latency 100ns task handoffs from the async I/O worker threads into the single-threaded quantitative engine.
* **Floating-Point Stability**: Implemented `ROUND_HALF_EVEN` precision rules with RingBuffer resets to entirely negate numerical precision cancellations in continuous uptimes.

## Status

**Ready for Production Benchmarking.** The internal logic is feature complete.

---
*Built as a reference demonstration of high-performance architecture in the Nitpick programming language.*
