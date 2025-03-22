# sfml

## circle-constraint
g++ *.cpp -o game -l sfml-system -l sfml-window -l sfml-graphics -L/opt/homebrew/opt/sfml@2/lib -I/opt/homebrew/opt/sfml@2/include
./game

## box2d-click-boxes
g++ *.cpp -o click-boxes -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lbox2d -L/opt/homebrew/opt/sfml@2/lib -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/box2d/lib -I/opt/homebrew/opt/box2d/include
./click-boxes

## grab-boxes
g++ *.cpp -o grab-boxes -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lbox2d -L/opt/homebrew/opt/sfml@2/lib -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/box2d/lib -I/opt/homebrew/opt/box2d/include
./grab-boxes

## collision-detection
g++ *.cpp -o collision-detection -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lbox2d -L/opt/homebrew/opt/sfml@2/lib -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/box2d/lib -I/opt/homebrew/opt/box2d/include
./collision-detection

https://box2d.org/documentation/hello.html