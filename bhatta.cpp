#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

typedef map<string, int> Histogram;

float mean(Histogram hist);
float bhatta(Histogram hist1, Histogram hist2);
vector<Histogram> reads_file(char* file_name);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "usage: <program> <instance_name>" << endl;

        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    vector<Histogram> histograms = reads_file(filename);

    vector<vector<float>> scores;

    for (int i=0; i<histograms.size(); i++)
    {
        vector<float> score;

        for (int j=0; j<histograms.size(); j++)
            score.push_back(bhatta(histograms[i], histograms[j]));

        scores.push_back(score);
    }

    for_each(scores.begin(), scores.end(), [](vector<float> score) 
        { 
            for_each(score.begin(), score.end(), [](float val) { cout << val << ' '; });
            cout << endl;
        }
    );
    
    return 0;
}

float mean(Histogram hist)
{
    float acc = 0;
    for (auto &pair : hist)
        acc += pair.second;
    
    return acc/hist.size();
}

float bhatta(Histogram hist1, Histogram hist2)
{
    float h1_ = mean(hist1);

    float h2_ = mean(hist2);

    float score = 0;

    // set of keys (features) that exist in both maps (histograms)
    set<string> keys;
    for (auto &pair : hist1)
        if (hist2.find(pair.first) != hist2.end())
            keys.insert(pair.first);

    for (auto &key : keys)
        score += sqrt(hist1.at(key) * hist2.at(key));

    // BUG (?): o valor calculado e passado pra esse `sqrt` mais externo é negativo, o que retorna um nan

    score = sqrt( 1 - ( 1 / sqrt(h1_ * h2_ * 8 * 8) ) * score );
    
    return score;
}

vector<Histogram> reads_file(char* file_name)
{
    vector<Histogram> instance;

    string line;
    ifstream file(file_name);
    if (file.is_open())
    {
        cout << "Started reading file" << endl;

        while (getline(file, line))
        {
            string entry;
            
            // ignore the first 2 entries (date and classification)
            istringstream iss(line);
            getline(iss, entry, ',');
            getline(iss, entry, ',');
            
            Histogram hist;
            
            while(!getline(iss, entry, ',').eof())
            {
                int split_pos = entry.find(':');

                string key = entry.substr(0, split_pos);
                string str_value = entry.substr(split_pos + 1);
                int value = stoi(str_value);

                hist.insert(std::pair<string,int>(key, value));              
            }

            instance.push_back(hist);
        }

        file.close();
    }

    cout << "Finished reading file" << endl;

    return instance;
} 