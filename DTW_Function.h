#ifndef DTW_FUNCTION_H
#define DTW_FUNCTION_H
#include"DTW_Structure.h"

class DTW_Function{
private:
    vector<string> split_str(string str);

    float Distance(float * ps1,float * ps2);

    float min(float num1, float num2, float num3);

    vector<vector<float> > rebuilt_mfcc_feat(vector<string> flatten_mfcc);

private:
    int MFCC_P;
    int MFCC_Pf;

public:
    vector<vector<float> > read_mfcc_from_csv(string filename, int line_num);
    int iteration_dtw(string filename, int lib_len, vector<vector<float> >  query_mfcc_feat, float* min_dist/*, int* min_idx*/);
    float ComputeDTW(vector<vector<float> > cep1,vector<vector<float> > cep2);
    DTW_Function(int mfcc_num);
    ~DTW_Function();
};

#endif 
