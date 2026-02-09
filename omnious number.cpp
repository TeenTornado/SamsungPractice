/*
https://www.geeksforgeeks.org/samsung-interview-experience-set-40-campus-white-box-testing/
https://www.geeksforgeeks.org/samsung-rd-sri-noida-on-campus-interview-experience/
https://code.hackerearth.com/01ac52j?key=b462f0a802c8c1faf1d87f2b1353b9ce

Problem — Valid Product Numbers

Company A manufactures products numbered with positive integers.

However, the company considers some digits unlucky.
If any product number contains those unlucky digits k or more times in total, the product is discarded.

You are given:

A range of product numbers [L, R]

A list of forbidden digits

An integer K

A number is invalid if the total occurrences of all forbidden digits inside that number is ≥ K.

Your task is to count how many numbers in the range [L, R] are valid.

Input Format
L R K
N
d1 d2 d3 ... dN


L = starting number

R = ending number

K = maximum allowed occurrences (exclusive limit)

N = number of forbidden digits

d1...dN = forbidden digits (0–9)

Output

Print the count of valid numbers.

Example
Input
24 50 3
3
1 3 5

Output
26

Explanation

Forbidden digits = 1, 3, 5
K = 3 → if total count of these digits ≥ 3 → INVALID

We check each number from 24 → 50.

Example checks:

Number	Count of (1,3,5)	Valid?
24	0	✔
31	2 (3,1)	✔
33	2	✔
35	2	✔
111	3	❌ (≥3)

So only numbers where total occurrences reach 3 or more are removed.

Since range small → 26 valid numbers.

Understanding the Rule (VERY IMPORTANT)

We are NOT checking:

“digit appears 3 times individually”

We are checking:

total occurrences of all forbidden digits combined.

Example:

Forbidden: 1,3,5
K = 3

Number	Reason
111 → 3 forbidden digits → invalid	
113 → 3 forbidden digits → invalid	
135 → 3 forbidden digits → invalid	
331 → 3 forbidden digits → invalid	
11223 → (1,1,3) → 3 → invalid	
11222 → only two → valid	

This is exactly what the code was doing.

How to Solve (Idea)

For every number from L → R:

Break number into digits

Count frequency of each digit

Add counts of forbidden digits

If total ≥ K → reject

else → count it

No DP needed (constraints small in Samsung test).

Dry Run

Range: 24 to 129

Forbidden digits: 1,3,5
K = 3

Check 113:

Digits:
1 → count 2
3 → count 1

Total = 3 → INVALID

Check 11222:

1 → 2
3 → 0
5 → 0

Total = 2 → VALID
*/
MY CODE 

#include <bits/stdc++.h>
using namespace std;

bool isValid(long long num, vector<int>& bad, int k) {

    int freq[10] = {0};

    // count digits
    while(num > 0){
        freq[num % 10]++;
        num /= 10;
    }

    // count forbidden digits
    int total = 0;
    for(int d : bad){
        total += freq[d];
    }

    // invalid if >= k
    return total < k;
}

int main(){

    long long L, R;
    int K;
    cin >> L >> R >> K;

    int N;
    cin >> N;

    vector<int> bad(N);
    for(int i = 0; i < N; i++)
        cin >> bad[i];

    int validCount = 0;

    for(long long num = L; num <= R; num++){
        if(isValid(num, bad, K))
            validCount++;
    }

    cout << validCount;
    return 0;
}

/*
#include <iostream>
using namespace std;

int numberOminous(int a, int b, int k, int *delNos, int n){
    int count = 0;
    for(int i = a; i <= b; i++){
        int temp = i;
        int digitArray[10] = {0};

        while(temp){
            digitArray[temp%10]++;
            temp /= 10;
        }
        
        int rougeK = 0;
        for(int i=0; i<n; i++){
            rougeK += digitArray[delNos[i]];
        }

        if(rougeK < k){
            count++;
        }

    }
    return count;
}

int main() {
    int a, b, k;
    cin >> a >> b >> k;
    int n;
    cin >> n;
    int *delNos = new int[n];
    for(int i=0; i<n; i++){
        cin >> delNos[i];
    }

    cout << numberOminous(a, b, k, delNos, n) << "\n";

    return 0;
}
*/
