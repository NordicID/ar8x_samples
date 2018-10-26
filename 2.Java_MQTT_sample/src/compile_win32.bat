del /f /q ..\zipcontents\bin\*.class
"%JAVA_HOME%\bin\javac" -cp ".;../zipcontents/lib/*" -d "../zipcontents/bin" src/*.java
pause