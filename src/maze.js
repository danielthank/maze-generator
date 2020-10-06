import maze from './wasm/build/maze'
import mazeBinary from './wasm/build/maze.wasm'

let initMazeWasm
let ready

export function initWasm() {
  ready = maze({
    canvas: document.getElementById('canvas'),
    locateFile: () => {
      return mazeBinary
    },
  }).then((instance) => {
    initMazeWasm = instance.cwrap('init_maze', null, [
      'number',
      'number',
      'number',
      'number',
    ])
  })
}

export async function initMaze(n, m, h, w) {
  await ready
  initMazeWasm(n, m, h, w)
}

export async function test() {
  return 123
}
