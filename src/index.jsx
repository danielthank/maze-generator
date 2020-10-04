import React from 'react'
import ReactDOM from 'react-dom'
import './index.css'
import maze from './maze'
import App from './App'
import * as serviceWorker from './serviceWorker'

ReactDOM.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
  document.getElementById('root')
)

const width =
  window.innerWidth ||
  document.documentElement.clientWidth ||
  document.body.clientWidth
const height =
  window.innerHeight ||
  document.documentElement.clientHeight ||
  document.body.clientHeight

maze.initMaze(10, 10, height, width)

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
serviceWorker.unregister()
