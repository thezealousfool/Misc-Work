#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

double closest(std::vector<std::pair<int, int>>& v) {

	auto points_x = v;
	auto points_y = v;

	auto distance = [] (const decltype(v[0])& p1, const decltype(v[0])& p2) -> double {

		return std::sqrt(std::pow(p2.first - p1.first, 2) + std::pow(p2.second - p1.second, 2));
	};

	auto brute = [&distance, &points_x] (int start, int N) {

		double min_dist = distance(points_x[start], points_x[start + 1]);
		for(int i = start; i < N-1; ++i) {
			for(int j = i+1; j < N; ++j) {
				double dist = distance(points_x[i], points_x[j]);
				if (dist < min_dist) min_dist = dist;
			}
		}
		return min_dist;
	};

	auto strip_closest = [&distance, &points_y] (decltype(v[0].first) mid_x, double d) {
		decltype(points_y) strip;
		for (auto point : points_y) {
			if (point.first <= (mid_x + d))
				strip.push_back(point);
		}
		for(int i = 0; i < strip.size() - 1; ++i) {
			for (int j = i+1; j < strip.size() && strip[j].second <= (strip[i].second + d); ++j)
				if (distance(strip[j], strip[i]) < d)
					d = distance(strip[j], strip[i]);
		}
		return d;
	};

	std::function<double (int, int)> solve_closest = [&brute, &solve_closest, &strip_closest, &points_x, &points_y] (int start, int N) { 

		if (N <= 3)
			return brute(start, N);
		else {
			int mid = N / 2;
			double d_left = solve_closest (start, mid);
			double d_right = solve_closest (start + mid, N - mid);
			double d = d_left < d_right ? d_left : d_right;
			d = strip_closest (mid, d);
			return d;
		}
		return 0.0;
	};

	std::sort (points_x.begin(), points_x.end(), [](const decltype(v[0])& p1, const decltype(v[0])& p2) {

		return p2.first < p1.first;
	});

	std::sort (points_y.begin(), points_y.end(), [](const decltype(v[0])& p1, const decltype(v[0])& p2) {

		return p2.second < p1.second;
	});	

	return solve_closest (0, v.size());
}

int main() {

	std::vector<std::pair<int, int>> P = { {0,0} , {0,3} , {3,4} , {2,0} , {2,1} };
	std::cout << "Smallest distance is: " << closest(P) << std::endl;
	return 0;
}