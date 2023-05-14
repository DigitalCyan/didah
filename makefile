all: compile 

compile: assets
	make --directory build

assets: cmake
	cp -r assets build

cmake:
	cmake -B build -S .

clean:
	rm -rf build