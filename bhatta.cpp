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
#include <algorithm>
#include <omp.h>

using namespace std;

typedef map<string, int> Histogram;

float mean(Histogram hist);
float bhatta(Histogram hist1, Histogram hist2);
pair<vector<Histogram>, vector<string>> reads_file(char* file_name);
int convert_date_to_int(string formatted_date);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "usage: <program> <instance_name>" << endl;
        return EXIT_FAILURE;
    }

    char *filename = argv[1];

    std::pair<vector<Histogram>, vector<string>> dataset = reads_file(filename);

    vector<Histogram> histograms = dataset.first;
    vector<string> classification = dataset.second;

    float** scores = (float**) malloc(histograms.size() * sizeof(float*));

    for (int i=0; i<histograms.size(); i++)
        scores[i] = (float*) malloc(histograms.size() * sizeof(float));

    #pragma omp parallel for
    for (int i=0; i<histograms.size(); i++) {
        for (int j=0; j<histograms.size(); j++)
            scores[i][j] = (bhatta(histograms[i], histograms[j]));
    }

    for (int i=0; i<histograms.size(); i++)
    {
        for (int j=0; j<histograms.size(); j++)
            cout << scores[i][j] << " ";

        cout << endl;
    }

    cout << "Done with " << filename << endl;

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
    float h1_mean = mean(hist1);

    float h2_mean = mean(hist2);

    float score = 0;

    // evaluate only keys present on both histograms
    for (auto &pair : hist1)
        if (hist2.find(pair.first) != hist2.end()) 
            score += sqrt(hist1.at(pair.first) * hist2.at(pair.first));            

    score = sqrt( 1 - ( 1 / sqrt(h1_mean * h2_mean * hist1.size() * hist2.size()) ) * score );

    return score;
}

pair<vector<Histogram>, vector<string>> reads_file(char* file_name)
{
    vector<Histogram> instance;
    vector<string> classification;

    string line;
    ifstream file(file_name);
    if (file.is_open())
    {
        cout << "Started reading file" << endl;

        while (getline(file, line))
        {
            Histogram hist;
            
            string entry;
            
            istringstream iss(line);

            getline(iss, entry, ',');
            // Ignoring date entry for now            
            //hist.insert(std::pair<string,int>("date", convert_date_to_int(entry)));

            getline(iss, entry, ',');
            classification.push_back(entry);
            
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

    return pair<vector<Histogram>, vector<string>>(instance, classification);
}

int convert_date_to_int(string formatted_date)
{
    string date;
    for (char c : formatted_date)
        if (c != '/') date += c;

    return stoi(date);
}
