#include<iostream>
#include <fstream>
#include <set>
using namespace std;
class Files{
    private:
    ifstream input;
    int maxError = 235;
    int MinError = 172;
    int count = 0;
    public:
    void Work(string filename){
        input.open(filename, ios::in);
        if(!input.is_open()){
            cout << "not open:" << filename << endl;
            return;
        }
        
        string info;
        while(input >> info){
            bool rare = true;
            for(int i = 0; i < info.size(); i = i + 4){
                set<char> current;
                
                for(int j = 0; j < 4; j++){
                    
                    if(current.find(info[i+j]) == current.end()){
                        current.insert(info[i+j]);
                    }
                    else rare = false;
                    
                }
                current.clear();
            }
            if(rare == true){
                count++;
            }

        }
        if(count < MinError || count > maxError){
            cout << filename[5] << filename[6] << filename[7]<<',';
        }
        count =0;
        input.close();
    }
};
int main(){
    string file;
    Files f;
    for(int i = 1; i<=500; i++ ){
        if(i < 10){
            file = "enreg00";
            file.append(to_string(i));
            file.append(".txt");
            
           
        }
        else if(i < 100){
            file = "enreg0";
            file.append(to_string(i));
            file.append(".txt");}
        else{
            file = "enreg";
            file.append(to_string(i));
            file.append(".txt");
            
        }
        f.Work(file);
    }


}
