gnome = import('gnome')

plparser_public_headers = [
  'xplayer-pl-parser.h',
  'xplayer-pl-playlist.h',
  'xplayer-pl-parser-mini.h',
]
install_headers(plparser_public_headers, subdir : 'xplayer-pl-parser/1/plparser')

# generate xplayer-pl-parser-features.h
version_cdata = configuration_data()
version_cdata.set('XPLAYER_PL_PARSER_VERSION_MAJOR', plparse_major_version)
version_cdata.set('XPLAYER_PL_PARSER_VERSION_MINOR', plparse_minor_version)
version_cdata.set('XPLAYER_PL_PARSER_VERSION_MICRO', plparse_micro_version)
features_h = configure_file(output: 'xplayer-pl-parser-features.h',
                            install_dir: 'include/xplayer-pl-parser/1/plparser',
                            configuration: version_cdata)

xplayer_pl_parser_builtins = gnome.mkenums('xplayer-pl-parser-builtins',
                                         sources: 'xplayer-pl-parser.h',
                                         c_template : 'xplayer-pl-parser-builtins.c.template',
                                         h_template : 'xplayer-pl-parser-builtins.h.template',
                                         install_dir : 'include/xplayer-pl-parser/1/plparser',
                                         install_header : true)

xplayer_pl_parser_builtins_h = xplayer_pl_parser_builtins[1]

xplayer_pl_parser_marshalers = gnome.genmarshal('xplayerplparser-marshal',
                                              sources : 'xplayerplparser-marshal.list',
                                              prefix : '_xplayerplparser_marshal')

plparser_sources = [
  'xplayer-disc.c',
  'xplayer-pl-parser.c',
  'xplayer-pl-parser-amz.c',
  'xplayer-pl-parser-lines.c',
  'xplayer-pl-parser-media.c',
  'xplayer-pl-parser-misc.c',
  'xplayer-pl-parser-pla.c',
  'xplayer-pl-parser-pls.c',
  'xplayer-pl-parser-podcast.c',
  'xplayer-pl-parser-qt.c',
  'xplayer-pl-parser-smil.c',
  'xplayer-pl-parser-videosite.c',
  'xplayer-pl-parser-wm.c',
  'xplayer-pl-parser-xspf.c',
  'xplayer-pl-playlist.c',
  'xmlparser.c',
  'xmllexer.c',
]

xplayerlib_inc = include_directories('../lib')

libexecdir = join_paths(get_option('prefix'), get_option('libexecdir'))

plparser_cflags = extra_warning_cflags + ['-DLIBEXECDIR="@0@"'.format(libexecdir)]

symbol_map = 'plparser.map'
symbol_link_args = '-Wl,--version-script,@0@/@1@'.format(meson.current_source_dir(), symbol_map)

plparser_lib = library('xplayer-plparser',
                       plparser_sources, features_h,
                       xplayer_pl_parser_builtins,
                       xplayer_pl_parser_marshalers,
                       include_directories: [config_inc, xplayerlib_inc],
                       c_args: plparser_cflags,
                       dependencies: xplayer_pl_parser_deps,
                       link_args : symbol_link_args,
                       link_with: xplayer_glibc_lib,
                       link_depends : symbol_map,
                       version: plparse_libversion,
                       install: true)

plparser_dep = declare_dependency(sources: [xplayer_pl_parser_builtins_h, features_h],
                                  include_directories: [config_inc, plparser_inc],
                                  dependencies: gio_dep,
                                  link_with: plparser_lib)

plparser_mini_sources = [
  'xplayer-pl-parser.c',
  'xplayer-pl-parser-lines.c',
  'xplayer-pl-parser-misc.c',
  'xplayer-pl-parser-pls.c',
  'xplayer-pl-parser-podcast.c',
  'xplayer-pl-parser-qt.c',
  'xplayer-pl-parser-smil.c',
  'xplayer-pl-parser-videosite.c',
  'xplayer-pl-parser-wm.c',
  'xplayer-pl-parser-xspf.c',
  'xplayer-pl-parser-amz.c',
  'xplayer-pl-playlist.c',
]

mini_symbol_map = 'plparser-mini.map'
mini_symbol_link_args = '-Wl,--version-script,@0@/@1@'.format(meson.current_source_dir(), mini_symbol_map)

plparser_mini_lib = library('xplayer-plparser-mini',
                            plparser_mini_sources,
                            xplayer_pl_parser_builtins, features_h,
                            include_directories: [config_inc, xplayerlib_inc],
                            c_args: plparser_cflags + ['-DXPLAYER_PL_PARSER_MINI'],
                            dependencies: gio_dep,
                            link_args : mini_symbol_link_args,
                            link_with: xplayer_glibc_lib,
                            link_depends : mini_symbol_map,
                            version: plparse_libversion,
                            install: true)

if have_quvi
  executable('xplayer-pl-parser-videosite',
             'videosite-parser.c', xplayer_pl_parser_builtins_h,
             c_args: '-DLIBEXECDIR="@0@"'.format(libexecdir),
             include_directories: [config_inc, xplayerlib_inc],
             dependencies: [quvi_dep, glib_dep],
             install_dir: join_paths(libexecdir),
             install: true)
endif

# Introspection
if not meson.is_cross_build()
  gnome.generate_gir(plparser_lib,
                     sources: plparser_public_headers + plparser_sources + [
                       xplayer_pl_parser_marshalers[1],
                       xplayer_pl_parser_builtins_h,
                       features_h,
                     ],
                     namespace: 'XplayerPlParser',
                     nsversion: '1.0',
                     identifier_prefix: 'XplayerPl',
                     symbol_prefix: 'xplayer_pl',
                     includes: ['GObject-2.0', 'Gio-2.0'],
                     extra_args: ['--identifier-prefix=XplayerDisc',
                                  '--symbol-prefix=xplayer_disc',
                                  '--identifier-prefix=XplayerCd',
                                  '--symbol-prefix=xplayer_cd',
                                  '--quiet'],
                     install: true)
endif

subdir('tests')
