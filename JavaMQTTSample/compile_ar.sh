#/bin/sh
rm -f ./bin/*.class
~/java/bin/javac -cp ".:./lib/*" -d "./bin" src/*.java