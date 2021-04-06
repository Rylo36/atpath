g++ -c *.cpp atpath/*.cpp -g
g++ *.o -o atpath-demo -lsfml-graphics -lsfml-window -lsfml-system
rm *.o