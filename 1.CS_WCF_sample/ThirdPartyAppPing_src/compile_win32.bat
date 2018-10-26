call %windir%\Microsoft.NET\Framework\v4.0.30319\msbuild.exe ThirdPartyAppPing.sln

del /Q ThirdPartyAppPing\bin\Debug\*.pdb
del /Q ThirdPartyAppPing\bin\Debug\*.xml
del /Q ThirdPartyAppPing\bin\Debug\*.config

xcopy /Q /E /Y ThirdPartyAppPing\bin\Debug ..\zipcontents\bin