project(
    'fstools',
    'c',
    version : '0.0.1',
    default_options : [ 'warning_level=3', 'werror=true' ],
)

sources = files(
    'src/fstools.c'
)

project_exe = executable(
    meson.project_name(),
    sources,
    include_directories : include_directories('fstools'),
    install : true,
)