call %windir%\Microsoft.NET\Framework\v4.0.30319\msbuild.exe nurapisample.sln

del /Q nurapisample\bin\Debug\*.pdb
del /Q nurapisample\bin\Debug\*.xml
del /Q nurapisample\bin\Debug\*.config

xcopy /Q /E /Y nurapisample\bin\Debug ..\zipcontents\bin
pause