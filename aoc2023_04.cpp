#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <map>

template <typename T>
void print(std::vector<T> x){
    for (T y: x){
        std::cout << y << " ";
    }
    std::cout << "\n";
}

void print(int x){
    std::cout << x << "\n";
}

template <typename T>
bool in_vector(std::vector<T> v, T y){
    for (T x: v){
        if (x == y){
            return true;
        }
    }
    return false;
}

class Card{
    private:
        std::vector<int> m_winning{};
        std::vector<int> m_my_num{};
    
    public:
        Card(std::vector<int>& x, std::vector<int>& y)
            : m_winning { x }
            , m_my_num { y }
        {
        }

        void print_card(){
            std::cout << "Winning numbers: ";
            print(m_winning);
            std::cout << "My numbers: ";
            print(m_my_num);
        }

        int won(){
            int winning {0};
            for (int x: m_winning){
                if (in_vector(m_my_num, x)){
                    winning += 1;
                }
            }
            return winning;
        }
        
        int points(){
            int winning { won () };
            if (winning == 0){
                return 0;
            }
            else{
                winning -= 1;
                return 1 << winning;
            }
        }
};

Card read_line(std::stringstream& s){
    int i { 0 }; // change to 1 when reading my numbers
    std::vector<int> winning {};
    std::vector<int> my_num {}; 
    std::string word {};
    while (s >> word){
        char back { word.back() };
        if (word == "|"){
            i = 1;
        }
        else if (isdigit(word[0]) && back != ':'){
            if (i == 0){
                winning.push_back(std::stoi(word));
            }
            else if (i == 1){
                my_num.push_back(std::stoi(word));
            }
        }
        else{
            continue;
        }
    }
    return Card(winning, my_num);
}

std::vector<Card> read_file(std::string file){
    std::vector<Card> data {};
    std::ifstream input { file };
    std::string line {};
    while (std::getline(input, line)){
        std::stringstream s { line };
        Card test {read_line(s)};
        data.push_back(test);
    }
    return data;
}

void test(){
    std::ifstream input {"input2023_04.txt"};
    std::string line {};
    while (std::getline(input, line)){
        std::stringstream s { line };
        Card test {read_line(s)};
        test.print_card();
        int result ( test.points() );
        print(result);
    }
}

void part_1(){
    int points { 0 };
    int x { 0 };
    std::vector<Card> data {read_file("input2023_04.txt")};
    std::cout << data.size() << "\n";
    for (Card c: data){
        c.print_card();
        x = c.points();
        print(x);
        points += x;
    }
    print(points);
}

void add_cards(std::map<int,int>& all_cards, int pos, int won){
    if (won > 0){
        for (int i = pos + 1; i < 219 && i < pos + won + 1; i++){
            all_cards[i] += all_cards[pos];
        }
    }
}

void part_2(){
    int result { 0 };
    std::vector<Card> data {read_file("input2023_04.txt")};
    std::cout << data.size() << "\n";
    std::map<int,int> all_cards {};
    for (int i = 0; i < 218; i++){
        all_cards[i] = 1;
    }
    for (int i = 0; i < 218; i++){
        add_cards(all_cards, i, data[i].won());
    }
    for (int i = 0; i < 218; i++){
        result += all_cards[i];
        std::cout << "Card " << i+1 << " " << "Won: " << data[i].won() << "\n";
        print(all_cards[i]);
    }
    print(result);
}

int main(){
    part_2();
    return 0;
}