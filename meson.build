project('HailMary', 'cpp', default_options : ['cpp_std=c++20'])
add_global_arguments('-DDEBUG', language: 'cpp')
subdir('src/')
subdir('src/internals')
subdir('src/objects')
subdir('src/managers')
subdir('src/harlequin')

# Handle the external dependencies first
sdl2_dep = dependency('sdl2')
sdl2_image_dep = dependency('sdl2_image')
sdl2_ttf_dep = dependency('sdl2_ttf')

pymod = import('python')
python = pymod.find_installation('python3')
python_dep = python.dependency(embed: true)

# Actually compile and link the modules
libinternals = static_library(
    'internals',
    internals_files,
    include_directories: internals_includes
)

libinternals_dep = declare_dependency(
    include_directories: internals_includes,
    link_with: libinternals
)

libobjects = static_library(
    'objects',
    objects_files,
    include_directories: objects_includes,
    dependencies: [
        libinternals_dep,
        sdl2_dep,
        sdl2_image_dep,
        sdl2_ttf_dep
    ]
)

libobjects_dep = declare_dependency(
    include_directories: objects_includes,
    link_with: libobjects
)


libharlequin = static_library(
    'harlequin',
    harlequin_files,
    include_directories: harlequin_includes,
    dependencies: [
        python_dep,
        libinternals_dep
    ]
)

libharlequin_dep = declare_dependency(
    include_directories: harlequin_includes,
    link_with: libharlequin
)

libmanagers = static_library(
    'managers',
    managers_files,
    include_directories: managers_includes,
    dependencies: [
        libharlequin_dep,
        libinternals_dep,
        libobjects_dep,
        sdl2_dep,
        sdl2_image_dep,
        sdl2_ttf_dep,
        python_dep
    ]
)

libmanagers_dep = declare_dependency(
    include_directories: managers_includes,
    link_with: libmanagers
)

executable('HailMary',
    main_file,
    dependencies: [
        libmanagers_dep,
        libinternals_dep,
        libharlequin_dep,
        libobjects_dep,
        sdl2_dep,
        sdl2_image_dep,
        sdl2_ttf_dep,
        python_dep
    ]
)