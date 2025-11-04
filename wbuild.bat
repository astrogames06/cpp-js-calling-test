
em++ main.cpp -o index.html -std=c++17 -Os -Wall -s WASM=1 -s "EXPORTED_RUNTIME_METHODS=['ccall','cwrap']" -lembind --shell-file shell.html