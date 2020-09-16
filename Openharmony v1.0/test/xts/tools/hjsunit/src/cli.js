#!/usr/bin/env node

// const argv = process.argv.slice(2)

// const x = NodeJS.Global | Window
// console.log(x)
// if (argv.length == 0) {
//
// }

const babel = require('@rollup/plugin-babel')
// const helpers = require('@babel/helpers')

const { promisify } = require('util')
const rollup = require('rollup')
const commonjs = require('@rollup/plugin-commonjs')
const resolve = require('@rollup/plugin-node-resolve')
const virtual = require('@rollup/plugin-virtual')
const inject = require('@rollup/plugin-inject')

const glob = promisify(require('glob-all'))
const argv = require('minimist')(process.argv.slice(2))


const outputFile = argv.o || argv.output || 'spec.js'
const pageFormat = argv.p || argv.page || false
const filePatterns = argv._.length === 0 ? ['./spec/**/*.test.js'] : argv._

function buildConfig () {
  return glob(filePatterns).then(function (specFiles) {
    let entryContent = `
      import JSUnit from '__spec_init__.js'
    `
    for (const specFile of specFiles) {
      entryContent += `import '${specFile}';`
    }

    // entryContent += `JSUnit.execute()`
    if (pageFormat) {
      entryContent += 'export default { onShow: function() { JSUnit.execute()} };'
    } else {
      entryContent += 'JSUnit.execute()'
    }

    let modules = {
      '__spec_init__.js': `import JSUnit from 'JSUnit'; JSUnit.init(); export default JSUnit`,
      '__spec_entry__.js': entryContent
    }
    // const systemModules = ['system.router', 'system.app', 'system.prompt']
    // systemModules.forEach((m) => {
    //   modules[`@${m}`] = `export default $app_require$('@app-module/${m}')`
    // })

    let injectConfig = {
      describe: ['JSUnit', 'describe'],
      it: ['JSUnit', 'it'],
      beforeAll: ['JSUnit', 'beforeAll'],
      beforeEach: ['JSUnit', 'beforeEach'],
      afterEach: ['JSUnit', 'afterEach'],
      afterAll: ['JSUnit', 'afterAll'],
      expect: ['JSUnit', 'expect']

    }

    return {
      input: '__spec_entry__.js',
      output: {
        format: 'umd'
      },
      plugins: [
        inject(injectConfig),

        virtual(modules),
        // babel({
        //   exclude: 'node_modules/**'
        // }),
        resolve(),
        commonjs({
          // non-CommonJS modules will be ignored, but you can also
          // specifically include/exclude files
          include: ['index.js', 'node_modules/**', 'src'], // Default: undefined

          // if true then uses of `global` won't be dealt with by this plugin
          ignoreGlobal: false, // Default: false

          // if false then skip sourceMap generation for CommonJS modules
          sourceMap: false // Default: true
        }),
        // babel.babel({
        //   presets: [
        //     ['@babel/preset-env', {
        //       'exclude': ['transform-for-of']
        //     }]
        //   ]
        // }),
        // babel.getBabelOutputPlugin({
        //   presets: [
        //     ['@babel/preset-env', {
        //       'exclude': ['transform-for-of']
        //     }]
        //   ]
        // }),
        // babel.babel({ babelHelpers: 'bundled' })

        babel.babel({ babelHelpers: 'bundled' })
      ]
    }
  })
}

// see below for details on the options

async function build () {
  const inputOptions = await buildConfig()
  const bundle = await rollup.rollup(inputOptions)
  const outputOptions = { output: { file: outputFile } }

  // generate output specific code in-memory
  // you can call this function multiple times on the same bundle object
  const { output } = await bundle.generate(outputOptions)

  for (const chunkOrAsset of output) {
    if (chunkOrAsset.type === 'asset') {
      // For assets, this contains
      // {
      //   fileName: string,              // the asset file name
      //   source: string | Uint8Array    // the asset source
      //   type: 'asset'                  // signifies that this is an asset
      // }
      // console.log('Asset', chunkOrAsset)
    } else {
      // For chunks, this contains
      // {
      //   code: string,                  // the generated JS code
      //   dynamicImports: string[],      // external modules imported dynamically by the chunk
      //   exports: string[],             // exported variable names
      //   facadeModuleId: string | null, // the id of a module that this chunk corresponds to
      //   fileName: string,              // the chunk file name
      //   imports: string[],             // external modules imported statically by the chunk
      //   isDynamicEntry: boolean,       // is this chunk a dynamic entry point
      //   isEntry: boolean,              // is this chunk a static entry point
      //   map: string | null,            // sourcemaps if present
      //   modules: {                     // information about the modules in this chunk
      //     [id: string]: {
      //       renderedExports: string[]; // exported variable names that were included
      //       removedExports: string[];  // exported variable names that were removed
      //       renderedLength: number;    // the length of the remaining code in this module
      //       originalLength: number;    // the original length of the code in this module
      //     };
      //   },
      //   name: string                   // the name of this chunk as used in naming patterns
      //   type: 'chunk',                 // signifies that this is a chunk
      // }
      // console.log('Chunk', chunkOrAsset.modules)
    }
  }

  // or write the bundle to disk
  await bundle.write(outputOptions)
}

build()
