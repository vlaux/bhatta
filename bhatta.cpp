#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>

using namespace std;

float mean(vector<int> hist);
float bhatt(vector<int> hist1, vector<int> hist2);

int main()
{
    std::vector<int> h1 { 1, 2, 3, 4, 5, 6, 7, 8 };
    std::vector<int> h2 { 6, 5, 4, 3, 2, 1, 0, 0 };
    std::vector<int> h3 { 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<int> h4 { 1, 2, 3, 4, 4, 3, 2, 1 };
    std::vector<int> h5 { 8, 8, 8, 8, 8, 8, 8, 8 };
    
    std::vector<vector<int>> h { h1, h2, h3, h4, h5 };

    std::vector<vector<float>> scores;

    for (int i=0; i<h.size(); i++)
    {
        vector<float> score;

        for (int j=0; j<h.size(); j++)
            score.push_back(bhatt(h[i], h[j]));

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

float mean(vector<int> hist)
{
    float acc = std::accumulate(hist.begin(), hist.end(), 0.0);
    return acc/hist.size();
}

float bhatt(vector<int> hist1, vector<int> hist2)
{
    float h1_ = mean(hist1);

    float h2_ = mean(hist2);
    
    float score = 0;

    for (int i=0; i<8; i++)
    {
        score += sqrt(hist1[i] * hist2[i]);
    }

    score = sqrt( 1 - ( 1 / sqrt(h1_ * h2_ * 8 * 8) ) * score );
    
    return score;
}
