game: main.cpp Game.cpp Commodity.cpp PhysicalCommodities.cpp DigitalCommodities.cpp Harvest.cpp Gems.cpp Crypto.cpp
	@clang++ -std=c++17 -g Commodity.cpp DigitalCommodities.cpp Gems.cpp Harvest.cpp PhysicalCommodities.cpp Crypto.cpp Game.cpp main.cpp -o game
	@./game