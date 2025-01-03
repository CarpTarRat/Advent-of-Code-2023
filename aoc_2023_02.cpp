#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<ctype.h>

bool read(std::stringstream& s, int max_red, int max_green, int max_blue){
    std::string word;
    int word_count { 0 };
    int blue { 0 };
    int red { 0 };
    int green { 0 };
    int current_number { 0 };
    while(s >> word){
        word_count += 1;
        if ( word_count == 1 || word_count == 2 ){
            continue;
        }
        if ( word_count % 2 == 1){
            current_number = std::stoi(word);
        }
        else{
            char final_char { word.back() };
            if (final_char == ',' || final_char == ';'){
                word.pop_back();
            }
            if ( word == "blue" ){
                blue += current_number;
            }
            else if ( word == "green" ){
                green += current_number;
            }
            else if ( word == "red" ){
                red += current_number;
            }
            if (final_char != ','){
                //std::cout << "blue: " << blue << " " << "red: " << red << " " << "green: " << green << "\n";
                if (blue > max_blue || green > max_green || red > max_red){
                    return false;
                }
                else{
                    blue = 0;
                    green = 0;
                    red = 0;
                }
            }
        }
    }
    return true;
}

void part_1(){
    std::ifstream input { "input2023_02.txt" };
    std::string line;
    int game_number { 0 };
    int sum { 0 };
    while (std::getline(input, line)){
        game_number += 1;
        std::stringstream stream {line};
        if (read(stream, 12, 13, 14)){
            std::cout << "game " << game_number << " " << "True" << "\n";
            sum += game_number;
        }
    }
    std::cout << sum << "\n";
}

int read2(std::stringstream& s){
    std::string word;
    int word_count { 0 };
    int blue { 0 };
    int red { 0 };
    int green { 0 };
    int current_number { 0 };
    int max_red ( 0 );
    int max_green { 0 };
    int max_blue { 0 };
    while(s >> word){
        word_count += 1;
        if ( word_count == 1 || word_count == 2 ){
            continue;
        }
        if ( word_count % 2 == 1){
            current_number = std::stoi(word);
        }
        else{
            char final_char { word.back() };
            if (final_char == ',' || final_char == ';'){
                word.pop_back();
            }
            if ( word == "blue" ){
                blue += current_number;
            }
            else if ( word == "green" ){
                green += current_number;
            }
            else if ( word == "red" ){
                red += current_number;
            }
            if (final_char != ','){
                if (blue > max_blue){
                    max_blue = blue;
                }
                if (red > max_red){
                    max_red = red;
                }
                if (green > max_green){
                    max_green = green;
                }
                blue = 0;
                green = 0;
                red = 0;
            }
        }
    }
    int product { max_red * max_green * max_blue };
    std::cout << max_red << " " << max_green << " " << max_blue << " " << product <<" \n";
    return product;
}

void part_2(){
    std::ifstream input { "input2023_02.txt" };
    std::string line;
    int power_sum { 0 };
    while (std::getline(input, line)){
        std::stringstream stream {line};
        power_sum += read2(stream);
    }
    std::cout << power_sum << "\n";
}


int main(){
    part_1();
    part_2();
    return 0;
}