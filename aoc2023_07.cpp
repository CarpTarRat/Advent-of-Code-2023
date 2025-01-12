#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

constexpr int hand_size {5};

template <typename T>
void print(T x){
    std::cout << x << "\n";
}

int quick_pow10(int n)
{
    static int pow10[10] = {
        1, 10, 100, 1000, 10000, 
        100000, 1000000, 10000000, 100000000, 1000000000
    };

    return pow10[n]; 
}

class CardHand{
    protected:
        std::string card_string {};
        std::vector<int> hand_order {};
        std::map<int,int> hand {};
        int card_string_num {};

        int card_trans(const char card){
            if (card == 'A'){
                return 14;
            }
            else if (card == 'K'){
                return 13;
            }
            else if (card == 'Q'){
                return 12;
            }
            else if (card == 'J'){
                return 1; // 11 for part 1
            }
            else if (card == 'T'){
                return 10;
            }
            else{
                return card -'0';
            }
        }

        void init_hand(std::map<int,int>& map){
            for (int i = 1; i < 15; i++){
                map[i] = 0;
            }
        }

        void update_hand(std::map<int,int>& map, const char card){
            int card_num {card_trans(card)};
            map[card_num] += 1;
        }

        std::map<int,int> input_hand(const std::string& cards){
            std::map<int,int> map {};
            init_hand(map);
            for (int i = 0; i < hand_size; i++){
                update_hand(map, cards[i]);
            }
            return map;
        }

        std::vector<int> order(const std::string& cards){
            std::vector<int> hand_order {};
            for (int i = 0; i < hand_size; i++){
                int card_num {card_trans(cards[i])};
                hand_order.push_back(card_num);
            }
            return hand_order;
        }

        int card_str_to_num(){
            int num_str { 0 };
            for (int i = 0; i < hand_size; i++){
                num_str += quick_pow10(8 - 2 * i) * card_trans(card_string[i]);
            }
            return num_str;
        }

    public:
        CardHand(const std::string& cards, int i=0)
            : hand { input_hand(cards) }
            , hand_order { order(cards) }
            , card_string { cards }
            , card_string_num { card_str_to_num() }
        {
        }

        void print_hand(){
            std::map<int,int>::iterator it {};
            for ( it = hand.begin(); it != hand.end(); it++ ){
                if (it->second != 0){
                    std::cout << it->first << ": " << it->second << "\n";
                }
            }
        }

        void print_hand_string(){
            print(card_string);
        }

        int diff_card_num(){
            int count { 0 };
            std::map<int,int>::iterator it {};
            for ( it = hand.begin(); it != hand.end(); it++ ){
                if (it->second != 0 && it->first != 1){ // remove second condition for part 1
                    count += 1;
                }
            }
            return count;
        }

        int most_card_num(){
            int max { 0 };
            std::map<int,int>::iterator it {};
            for ( it = hand.begin(); it != hand.end(); it++ ){
                if (it->second > max && it->first != 1){ //remove second condition for part 1
                    max  = it->second;
                }
            }
            return max + hand[1]; //remove +hand[1] for part 1
        }

        int hand_type(){
            int diff_card {diff_card_num()};
            if (diff_card == 5){
                return 1;
            }
            else if (diff_card == 4){
                return 2;
            }
            else if (diff_card == 3){
                int most_card {most_card_num()};
                if (most_card == 2){
                    return 3;
                }
                else{
                    return 4;
                }
            }
            else if (diff_card == 2){
                int most_card {most_card_num()};
                if (most_card == 3){
                    return 5;
                }
                else{
                    return 6;
                }
            }
            else{
                return 7;
            }
        }

        int card_number(int i){
            return hand_order[i];
        }

        int card_str_num(){
            return card_string_num;
        }

        std::string get_hand_string(){
            return card_string;
        }

        friend bool operator== (const CardHand& x, const CardHand& y);
        friend bool operator< (const CardHand& x, const CardHand& y);
        
};

bool operator== (const CardHand& x, const CardHand& y){
        return (x.card_string == y.card_string);
}

//this comparison does not take into account hand type
bool operator< (const CardHand& x, const CardHand& y){
        return (x.card_string_num < y.card_string_num);
}

CardHand better_same_hand(CardHand& hand1, CardHand& hand2){
    int hand1_card {hand1.card_str_num()};
    int hand2_card {hand2.card_str_num()};
        if (hand1_card > hand2_card){
            return hand1;
        }
        else if (hand2_card > hand1_card){
            return hand2;
        }
        else{
            return hand1;
        }
}

CardHand better_hand(CardHand& hand1, CardHand& hand2){
    int hand1_type {hand1.hand_type()};
    int hand2_type {hand2.hand_type()};
    if (hand1_type = hand2_type){
        return better_same_hand(hand1, hand2);
    }
    else if (hand1_type > hand2_type){
        return hand1;
    }
    else{
        return hand2;
    }
}

class CamelCards{
    private:
        std::vector<CardHand> hands {};
        std::map<std::string,int> bets {};

        void convert_input(std::istream& input){
            std::string line {};
            std::string word {};
            std::string hand {};
            while(std::getline(input, line)){
                int i = 0;
                std::stringstream s {line};
                while(s >> word){
                    if (i == 0){
                        hand  = word;
                        hands.push_back(CardHand(word));
                        i = 1;
                    }
                    else if (i == 1){
                        bets[hand] = std::stoi(word); 
                    }
                }
            }
        }

    public:
        CamelCards(std::istream& input)
        : hands {}
        , bets {}
        {
            convert_input(input);
        }

        void print_hands(){
            std::vector<CardHand>::iterator it {};
            for (it = hands.begin(); it != hands.end(); it++){
                it->print_hand_string();
            }
        }

        void sort_hands(){
            std::vector<CardHand>::iterator it {};
            std::vector<std::vector<CardHand>> hand (7);
            for (it = hands.begin(); it != hands.end(); it ++){
                hand[it->hand_type() - 1].push_back(*it);
            }
            std::vector<CardHand> result {};
            for (int i=0; i<7; i++){
                std::sort(hand[i].begin(), hand[i].end());
                result.insert( result.end(), hand[i].begin(), hand[i].end() );
            }
            hands = result;
        }

        int total_winnings(){
            int size { hands.size() };
            int result { 0 };
            for (int i = 0; i < size; i++){
                result += (i+1) * bets[hands[i].get_hand_string()];
            }
            return result;
        }
};


void part1(){
    std::ifstream ifs {"input2023_07.txt"};
    std::istream& stream { ifs };
    CamelCards camel_cards {stream};
    camel_cards.sort_hands();
    camel_cards.print_hands();
    print(camel_cards.total_winnings());
}

void test2(){
    CardHand hand {"TTTJJ",1};
    hand.print_hand();
    print(hand.hand_type());
}

int main(){
    part1();
    return 0;
}