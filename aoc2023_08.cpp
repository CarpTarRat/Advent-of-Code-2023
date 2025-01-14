#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <numeric>

typedef std::map<std::string,std::pair<std::string,std::string>> Nodes;

template <typename T>
void print(T x){
    std::cout << x << "\n";
}

class Network{
    protected:
        std::string instruct {};
        Nodes nodes {};
        std::string current_node {};

        std::string load_instruct(std::istream& input){
            std::string result {};
            std::string line {};
            while(std::getline(input, line)){
                if (line == ""){
                    break;
                }
                result += line;
            }
            return result;
        }

        void read_node_line(std::stringstream& stream, Nodes& node){
            std::string word {};
            std::string node_name {};
            std::string l_node {};
            std::string r_node {};
            int i { 0 };
            while(stream >> word){
                if ( i == 0 ){
                    node_name = word;
                }
                else if ( i == 2){
                    l_node = word.substr(1,3);
                }
                else if (i == 3){
                    r_node = word.substr(0,3);
                }
                i += 1;
            }
            node[node_name] = { l_node, r_node };
        }

        Nodes load_nodes(std::istream& input){
            Nodes result {};
            std::string line {};
            std::stringstream stream {};
            while(std::getline(input, line)){
                std::stringstream stream { line };
                read_node_line(stream, result);
            }
            return result;
        }

    public:
        Network(std::istream& input)
            : instruct {load_instruct(input)}
            , nodes {load_nodes(input)}
            , current_node {"AAA"}
        {
        }

        void print_nodes(){
            Nodes::iterator it {};
            for (it = nodes.begin(); it != nodes.end(); it++){
                std::cout << it->first << ": " << it->second.first << "," << it->second.second << "\n";
            }
        }

        void print_instruct(){
            print(instruct);
        }

        void print_current_node(){
            print(current_node);
        }

        std::string get_current_node(){
            return current_node;
        }

        std::string choose_node(const char a, std::string& node){
            std::string next_node {};
            if (a == 'L'){
                next_node = nodes[node].first;
            }
            else if (a == 'R'){
                next_node = nodes[node].second;
            }
            return next_node;
        }

        void update_current_node(const char a){
            current_node = choose_node(a, current_node);
        }

        void run_instructions(bool check_zzz = false){
            static int run_count { 0 };
            for (int i = 0; i < instruct.size(); i++){
                update_current_node(instruct[i]);
                run_count += 1;
                if (check_zzz == true && current_node == "ZZZ"){
                    print(run_count);
                    break;
                }
            }
        }

        void find_zzz(){
            while (true){
                run_instructions(true);
                if (current_node == "ZZZ"){
                    break;
                }
            }
        }
};


class Network2 : public Network{
    private:
        std::vector<std::string> starting_nodes {};
        std::set<std::string> end_nodes {};

        std::vector<std::string> load_nodes(const char f){
            std::vector<std::string> result {};
            Nodes::iterator it {};
            for (it = nodes.begin(); it != nodes.end(); it++){
                std::string node {it->first};
                char final {node.back()};
                if (final == f){
                    result.push_back(node);
                }
            }
            return result;
        }

        std::set<std::string> load_end_nodes(){
            std::vector<std::string> v {load_nodes('Z')};
            std::set<std::string> result (v.begin(), v.end());
            return result;
        }

    public:
        Network2(std::istream& input)
            : Network(input)
            , starting_nodes {load_nodes('A')}
            , end_nodes {load_end_nodes()}
        {
        }

        void print_starting_nodes(){
            for ( int i = 0; i < starting_nodes.size(); i++){
                print(starting_nodes[i]);
            }
        }

        void print_end_nodes(){
            std::set<std::string>::iterator it {};
            for (it = end_nodes.begin(); it !=end_nodes.end(); it++){
                print(*it);
            }
        }

        bool check_all_end_nodes(){
            bool result {true};
            for (int i = 0; i < starting_nodes.size(); i++){
                if (!end_nodes.count(starting_nodes[i])){
                    result = false;
                    break;
                }
            }
            return result;
        }

        void update_starting_nodes(const char a){
            for (int i = 0; i < starting_nodes.size(); i ++){
                starting_nodes[i] = choose_node(a, starting_nodes[i]);
            }
        }

        void run_instructions_2(){
            static int run_count { 0 };
            for (int i = 0; i < instruct.size(); i++){
                update_starting_nodes(instruct[i]);
                run_count += 1;
                if (check_all_end_nodes()){
                    print(run_count);
                    break;
                }
            }
        }

        void find_end(){
            while (true){
                run_instructions_2();
                if (check_all_end_nodes()){
                    break;
                }
            }
        }

        int find_period(std::string& start){
            std::string node { start };
            int total_time { 0 };
            int j { 0 };
            std::set<std::pair<std::string,int>> end_visited {};
            std::pair<std::string,int> p {};
            while (true){
                for (int i = 0; i < instruct.size(); i++){
                    total_time += 1;
                    start = choose_node(instruct[i], start);
                    //std::cout << total_time << ": " << start << " " << i << " " << end_visited.size() <<"\n";
                    if (end_nodes.count(start)){
                        j = 1;
                        std::cout << total_time << ": " << start << " " << i << "\n";
                        p = {start, i};
                    }
                    if (end_visited.count(p) && j == 1){
                        j = 2;
                        break;
                    }
                    else{
                        if (j == 1){
                            end_visited.insert(p);
                            j = 0;
                        }
                    }
                }
                if (j == 2){
                    print("");
                    break;
                }
            }
            return total_time / 2;
        }

        void all_periods(){
            std::vector<int> periods {};
            for (auto x: starting_nodes){
                periods.push_back(find_period(x));
            }
            long long int lcm {1};
            for (long long x: periods){
                lcm = std::lcm(lcm, x);
                print(lcm);
            }
        }
};

void part1(){
    std::ifstream s {"input2023_08.txt"};
    std::istream& stream { s };
    Network network {s};
    network.print_instruct();
    network.print_nodes();
    network.find_zzz();
}

void part2(){
    std::ifstream s {"input2023_08.txt"};
    std::istream& stream { s };
    Network2 network {s};
    network.print_starting_nodes();
    print(" ");
    network.print_end_nodes();
    network.all_periods();
    //take lowest common multiple of result
}

int main(){
    part2();
    return 0;
}