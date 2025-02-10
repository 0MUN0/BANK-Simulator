#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std ;

string const Filename = "data.json" ;

enum choese {showC= 1 ,addC ,DeletC,upDate,findC,Exit} ;

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkToDelete = false;

};
//
void clearConsole() 
{
     system("cls");
    // cout << "\033[2J\033[1;1H";
}
//

vector <sClient> readAllClientFromFile() ;
//
char EnterYorNOnly(string message) {
    char C;
    cout << message << endl;

    do {
        cout << "Enter Y or N only: ";
        cin >> C;
        C = toupper(C);  // تحويل الإدخال إلى حرف كبير لتوحيد المقارنة
    } while (C != 'Y' && C != 'N');  // تصحيح الشرط

    return C;
}
//
//

sClient ChangeClientRecord(string AccountNumber)
{
sClient Client;
Client.AccountNumber = AccountNumber;
    
    cout << "\n\nEnter PinCode? ";
        getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
        getline(cin, Client.Name);
    cout << "Enter Phone? ";
        getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
        cin >> Client.AccountBalance;

return Client;
}

bool checkIsClientEx(string ACC,vector <sClient>allClints)
{
    for(sClient C : allClints)
    {
        if(ACC == C.AccountNumber)
        {
            return false ;
        }
    }
    return true ;
}


string ReadClientAccountNumber()
{
string AccountNumber = "";
cout << "\nPlease enter AccountNumber? ";
cin >> AccountNumber;
return AccountNumber;
}


void readAllClient(vector <sClient>& allClints)
{
    
  
   
    char answer = 'Y' ;
    string ACC;
    do
    {
          ACC = ReadClientAccountNumber() ;
        if(checkIsClientEx(ACC,allClints))
        {
        allClints.push_back(ChangeClientRecord(ACC)) ;     
            answer = EnterYorNOnly("\n do you want to countenue Y:N") ;
            cout<<"\n"<<endl;
        }
        else
        {
            cout<<"the Client is already Exiest ["<<ACC<<"]"<<endl ;
        }
    }while (toupper(answer) == 'Y') ;
   
}
//
string join(string delim ,sClient clients)
{
    string S1 ;
        S1 = S1+clients.AccountNumber+delim ;
        S1 = S1+clients.PinCode+delim ;
        S1 = S1+clients.Name+delim ;
        S1 = S1+clients.Phone+delim ;
        S1 = S1+to_string(clients.AccountBalance);
            return S1 ;
}

void saveAllLinesAtFile(vector<sClient> & clients)
{
    fstream Folder ;
    Folder.open(Filename,ios ::out) ;
    if(Folder.is_open())
    {
        for(sClient &infoClints :clients)
        {
            if(infoClints.MarkToDelete == false)
            {
            Folder<<join("/##/",infoClints) ;
            Folder<<"\n" ;
            }
        }
            Folder.close() ;    
    }
}

void upPart()
{
    
    string space = "________________________________________________________________________________________" ;
    cout<<space<<"\n\n" ;
    cout<<setw(15)<<"|Account Number"<<setw(10)<<"|Pin Code"<<setw(22)<<"|Client Name"<<setw(15)<<"|Phone"<<setw(22)<<"|Balance"<<endl ;
    cout<<space<<"\n" ;

}
//
void DownPart(vector <sClient> & vListName)
{
    for(sClient & part : vListName)
    {
        cout << "| " << setw(14) << left << part.AccountNumber
         << "| " << setw(17) << left << part.PinCode
         << "| " << setw(19) << left << part.Name
         << "| " << setw(18) << left << part.Phone
         << "| " << setw(10) << fixed << setprecision(2) << part.AccountBalance
        << endl;
    }
}
//
void printAllClients(vector<sClient> & clients)
{
    clearConsole() ;
    cout<<"Clients List ("<<clients.size()<<") "<<endl ;
    upPart();
    DownPart(clients) ;
}
//
short readNumFromTo(short from,short to)
{
    short num ;
    cout<<"Choose what do you do [1 to 6] "<<endl ;
    cin>>num ;
    while(num>to ||from>num)
    {
        cout<<"Enter number between "<<to<<" and "<<from<<endl ;
        cin>>num ;

    }
    return num ;
}
//
void endFunction() 
{
     cout<<"press Enter to return to last screen..." ;
            cin.ignore() ;
            cin.ignore() ;
            cout<<endl;
}
//
vector<string> sliceOneLineAndChToStru(string S1)
{
vector<string> vinfCliAtVecBeForConv ;

string delim = "/##/";  
short pos = 0; 

string sWord;  

while ((pos = S1.find(delim)) != std::string::npos) // هذا الوايل لوب يقوم ب التحقق من طول البوز عن طريق دالة find اذا وجدت والا يخرج من الدالة 
{
    sWord = S1.substr(0, pos); //الكلمة تساوي الاندكس من الصفر الى مكان الذي توقف عندة البوز
    if (sWord != "")
    
    {
        vinfCliAtVecBeForConv.push_back(sWord) ;
    }

S1.erase(0, pos + delim.length()); 
// هنا يقوم ب بقص النص لكي يعود الى البداية 

}

if (S1 != "")
{   
   vinfCliAtVecBeForConv.push_back(S1) ;
}

return vinfCliAtVecBeForConv ;
     
}
//
sClient ConvertLinetoRecord(string Line)
{

sClient Client;
vector<string> vClientData;
vClientData = sliceOneLineAndChToStru(Line);
Client.AccountNumber = vClientData[0];
Client.PinCode = vClientData[1];
Client.Name = vClientData[2];
Client.Phone = vClientData[3];
Client.AccountBalance = stod(vClientData[4]);//cast string todouble
return Client;
}
//
//دالة تقوم بعمل قراة للمعلومات من الملف وتقوم دالة في داخلها بعمل الفصل وتقوم دالة اجر بارجاع القيمة الى الفيكتور 

