del /f /q bin\*.class
"%JAVA_HOME%\bin\javac" -cp ".;lib/*" -d "bin" src/*.java
pause