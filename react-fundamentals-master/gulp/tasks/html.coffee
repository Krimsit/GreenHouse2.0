gulp = require 'gulp'
browserSync = require 'browser-sync'
reload = browserSync.reload

gulp.task 'html', ->
  gulp.src './app/html/*.html'
    .pipe gulp.dest('./build')
    .pipe reload({ stream: true })