void PrintClientCard(sClient Client)
{
cout << "\nThe following are the client details:\n";
cout << "\nAccout Number: " << Client.AccountNumber;
cout << "\nPin Code : " << Client.PinCode;
cout << "\nName : " << Client.Name;
cout << "\nPhone : " << Client.Phone;
cout << "\nAccount Balance: " << Client.AccountBalance;
}
//
bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector <sClient> &vClients)
{
    for(sClient & Client :vClients)
    {
        if(AccountNumber == Client.AccountNumber)
        {
            Client.MarkToDelete = true ;
            return true ;
        }
    }
        return false ;
}
//
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> &vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }  
    }
        return false;
}
//
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
sClient Client;
char Answer = 'n';

if (FindClientByAccountNumber(AccountNumber, vClients,Client))
{
PrintClientCard(Client);
cout << "\n\nAre you sure you want delete this client? y/n ? ";
cin >> Answer;
if (Answer == 'y' || Answer == 'Y')
{
MarkClientForDeleteByAccountNumber(AccountNumber,vClients);

//Refresh Clients
saveAllLinesAtFile(vClients);
cout << "\n\nClient Deleted Successfully.";
return true;
}
}
else
{
cout << "\nClient with Account Number (" << AccountNumber
<< ") is Not Found!";
return false;
}
}
//
void showClintByACC(vector<sClient> vClients)
{
    sClient newCli ;
    string ClintoFind = ReadClientAccountNumber() ;
    if(FindClientByAccountNumber(ClintoFind,vClients,newCli))
        {
            PrintClientCard(newCli) ;
        }
    else 
        {
            cout<<"the Account you looking "<<ClintoFind<<" is not Found "<<endl;
            cout<<"Enter Account Number Again "<<endl;
        }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients,Client))
        {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want update this client? y/n? ";
                cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
                {
                    for (sClient & C : vClients)
                        {
                            if (C.AccountNumber == AccountNumber)
                                {
                                    C = ChangeClientRecord(AccountNumber);
                                    break;
                                }
                        }
                        saveAllLinesAtFile(vClients);
                        cout << "\n\nClient Updated Successfully.";
                        return true;
                        }
        }
    else
    {
    cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
    return false;
    }
}

void readClientsAndAdd(vector<sClient> & Data)
{
    
    Data = readAllClientFromFile() ;
            // chick

            readAllClient(Data) ;
            saveAllLinesAtFile(Data) ;
            
}

void projctScreen()
{
    short UserChoose = 0 ;
    vector<sClient> Data ;
    while(UserChoose!= 6)
    {
    clearConsole() ;
    string space = "========================================" ;
    cout<<space<<endl;
    cout<<"Main Menus Screen "<<endl ;
    cout<<space<<endl;
    cout<<"[1] Show Clinent List. "<<endl
    <<"[2] add New Client."<<endl
    <<"[3] Delete Client."<<endl
    <<"[4] Update Client."<<endl
    <<"[5] Find Client."<<endl 
    <<"[6] Exit ."<<endl ;
    cout<<space<<endl;
   
    UserChoose = readNumFromTo(1,6) ;
    switch(UserChoose) {
        case choese::showC :
            clearConsole() ;
            Data = readAllClientFromFile() ;
            printAllClients(Data) ;
            Data.clear() ;
            endFunction() ;
            
            cout<<endl;
            break;
        case choese::addC :
            clearConsole() ;
            readClientsAndAdd(Data) ;
            Data.clear() ;
            endFunction() ;
           
            break;
        case choese::DeletC :
            clearConsole() ;
            Data = readAllClientFromFile() ;
            DeleteClientByAccountNumber(ReadClientAccountNumber(),Data) ;
            endFunction() ;
            break;
        
        case choese::upDate :
            clearConsole() ;
            Data = readAllClientFromFile() ;
            UpdateClientByAccountNumber(ReadClientAccountNumber(),Data) ;
            endFunction() ;
            break;

        case choese::findC :
            clearConsole() ;
            Data = readAllClientFromFile() ;
            showClintByACC(Data) ;
            endFunction() ;
            break ;
        case choese::Exit :
            break;

            default :
                cout<<"you are Crayz :-() "<<endl ;
    
    }


    }
}


int main() 
{
projctScreen() ;
cout<<"press Enter to Exit from Project... " ;
cin.ignore() ;
}



vector<sClient> readAllClientFromFile()
{
    vector<sClient> clients ;
    fstream Folder;
 
    Folder.open(Filename,ios ::out |ios :: in ) ;
    if(Folder.is_open())
    {

    string line ;
    while(getline(Folder,line))
    {
       if(line!="")
       clients.push_back(ConvertLinetoRecord(line)) ;
    }
        
    }
    else
    {
        cout<<"sory the File is NOT found ): " ;
    }
    return clients ;
}

