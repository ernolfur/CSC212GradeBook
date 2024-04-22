#include "skip_list.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>

int main(int argc, char* argv[]){

    srand(static_cast<int>(time(nullptr)));
    //srand(static_cast<int>(1));

    //std::string file_name(argv[1]);
    std::string file_name("test.txt");

    SkipList* SL;
    std::vector<int> file_data;
    std::string line;

    std::ifstream file(file_name);

    std::string data;
    while(std::getline(file, data, ' ')){
        file_data.push_back(std::stoi(data));
    }

    if(file_data.size() == 0){
        SL = new SkipList();
    }else if (file_data.size() == 1){
        SL = new SkipList(file_data[0]);
    }else{
        SL = new SkipList(file_data);
    }
    SL->remove(52);
    std::cout<< SL->to_string() <<std::endl;
    std::cout<< SL->full_print() <<std::endl;
    return 0;
}