#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include<math.h>
using namespace std;

vector<string> extra;
void printContent(string file,string name)
{
    fstream scan;
    scan.open(file.c_str());
    if(scan.is_open())
	{
		cout << "Reading "<<name <<"..." << endl;
		for(string line; getline(scan, line);)
		{
	    	cout << line << endl;
		}
	cout << endl;
	}
	scan.close();
}


string printUsers(string file,string searchName)
{
    int count=0,it=0;
    fstream scan;
    scan.open(file.c_str());
    string str;
    while (std::getline(scan, str))
    {
        if(count%2==0)
        {
           cout<<(it++)<<". "<<str<<endl;
        }
        count++;
    }
    scan.close();

    for(int i=0;i<extra.size();i++)
    {
        cout<<(it++)<<". "<<extra.at(i)<<endl;
        searchName=extra.at(i);
    }
    return searchName;
}

int printItems(string file)
{
    int count=0;
    fstream scan;
    scan.open(file.c_str());
    if(scan.is_open())
	{
		//cout << "Reading "<<name <<"..." << endl;
		for(string line; getline(scan, line);)
		{
	    	cout <<count<<". "<< line << endl;
	    	count++;
		}
	cout << endl;
	}
	scan.close();
	return count+1;
}

string addUser(string file,string searchName)
{
    string user="";
    cout<<"Please add a username"<<endl;
    getline(cin,user);
    extra.push_back(user);
     searchName=user;
    return searchName;
}

string login(string file,string input,string searchName)
{

    fstream scan;
    int flag=0;

            string str;

            int n=input.length();
            int pos=-1;
            for(int i=0;i<n;i++)
            {
                if(input[i]==' ')
                {
                    pos=i;
                    break;
                }
            }
            string sf=input.substr(pos+1,n);
            //cout<<"What is it??"<<sf;
            scan.open(file.c_str());
            int ff=0;
            while (std::getline(scan, str))
            {
                if(str==sf)
                {
                    cout<<"Success! Found you"<<endl;
                    searchName=str;
                    flag=1;
                    break;
                }
                for(int i=0;i<extra.size();i++)
                {
                    if(sf==extra.at(i))
                    {
                        cout<<"Success! Found you"<<endl;
                        searchName=sf;
                        ff=1;
                        break;
                    }
                }
                if(ff==1)
                    break;
            }
            scan.close();
            if(flag==0 && ff==0)
            {
                cout<<"Error "<<endl;
                searchName="";
            }


            return searchName;
}

void recommendation(string file,string searchName,vector<string> restroName,float arr[])
{
            if(searchName=="")
            {
                cout<<"Try Again! Must be logged in"<<endl;
                return;
            }
            fstream scan;
            string str;
            scan.open(file.c_str());
            int flag=0;


            int n=restroName.size();
            pair<float,string> pp[n];



            while (std::getline(scan, str))
            {
                if(str==searchName)
                {
                    flag=1;
                    break;
                }
            }
            if(std::getline(scan, str))
            {

                vector<string> rating;
                stringstream ss(str);
                string temp;
                while(ss>>temp)
                {
                    rating.push_back(temp);
                }
                int s=restroName.size();
                cout<<"\nHey "<<searchName<<" "<<"following are your top restro recommendation "<<endl;

                int t=1;
                for(int i=0;i<n;i++)
            {
                if(rating.at(i)=="0")
                {
                    pp[i].first=arr[i];
                    pp[i].second=restroName.at(i);
                }
                else
                    pp[i].first=-99999;
            }

            sort(pp,pp+n);
            int k=0;
                for(int i=n-1;i>=max(n-5,0);i--)
                {
                    if(pp[i].second!="")
                    {
                        //cout<<pp[i].second<<" "<<pp[i].first<<"/5"<<endl;
                        k++;
                    }

                }

                pair<float,string> pf[k];
                for(int i=0;i<k;i++)
                {
                    pf[i].first=pp[n-1-i].first;
                    pf[i].second="";
                }

                for(int i=0;i<restroName.size();i++)
                {
                    for(int j=n-1;j>=max(n-5,0);j--)
                    {
                        if(pp[j].second==restroName.at(i))
                        {
                            for(int h=0;h<k;h++)
                            {
                                if(pf[h].first==pp[j].first && pf[h].second=="")
                                {
                                    pf[h].second=pp[j].second;
                                    break;
                                }
                            }
                        }

                    }
                }

                for(int i=0;i<k;i++)
                {
                    cout<<pf[i].second<<" "<<pf[i].first<<endl;
                }
                cout<<endl;

            }
            scan.close();
}


