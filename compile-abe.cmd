/* compile-abe.cmd -- Build Abe's Amazing Adventure on ArcaOS */
parse source . . script
scriptdir = filespec('D', script) || filespec('P', script)
logfile = scriptdir || 'compile-abe.log'

'set EMXOMFLD_TYPE=WLINK'
'set EMXOMFLD_LINKER=wl.exe'
'set EMXOMFLD_PRELINK=0'
'cd ' || scriptdir || 'src'
'make -f Makefile.os2 2>&1 | tee ' || logfile
say 'Build log: ' || logfile
