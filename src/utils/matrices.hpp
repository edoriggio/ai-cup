#include <vector>

using namespace std;


vector<vector<float> > m_transpose(vector<vector<float> > b) {
    vector<vector<float> > trans_vec(b[0].size(), vector<float>(b[0].size()));

    for (int i = 0; i < b.size(); i++) {
      for (int j = 0; j < b[i].size(); j++) {
        if (trans_vec[j].size() != b.size()) {
          trans_vec[j].resize(b.size());
        }

        trans_vec[j][i] = b[i][j];
      }
    }

    return trans_vec;
}


vector<vector<float> > m_sum(vector<vector<float> > a, vector<vector<float> > b) {
  vector<vector<float> > result(a[0].size(), vector<float>(a[0].size()));

  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      result[i][j] = a[i][j] + b[i][j];
    }
  }

  return result;
}