vector<string> show(string file,string searchName,vector<string> restroName)
{
            vector<string> rating;
            if(searchName=="")
            {
                cout<<"Try Again! Must be logged in"<<endl;
                return rating;
            }
            cout<<"\nHi "<<searchName<<" "<<"following are your restro reviews"<<endl;
            int flag=0;

            string str;

            fstream scan;
            scan.close();
            scan.open(file.c_str());
            while (std::getline(scan, str))
            {
                if(str==searchName)
                {
                    flag=1;
                    break;
                }
            }
            if(std::getline(scan, str))
            {
                stringstream ss(str);
                string temp;
                while(ss>>temp)
                {
                    rating.push_back(temp);
                }
                for(int i=0;i<restroName.size();i++)
                {
                    if(rating.at(i)!="0")
                    cout<<restroName.at(i)<<" "<<rating.at(i)<<"/5"<<endl;
                }
                cout<<endl;
            }
            scan.close();
            return rating;
}

//Helper function to provide advanced recommendations
void advrecom(string file,string searchName,vector<string> restroName)
{
            if(searchName=="")
            {
                cout<<"Try Again! Must be logged in"<<endl;
                return;
            }
            string str;
            fstream scan;
            scan.open(file.c_str());
            vector<int> rating1;
            while (std::getline(scan, str))
            {
                if(str==searchName)
                {
                    break;
                }
            }
            if(std::getline(scan, str))
            {
                stringstream ss(str);
                string temp;
                while(ss>>temp)
                {
                    stringstream gg(temp);
                    int y=0;
                    gg>>y;
                    rating1.push_back(y);
                }
            }
            scan.close();


            scan.open(file.c_str());
            int maxim=-99999,posg=-1,countl=0,countg=0;
            string name="",namef="";
            int ratingf[10000];
            int g=0;
            while (std::getline(scan, str))
            {
                if(str!=searchName && ((str[0]>='A' && str[0]<='Z') ||(str[0]>='a' && str[0]<='z')))
                {
                    name=str;
                    //cout<<name;
                    if(std::getline(scan, str))
                    {
                        vector<int> rating;
                        stringstream ss(str);
                        string temp;
                        while(ss>>temp)
                        {
                            int y=0;
                            stringstream gg(temp);
                            gg>>y;
                            rating.push_back(y);
                        }

                        int sum=0,pos=-1;
                        for(int i=0;i<rating1.size();i++)
                        {
                            int prod=rating1.at(i)*rating.at(i);
                            sum+=prod;
                            pos=i;
                        }
                        countl++;
                        cout<<"Final Name --> "<<name<<" "<<sum<<endl;
                        if(sum>maxim)
                        {
                            maxim=sum;
                            countg=countl;
                            namef=name;
                            for(int i=0;i<rating.size();i++)
                            {
                                ratingf[i]=rating.at(i);
                            }
                        }

                    }
                }
            }
            cout<<"\nMax Similarity--> "<<maxim<<" "<<" with "<<namef<<endl;
            int cc=0;
            pair<int,string> rp[10000];
            for(int i=0;i<rating1.size();i++)
            {
                if(rating1.at(i)==0)
                {
                    rp[cc].first=ratingf[i];
                    rp[cc++].second=restroName.at(i);
                }

            }

            cout<<endl;
            cout<<"----------------------------------"<<endl;
            cout<<"Top Recommendations from "<<namef;
            cout<<endl;
            sort(rp,rp+cc);



            pair<int,string> rf[cc];

            for(int i=0;i<cc;i++)
            {
                rf[i].first=rp[cc-1-i].first;
                rf[i].second="";

            }

            for(int i=0;i<restroName.size();i++)
            {
                for(int j=cc-1;j>=0;j--)
                {
                    if(restroName.at(i)==rp[j].second)
                    {
                        for(int h=0;h<cc;h++)
                            {
                                if(rf[h].first==rp[j].first && rf[h].second=="")
                                {
                                    rf[h].second=rp[j].second;
                                    break;
                                }
                            }
                    }
                }
            }
            int tt=1;
            for(int i=0;i<cc;i++)
            {
                if(rf[i].second!="" && tt<=5)
                cout<<rf[i].second<<" "<<rf[i].first<<"/5"<<endl;
                tt++;
            }
            cout<<endl;
            scan.close();

}

