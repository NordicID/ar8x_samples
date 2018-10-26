call %windir%\Microsoft.NET\Framework\v4.0.30319\msbuild.exe NormaConfig.sln

del /Q NormaConfig\bin\Debug\*.pdb
del /Q NormaConfig\bin\Debug\*.xml
del /Q NormaConfig\bin\Debug\*.config

xcopy /Q /E /Y NormaConfig\bin\Debug ..\zipcontents\bin
pause