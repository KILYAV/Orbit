g++ -g -O0 -std=c++20 main.cpp parser.cpp celestial.cpp orbit.cpp -I/glm/glm -o orbit
orbit.exe -g -b 3 -d 50 -s 500 -c -n nibiru -r 6378 -o -p 7000 -a 8000

