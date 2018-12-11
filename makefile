all: PokerRNG.so

srcs=decentralized_rng_dll.cpp modules/sfmt.cpp modules/keccak.cpp
args=-DSFMT_MEXP=19937 -std=c++1z -Wall -Wextra -Wpedantic ${srcs}

PokerRNG.so: ${srcs}
	echo "int main(){}" | g++ -o /dev/null -x c++ ${args} -
	g++ ${args} -shared -fPIC -o PokerRNG.dll
