#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

vector<float> loadFile(string fileName);
void takeLog(vector<float> &v);
float calcMean(vector<float> v);
float calcRange(vector<float> v);
float calcVariance(vector<float> v, float mean);
float calcSTD(float variance);
vector<float> pearCorrHelper(vector<float> v, float mean, float std);
float calcPearsonCorr(vector<float> vStdVals, vector<float> maStdVal);
int counter(vector<float> v);


int main()
{
    vector<float> vAdjClose = loadFile("V.csv");
    takeLog(vAdjClose);
    float vMean = calcMean(vAdjClose);
    float vSpread = calcRange(vAdjClose);
    float vVariance = calcVariance(vAdjClose, vMean);
    float vSTD = calcSTD(vVariance);
    cout << "V mean: " << fixed << setprecision(6) << vMean << endl;
    cout << "V spread: " << vSpread << endl;
    cout << "V variance: " << vVariance << endl;
    cout << "V STD: " << vSTD << endl;

    cout << endl ;

    vector<float> maAdjClose = loadFile("MA.csv");
    takeLog(maAdjClose);
    float maMean = calcMean(maAdjClose);
    float maSpread = calcRange(maAdjClose);
    float maVariance = calcVariance(maAdjClose, maMean);
    float maSTD = calcSTD(maVariance);
    cout << "MA mean: " << maMean << endl;
    cout << "MA spread: " << maSpread << endl;
    cout << "MA variance: " << maVariance << endl;
    cout << "MA STD: " << maSTD << endl;

    vector<float> vStdVal = pearCorrHelper(vAdjClose, vMean, vSTD);
    vector<float> maStdVal = pearCorrHelper(maAdjClose, maMean, maSTD);
    float corr = calcPearsonCorr(vStdVal, maStdVal);
    cout << "Correlation between V and MA: " << corr << endl;

    int vCount = counter(vAdjClose);
    int maCount = counter(maAdjClose);
    cout << "v count: " << vCount << endl;
    cout << "ma count: " << maCount << endl;
    return 0;
}

vector<float> loadFile(string fileName)
{
    ifstream infile(fileName);

    if (!infile.is_open())
        cout << "ERROR: File Open" << '\n';

    vector<float> adj_close;
    string date;
    string open;
    string high;
    string low;
    string close;
    string adjClose;
    string volume;

    getline(infile, date, '\n'); // skips first line which are the labels

    while (infile.peek() != EOF)
    {

        getline(infile, date, ',');
        cout << "date: " << date << endl;
        getline(infile, open, ',');
        getline(infile, high, ',');
        getline(infile, low, ',');
        getline(infile, close, ',');
        getline(infile, adjClose, ',');
        getline(infile, volume, '\n');

        
        adj_close.push_back(stof(adjClose));
    }

    for (int i = 0; i < adj_close.size(); i++)
    {
        cout << "Adj Values: " << fixed << setprecision(6) << adj_close[i] << endl;
    }

    return adj_close;
}

void takeLog(vector<float> &v)
{
    //start at i = 1 because cant adjust v[0]
    for(int i = 1; i < v.size(); i++)
    {
        cout << "cur val: " << v[i] << endl;
        v[i] = abs(log(v[i]) - log(v[i - 1]));
        cout << "log'd ver: " << v[i] << endl;
    }
}

float calcMean(vector<float> v)
{
    float mean = 0;
    for(int i = 0; i < v.size(); i++)
        mean += v[i];
    return mean/v.size();
}%

float calcRange(vector<float> v)
{
    int max = v[0];
    int min = v[1];
    for(int i = 2; i < v.size(); i++)
    {
        if(v[i] > max)
            max = v[i];
        else if(v[i] < min)
            min = v[i];
    }
    return max-min;
}

float calcVariance(vector<float> v, float mean)
{
    float total = 0;
    for(int i = 0; i < v.size(); i++)
        total += pow(v[i] - mean, 2);
    return total/(v.size() - 1);
}

float calcSTD(float variance)
{
    return sqrt(variance); //instructions: https://www.indeed.com/career-advice/career-development/how-to-calculate-correlation-coefficient
}

vector<float> pearCorrHelper(vector<float> v, float mean, float std) //finds the standardized value used in pearson correlation
{
    vector<float> stdVal;
    for(int i = 0; i < v.size(); i++)
        stdVal.push_back((v[i] - mean) / std); 
    return stdVal;
}

float calcPearsonCorr(vector<float> vStdVals, vector<float> maStdVal)
{
    float sum = 0;
    for(int i = 0; i < vStdVals.size(); i++)
        sum += vStdVals[i] * maStdVal[i];
    return sum / (vStdVals.size() - 1); //divide sum by n-1
}

int counter(vector<float> v)
{
    int count = 0;
    for(float val : v)
    {
        count++;
    }
    return count;
}