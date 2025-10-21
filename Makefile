game: main.cpp Game.cpp Commodity.cpp PhysicalCommodities.cpp DigitalCommodities.cpp Harvest.cpp Gems.cpp Crypto.cpp
	@clang++ -std=c++17 -g main.cpp Commodity.cpp DigitalCommodities.cpp Game.cpp Gems.cpp Harvest.cpp PhysicalCommodities.cpp Crypto.cpp -o game
	@./game



