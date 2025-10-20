//run game 

game: main.cpp Game.cpp Commodity.cpp PhysicalCommodities.cpp DigitalCommodities.cpp Harvest.cpp Gems.cpp Crypto.cpp
	@g++ main.cpp Game.cpp Commodity.cpp PhysicalCommodities.cpp DigitalCommodities.cpp Harvest.cpp Gems.cpp Crypto.cpp -o game
	@./game

 



