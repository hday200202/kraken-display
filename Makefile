all:
	@echo "building kraken-display..."
	g++ -Isrc -Iinc -ISFML/include -O3 -o bin/kraken-display src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -fexpensive-optimizations -ffast-math -march=native -flto -fopenmp
	./bin/kraken-display