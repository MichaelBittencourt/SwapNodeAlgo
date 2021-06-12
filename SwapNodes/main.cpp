#include <bits/stdc++.h>
#include <map>
//#define DEBUG
//#define STRATEGY_1
//#define STRATEGY_2
//#define STRATEGY_3

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);
int amountOflevels = 0;
vector<list<int>> levelList(1024);

/*
 * Complete the 'swapNodes' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */
 
 
void printIndexes(vector<vector<int>> indexes) {
    int indexesSize = indexes.size();
    cout << "indexes.size() = " << indexesSize << endl;
    for(int i = 0; i < indexesSize; i++) {
        int tempIndexesSize = indexes[i].size();
        //cout << "indexes[" << i << "].size() = " << tempIndexesSize << endl;
        for (int j = 0; j < tempIndexesSize; j++) {
            cout << "indexes[" << i << "][" << j << "] = " << indexes[i][j] << " ";
        }
        cout << endl;
    }
}

void printQueries(vector<int> queries) {
    int size = queries.size();
    cout << "queries.size() = " << size << endl;
    for (int i = 0; i < size; i++) {
        cout << "queries[" << i << "] = " << queries[i] << endl; 
    }
}

void inOrderAcess(vector<vector<int>> indexes, vector<int> & ret, int & retPosition, int index) {
    if (index >= 0) {
        inOrderAcess(indexes, ret, retPosition, indexes[index][0] - 1);
        ret[retPosition++] = (index+1);
        inOrderAcess(indexes, ret, retPosition, indexes[index][1] - 1);
    }
}

void inOrderAcess(vector<vector<int>> indexes, vector<int> & ret) {
    int initialPosition = 0;
    inOrderAcess(indexes, ret, initialPosition, 0);
}

void addLevelOnTree(vector<vector<int>> & indexes, int index, int level) {
    if (index >= 0) {
        if (level > amountOflevels) {
            amountOflevels = level;
        }
        addLevelOnTree(indexes, indexes[index][0] - 1, level + 1);
        indexes[index].push_back(level);
        levelList[level-1].push_back(index);
        addLevelOnTree(indexes, indexes[index][1] - 1, level + 1);
    }
}

void addLevelOnTree(vector<vector<int>> & indexes) {
    addLevelOnTree(indexes, 0, 1);
    //printIndexes(indexes);
}

void swapInLevel(vector<vector<int>> & indexes, int node, int level, int querie) {
    if (node >= 0) {
        if (level % querie == 0) {
            int temp = indexes[node][0];
            indexes[node][0] = indexes[node][1];
            indexes[node][1] = temp;
        } 
        swapInLevel(indexes, indexes[node][0] - 1, level+1, querie);
        swapInLevel(indexes, indexes[node][1] - 1, level+1, querie);
    }
}

void swapInLevel(vector<vector<int>> & indexes, int querie) {
    for(int i = 0; i < indexes.size(); i++) {
        if (indexes[i][2] % querie == 0) {
            int temp = indexes[i][0];
            indexes[i][0] = indexes[i][1];
            indexes[i][1] = temp;           
        }
    }
}

void forInLevel(vector<vector<int>> & indexes, int querie) {
    //cout << "############### For in Level ######################" << endl;
    for(int i = querie; i <= amountOflevels; i+=querie) {
        //cout << "amountOfLevels = " << amountOflevels << endl;
        //cout << "querie = " << querie << endl;
        //cout << "i = " << i << endl;
        for(list<int>::iterator it = levelList[i-1].begin(); it != levelList[i-1].end(); it++) {
            //cout << "it = " << (*it) << endl;
            int temp = indexes[(*it)][0];
            indexes[(*it)][0] = indexes[(*it)][1];
            indexes[(*it)][1] = temp;
        }
    }
}

void singleSwap(vector<vector<int>> & indexes, int querie) {
#ifdef STRATEGY_1
    //cout << "############### Strategy 1 #################" << endl;
    swapInLevel(indexes, 0, 1, querie);
#else
#ifdef STRATEGY_2
    //cout << "############### Strategy 2 #################" << endl;
    swapInLevel(indexes, querie);
#else
    //cout << "############### Strategy 3 #################" << endl;
    forInLevel(indexes, querie);
#endif
#endif
    //printIndexes(indexes);
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    addLevelOnTree(indexes);
    vector<vector<int>> ret(queries.size());
    for(int i = 0; i < ret.size(); i++) {
        ret[i].resize(indexes.size());
        singleSwap(indexes, queries[i]);
        inOrderAcess(indexes, ret[i]);
    }
    return ret;
};

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> indexes(n);

    for (int i = 0; i < n; i++) {
        indexes[i].resize(2);

        string indexes_row_temp_temp;
        getline(cin, indexes_row_temp_temp);

        vector<string> indexes_row_temp = split(rtrim(indexes_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int indexes_row_item = stoi(indexes_row_temp[j]);

            indexes[i][j] = indexes_row_item;
        }
    }

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
