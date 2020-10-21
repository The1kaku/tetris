g++ -c *.cpp -lpdcurses -std=c++11
g++ -o main *.o -lpdcurses -std=c++11
rm -f *.o
start
