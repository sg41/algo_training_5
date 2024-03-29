#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

struct Info {
  long votes = 0;
  long bribe = 0;
  int number = 0;
  long new_votes = 0;
  long long votes_to_buy = 0;
};

std::pair<long long, int> calc_number(const std::vector<Info>& partys,
                                      long votes, int party_number) {
  long res = 0, count = 0;
  long need_votes = votes - partys[party_number].votes + 0;
  for (int i = 0; i < partys.size(); i++) {
    if (i == party_number) {
      count++;
      continue;
    }
    if (partys[i].votes > partys[party_number].votes + res) {
      // res += partys[i].votes - partys[party_number].votes - res;
      res += (partys[i].votes - votes) > 0 ? partys[i].votes - votes + 1 : 1;
      //!  : need_votes;
      count++;
    } else if (partys[i].votes == partys[party_number].votes + res) {
      res += 1;
      count++;
    } else {
      break;
    }
  }

  return std::make_pair(res, count);
}
std::pair<long long, int> l_bin_search_votes(const std::vector<Info>& partys,
                                             int party_number,
                                             bool calc_new_votes = false) {
  int start = 0, end = partys[0].votes + 1;
  long long votes_to_buy = 0;
  long long prev_votes = 0;
  int partys_to_buy = 0;
  while (start < end) {
    int mid = (start + end) / 2;
    std::tie(votes_to_buy, partys_to_buy) =
        calc_number(partys, mid, party_number);
    if (partys[party_number].votes + votes_to_buy < mid + 1) {
      end = mid - 1;
    } else if (partys[party_number].votes + votes_to_buy == mid + 1) {
      break;
    } else {
      start = mid + 1;
    }
    // if (votes_to_buy == prev_votes) {
    //   break;
    // } else {
    //   prev_votes = votes_to_buy;
    // }
  }
  return std::make_pair(votes_to_buy, partys_to_buy);
}

bool calc_new_votes(std::vector<Info>& partys, long long& bribe,
                    int party_number, int partys_to_buy) {
  long long paid = bribe - partys[party_number].bribe;
  long long my_party_votes = partys[party_number].votes + paid;
  int start = 0;
  if (party_number == 0) {
    start = 1;
  }

  partys[party_number].new_votes = my_party_votes;
  int parts = partys_to_buy == 0 ? 1 : partys_to_buy;
  if (party_number < partys_to_buy && partys_to_buy > 1) {
    parts = partys_to_buy - 1;
  }
  for (int i = start; i < partys_to_buy; i++) {
    if (i == party_number) {
      continue;
    }
    partys[i].new_votes = partys[i].votes - (paid) / parts;
  }
  partys[start].new_votes -= paid - ((paid) / parts) * parts;

  return paid + partys[party_number].bribe <= bribe;
}

std::pair<long long, long> bribe_elections(std::vector<Info>& partys,
                                           long long total_votes,
                                           long long max_bribe) {
  long long total_bribe = total_votes + max_bribe + 1;
  long party_number = 0;
  long partys_to_buy = 0;

  for (int i = 0; i < partys.size(); i++) {
    if (partys[i].bribe > 0) {
      long long bribe, to_buy;
      std::tie(bribe, to_buy) = l_bin_search_votes(partys, i);
      bribe += partys[i].bribe;
      if (bribe < total_bribe) {
        total_bribe = bribe;
        party_number = i;
        partys_to_buy = to_buy;
      }
    }
  }
  calc_new_votes(partys, total_bribe, party_number, partys_to_buy);
  return std::make_pair(total_bribe, partys[party_number].number);
}

int main(void) {
  long n;
  std::cin >> n;

  std::vector<Info> partys(n);
  std::vector<Info> bribe_partys(n);
  long long total_votes = 0;
  long long max_bribe = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> partys[i].votes >> partys[i].bribe;
    partys[i].number = i;
    partys[i].new_votes = partys[i].votes;
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
  std::sort(partys.begin(), partys.end(),
            [](const Info& a, const Info& b) { return a.votes > b.votes; });

  std::tie(total_bribe, party_number) =
      bribe_elections(partys, total_votes, max_bribe);
  std::cout << total_bribe << "\n" << party_number + 1 << std::endl;

  std::sort(partys.begin(), partys.end(),
            [](const Info& a, const Info& b) { return a.number < b.number; });
  for (auto p : partys) {
    std::cout << p.new_votes << " ";
  }
  std::cout << std::endl;

  return 0;
}