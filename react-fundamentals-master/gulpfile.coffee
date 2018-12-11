gulp = require 'gulp'
requireDir = require 'require-dir'
runSequence = require 'run-sequence'

# Require all tasks in gulp/tasks, including subfolders
requireDir './gulp/tasks', recurse: true

gulp.task 'default', ['server']

gulp.task 'build', ['clean'], (cb) ->
  runSequence ['scripts', 'html', 'less'], cb

gulp.task 'server', ['setWatch', 'build'], ->
  gulp.start 'watch'