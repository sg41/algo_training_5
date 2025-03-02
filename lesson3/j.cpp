#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Device {
  int number;
  std::vector<int> downloaded_parts;
  std::vector<int> value;
  int downloaded_parts_count;
};

struct Request {
  int from;
  int part;
  int value;
  int downloaded;
};

int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector<Device> devices(n);

  devices[0].number = 0;
  devices[0].downloaded_parts = std::vector<int>(k, 1);
  devices[0].value = std::vector<int>(n, 0);
  devices[0].downloaded_parts_count = k;
  for (int i = 1; i < n; ++i) {
    devices[i].number = i;
    devices[i].value = std::vector<int>(n, 0);
    devices[i].downloaded_parts = std::vector<int>(k, 0);
    devices[i].downloaded_parts_count = 0;
  }

  std::vector<int> time_slots_elapsed(n, 0);
  std::vector<int> parts_count_over_network(k, 1);

  int done = 0, timeslot = 1;
  while (done != n - 1 && timeslot < n * k) {
    std::map<int, std::vector<Request>> request_queue;
    // TODO: replace with O(1) algorithm
    // Update network parts count
    int min_downloads_number = n * k + 1;
    for (int i = 0; i < k; ++i) {
      //  detrminine minium downloaded part
      if (parts_count_over_network[i] < min_downloads_number) {
        min_downloads_number = parts_count_over_network[i];
      }
    }

    // create the request
    for (int i = 0; i < n; ++i) {  // i=request from
      if (devices[i].downloaded_parts_count == k) {
        continue;
      }

      // choose part to download
      int request_part = -1;
      for (int j = 0; j < k; ++j) {                 // Min number
        if (devices[i].downloaded_parts[j] == 0) {  // Absent
          if (request_part == -1 || parts_count_over_network[j] <
                                        parts_count_over_network[request_part])
            request_part = j;
          if (parts_count_over_network[j] <=
              min_downloads_number) {  // Least downloaded
            request_part = j;
            break;
          }
        }
      }

      // choose device to request
      int best_index = -1;
      int min_downloaded_parts = k + 1;
      for (int d = n - 1; d >= 0; d--) {                       // Min number
        if (devices[d].downloaded_parts[request_part] == 1) {  // Part present
          if (devices[d].downloaded_parts_count <=
              min_downloaded_parts) {  // Min downloaded parts
            min_downloaded_parts = devices[d].downloaded_parts_count;
            best_index = d;
          }
        }
      }
      request_queue[best_index].emplace_back(i, request_part,
                                             devices[best_index].value[i],
                                             devices[i].downloaded_parts_count);
      //   break;

    }  //  create request loop
    // accept request
    // std::cout << "Timeslot: " << timeslot << " " << std::endl;
    // std::cout << "----------------------" << std::endl;
    for (auto [request_to, request] : request_queue) {
      std::sort(request.begin(), request.end(), [](auto &a, auto &b) {
        if (a.value > b.value) {
          return true;
        } else if (a.value == b.value) {
          if (a.downloaded < b.downloaded) {
            return true;
          } else if (a.downloaded == b.downloaded) {
            return a.from < b.from;
          }
        }
        return false;
      });

      devices[request[0].from].downloaded_parts_count++;
      devices[request[0].from].downloaded_parts[request[0].part] = 1;
      devices[request[0].from].value[request_to]++;
      parts_count_over_network[request[0].part]++;

      // std::cout << "DeviceID:" << request[0].from + 1
      //           << ".Downloaded part:" << request[0].part + 1
      //           << " From DeviceID:" << request_to + 1 << ". Total:";
      // int id = 0;
      // for (auto p : devices[request[0].from].downloaded_parts) {
      //   std::cout << p;
      //   if (id++ != devices[request[0].from].downloaded_parts.size() - 1) {
      //     std::cout << ",";
      //   }
      // }
      // std::cout << std::endl;

      if (devices[request[0].from].downloaded_parts_count == k) {
        time_slots_elapsed[request[0].from] = timeslot;
        done++;
      }
    }
    timeslot++;
  }  // timeslot loop

  int i = 0;
  for (int slots : time_slots_elapsed) {
    if (i++ == 0) {
      continue;
    }
    std::cout << slots << " ";
  }
  std::cout << std::endl;

  return 0;
}
