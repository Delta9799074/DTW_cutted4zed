#include"DTW_Function.h"
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;

#define TEST_TIMES 1
#define LIB_LEN 2250
#define QUERY_LEN 750

int main(int argc, char *argv[])
{
    DTW_Function* dtw_example = new DTW_Function(13);
    vector<vector<float> >  match_mfcc_feat;

    vector<vector<float> >  query_mfcc_feat;


/*
    string match_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\mfcc_csv\\find_directory\\";
    string query_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\mfcc_csv\\query\\";
 */
    string match_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\database_for_zed\\find_directory\\";
    string query_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\database_for_zed\\query\\";

    string match_path, query_path;
    int random_gen_seed;

//Dynamic Time Warping to Recognize
    vector<float> total_mindist;
    total_mindist.reserve(10);
    float minimum_dist;
    float recog_result;
    double corr_rate;
    int   minimum_index;
    int query_rand_num;
    int correct_num ,wrong_num;
    correct_num = 0;
    wrong_num = 0;
    auto recog_start = chrono::high_resolution_clock::now();
    for (int t = 0; t < TEST_TIMES; t++)
    {
        srand(time(0));
        query_rand_num = rand() % 10;
        query_path = query_lib_path + to_string(query_rand_num) + ".csv";

        total_mindist.clear();
        for (int j = 0; j < 10; j++){
            match_path = match_lib_path + to_string(j) + ".csv";
            srand(time(0));
            random_gen_seed = rand() % QUERY_LEN;
            query_mfcc_feat = dtw_example->read_mfcc_from_csv(query_path, random_gen_seed);
            dtw_example -> iteration_dtw(match_path, LIB_LEN, query_mfcc_feat, &minimum_dist);
            total_mindist.push_back(minimum_dist);
            random_gen_seed = 0;
        }
        minimum_index = std::min_element(total_mindist.begin(), total_mindist.end()) - total_mindist.begin();

        //cout << "Recognization Number: " << minimum_index << endl;
        if(minimum_index == query_rand_num){
            //cout << "Recognization Result:TRUE" << endl;
            correct_num += 1;
        }
        else{
            //cout << "Recognization Result:FALSE" << endl;
            wrong_num += 1;
        }
        query_rand_num = 0;
    }
    auto recog_stop = chrono::high_resolution_clock::now();
    auto recog_duration = chrono::duration_cast<chrono::seconds>(recog_stop - recog_start);
    cout << "Recogniton execute time:" << recog_duration.count() / 60 << "min"  << recog_duration.count() % 60 << "s" << endl;
    corr_rate = double(correct_num) / double((correct_num + wrong_num));
    cout << "correct times:" << correct_num << endl;
    cout << "wrong times:" << wrong_num << endl;
    cout << "Recogniton Correct rate:" << corr_rate * 100 << "%" << endl;

    return 0;
}