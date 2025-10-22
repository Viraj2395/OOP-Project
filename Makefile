#builds the game
game: main.cpp Game.cpp Commodity.cpp PhysicalCommodities.cpp DigitalCommodities.cpp Harvest.cpp Gems.cpp Crypto.cpp
	@clang++ -std=c++17 -g main.cpp Commodity.cpp DigitalCommodities.cpp Game.cpp Gems.cpp Harvest.cpp PhysicalCommodities.cpp Crypto.cpp -o game
	@echo "Building and running the game..."

#runs the game
run: game
	@./game

#clean target
clean:
	@rm -f game *.o
	@echo "Build files removed."


 



