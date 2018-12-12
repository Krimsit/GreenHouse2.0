gulp = require 'gulp'
less = require 'gulp-less'
rename = require 'gulp-rename'
autoprefixer = require 'gulp-autoprefixer'
sourcemaps = require 'gulp-sourcemaps'
handleErrors = require '../util/handleErrors'

gulp.task 'less', ->
  gulp.src './app/stylesheets/main.less'
    .pipe sourcemaps.init()
    .pipe less()
    .on 'error', handleErrors
    .pipe autoprefixer({cascade: false, browsers: ['last 2 versions']})
    .pipe sourcemaps.write()
    .pipe rename 'style.css'
    .pipe gulp.dest('./build/stylesheets')