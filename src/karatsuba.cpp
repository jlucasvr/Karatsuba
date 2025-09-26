#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// --- Funções auxiliares ---
string soma_str(string str1, string str2) {
    string resultado = "";
    int carry = 0;
    int n1 = str1.size();
    int n2 = str2.size();
    int n = max(n1, n2);
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    for (int i = 0; i < n; i++) {
        int digit1 = (i < n1) ? (str1[i] - '0') : 0;
        int digit2 = (i < n2) ? (str2[i] - '0') : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        resultado.push_back((sum % 10) + '0');
    }
    if (carry) resultado.push_back(carry + '0');
    reverse(resultado.begin(), resultado.end());
    return resultado;
}

string sub_str(string str1, string str2) {
    string resultado = "";
    int carry = 0;
    int n1 = str1.size();
    int n2 = str2.size();
    int n = max(n1, n2);
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    for (int i = 0; i < n; i++) {
        int digit1 = (i < n1) ? (str1[i] - '0') : 0;
        int digit2 = (i < n2) ? (str2[i] - '0') : 0;
        int diff = digit1 - digit2 - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        resultado.push_back(diff + '0');
    }
    while (resultado.length() > 1 && resultado.back() == '0')
        resultado.pop_back();
    reverse(resultado.begin(), resultado.end());
    return resultado;
}


string multKaratsuba(const string &x, const string &y);

string addZeros(const string &a, int n) {
    string res = a;
    res.append(n, '0');
    return res;
}

string multKaratsuba(const string &x, const string &y) {
    int n = max(x.size(), y.size());
    if (n <= 32) return multUsual(x, y); // caso base

    int m = n / 2;
    string a = (x.size() > m) ? x.substr(0, x.size() - m) : "0";
    string b = (x.size() > m) ? x.substr(x.size() - m) : x;
    string c = (y.size() > m) ? y.substr(0, y.size() - m) : "0";
    string d = (y.size() > m) ? y.substr(y.size() - m) : y;

    string ac = multKaratsuba(a, c);
    string bd = multKaratsuba(b, d);
    string ab = soma_str(a, b);
    string cd = soma_str(c, d);
    string abcd = multKaratsuba(ab, cd);
    string adbc = sub_str(sub_str(abcd, ac), bd);

    string part1 = addZeros(ac, 2 * m);
    string part2 = addZeros(adbc, m);
    string result = soma_str(soma_str(part1, part2), bd);

    int i = 0;
    while (i < result.size() - 1 && result[i] == '0') i++;
    return result.substr(i);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string num1, num2;
    cin >> num1 >> num2;   


    //int start = high_resolution_clock::now();
    string r2 = multKaratsuba(num1, num2);
    //string r2 = multUsual(num1, num2); 
    cout << r2 << "\n";


    return 0;
}
