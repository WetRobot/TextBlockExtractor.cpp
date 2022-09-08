
rm -rf bin
mkdir bin
mkdir bin/static

g++ -c src/main.cpp -o bin/main.o

g++ -c src/tbe/utils.cpp -o bin/static/utils.o
g++ -c src/tbe/store.cpp -o bin/static/store.o
g++ -c src/tbe/extract.cpp -o bin/static/extract.o

ar rcs bin/static/libtbe.a bin/static/utils.o bin/static/store.o bin/static/extract.o

g++ bin/main.o -Lbin/static -ltbe -o bin/lbe

./bin/lbe
