import resolve from '@rollup/plugin-node-resolve'
import commonJS from '@rollup/plugin-commonjs'
import babel from '@rollup/plugin-babel'

export default {
  input: 'src/index.js',
  output: {
    format: 'esm',
    file: 'index.js'
  },
  plugins: [
    resolve(),
    commonJS({
      include: 'node_modules/**'
    }),

    // getBabelOutputPlugin({
    //   presets: ['@babel/preset-env']
    // }),

    babel({ babelHelpers: 'bundled' })
  ]
}
