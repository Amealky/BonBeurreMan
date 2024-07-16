//
//  Utils.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//


#ifndef Utils_hpp
#define Utils_hpp


#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream> 
#include <iostream>
#include <filesystem>
#include <algorithm>

using namespace std;

static string executablePath = "";

void setExecutablePath(string path);
string getAssetDirectory();
bool randomChance(int X);
bool contains(const vector<string> list1, const vector<string> list2);
bool contains(const vector<string> list, string value);
vector<string> listFilesFrom(string directory, string fileExt);
vector<vector<string>> fileToArray(string filePath);

#endif
