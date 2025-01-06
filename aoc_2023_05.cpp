#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <ctype.h>

typedef std::map<long long int, std::pair<long long int,long long int>> Map;

template <typename T>
void print(T x){
    std::cout << x << "\n";
}

long long int min(long long int x, long long int y){
    if (x < y){
        return x;
    }
    return y;
}

long long int find_map_interval(Map& map, long long int x){
    Map::iterator it {};
    long long int current {0};
    long long int right_end { 0 };
    for (it = map.begin(); it != map.end(); it ++){
        current = it->first;
        right_end = current + it->second.first - 1;
        if (x >= current && x <= right_end){
            return current;
        }
    }
    return -1;
}

bool in_interval(std::pair<long long int, long long int> pair, long long int x){
    if (x >= pair.first && x <= pair.second){
        return true;
    }
    return false;
}

long long int loc_inv(Map* map, long long int loc){
    Map::iterator it {};
    std::pair<long long int, long long int> interval {};
    for (it = (*map).begin(); it != (*map).end(); it++){
        interval = {it->second.second, it->second.second + it->second.first - 1};
        //std::cout << "(" << interval.first << "," << interval.second << ")" << "\n";
        if (in_interval(interval,loc)){
            return it->first + loc - interval.first;
        }
        else{
            continue;
        }
    }
    return loc;
}

class Almanac{
    private:   
        std::vector<long long int> seeds {};
        Map seed_soil {};
        Map soil_fert {};
        Map fert_water {};
        Map water_light {};
        Map light_temp {};
        Map temp_hum {};
        Map hum_loc {};
        std::vector<Map*> maps {};
        std::vector<std::pair<long long int, long long int>> seed_intervals {};

        Map produce_map(std::istream& input){
            Map map {};
            std::string line {};
            std::string word {};
            std::vector<long long int> numbers {};
            numbers.reserve(3);
            while(std::getline(input, line)){
                if (line == ""){
                    return map;
                }
                else if (!isdigit(line[0])){
                    continue;
                }
                std::stringstream s { line };
                while (s >> word){
                    numbers.push_back(std::stoll(word));
                }
                map[numbers[1]] = {numbers[2], numbers[0]};
                numbers.clear();
            }
            return map;
        }

        std::vector<long long int> read_seeds(std::istream& input){
            std::vector<long long int> seeds1 {};
            std::string line {};
            std::string word {};
            while (std::getline(input, line)){
                if (line == ""){
                    return seeds1;
                }
                std::stringstream s {line};
                while (s >> word){
                    if (word == "seeds:"){
                        continue;
                    }
                    seeds1.push_back(std::stoll(word));
                }
            }
            return seeds1;
        }
        
        std::vector<Map*> all_maps(){
            std::vector<Map*> maps {};
            maps.reserve(7);
            maps.push_back(&seed_soil);
            maps.push_back(&soil_fert);
            maps.push_back(&fert_water);
            maps.push_back(&water_light);
            maps.push_back(&light_temp);
            maps.push_back(&temp_hum);
            maps.push_back(&hum_loc);
            return maps;
        }

        std::vector<std::pair<long long int, long long int>> intervals(){
            std::vector<std::pair<long long int, long long int>> result {};
            for (int i = 0; i < seeds.size() / 2; i ++){
                result.push_back({seeds[2*i], seeds[2*i] + seeds[2*i + 1] - 1});
            }
            return result;
        }

    public:
        Almanac(std::istream& input)
            : seeds {read_seeds(input)}
            , seed_soil {produce_map(input)}
            , soil_fert {produce_map(input)}
            , fert_water {produce_map(input)}
            , water_light {produce_map(input)}
            , light_temp {produce_map(input)}
            , temp_hum {produce_map(input)}
            , hum_loc {produce_map(input)}
            , maps { all_maps() }
            , seed_intervals { intervals() }
        { 
        }

        long long int seed_index(int x){
            return seeds[x];
        }

        long long int seed_location(long long int number){
            long long int seed {number};
            long long int next_number { seed };
            long long int interval {};
            for (Map* map: maps){
                interval = find_map_interval(*map, next_number);
                if (interval == -1){
                    continue;
                }
                else{
                    next_number = (*map)[interval].second + next_number - interval;
                }
            }
            return next_number;
        }

        int number_of_seeds(){
            return static_cast<int> (seeds.size());
        }

        long long int loc_to_seed(long long int loc){
            long long int current_loc {loc};
            for (int i = 6; i >= 0; i--){
                current_loc = loc_inv(maps[i], current_loc);
                //print(current_loc);
            }
            return current_loc;
        }

        bool seed_in_intervals(long long int seed){
            for (std::pair<long long int, long long int> interval: seed_intervals){
                if (in_interval(interval, seed)){
                    return true;
                }
            }
            return false;
        }

        void print_seeds(){
            std::cout << "seeds: ";
            for (long long int i : seeds){
                std::cout << i << " ";
            }
            std::cout << "\n";
        }

        void print_seed_soil(){
            Map::iterator it {};
            for (it = seed_soil.begin(); it != seed_soil.end(); it++)
            {
                std::cout << it->first <<  ": " << it->second.second << "\n";
            }
        }

        void print_seed_intervals(){
            for (std::pair<long long int, long long int> x: seed_intervals){
                std::cout << "(" << x.first << "," << x.second << ")" << "\n";
            }
        }
};

long long int part_1(){
    std::ifstream s {"input2023_05.txt"};
    std::istream& stream { s };
    Almanac almanac {s};
    long long int min_seed_loc {almanac.seed_location(almanac.seed_index(0))};
    for (int i = 1; i < almanac.number_of_seeds(); i++){
        min_seed_loc = min(min_seed_loc, almanac.seed_location(almanac.seed_index(i)));
    }
    return min_seed_loc;
}

long long int part_2(){
    std::ifstream s {"input2023_05.txt"};
    std::istream& stream { s };
    Almanac almanac {s};
    long long int seed {almanac.loc_to_seed(331445006 / 2)};
    for (long long int i = 0; i < 331445006; i++){
        if (i % 1000000 == 0){
            print(i);
        }
        seed = almanac.loc_to_seed(i);
        if (almanac.seed_in_intervals(seed)){
            return i;
        }
    }
    return 0;
}

int main(){
    long long int result {part_2()};
    print(result);
    return 0;
}