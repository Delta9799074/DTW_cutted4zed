#include"DTW_Function.h"
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;

#define TEST_TIMES 1

int main(int argc, char *argv[])
{
    DTW_Function* dtw_example = new DTW_Function(13);
//read and reshape array
    vector<vector<string> > match_csv_content;
    vector<vector<float> >  match_mfcc_feat;

    vector<vector<string> > query_csv_content;
    vector<vector<float> >  query_mfcc_feat;


//    auto prep_start = chrono::high_resolution_clock::now();

    string match_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\mfcc_csv\\find_directory\\";
    string query_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\mfcc_csv\\query\\";
 /*
    string match_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\database_for_zed\\find_directory\\";
    string query_lib_path = "G:\\py_mfcc_n_dtw\\dtw_cpp\\database_for_zed\\query\\";
*/
    string match_path, query_path;
    int random_gen_seed;

/* 
    auto prep_stop = chrono::high_resolution_clock::now();

    auto prep_duration = chrono::duration_cast<chrono::microseconds>(prep_stop - prep_start);
    cout << "Preparing data execute time:" << prep_duration.count() << "ms"<< endl;
 */
//Dynamic Time Warping to Recognize
    vector<float> total_mindist;
    float minimum_dist;
    float aver_dist;
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

    //    cout << "Now test : " << query_rand_num << endl;

        query_path = query_lib_path + to_string(query_rand_num) + ".csv";
        query_csv_content = dtw_example ->read_mfcc_from_csv(query_path);

        total_mindist.clear();
        for (int j = 0; j < 10; j++)
            {
            match_path = match_lib_path + to_string(j) + ".csv";
            match_csv_content = dtw_example -> read_mfcc_from_csv(match_path);
            srand(time(0));
            random_gen_seed = rand() % query_csv_content.size();
            query_mfcc_feat = dtw_example -> rebuilt_mfcc_feat(query_csv_content[random_gen_seed]);
            dtw_example -> iteration_dtw(match_csv_content, query_mfcc_feat, &minimum_dist, &minimum_index);
        //    cout << "Number" << j << "Normalized distance is:" << setprecision(15) << minimum_dist << endl;
            total_mindist.push_back(minimum_dist);
        //    cout << total_mindist.size() << endl;
            random_gen_seed = 0;
        }
        minimum_index = std::min_element(total_mindist.begin(), total_mindist.end()) - total_mindist.begin();

        //cout << "Recognization Number: " << minimum_index << endl;
/* 
    aver_dist = float(accumulate(total_mindist.begin(), total_mindist.end(), 0) / total_mindist.size());
    cout << "Average Recognization Distance:" << aver_dist << endl;
 */    
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