pushd NormaConfig\ & call compile_win32.bat < nul & popd
..\tools\ar_signtool_cli\bin\ar_signtool_cli.exe zipcontents NormaLLRPSample-Signed.zip
pause