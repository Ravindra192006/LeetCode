class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x,
                             vector<int>& queries) {

        int m = queries.size();
        vector<int> ans(m);

        vector<pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());
        sort(logs.begin(), logs.end(),
             [](auto &a, auto &b) {
                 return a[1] < b[1];
             });

        vector<int> cnt(n + 1, 0);

        int left = 0, right = 0;
        int active = 0;

        for (auto [time, idx] : q) {

            while (right < logs.size() && logs[right][1] <= time) {
                int id = logs[right][0];

                if (cnt[id] == 0)
                    active++;

                cnt[id]++;
                right++;
            }

            while (left < right && logs[left][1] < time - x) {
                int id = logs[left][0];

                cnt[id]--;

                if (cnt[id] == 0)
                    active--;

                left++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};