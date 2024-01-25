import os
import ycm_core

def Settings(**kwargs):
    cmake_build_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'build')  # Prilagodite glede na dejansko ime build direktorija

    return {
        'flags': [
            '-x',
            'c++',
            '-Wall',
            '-Wextra',
            '-Werror',
            '-std=c++20',  # Posodobite standard na C++20 ali po potrebi
            '-I',
            'lib/CelicniAvtomat',
            'lib/HenigmaEngine/include',
        ],
        'include_paths_relative_to_dir': os.path.dirname(os.path.abspath(__file__)),
        'override_filename': kwargs.get('filename', None),
        'do_cache': True,
        'cache_directory': cmake_build_dir,
        'fallback_flags': ['-std=c++20'],  # Dodatek za dodatne zastave
    }

