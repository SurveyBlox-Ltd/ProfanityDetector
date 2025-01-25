/*
 * @fileProfanityDetector.cpp
 * 
 * @description Checks messages for profanity
 * 
 * @copyright SurveyBlox Ltd & Shayden Seymour
 */

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ios>

namespace BProfanity {
	namespace FileSystem {
		namespace SSTable {
			void write(const std::string& tablePath, const std::string& content) {
				std::ofstream dataStream(tablePath, std::ios::binary);
			}
		} // namespace SSTable

		void loadBlacklistsWordFile() {
			std::fstream fileStream;

			fileStream.open("data/blacklistedWords.txt");
		}
	} // namespace FileSystem

	bool check(std::string& content) {
		if (content.empty()) {
			return false;
		}

		std::transform(content.begin(), content.end(), content.begin(), ::tolower);
	}
}