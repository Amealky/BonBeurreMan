#include "Utils.hpp"

void setExecutablePath(string path) {
    executablePath = path;
} 

string getAssetDirectory() {
    std::filesystem::path fsFullPath = std::filesystem::absolute(executablePath);
    std::filesystem::path fsExecutablePath = fsFullPath.parent_path();
    return fsExecutablePath.string() + "/../../assets/";
}

bool randomChance(int X) {
    return (rand() % X) == 0;
}

bool contains(const vector<string> list1, const vector<string> list2) {
    for (const string item1 : list1) {
        for (const string item2 : list2) {
            if (item1 == item2) {
                return true;
            }
        }
    }
    return false;
}

bool contains(const vector<string> list, string value) {
    for(const string item : list) {
        if(item == value) {
            return true;
        }
    }
    return false;
}

vector<string> listFilesFrom(string directory, string fileExt) {
    vector<string> files;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == "."+fileExt) {
            files.push_back(entry.path().string());
        }
    }

    sort(files.begin(), files.end());

    return files;
}

vector<vector<string>> fileToArray(string filePath) {
    int x, y;
    
    fstream fin;
    

    stringstream iostr;
    

    string strBuf, strTmp;
    

    fin.open(filePath, fstream::in);
    
    if (!fin.is_open())
    {
        cerr << "Erreur de chargement du fichier : " + filePath << endl;
        exit(1);
    }
    
    vector<vector<string>> fileLines;
    vector<string> lines;

    while (!fin.eof())
    {
    
        getline(fin, strBuf);
        
        if (!strBuf.size())
            continue;

        iostr.clear();
        
        iostr.str(strBuf);
        
        lines.clear();
        
        while (true)
        {

            getline(iostr, strTmp, ' ');
            
            lines.push_back(strTmp.c_str());
            
            if (!iostr.good()) break;
        }
        
        if (lines.size())
            fileLines.push_back(lines);
        
    }
    
    fin.close();

    return fileLines;
}