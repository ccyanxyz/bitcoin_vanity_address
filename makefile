vanity_miner:
	g++ -o vanity_miner vanity_addr.cc `pkg-config --libs --cflags libbitcoin` --std=c++11

clean:
	rm -rf a.out a.out* vanity_miner
