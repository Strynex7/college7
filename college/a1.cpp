#include <iostream>
#include <string>
using namespace std;

class BankAccount {
    string name, dob, addr, phone, accType, ifsc;
    long accNo;
    double balance;
public:
    BankAccount() { name=dob=addr=phone=accType=ifsc=""; accNo=0; balance=0; }
    BankAccount(string n,long a,string d,string ad,string p,string t,string i,double b){
        name=n; accNo=a; dob=d; addr=ad; phone=p; accType=t; ifsc=i; balance=b;
    }
    BankAccount(const BankAccount &x){
        name=x.name; accNo=x.accNo; dob=x.dob; addr=x.addr;
        phone=x.phone; accType=x.accType; ifsc=x.ifsc; balance=x.balance;
    }
    ~BankAccount() {}
    void create(){
        cout<<"Enter Name: "; getline(cin,name);
        cout<<"Account No: "; cin>>accNo; cin.ignore();
        cout<<"DOB: "; getline(cin,dob);
        cout<<"Address: "; getline(cin,addr);
        cout<<"Phone: "; getline(cin,phone);
        cout<<"Account Type(Saving/Current): "; getline(cin,accType);
        cout<<"IFSC: "; getline(cin,ifsc);
        cout<<"Initial Balance: "; cin>>balance; cin.ignore();
    }
    long getAccNo(){ return accNo; }
    void display(){
        cout<<"\n--- Account Details ---\n";
        cout<<"Name: "<<name<<"\nAcc No: "<<accNo<<"\nDOB: "<<dob
            <<"\nAddress: "<<addr<<"\nPhone: "<<phone
            <<"\nType: "<<accType<<"\nIFSC: "<<ifsc
            <<"\nBalance: "<<balance<<"\n";
    }
    void deposit(){
        double amt; cout<<"Enter deposit amount: "; cin>>amt;
        if(amt>0) balance+=amt; cout<<"Updated Balance: "<<balance<<"\n";
    }
    void withdraw(){
        double amt; cout<<"Enter withdrawal amount: "; cin>>amt;
        if(amt>0 && amt<=balance) balance-=amt;
        else cout<<"Insufficient balance\n";
        cout<<"Current Balance: "<<balance<<"\n";
    }
    void viewBal(){ cout<<"Current Balance: "<<balance<<"\n"; }
};

int main(){
    BankAccount acc[50];
    int count=0; string choice;
    while(true){
        cout<<"\n1.Create Account\n2.Display Details\n3.Deposit\n4.Withdraw\n5.View Balance\n6.Exit\nChoice: ";
        getline(cin,choice);
        if(choice=="1"){ acc[count++].create(); }
        else if(choice=="2"){
            long n; cout<<"Enter Account No: "; cin>>n; cin.ignore();
            bool f=false; for(int i=0;i<count;i++) if(acc[i].getAccNo()==n){ acc[i].display(); f=true; }
            if(!f) cout<<"Account not found\n";
        }
        else if(choice=="3"){
            long n; cout<<"Enter Account No: "; cin>>n; cin.ignore();
            bool f=false; for(int i=0;i<count;i++) if(acc[i].getAccNo()==n){ acc[i].deposit(); f=true; }
            if(!f) cout<<"Account not found\n";
        }
        else if(choice=="4"){
            long n; cout<<"Enter Account No: "; cin>>n; cin.ignore();
            bool f=false; for(int i=0;i<count;i++) if(acc[i].getAccNo()==n){ acc[i].withdraw(); f=true; }
            if(!f) cout<<"Account not found\n";
        }
        else if(choice=="5"){
            long n; cout<<"Enter Account No: "; cin>>n; cin.ignore();
            bool f=false; for(int i=0;i<count;i++) if(acc[i].getAccNo()==n){ acc[i].viewBal(); f=true; }
            if(!f) cout<<"Account not found\n";
        }
        else if(choice=="6"){ cout<<"Exiting...\n"; break; }
        else cout<<"Invalid Option\n";
    }
    return 0;
}
