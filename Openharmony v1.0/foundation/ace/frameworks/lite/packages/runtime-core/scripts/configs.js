/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
const babel = require('rollup-plugin-babel');
const commonjs = require('@rollup/plugin-commonjs');
const { eslint } = require('rollup-plugin-eslint');
const prettier = require('rollup-plugin-prettier');
const { nodeResolve } = require('@rollup/plugin-node-resolve');
const { sizeSnapshot } = require('rollup-plugin-size-snapshot');
const strip = require('@rollup/plugin-strip');
const { terser } = require('rollup-plugin-terser');

const format = 'umd';
const name = 'ViewModel';
const input = 'src/index.js';
const extensions = ['.js'];
const exclude = 'node_modules/**';
const beautifyPlugins = [prettier({ parser: 'babel' }), sizeSnapshot()];
const minimizePlugins = [terser(), sizeSnapshot()];

const banner = `/*
* Copyright (c) 2020 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/`;

module.exports = [
  {
    input,
    plugins: [
      eslint({ fix: true }),
      strip({ functions: ['startTracing', 'stopTracing'] }),
      nodeResolve({ extensions }),
      commonjs(),
      babel({ exclude, extensions }),
    ],
    output: [
      {
        name,
        banner,
        format,
        file: 'build/framework.js',
        plugins: beautifyPlugins,
      },
      {
        name,
        banner,
        format,
        file: 'build/framework.min.js',
        plugins: minimizePlugins,
      },
    ],
  },
  {
    input,
    plugins: [
      eslint({ fix: true }),
      nodeResolve({ extensions }),
      commonjs(),
      babel({ exclude, extensions }),
    ],
    output: [
      {
        name,
        banner,
        format,
        file: 'build/framework-dev.js',
        plugins: beautifyPlugins,
      },
      {
        name,
        banner,
        format,
        file: 'build/framework-dev.min.js',
        plugins: minimizePlugins,
      },
    ],
  },
];
