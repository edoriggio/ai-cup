#include <vector>

using namespace std;


vector<vector<int> > m_transpose(vector<vector<int> > b) {
    vector<vector<int> > trans_vec(b[0].size(), vector<int>(b[0].size()));

    for (int i = 0; i < b.size(); i++) {
      for (int j = 0; j < b[i].size(); j++) {
        if (trans_vec[j].size() != b.size())
          trans_vec[j].resize(b.size());

        trans_vec[j][i] = b[i][j];
      }
    }

    return trans_vec;
}


vector<vector<int> > m_sum(vector<vector<int> > a, vector<vector<int> > b) {
  vector<vector<int> > result(a[0].size(), vector<int>(a[0].size()));

  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      result[i][j] = a[i][j] + b[i][j];
    }
  }

  return result;
}
