# sfml

g++ *.cpp -o game -l sfml-system -l sfml-window -l sfml-graphics -L/opt/homebrew/opt/sfml@2/lib -I/opt/homebrew/opt/sfml@2/include

g++ *.cpp -o box2d_hello -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lbox2d -L/opt/homebrew/opt/sfml@2/lib -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/box2d/lib -I/opt/homebrew/opt/box2d/include