import maze from './wasm/build/maze'
import mazeBinary from './wasm/build/maze.wasm'

class Maze {
  constructor() {
    this.ready = maze({
      canvas: (() => document.getElementById('canvas'))(),
      locateFile: () => {
        return mazeBinary
      },
    }).then((instance) => {
      this.initMazeWasm = instance.cwrap('init_maze', null, [
        'number',
        'number',
        'number',
      ])
      this.ready = true
    })
  }

  async initMaze(n, m, w, h) {
    await this.ready
    this.initMazeWasm(n, m, w, h)
  }
}

const mazeInstance = new Maze()

export default mazeInstance
