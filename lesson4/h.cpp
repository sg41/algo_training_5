#include <algorithm>
#include <iostream>
#include <vector>

struct Info {
  long votes;
  long bribe;
  int number;
};

bool calc_new_votes(const std::vector<Info>& partys, long long bribe,
                    int party_number, std::vector<long>& new_votes) {
  long long paid = 0;
  long long my_party_votes = partys[party_number].votes;
  int victory_size = -1;
  for (int i = 0; i < partys.size(); i++) {
    if (i == party_number) continue;
    if (partys[i].votes >= my_party_votes) {
      long votes_to_buy = (partys[i].votes - my_party_votes + 1) / 2 + 1;
      paid += votes_to_buy;
      my_party_votes += votes_to_buy;
      new_votes[partys[i].number] = partys[i].votes - votes_to_buy;
    } else {
      victory_size = my_party_votes - partys[i].votes;
      break;
    }
  }
  if (victory_size > 1) {
    new_votes[partys[0].number] += victory_size - 1;
    paid -= victory_size - 1;
    my_party_votes -= victory_size - 1;
  }
  new_votes[partys[party_number].number] = my_party_votes;
  return paid + partys[party_number].bribe <= bribe;
}

long long l_bin_search(const std::vector<Info>& partys, int party_number,
                       long long max_bribe, std::vector<long>& new_votes) {
  long long start = 0, end = max_bribe;
  while (start < end) {
    long long mid = (start + end) / 2;
    if (calc_new_votes(partys, mid, party_number, new_votes)) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return start;
}

std::pair<long long, long> bribe_elections(const std::vector<Info>& partys,
                                           std::vector<long>& new_votes,
                                           long long total_votes,
                                           long long max_bribe) {
  long long total_bribe = total_votes + max_bribe + 1;
  long party_number = 0;

  for (int i = 0; i < partys.size(); i++) {
    if (partys[i].bribe > 0) {
      long long bribe = l_bin_search(partys, i, max_bribe, new_votes);
      if (bribe < total_bribe) {
        total_bribe = bribe;
        party_number = i;
      }
    }
  }
  return std::make_pair(total_bribe, party_number);
}

int main(void) {
  long n;
  std::cin >> n;

  std::vector<Info> partys(n);
  std::vector<Info> bribe_partys(n);
  std::vector<long> new_votes(n);
  long long total_votes = 0;
  long long max_bribe = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> partys[i].votes >> partys[i].bribe;
    partys[i].number = i;
    new_votes[i] = partys[i].votes;
    total_votes += partys[i].votes;
    if (partys[i].bribe > 0) {
      bribe_partys[i] = partys[i];
      if (partys[i].bribe > max_bribe) {
        max_bribe = partys[i].bribe;
      }
    }
  }
  long long total_bribe = 0;
  long party_number = 0;
  auto sorted_partys = partys;
  std::sort(sorted_partys.begin(), sorted_partys.end(),
            [](const Info& a, const Info& b) { return a.votes > b.votes; });
  std::tie(total_bribe, party_number) =
      bribe_elections(sorted_partys, new_votes, total_votes, max_bribe);
  std::cout << total_bribe << "\n" << party_number + 1 << std::endl;
  for (auto v : new_votes) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  return 0;
}