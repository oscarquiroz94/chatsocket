# C++ WebSocket Echo (websocketpp + standalone Asio)

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Run

Terminal 1:
```bash
./build/bin/ws_server 9002
```

Terminal 2:
```bash
./build/bin/ws_client ws://127.0.0.1:9002 "Hello there"
```

Expected output in Terminal 2:
```text
Received: Hello there
```

Notes:
- Ports and URI are configurable via command-line arguments.
- Dependencies are fetched automatically at configure time via CMake FetchContent.
- On Linux, `pthread` is linked automatically.
