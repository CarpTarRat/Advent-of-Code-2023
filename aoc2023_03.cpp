#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <ctype.h>
#include <algorithm>

typedef std::map<std::pair<int, int>, int> Dict;
typedef Dict::const_iterator It;

std::pair<int,int> add_pair(std::pair<int,int> x, std::pair<int,int> y){
    int z1 {x.first + y.first};
    int z2 {x.second + y.second};
    return {z1,z2};
}

void remove_duplicates(std::vector<int>& vec){
    std::unordered_set<int> s;
    for (int i : vec)
        s.insert(i);
    vec.assign( s.begin(), s.end() );
    sort( vec.begin(), vec.end() );
}

struct Engine
{
    std::vector<int> Numbers {};
    Dict position_Number_index {}; // index in Number for a digit in a particular position
    std::vector<std::pair<int,int>> symbol_position {}; 
    std::vector<char> symbol_list {};
    std::vector<std::pair<int,int>> neighbours {{1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1},{0,-1}, {1,-1}};

    void load_data(std::string file_name){
        std::ifstream input { file_name };
        std::string line {};
        int line_number { 0 };
        std::string current_number {};
        int current_number_int {};
        char current_char {};
        int number_index { 0 };
        while (std::getline(input, line)){
            for (int j = 0; j < line.length(); j++){
                current_char = line[j];
                if (isdigit(current_char)){
                    position_Number_index[{line_number, j}] = number_index; 
                    current_number += current_char;
                }
                else{
                    if (current_char == '.'){
                        if (current_number == ""){
                            continue;
                        }
                        else{
                            current_number_int = std::stoi(current_number);
                            Numbers.push_back(current_number_int);
                            current_number = "";
                            number_index += 1;
                        }
                    }
                    else{
                        symbol_position.push_back({line_number, j});
                        symbol_list.push_back(current_char);
                        if (current_number == ""){
                            continue;
                        }
                        else{
                            current_number_int = std::stoi(current_number);
                            Numbers.push_back(current_number_int);
                            current_number = "";
                            number_index += 1;
                        }
                    }
                }
            }
            if (current_number != ""){
                current_number_int = std::stoi(current_number);
                Numbers.push_back(current_number_int);
                current_number = "";
                number_index += 1;
            }
            line_number += 1;
        }
    }

    void print_numbers(){
        for (int i: Numbers){
            std::cout << i << "\n";
        }
    }

    void print_symbol_positions(){
        for (std::pair x: symbol_position){
            std::cout << '(' << x.first << "," << x.second << ")" << "\n";
        }
    }

    void print_position_number_index(){
        for (It it(position_Number_index.begin()); it != position_Number_index.end(); ++it){
            int i {it->first.first};
            int j {it->first.second};
            std::cout << "(" << i << "," << j << ")" << ": " << it->second << "\n";
        }
    }

    bool is_number(std::pair<int,int> x){
        It i {position_Number_index.find(x)};
        if (i == position_Number_index.end()){
            return false;
        }
        else{
            return true;
        }
    }

    void part_1(){
        std::pair<int,int> z {};
        int a {};
        std::vector<int> part_numbers {};
        for (std::pair x: symbol_position){
            for (std::pair y: neighbours){
                z = add_pair(x,y);
                It i {position_Number_index.find(z)};
                if (i == position_Number_index.end()){
                    continue;
                }
                else{
                    a = i->second;
                    part_numbers.push_back(a);
                }
            }
        }
        remove_duplicates(part_numbers);
        int result { 0 };
        for (int x: part_numbers){
            std::cout << Numbers[x] << "\n";
            result += Numbers[x];
        }
        std::cout << result << "\n";
    }

    void part_2(){
        int result { 0 };
        int product { 1};
        std::pair<int,int> z {};
        std::set<int> adjacent {};
        std::vector<int> part_numbers {};
        for (std::pair x: symbol_position){
            adjacent = {};
            for (std::pair y: neighbours){
                z = add_pair(x,y);
                It i {position_Number_index.find(z)};
                if (i == position_Number_index.end()){
                    continue;
                }
                else{
                    adjacent.insert(i->second);
                }
            }
            if (adjacent.size() == 2){
                product = 1;
                for (int x: adjacent){
                    product *= Numbers[x];
                }
                result += product;
            }
            //std::cout << "(" << x.first << "," << x.second << ")" << ": " << adjacent.size() << "\n";
        }
        std::cout << result << "\n";
    }
};

void test(){
    Engine a {};
    a.load_data("input2023_03.txt");
    a.part_2();
}


int main(){
    test();
    return 0;
}