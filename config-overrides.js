module.exports = function override(config, env) {
  config.module.rules.push({
    test: /\.worker.js$/,
    loader: 'workerize-loader',
  })

  config.module.rules.forEach((rule) => {
    ;(rule.oneOf || []).forEach((oneOf) => {
      if (oneOf.loader && oneOf.loader.indexOf('file-loader') >= 0) {
        // Make file-loader ignore WASM files
        oneOf.exclude.push(/\.wasm$/)
      }
    })
  })

  config.module.rules.push({
    test: /\.wasm$/,
    type: 'javascript/auto',
    loader: 'file-loader',
    options: {
      esModule: false,
    },
  })
  return config
}
