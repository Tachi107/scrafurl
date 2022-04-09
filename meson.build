# SPDX-FileCopyrightText: 2022 Andrea Pappacoda
#
# SPDX-License-Identifier: LGPL-3.0-or-later

project(
	'scrafurl',
	'cpp',
	default_options: [
		'cpp_std=c++20',
		'b_ndebug=if-release',
		'b_lto=true'
	],
	license: 'LGPL-3.0-or-later',
	meson_version: '>=0.49.0',
	version: '0.0.1'
)

libcurl_dep = dependency('libcurl', version: '>=7.49.0')

include_dir = include_directories('include')

libscrafurl = library(
	'scrafurl',
	'src'/'scrafurl.cpp',
	dependencies: libcurl_dep,
	include_directories: include_dir
)

scrafurl_dep = declare_dependency(
	link_with: libscrafurl,
	dependencies: libcurl_dep,
	include_directories: include_dir
)

if meson.version().version_compare('>=0.54.0')
	meson.override_dependency('scrafurl', scrafurl_dep)
endif

install_headers('include'/'scrafurl.hpp')

import('pkgconfig').generate(
	libscrafurl,
	description: 'Lightweight libcurl wrapper written in C++20'
)
