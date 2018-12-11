gulp = require 'gulp'
browserSync = require 'browser-sync'

gulp.task 'browserSync', ->
  browserSync
    port: 9000
    open: false
    server:
      baseDir: ['./build', './app']
    files: ['./build/**']