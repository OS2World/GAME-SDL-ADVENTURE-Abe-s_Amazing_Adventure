/* run-abe.cmd -- Launch Abe's Amazing Adventure from its own directory */
parse source . . script
scriptdir = filespec('D', script) || filespec('P', script)
logfile = scriptdir || 'run-abe.log'
'cd ' || scriptdir
'abe.exe --window 2>"' || logfile || '"'
say 'Run log: ' || logfile
