xplayer_glibc_sources = ['stub.c']

if not cc.has_function('asprintf')
  # FIXME: this is untested
  xplayer_glibc_sources += ['asprintf.c']
  cdata.set('asprintf', 'xplayer_private_asprintf')
else
  cdata.set('HAVE_ASPRINTF', true)
endif

xplayer_glibc_lib = static_library('xplayer_glibc',
                                 xplayer_glibc_sources,
                                 install: false)
