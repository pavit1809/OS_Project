#include<bits/stdc++.h>
using namespace std;
const double prev_medical_history=200;
const double symptom_severity_score[3]={0,100,200};
struct patient
{
    int age;
    vector<bool>Severity_cough=vector<bool> (3);
    vector<bool>Severity_fever=vector<bool> (3);
    vector<bool>Severity_breathlessness=vector<bool> (3);
    bool neurological_history;
    bool cardiovascular_history;
    bool gastric_history;
    int reference_number;   
};
patient getdata()
{
    patient curr_data;
    int degree_fever,degree_breathlessness,degree_cough;
    curr_data.Severity_cough[0]=false;
    curr_data.Severity_cough[1]=false;
    curr_data.Severity_cough[2]=false;
    curr_data.Severity_fever[0]=false;
    curr_data.Severity_fever[0]=false;
    curr_data.Severity_fever[0]=false;
    curr_data.Severity_breathlessness[0]=false;
    curr_data.Severity_breathlessness[0]=false;
    curr_data.Severity_breathlessness[0]=false;
    cout<<"! Please enter your details with complete honesty and alertness !"<<endl<<endl;
    cout<<"Enter your age: ";
    cin>>curr_data.age;
    cout<<"! Enter your symptoms carefully !"<<endl<<endl;
    cout<<"No symptoms -> 1"<<endl;
    cout<<"Mild symptoms -> 2"<<endl;
    cout<<"Severe symptoms -> 3"<<endl;
    cout<<"Enter your degree of symptoms for FEVER: ";
    cin>>degree_fever;
    cout<<"Enter your degree of symptoms for COUGH: ";
    cin>>degree_cough;
    cout<<"Enter your degree of symptoms for BREATHLESSNESS: ";
    cin>>degree_breathlessness;
    string response;
    cout<<"Do you have a medical history (present and past) for neurological ailment(Yes/No) :";
    cin>>response;
    curr_data.neurological_history=((response=="Yes")?true:false);
    cout<<"Do you have a medical history (present and past) for cardiovascular ailment(Yes/No) :";
    cin>>response;
    curr_data.cardiovascular_history=((response=="Yes")?true:false);
    cout<<"Do you have a medical history (present and past) for gastric ailment(Yes/No) :";
    cin>>response;
    curr_data.gastric_history=((response=="Yes")?true:false);
    curr_data.Severity_fever[degree_fever-1]=true;
    curr_data.Severity_cough[degree_cough-1]=true;
    curr_data.Severity_breathlessness[degree_breathlessness-1]=true;
    return curr_data;
}
double totalscore(double age_score,double symptom_score,double medical_history_score)
{
    return ((0.4)*symptom_score+(0.3)*age_score+(0.3)*medical_history_score)*(100.0);
}
double get_age_score(int age)
{
    double returnval=0.0;
    if (age<=13)
        return (double)(14-(double)age)*(3.0);
    if (age>=14 && age<=50)
        return 1.0;
    if (age>=51)
        return (double)(age-51)*(2.0);
    return returnval;
}
double get_symptoms_score(vector<bool> fever,vector<bool> cough,vector<bool> breathlessness)
{
    double estimate=0.0;
    for(int i=0;i<3;i++)
    {
        estimate=estimate+(0.5)*(symptom_severity_score[i])*((breathlessness[i]==true)?1:0);
    }
    for(int i=0;i<3;i++)
    {
        estimate=estimate+(0.3)*(symptom_severity_score[i])*((fever[i]==true)?1:0);
    }
    for(int i=0;i<3;i++)
    {
        estimate=estimate+(0.2)*(symptom_severity_score[i])*((cough[i]==true)?1:0);
    }
    return estimate;
}
double get_history_priority(bool neurological_history,bool cardiovascular_history,bool gastric_history)
{
    double ans=0.0;
    if (cardiovascular_history==true)
    {
        ans+=(0.5*200);
    }
    if (gastric_history==true)
    {
        ans+=(0.3*200);
    }
    if (neurological_history==true)
    {
        ans+=(0.2*200);
    }
    return ans;
}
double getfinalscore(double age,double symptoms,double history)
{
    return ((0.4)*symptoms + (0.3)*age + (0.3)* history);
}
bool comp(const pair<int,double> p1,const pair<int,double> p2)
{
    return p1.second>p2.second;
}
int main()
{
    srand((unsigned) time(0));
    int total_patient=1;
    vector<patient> data=vector<patient> (total_patient);
    cout<<"Here we are taking details for 4 patients just for demo"<<endl;
    for(int i=1;i<=total_patient;i++)
    {
        data[i-1]=getdata();
        data[i-1].reference_number=rand()%1000;
    }
    vector<pair<int,double>> static_scores =vector<pair<int,double>>(total_patient);
    for(int i=0;i<total_patient;i++)
    {
        double age_score=get_age_score(data[i].age);
        cout<<age_score<<endl;
        double symptoms_score=get_symptoms_score(data[i].Severity_fever,data[i].Severity_cough,data[i].Severity_breathlessness);
        cout<<symptoms_score<<endl;
        double history_score=get_history_priority(data[i].neurological_history,data[i].cardiovascular_history,data[i].gastric_history);
        cout<<history_score<<endl;
        double score=getfinalscore(age_score,symptoms_score,history_score);
        static_scores[i].first=data[i].reference_number;
        static_scores[i].second=score;
    }
    for(int i=0;i<total_patient;i++)
    {
        cout<<"Reference No"<<" "<<static_scores[i].first<<endl;
        cout<<"Score ";
        cout<<static_scores[i].second<<endl;
    }
	return 0;
}