//Helper function to add rating for a new user
void addRating(string file1,string file,string searchName,vector<string> restroName)
{
    vector<string> addr;

    addr=show(file,searchName,restroName);
    if(addr.size()==0)
    {
        int pos=-1;
        for(int i=0;i<extra.size();i++)
        {
            if(extra.at(i)==searchName)
            {
                pos=i;
                break;
            }
        }
        extra.erase(extra.begin()+pos);
        for(int i=0;i<extra.size();i++)
        {
            cout<<extra.at(i)<<" ";
        }
        cout<<"-----No Reviews------"<<endl;
        int c=0;
        fstream sc;
        sc.open(file1.c_str());
        string str;
        while (std::getline(sc, str))
        {
            c++;
        }
        sc.close();


        string id;
        cout<<"Enter restro ID\n";
        std::getline(cin,id);
        int idx;
        idx=stoi(id);
        int arr[c];
        for(int i=0;i<c;i++)
            arr[i]=0;
        string rate;


        cout<<"Enter rating for ";
        cout<<restroName.at(idx)<<": ";
        std::getline(cin,rate);
        int ratex=stoi(rate);
        arr[idx]=ratex;

        ofstream foutput;
        ifstream finput;
        finput.open (file);
        foutput.open (file,ios::app);

        if(finput.is_open())
        {
            foutput<<"\n"<<searchName<<"\n";
        }
        for(int i=0;i<c;i++)
        {
            foutput<<arr[i]<<" ";
        }
    }
    else
    {
        cout<<"Enter the restro ID ";
        string id;
        std::getline(cin,id);
        int idx;
        idx=stoi(id);

        string rate;
        cout<<"Enter restro rating for ";
        cout<<restroName.at(idx)<<": ";
        std::getline(cin,rate);
        int ratex=stoi(rate);
        addr.at(idx)=to_string(ratex);
        fstream scan;
        string str;
        while (std::getline(scan, str))
            {
                if(str==searchName)
                {
                    break;
                }
            }
            scan.close();

    }

    return;
}

//test
int main()
{
	string filename;
	string filenameB;
	fstream scan;

	cout<<"Enter the filenames to read"<<endl;
	cin >> filename;
	cout << endl;
	scan.open(filename.c_str());
    vector<string> restroName;
    printContent(filename,"restaurants");
	if(scan.is_open())
	{
		for(string line; getline(scan, line);)
		{
		    restroName.push_back(line);
		}
	}
	scan.close();

	cin>> filenameB;
	printContent(filenameB,"ratings");
	scan.open(filenameB.c_str());
	int cl=1,co=0;
	if(scan.is_open())
	{
		for (string line; getline(scan, line);)
		{
		    if(cl%2!=0)
                co++;
	    	cl++;
		}
	}
	scan.close();


	//Recommendation Code

    int n=restroName.size();
    float arr[n];
    for(int i=0;i<n;i++)
    {
            arr[i]=0;
    }

    scan.open(filenameB.c_str());
    string x;
    while (std::getline(scan,x))
    {
        stringstream ff(x);
        string temp;
        int count=0;
        while(ff>>temp)
        {
            stringstream gg(temp);
            int y=0;
            gg>>y;
            arr[count]=arr[count]+y;
            count++;
        }
    }
    scan.close();

    for(int i=0;i<n;i++)
    {
        arr[i]=arr[i]/co;
    }

    //End of Recommendation
	string input;
    string searchName="";
    getline(cin,input);

    cout<<input;
	while(input!="#")
    {

        cout << "Enter command or # to quit: "<<endl;
        getline(cin,input);



        if(input!="")
        {


        if(input=="#")
        {
            exit(0);
        }
        else if(input!="Show" && input!="Recommend" && input!="Advanced Recommendations" && input!="Print Items" && input!="Print Users" && input!="Add User" && input!="Add Rating")
        {
            searchName=login(filenameB,input,searchName);
        }
        else if(input=="Recommend")
        {
            recommendation(filenameB,searchName,restroName,arr);

        }
        else if(input=="Show")
        {
            show(filenameB,searchName,restroName);
        }
        else if(input=="Print Items")
        {
            printItems(filename);
        }
        else if(input=="Print Users")
        {
            searchName=printUsers(filenameB,searchName);
        }
        else if(input=="Add User")
        {
            searchName=addUser(filenameB,searchName);
        }
        else if(input=="Add Rating")
        {
            addRating(filename,filenameB,searchName,restroName);
            //cout<<"Done wit call"<<endl;
        }
        else
        {
            advrecom(filenameB,searchName,restroName);
        }
    }
    }
}
