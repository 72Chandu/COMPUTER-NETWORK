/*
 (a) Implement 2- D Parity checker: (i) Take the following input : n bits data stream, m bits/block,
 (ii) Output: Transmitted data stream and Efficiency of the system.
 (b) Implement Checksum: (i) Take the following input : n bits data stream, m bits/block, (ii)
 Output: Checksum value and Efficiency of the system.
 (c) Implement CRC: (i) Take the following input : k bits data stream, n − k + 1 bits of pattern,
 (ii) Output: Transmitted data stream of length (n) and Efficiency of the system.
 (d) Implement Hamming Code: (i) Take the following input : n bits data stream,, (ii) Output:
 Transmitted data stream of length (n+r), where r bits of parity added with the transmitted data
 and Efficiency of the system.
 
*/
#include<bits/stdc++.h>
using namespace std;

// Function to calculate 2D Parity Check
void twoDParity(vector<string>& data) {
    int rows = data.size(), cols = data[0].size();
    vector<int> rowParity(rows, 0), colParity(cols, 0);
     
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rowParity[i] ^= (data[i][j] - '0');
            colParity[j] ^= (data[i][j] - '0');
        }
    }
    cout << "Transmitted Data with 2D Parity:\n";
    for (int i = 0; i < rows; i++) {
        cout << data[i] << " " << rowParity[i] << endl;
    }
    for (int j = 0; j < cols; j++) cout << colParity[j];
    cout << "\nEfficiency: " << (double)(rows * cols) / ((rows + 1) * (cols + 1)) << "\n";
}

// Function to calculate Checksum
void checksum(vector<string>& data) {
    int m = data[0].size(), sum = 0;
    for (auto &row : data) sum += stoi(row, nullptr, 2);
    int checksum = ~sum;
    cout << "Checksum Value: " << bitset<16>(checksum) << "\n";
    cout << "Efficiency: " << (double)(m * data.size()) / (m * (data.size() + 1)) << "\n";
}

// Function to calculate CRC
string xorStrings(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}
string divideCRC(string data, string poly) {
    int n = data.size(), k = poly.size();
    string dividend = data.substr(0, k);
    for (int i = k; i < n; i++) {
        if (dividend[0] == '1')
            dividend = xorStrings(dividend, poly) + data[i];
        else
            dividend = xorStrings(dividend, string(k, '0')) + data[i];
    }
    return (dividend[0] == '1') ? xorStrings(dividend, poly) : xorStrings(dividend, string(k, '0'));
}
void crc(string data, string poly) {
    string remainder = divideCRC(data + string(poly.size() - 1, '0'), poly);
    string transmitted = data + remainder;
    cout << "Transmitted Data: " << transmitted << "\nEfficiency: " << (double)data.size() / transmitted.size() << "\n";
}

// Function to calculate Hamming Code
void hammingCode(string data) {
    int n = data.size(), r = 0;
    while ((1 << r) < (n + r + 1)) r++;
    vector<int> encoded(n + r + 1, 0);
    for (int i = 0, j = 0; i < encoded.size(); i++) {
        if ((i & (i + 1)) == 0)
            continue;
        encoded[i] = data[j++] - '0';
    }
    for (int i = 0; i < r; i++) {
        int pos = (1 << i), val = 0;
        for (int j = pos - 1; j < encoded.size(); j += 2 * pos) {
            for (int k = 0; k < pos && j + k < encoded.size(); k++)
                val ^= encoded[j + k];
        }
        encoded[pos - 1] = val;
    }
    cout << "Transmitted Data: ";
    for (int i = 0; i < encoded.size(); i++) cout << encoded[i];
    cout << "\nEfficiency: " << (double)n / (n + r) << "\n";
}

int main() {
    vector<string> data = {"1101", "1011", "1001"};
    cout << "\n2D Parity Check:\n";
    twoDParity(data);
    cout << "\nChecksum:\n";
    checksum(data);
    cout << "\nCRC:\n";
    crc("11010011101100", "1011");
    cout << "\nHamming Code:\n";
    hammingCode("1011001");
    return 0;
}

