import React, { useEffect } from 'react'
import { initWasm, initMaze } from './maze'

function App() {
  useEffect(() => {
    initWasm()

    const width =
      window.innerWidth ||
      document.documentElement.clientWidth ||
      document.body.clientWidth
    const height =
      window.innerHeight ||
      document.documentElement.clientHeight ||
      document.body.clientHeight
    initMaze(10, 10, height, width)
  }, [])

  return (
    <div className="App">
      <canvas id="canvas" />
    </div>
  )
}

export default App
