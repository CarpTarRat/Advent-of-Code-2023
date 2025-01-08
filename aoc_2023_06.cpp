#include <iostream>
#include <vector>

const std::vector times {44, 80, 65, 72};
const std::vector time_test {7, 15, 30};
const std::vector distances {208, 1581, 1050, 1102};
const std::vector distance_test {9, 40, 200};

constexpr long long int time2 { 44806572 };
constexpr long long int distance2 { 208158110501102 };

template <typename T>
void print(const T x){
    std::cout << x << "\n";
}

template <typename T>
T dis_trav(const T button_time, const T race_time){
    T speed {button_time};
    T remaining_time {race_time - button_time};
    return speed * remaining_time;
}

template <typename T>
bool beat_record(const T time, const T distance, const T button_time){
    T boat_distance { dis_trav(button_time, time) };
    return (boat_distance > distance);
}

template <typename T>
T beat_record_num(const T time, const T distance){
    for (T i = 0; i < time; i++){
        if (beat_record(time, distance, i)){
            return time - 2 * i + 1;
        }
    }
}

template <typename T>
T part_1(const std::vector<T>& time, const std::vector<T>& distance){
    T result { 1 };
    T races { time.size() };
    for (T i = 0; i < races; i++){
        result *= beat_record_num(time[i], distance[i]);
        print(result);
    }
    return result;
}

int main(){
    print(part_1(time_test, distance_test));
    print(part_1(times, distances));
    print(beat_record_num(time2, distance2));
    return 0;
}