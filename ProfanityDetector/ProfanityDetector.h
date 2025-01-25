/*
 * @fileProfanityDetector.h
 * 
 * @description Checks messages for profanity
 * 
 * @copyright SurveyBlox Ltd & Shayden Seymour
 */

#ifndef B_PROFANITY_DETECTOR
#define B_PROFANITY_DETECTOR

#include <string>
#include <iostream>
#include <algorithm>

namespace BProfanity {
	/**
		* @brief Checks if the message contains a blacklisted word, returns true or false.
		* @param std::string content The message you want to check 
		*/
	bool check(std::string& content);
}

#endif // B_PROFANITY_DETECTOR