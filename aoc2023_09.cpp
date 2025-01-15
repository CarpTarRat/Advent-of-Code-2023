#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

void print(int x){
    std::cout << x << "\n";
}

void print(std::vector<int> v){
    for (int x: v){
        std::cout << x << " ";
    }
    std::cout << "\n";
}

std::vector<int> next_line(const std::vector<int>& v){
    std::vector<int> result;
    for (int i=0; i < v.size() - 1; i++){
        result.push_back(v[i+1]-v[i]);
    }
    return result;
}

bool check_zero(const std::vector<int>& v){
    bool result { true };
    for (int i: v){
        if (i != 0){
            result = false;
            break;
        }
    }
    return result;
}

int process(const std::vector<int>& v){
    int result { v.back() };
    print(v);
    std::vector<int> next { next_line(v) };
    while ( !check_zero(next) ){
        //print(next);
        result += next.back();
        next = next_line(next);
    }
    return result;
}

int extrap_beginning(const std::vector<int> v){
    int result { 0 };
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit){
        result = *rit - result;
    }
    return result;
}

int process2(const std::vector<int>& v){
    std::vector<int> first_numbers {};
    first_numbers.push_back(v[0]);
    std::vector<int> next { next_line(v) };
    while ( !check_zero(next) ){
        first_numbers.push_back(next[0]);
        next = next_line(next);
    }
    return extrap_beginning(first_numbers);
}

std::vector<int> read_line(const std::string& line){
    std::vector<int> result {};
    std::stringstream stream { line };
    std::string number {};
    while (stream >> number){
        result.push_back(std::stoi(number));
    }
    return result;
}

void test(){
    std::vector<int> v {10, 13, 16, 21, 30, 45};
    print(process(v));
}

void test1(){
    std::vector<int> v {10, 13, 16, 21, 30, 45};
    print(process2(v));
}

void part1(){
    std::ifstream s {"input2023_09.txt"};
    std::istream& stream { s };
    std::string line { };
    std::vector<int> current_line {};
    int result { 0 };
    while (std::getline(stream, line)){
        current_line = read_line(line);
        result += process(current_line);
    }
    print(result);
}

void part2(){
    std::ifstream s {"input2023_09.txt"};
    std::istream& stream { s };
    std::string line { };
    std::vector<int> current_line {};
    int result { 0 };
    while (std::getline(stream, line)){
        current_line = read_line(line);
        result += process2(current_line);
    }
    print(result);
}

int main(){
    part2();
    return 0;
}
