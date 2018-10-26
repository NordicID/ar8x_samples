#/bin/sh
rm -f ../zipcontents/bin/bin/*.class
~/java/bin/javac -cp ".:../zipcontents/lib/*" -d "../zipcontents/bin" src/*.java