/*
 * proto_benchmark_main.cc
 *
 *  Created on: Mar 22, 2015
 *      Author: "enjolras"
 */

#include <iostream>
#include <fstream>
#include <google_speed.pb.h>
#include <google_size.pb.h>
#include "Time_Test.h"
using namespace std;

template<typename MSG, int Time>
void benchmark(string &content, const string &msg_type) {
	int repeat = Time;
	size_t file_len = content.size();
	double total_size = (double(repeat) * file_len) / (1024*1024);
	MSG msg;
	{
		char info[256] = {0};
		snprintf(info, sizeof(info), "deserialize %s %d times, total size : %f mb", msg_type.c_str(), repeat, total_size);
		Time_Test tester(info);
		for (int i = 0; i < repeat; ++i) {
			// deserialize
			if (!msg.ParseFromString(content)) {
				cerr << "Failed to parse speed message." << endl;
				return;
			}
		}
	}
	{
		char info[256] = {0};
		snprintf(info, sizeof(info), "serialize %s %d times, total size : %f mb", msg_type.c_str(), repeat, total_size);
		Time_Test tester(info);
		for (int i = 0; i < repeat; ++i) {
			// serialize
			msg.SerializeToString(&content);
		}
	}

}

int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (argc != 3) {
        cerr << "Usage:  " << argv[0] << " message_dat_file1 message_dat_file2" << endl;
        return -1;
    }

    ifstream file1(argv[1]);
    string content1;
    file1.seekg(0, std::ios::end);
    content1.reserve(file1.tellg());
    file1.seekg(0, std::ios::beg);
    content1.assign((std::istreambuf_iterator<char>(file1)), std::istreambuf_iterator<char>());

    benchmark<benchmarks::SpeedMessage1, 1000000>(content1, "speed msg1");
    benchmark<benchmarks::SizeMessage1, 1000000>(content1, "size msg1");

    ifstream file2(argv[2]);
	string content2;
	file2.seekg(0, std::ios::end);
	content2.reserve(file2.tellg());
	file2.seekg(0, std::ios::beg);
	content2.assign((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());

	benchmark<benchmarks::SpeedMessage2, 3000>(content2, "speed msg2");
	benchmark<benchmarks::SizeMessage2, 3000>(content2, "size msg2");

    return 0;
}


