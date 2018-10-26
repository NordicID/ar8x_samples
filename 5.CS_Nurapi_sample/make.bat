pushd nurapisample_src\ & call compile_win32.bat < nul & popd
..\tools\ar_signtool_cli\bin\ar_signtool_cli.exe zipcontents csnurapisample-Signed.zip
pause