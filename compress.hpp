#ifndef COMPRESS
#define COMPRESS

#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <boost/math/cstdfloat/cstdfloat_types.hpp>

typedef boost::float32_t float32;


int compress(boost::dynamic_bitset<unsigned char>& input, boost::dynamic_bitset<unsigned char>& output){

	// std::cout << "\n" << "compressing..." << "\n";

	//reads bitset, reads the floats, converts to a short, stores the short.

	unsigned char *ptr;
	std::vector<unsigned char> data;

	int size = (input.num_blocks()/4);

	for (int i = 0; i < size; i++){

		std::bitset<32> bset;

		for (int x = 0; x < 32; x++){

			bset[x] = input[(i*32)+x];
		}

		float32 test;
		std::memcpy( &test, &bset, sizeof(boost::uint32_t));

		short reduced = (short)test;

		ptr = (unsigned char *)&reduced;
      	      for(int i = 0; i < 2; ++i){
		      data.push_back(*ptr);
		      ++ptr;
              }
	}

	output.init_from_block_range(data.begin(), data.end());

	// std::cout << "compressed size: "<< input.size()/(8e+6) << " mbs  new size: "<< output.size()/8e+6 << " mbs" << "\n";

	return true;
}

int decompress(boost::dynamic_bitset<unsigned char>& input, boost::dynamic_bitset<unsigned char>& output){

	//reads bitset, reads the shorts, converts to floats, stores the float back into the bitset.

	std::cout << "\n" << "decompressing..." << "\n";

	unsigned char *ptr;
	std::vector<unsigned char> data;

	int size = (input.num_blocks()/2);

	for (int i = 0; i < size; i++){

		std::bitset<16> bset;

		for (int x = 0; x < 16; x++){

			bset[x] = input[(i*16)+x];
		}

		short shrt;

		std::memcpy( &shrt, &bset, sizeof(boost::uint32_t));
		float32 value = (float32)shrt;

		boost::uint32_t original;
		std::memcpy( &original, &value, sizeof(boost::uint32_t));

		ptr = (unsigned char *)&original;
      	      for(int i = 0; i < 4; ++i){
		      data.push_back(*ptr);
		      ++ptr;
              }
	}

	output.init_from_block_range(data.begin(), data.end());

	// std::cout << "compressed size: "<< input.size()/(8e+6) << " mbs  new size: "<< output.size()/8e+6 << " mbs" << "\n";

	return true;
}

#endif
