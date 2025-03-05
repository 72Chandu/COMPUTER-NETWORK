/*Do the following task to implement the parity generator ( sender side) and parity Checker ( Receiver
 Side)—
 (a) At the sender side, the user would give the input of (n − 1) bits data and types of parity
 required i.e. even or odd parity.
 (b) System would generate the n bits data ( including the parity bit ) .
 (c) At the receiver end, the user would give a n bits received data as input along with the kind
 of parity used in the system.
 (d) System would show if there is any error or not. If the error is there error message would be
 shown accordingly. If there is no such error, print the correct (n − 1) bits data.
*/
#include <iostream>
using namespace std;

// Function to calculate parity bit
char calculateParity(string data, string parityType) {
    int count = 0;
    for (char bit : data) {
        if (bit == '1') count++;
    }
    return (parityType == "even") ? ((count % 2 == 0) ? '0' : '1') : ((count % 2 == 0) ? '1' : '0');
}

// Function to check received data
bool checkParity(string receivedData, string parityType) {
    int count = 0;
    for (char bit : receivedData) {
        if (bit == '1') count++;
    }
    return (parityType == "even") ? (count % 2 == 0) : (count % 2 != 0);
}

int main() {
    int n;
    cout << "Enter number of bits (excluding parity bit): ";
    cin >> n;
    
    string data, parityType;
    cout << "Enter " << n << "-bit data: ";
    cin >> data;
    
    cout << "Enter parity type (even/odd): ";
    cin >> parityType;
    
    // Generate parity bit
    char parityBit = calculateParity(data, parityType);
    string transmittedData = data + parityBit;
    
    cout << "Transmitted data (with parity bit): " << transmittedData << endl;
    
    // Receiver side
    string receivedData;
    cout << "Enter received data: ";
    cin >> receivedData;
    
    cout << "Enter parity type used in system (even/odd): ";
    cin >> parityType;
    
    if (checkParity(receivedData, parityType)) {
        cout << "No error detected. Original data: " << receivedData.substr(0, n) << endl;
    } else {
        cout << "Error detected in received data!" << endl;
    }
    
    return 0;
}
/*
Example 1: Even Parity
Sender Side
Step 1: User inputs (n-1) bits of data.
Input: 1011 (4 bits)
Step 2: User selects even parity.
Step 3: Calculate the parity bit:
Number of 1s in 1011 = 3 (odd count).
Since we need even parity, add a 1 to make it even.
Parity bit = 1
Step 4: Transmitted data = 10111 (4-bit data + 1 parity bit).
Output at sender:
Transmitted data (with parity bit): 10111

Receiver Side
Step 5: Receiver gets 10111 as input.
Step 6: User specifies that even parity was used.
Step 7: Check the parity:
Number of 1s in 10111 = 4 (even count).
Since even parity is expected, there is no error.
Step 8: Extract and display original data: 1011.
Output at receiver:
✅ No error detected. Original data: 1011

Example 2: Odd Parity with Error
Sender Side
Input: 1101 (4 bits)
Parity type: Odd parity
Number of 1s in 1101 = 3 (already odd).
Parity bit = 0 (to keep it odd).
Transmitted data = 11010 (4-bit data + 1 parity bit).
Output at sender:
Transmitted data (with parity bit): 11010

Receiver Side (With Error)
Received data: 11000 (1 bit flipped by error).
Parity type: Odd parity.
Check parity:
Number of 1s in 11000 = 2 (even count).
But the system expects odd parity → Error detected!
Output at receiver:
❌ Error detected in received data!


*/
