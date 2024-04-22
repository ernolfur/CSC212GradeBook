#include "SkipList.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>

int main(int argc, char* argv[]){

    srand(static_cast<int>(time(nullptr)));
    //srand(static_cast<int>(1));

    SkipList<int>* SL;
    std::string file_name(argv[1]);
    //std::string file_name("test.txt");

    std::vector<int> file_data;
    std::string line;

    std::ifstream file(file_name);

    std::string data;
    while(std::getline(file, data, ' ')){
        file_data.push_back(std::stoi(data));
    }

    if(file_data.size() == 0){
        SL = new SkipList<int>();
    }else if (file_data.size() == 1){
        SL = new SkipList<int>(file_data[0]);
    }else{
        SL = new SkipList<int>(file_data);
    }
    std::cout<< SL->full_print() <<std::endl;
    SL->remove(52);
    std::cout<< "Removed 52" <<std::endl;
    std::cout<< "Final:\n";
    std::cout<< SL->to_string() <<std::endl;
    std::cout<< SL->full_print() <<std::endl;
    std::cout<< "No Crash" <<std::endl;
    return 0;
}
