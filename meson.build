project(
	'libscrafurl',
	'cpp',
	version: '0.0.1',
	default_options: [
		'cpp_std=c++17',
		'b_ndebug=if-release',
		'b_lto=true'
	],
	meson_version: '>=0.50.0'
)

libcurl_dep = dependency('libcurl')

libscrafurl_dep = declare_dependency(
	link_with: library(
		'libscrafurl',
		sources: 'libscrafurl'/'scrafurl.cpp',
		dependencies: libcurl_dep
	),
	dependencies: libcurl_dep
)

if meson.version().version_compare('>=0.54.0')
	meson.override_dependency('libscrafurl', libscrafurl_dep)
endif
