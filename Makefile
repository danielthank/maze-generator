wasm: src/wasm/main.cpp src/wasm/maze.cpp
	mkdir -p src/wasm/build
	emcc src/wasm/main.cpp src/wasm/maze.cpp -o src/wasm/build/maze.js -s WASM=1 -s USE_SDL=2 -s MODULARIZE=1 -s EXPORTED_FUNCTIONS='["_init_maze"]' -s EXPORTED_RUNTIME_METHODS='["cwrap"]'
