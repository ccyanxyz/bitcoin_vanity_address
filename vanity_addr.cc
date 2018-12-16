#include <bitcoin/bitcoin.hpp>
#include <random>
#include <iostream>

std::string search_str = "1cyan";

bc::ec_secret random_secret(std::default_random_engine& engine); 

std::string bitcoin_address(const bc::ec_secret& secret);

bool match_found(const std::string& address);

int main(int argc, char *argv[]) {

	if(argc < 2) {
		std::cerr << "Usage: ./vanity_miner <search_string>" << std::endl;
		return 1;
	}

	search_str = argv[1];

	std::cout << "Searching " << search_str << "..." << std::endl;

	std::random_device random;
	std::default_random_engine engine(random());

	while (true)
	{
		bc::ec_secret secret = random_secret(engine); 
		std::string address = bitcoin_address(secret);
		if (match_found(address))
		{
			std::cout << "Address: " << address << std::endl;
			std::cout << "PrivateKey: " << bc::wallet::ec_private(secret) << std::endl;
			break;
		} 
	}
	return 0; 
}

bc::ec_secret random_secret(std::default_random_engine& engine) {
		bc::ec_secret secret;
		for(uint8_t &byte: secret)
			byte = engine() % std::numeric_limits<uint8_t>::max(); 
		return secret;
}

std::string bitcoin_address(const bc::ec_secret& secret) {
	bc::wallet::ec_private private_key(secret);
	bc::wallet::payment_address payaddr(private_key);
	return payaddr.encoded();
}

bool match_found(const std::string& address) {
	auto addr_it = address.begin();
	for (auto it = search_str.begin(); it != search_str.end(); ++it, ++addr_it)
		if (*it != std::tolower(*addr_it)) return false;
	return true;
}
