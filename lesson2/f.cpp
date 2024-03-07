#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int calculateWinnings(int n, const vector<int>& sectors, int a, int b, int k) {
  int maxWinnings = 0;
  for (int initialVelocity = a; initialVelocity <= b; initialVelocity++) {
    int currentSector = 0;
    int currentVelocity = initialVelocity;
    int winnings = 0;
    while (true) {
      if (currentVelocity <= k) {
        break;
      }
      currentSector = (currentSector + currentVelocity) % n;
      winnings = max(winnings, sectors[currentSector]);
      currentVelocity -= k;
    }
    maxWinnings = max(maxWinnings, winnings);
  }
  return maxWinnings;
}

int main() {
  int n, a, b, k;
  cin >> n;
  vector<int> sectors(n);
  for (int i = 0; i < n; i++) {
    cin >> sectors[i];
  }
  cin >> a >> b >> k;
  cout << calculateWinnings(n, sectors, a, b, k) << endl;
  return 0;
}