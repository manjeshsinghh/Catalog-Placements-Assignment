#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;


ll baseToDecimal(const string& numStr, int base) {
    ll result = 0;
    for (char ch : numStr) {
        int digit;
        if (isdigit(ch)) digit = ch - '0';
        else digit = tolower(ch) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}

ll lagrangeInterpolation(const vector<pair<ll, ll>>& points) {
    long double result = 0.0;
    int k = points.size();

    for (int i = 0; i < k; ++i) {
        long double term = points[i].second;
        for (int j = 0; j < k; ++j) {
            if (i == j) continue;
            term *= -points[j].first / (double)(points[i].first - points[j].first);
        }
        result += term;
    }

    return ll(round(result));
}

ll shamirSecretSharing(map<string, map<string, string>> testCase) {
    int k = stoi(testCase["keys"]["k"]);
    vector<pair<ll, ll>> points;

    for (auto& [key, val] : testCase) {
        if (key == "keys") continue;

        ll x = stoll(key);
        int base = stoi(val.at("base"));
        string value = val.at("value");

        ll y = baseToDecimal(value, base);
        points.push_back({x, y});
    }

    // Generate all combinations of k points and count the most frequent result
    int n = points.size();
    vector<int> comb(n, 0);
    for (int i = 0; i < k; ++i) comb[i] = 1;

    map<ll, int> freq;

    do {
        vector<pair<ll, ll>> subset;
        for (int i = 0; i < n; ++i)
            if (comb[i]) subset.push_back(points[i]);

        ll secret = lagrangeInterpolation(subset);
        freq[secret]++;
    } while (prev_permutation(comb.begin(), comb.end()));


    ll correct = 0, maxFreq = 0;
    for (auto& [secret, count] : freq) {
        if (count > maxFreq) {
            maxFreq = count;
            correct = secret;
        }
    }

    return correct;
}

int main() {
    
    map<string, map<string, string>> test1 = {
        {"keys", {{"n", "4"}, {"k", "3"}}},
        {"1", {{"base", "10"}, {"value", "4"}}},
        {"2", {{"base", "2"}, {"value", "111"}}},
        {"3", {{"base", "10"}, {"value", "12"}}},
        {"6", {{"base", "4"}, {"value", "213"}}}
    };

    ll secret = shamirSecretSharing(test1);
    cout << secret << endl;

    return 0;
}
