#builds the game
game: main.cpp Game.cpp Commodity.cpp PhysicalCommodities.cpp DigitalCommodities.cpp Harvest.cpp Gems.cpp Crypto.cpp
	@g++ -Wall -Werror -std=c++11 main.cpp Game.cpp Commodity.cpp PhysicalCommodities.cpp DigitalCommodities.cpp Harvest.cpp Gems.cpp Crypto.cpp -o game
	@echo "Building and running the game..."

#runs the game
run: game
	@./game

#clean target
clean:
	@rm -f game *.o
	@echo "Build files removed."


 



