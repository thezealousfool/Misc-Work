#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include "csv.h"

void load_name_map (std::unordered_map <int, std::string>& name_map) {
    io::CSVReader <2, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>> movies ("movie_ratings\\movies.csv");
    movies.read_header (io::ignore_extra_column, "movieId", "title");
    std::string name;
    int id;
    while (movies.read_row (id, name)) {
        name_map[id] = name;
    }
}

void load_rating_map (std::unordered_map <int, std::vector<std::pair <int, float>>>& rating_map) {
    io::CSVReader <3> ratings ("movie_ratings\\ratings.csv");
    ratings.read_header (io::ignore_extra_column, "userId", "movieId", "rating");
    int userId, movieId;
    float rating;
    while (ratings.read_row(userId, movieId, rating)) {
        rating_map[movieId].push_back (std::make_pair (userId, rating));
    }
}

auto find (std::unordered_map <int, std::vector<std::pair <int, float>>>& rating_map, int id) {
    for (const auto& e : rating_map) {
        if (e.first == id) {
            return e.second;
        }
    }
}

float get_pearson_score (std::vector<std::pair <int, float>>& movie1, std::vector<std::pair <int, float>>& movie2) {
    std::sort (movie1.begin(), movie1.end(), [](const std::pair <int, float>& p1, const std::pair <int, float>& p2) { return p1.first < p2.first; });
    std::sort (movie2.begin(), movie2.end(), [](const std::pair <int, float>& p1, const std::pair <int, float>& p2) { return p1.first < p2.first; });
    unsigned int pointer1 = 0, pointer2 = 0;
    float s_xiyi = 0.0, s_xi = 0.0, s_yi = 0.0, s_xi2 = 0.0, s_yi2 = 0.0;
    int n = 0;
    while (pointer1 < movie1.size() && pointer2 < movie2.size()) {
        if (movie1[pointer1].first == movie2[pointer2].first) {
            // std::cout << movie1[pointer1].first << " = " << movie1[pointer1].second << " " << movie2[pointer2].second << "\n";
            s_xi += movie1[pointer1].second;
            s_yi += movie2[pointer2].second;
            s_xiyi += movie1[pointer1].second * movie2[pointer2].second;
            s_xi2 += std::pow (movie1[pointer1].second, 2);
            s_yi2 += std::pow (movie2[pointer2].second, 2);
            ++n;
            ++pointer1; ++pointer2;
        }
        else if (movie1 [pointer1].first < movie2 [pointer2].first) {
            ++pointer1;
        }
        else {
            ++pointer2;
        }
    }
    // std::cout << " n = " << n << "\n s_xi = " << s_xi << "\n s_yi = " << s_yi << "\n s_xiyi = " << s_xiyi << "\n s_xi2 = " << s_xi2 << "\n s_yi2 = " << s_yi2 << "\n";
    if (n == 0)
        return 0.0;
    else if (std::abs((s_xi2 - (std::pow(s_xi,2) / (n*1.0)))*(s_yi2 - (std::pow(s_yi,2) / (n*1.0)))) <= 0.000001)
        return 0.0;
    else
        return n*(s_xiyi - (s_xi * s_yi / (n*1.0))) / std::sqrt((s_xi2 - (std::pow(s_xi,2) / (n*1.0)))*(s_yi2 - (std::pow(s_yi,2) / (n*1.0))));
}

void make_recommendations (std::unordered_map <int, std::string>& name_map, std::unordered_map <int, std::vector<std::pair <int, float>>>& rating_map, int no_of_recommendations) {
    std::cout << "Enter movie ID: ";
    int id;
    std::cin >> id;
    std::cout << "Recommendations for: " << name_map[id] << "\n";
    std::vector<std::pair <int, float>> recommendations;
    recommendations.reserve(rating_map.size() - 1);
    auto reference_movie = find(rating_map, id);
    for (auto& movie : rating_map) {
        if (movie.first != id) {
            recommendations.push_back(std::make_pair(movie.first, get_pearson_score(movie.second, reference_movie)));
        }
    }
    std::sort(recommendations.begin(), recommendations.end(), [](const auto& p1, const auto& p2) { return p1.second > p2.second; });
    for (auto e : recommendations) {
        if (!no_of_recommendations)
            break;
        std::cout << "Movie name: " << name_map[e.first] << "\n\t" << "Recommendation weight: " << e.second <<"\n";
        --no_of_recommendations;
    }
}

int main() {
    std::unordered_map <int, std::string> name_map;
    load_name_map (name_map);
    std::unordered_map <int, std::vector<std::pair <int, float>>> rating_map;
    load_rating_map (rating_map);
    make_recommendations (name_map, rating_map, 10);
    // auto movie1 = find(rating_map, 170);
    // auto movie2 = find(rating_map, 33836);
    // std::cout << get_pearson_score(movie1, movie2) << "\n";
    return 0;
}