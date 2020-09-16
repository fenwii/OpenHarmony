module.exports = {
  env: {
    browser: true,
    es6: true,
    node: true
  },
  extends: ['google'],
  globals: {
    profiler: 'readonly',
    initStyleSheet: 'readonly'
  },
  plugins: ['jest'],
  parserOptions: {
    ecmaVersion: 2018,
    sourceType: 'module'
  },
  rules: {
    'arrow-parens': ['error', 'as-needed'],
    'object-curly-spacing': ['error', 'always'],
    'comma-dangle': ['error', 'never']
  }
};
