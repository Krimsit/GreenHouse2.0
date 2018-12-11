_ = require 'lodash'
gulp = require 'gulp'
browserify = require 'browserify'
watchify = require 'watchify'
source = require 'vinyl-source-stream'
bundleLogger = require '../util/bundleLogger'
handleErrors = require '../util/handleErrors'

# External dependencies we do not want to rebundle while developing
dependencies =
  react: './node_modules/react'
  lodash: './node_modules/lodash'

gulp.task 'scripts', ->
  #==========  Client bundler  ==========#

  clientBundler = browserify
    cache: {}, packageCache: {}
    entries: './app/scripts/main.coffee'
    extensions: ['.cjsx', '.coffee']

  _.forEach dependencies, (path, dep) ->
    clientBundler.external dep

  rebundle = ->
    bundleLogger.start 'client.js'

    clientBundler.bundle()
      .on 'error', handleErrors
      .pipe source('client.js')
      .pipe gulp.dest('./build/scripts')
      .on 'end', ->
        bundleLogger.end 'client.js'

  if global.isWatching
    clientBundler = watchify clientBundler
    clientBundler.on 'update', rebundle
  rebundle()

  #==========  Vendor bundler  ==========#

  vendorBundler = browserify
    cache: {}, packageCache: {}
    extensions: ['.coffee']

  _.forEach dependencies, (path, dep) ->
    vendorBundler.require path, expose: dep

  bundleLogger.start 'vendor.js'

  vendorBundler.bundle()
    .on 'error', handleErrors
    .pipe source('vendor.js')
    .pipe gulp.dest('./build/scripts')
    .on 'end', ->
      bundleLogger.end 'vendor.js'