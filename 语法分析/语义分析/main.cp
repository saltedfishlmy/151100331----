/*标识符：(1，标识符表指针)  正整数(2，正整数值)
 program：(3,0)      procedure：(5,0)        var：(4,0)
 begin： (6,0)       end：(7,0)              if：(8,0)
 then：(9,0)         else：(10,0)             while：(11,0)
 do：(12,0)         call：(13,0)             integer：(14,0)
 real：(15,0)        +：(16,0)               －：(17,0)
 *：(18,0)            /：(19,0)                 ~：(20,0)
 ：(21,0)             ：(22,0)                 <：(23,0)
 <= ：(24,0)          >：(25,0)                >=：(26,0)
 = ：(27,0)           <>：(28,0)               :=：(29,0)
 ; ：(30,0)            . ：(31,0)               , ：(32,0)
 ( ： (32,0)           ) ：(33,0)               : ：(34,0)
 */

#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <cstring>
#include <sstream>

using namespace std;
/*################################语法分析部分全局变量##############################*/

char  TOKEN[200];
int value;
int sym = 0;
int error = 0;
FILE *fp;
string strOfExpression;
/*################################语法分析部分全局变量##############################*/




/*################################输出四元式部分全局变量##############################*/



vector<string> RevPoland;

typedef struct {
    int numOfFourGen;
    string op;
    string op1;
    string op2;
    string result;
    
}quadList;


vector<quadList> vecOfQuadList;
vector<int> Tchain;
stack<int> Fchain;



int numOfFourGen = 0;
int numOfT = 0;


/*################################输出四元式部分全局变量##############################*/





/*##################################################################################################################
 #############################################算法算法算法算法算法###################################################
 ##################################################################################################################
 ##################################################################################################################*/


typedef struct st
{
    int maxsize;
    int top;
    int *pStack;
}Stack;

void create_Stack(Stack *s, int ms);
void push(Stack *s, int x);
int pop(Stack *s);
void clear_Stack(Stack *s);
char read_Stack(Stack *s);
int priority(char ch);
void transform(char a[], char b[]);



void create_Stack(Stack *s, int ms)
{
    s->maxsize = ms;
    s->top = -1;
    s->pStack = (int *)malloc(ms*sizeof(int));
    s->pStack[++s->top] = '@'; //这里@被假定为优先级最低的运算符
}

void push(Stack *s, int x)
{
    if(s->top < s->maxsize-1)
        s->pStack[++s->top] = x;
}

int pop(Stack *s)
{
    if(s->top != -1)
        return s->pStack[s->top--];
    return 0;
}

char read_Stack(Stack *s)
{
    return (s->pStack[s->top]);
}

int priority(char ch)
{
    int flag = 0;
    
    switch(ch)
    {
        case '+':
        case '-':
            flag = 1;
            break;
        case '*':
        case '/':
            flag = 2;
            break;
        default:
            flag = 0; //@的优先级设置为最低：0
            break;
    }
    
    return flag;
}

void transform(char a[], char b[])
{
    Stack s;
    int i = 0, j = 0;
    
    create_Stack(&s, 20);
    while(a[i])
    {
        if(isalnum(a[i]))
        {
            b[j++] = a[i];
        }
        else if(a[i] == '(')
            push(&s, a[i]);
        else if(a[i] == ')')
        {
            b[j++] = ' ';
            while(read_Stack(&s) != '(')
            {
                b[j++] = pop(&s);
                b[j++] = ' ';
            }
        }
        else
        {
            b[j++] = ' ';
            while(priority(a[i]) <= priority(read_Stack(&s)))
            {
                b[j++] = pop(&s);
                b[j++] = ' ';
            }
            push(&s, a[i]);
        }
        i ++;
    }
    while(s.top != 0) //如果判断a[]结束栈中还有运算符则出栈到b[]中
    {
        b[j++] = ' ';
        b[j++] = pop(&s);
    }
    
    b[j++] = '\0'; //将b转换为字符换
    
}
void trim(string &s)
{
    /*
     if( !s.empty() )
     {
     s.erase(0,s.find_first_not_of(" "));
     s.erase(s.find_last_not_of(" ") + 1);
     }
     */
    int index = 0;
    if( !s.empty())
    {
        while( (index = s.find(' ',index)) != string::npos)
        {
            s.erase(index,1);
        }
    }
    
}

/*##################################################################################################################
 #############################################算法算法算法算法算法###################################################
 ##################################################################################################################
 ##################################################################################################################*/

/*################################函数函数函数函数##############################*/

int chengxuti();
int bianliangshuoming();
int yujuchuan();
int shuomingbiao();
int bianliangbiao();
int leixing();
bool check_shuomingbiao();
bool check_bianliangbiao();
int yuju();
bool check_yujuchuan();
int fuheyuju();
int tiaojianyuju();
int fuzhiyuju();
int xunhuanyuju();
int biaodashi();
bool check_tiaojianyuju();
int xiang();
int check_biaodashi();
int yinzi();
bool check_xiang();
int changshu();
int guanxibiaodashi();
int guanxi();
int biaozhifu();
bool check_boolbiaodashi();
int boolbiaodashi();
void putsym();
void Gen_biaodashi(string final);
void Gen_boolbiaodashi();
void fillFchain(int x1,int x2);
void fillFchainWhile(int x1,int x2);

/*################################函数函数函数函数##############################*/




/*################################语法分析部分##############################*/

char str[100];

void getsym(){
    
    fscanf(fp,"%s\n",str);
    sscanf(str,"(%d,%d)%s",&sym,&value,TOKEN);
   
}
void trace_back(){
    
    fseek(fp,-(strlen(str)),SEEK_CUR);
    
    
}

int program(){
    getsym();
    if(sym == 3){
        getsym();
        if(sym == 1){
            getsym();
            if(sym == 30){
                error = chengxuti();
                
                
                quadList temp1;
                temp1.numOfFourGen = ++numOfFourGen;
                temp1.op = "Ret" ;
                temp1.op1 = "0";
                temp1.op2 = "0";
                temp1.result = "0";
                vecOfQuadList.push_back(temp1);

                
            }else {if(error==0) return(error=2); else return error;};
            
        }else {if(error==0) return(error=2); else return error;};
        
    }else{
        {if(error==0) return(error=1); else return error;};
    }
    return error;
}
int chengxuti(){
    error = bianliangshuoming();
    if(error == 0){
        getsym();
        
        if(sym == 6){
            error = yujuchuan();
            if(error == 0){
                getsym();
                if(sym == 7){
                    getsym();
                    if(sym == 31) return error;
                    else {if(error==0) return(error=6); else return error;}
                }else  {if(error==0) return(error=5); else return error;}
            }else return(error);
        }else {if(error==0) return(error=4); else return error;}
        
        
        
    }else return(error);
}
int bianliangshuoming(){
    getsym();
    if(sym == 4){
        error = shuomingbiao();
        return error;
    }else {if(error==0) return(error=7); else return error;}
    
    
}

int shuomingbiao(){
    error = bianliangbiao();
    if(error==0){
        getsym();
        if(sym==34){
            error = leixing();
            
        }else {if(error==0) return(error=8); else return error;}
        
        while(!check_shuomingbiao()){
            getsym( );
            if(sym==30){
                error = shuomingbiao();
                return error;
                
            }
        }
        return error;
    }
    return error;
}

bool check_shuomingbiao(){//检查往下走是否为下一个非终结符号的FIRST,如果是就返回1，不是就返回0
    
    getsym();
    getsym();
    if(sym == 6){
        trace_back();
        return 1;
    }else{
        trace_back();
        return 0;
    }
}
int leixing(){
    getsym();
    if(sym==14){
        return error;
    }else {if(error==0) return(error=9); else return error;}
}

int bianliangbiao(){
    getsym();
    if(sym==1){
        while(!check_bianliangbiao()){
            getsym();
            if(sym == 32){
                getsym();
                if(sym==1){
                    continue;
                }else {if (error==0) return (error=10); else return error;}
            }else {if (error==0) return (error=11); else return error;}
        }
        
    }else {if (error==0) return (error=10); else return error;}
    //这里需要加入变量识别
    return error;
}
bool check_bianliangbiao(){
    long temp = (long)fp;
    getsym();
    if(sym == 34){
        trace_back();
        return 1;
    }else{
        trace_back();
        return 0;
    }
}


int yujuchuan(){
    error = yuju();
    if(error == 0){
        while(!check_yujuchuan()){
            getsym();
            if(sym == 30){
                error = yujuchuan();
            }else {
                
                if(error==0) return (error=13);
                else return error;
            }
        }
        return error;
        
    }
    return error;
}
bool check_yujuchuan(){
    FILE* temp = fp;
    getsym();
    if(sym==7){
        trace_back();
        return 1;
    }else{
        trace_back();
        return 0;
    }
}

int yuju(){
    FILE* temp = fp;
    getsym();
    if(sym == 6){
        trace_back();
        error = fuheyuju();
    }else if(sym==1){
        trace_back();
        error = fuzhiyuju();
    }else if(sym == 8){
        trace_back();
        error = tiaojianyuju();
    }else if(sym == 11){
        trace_back();
        error = xunhuanyuju();
    }else{
        {if (error==0) return (error=14); else return error;}
    }
    return error;
}
int fuheyuju(){
    getsym();
    error = yujuchuan();
    if(error == 0){
        getsym();
        if(sym == 7){
            return error;
        }else {if (error==0) return (error=15); else return error;}
    }
    return error;
}
int fuzhiyuju(){
    getsym();
    string final = TOKEN;
    getsym();
    if(sym == 29){
                error = biaodashi();
        cout<<strOfExpression<<"的四元式输出：\n";
        Gen_biaodashi(final);
        strOfExpression.clear();
        return error;
    }else {if (error==0) return (error=16); else return error;}
    
    
}
int tiaojianyuju(){
    getsym();
    cout<<" if \n";
    int temp1 = numOfFourGen;
    error = boolbiaodashi();
       if(error==0){
        getsym();
        if(sym==9){
            cout<<" then \n";
            int temp2 = numOfFourGen;
            

            error = yuju();
            if(error == 0){
                while(!check_tiaojianyuju()){
                    getsym();
                    error = yuju();
                    
                }
                    fillFchain(temp1,temp2);
                
                
                
                cout<<" if结束 \n";
            }
        }else {if (error==0) return (error=17); else return error;}
    }
    return error;
}
int xunhuanyuju(){
    getsym();
    cout<<" while \n";
        int temp1 = numOfFourGen;
    int jump = numOfFourGen;
    if(sym==11){
        error = boolbiaodashi();
        if(error==0){
            getsym();
            if(sym==12){
                cout<<" do \n";
                int temp2 = numOfFourGen;
                error=yuju();
                fillFchainWhile(temp1,temp2);

                cout<<" while结束 \n";
                quadList temp1;
                temp1.numOfFourGen = ++numOfFourGen;
                temp1.op = "j";
                temp1.op1 = "0";
                temp1.op2 = "0";
                temp1.result = to_string(jump+1);
                vecOfQuadList.push_back(temp1);

                
                
                
                
                
                
                return error;
            }else {if (error==0) return (error=19); else return error;}
        }
        return error;
    }else {if (error==0) return (error=18); else return error;}
}

bool check_tiaojianyuju(){
    FILE* temp = fp;
    getsym();
    if(sym!=10){
        trace_back();
        return 1;
    }else{
        trace_back();
        return 0;
    }
}
int biaodashi(){
    error = xiang();
    while(!check_biaodashi()){
        getsym();
        
        if(sym==18||sym==16){
            putsym();
            error = xiang();
        }else {if (error==0) return (error=25); else return error;}
        
    }
    return error;
}
int check_biaodashi(){
    FILE* temp = fp;
    getsym();
    if(sym!=16){
        trace_back();
        return 1;
    }else{
        trace_back();
        return 0;
    }
}
int xiang(){
    error = yinzi();
    while(!check_xiang()){
        getsym();
        if(sym==18||sym==17){
            putsym();
            
            error = yinzi();
        }else {if (error==0) return (error=25); else return error;}
        continue;
        
    }
    return error;
}
bool check_xiang(){
    FILE* temp = fp;
    getsym();
    if(sym!=18&&sym!=17){
        trace_back();
        return 1;
    }else{
        trace_back();
        return 0;
    }
}
int yinzi(){
    FILE* temp = fp;
    getsym();
    
    if(sym == 2){
        trace_back();
        error = changshu();
        
    }
    else if(sym == 32){
        putsym();
        error = biaodashi();
        getsym();
        
        if(sym==33){
            putsym();
            return error;
        }else {if (error==0) return (error=25); else return error;}
    }else if(sym==1){
        trace_back();
        error = biaozhifu();
        return error;
    }
    
    
    
    else {if (error==0) return (error=24); else return error;}
    
    
    return error;
}
int guanxibiaodashi(){
    error = biaodashi();
    if(error==0){
        error=guanxi();
        if(error==0){
            error=biaodashi();
            return error;
        }
        return error;
    }
    return error;
}
int guanxi(){
    getsym();
    putsym();
    if(sym>=23&&sym<=28){
        return error;
    }else {if (error==0) return (error=23); else return error;};
}


int boolbiaodashi(){
    
    error = guanxibiaodashi();
    
    while(!check_boolbiaodashi()){
        getsym();
        putsym();
        error = guanxibiaodashi();
    }
    cout<<strOfExpression<<"######\n\n";
    Gen_boolbiaodashi();
    strOfExpression.clear();

    return error;
    
}

bool check_boolbiaodashi(){
    getsym();
    if(sym==21||sym==22){
        
        
        trace_back();
        return 0;
        
        
    }else{
        
        
        trace_back();
        return 1;

    }
}
int changshu(){
    getsym();
    putsym();
    if(sym==2){
        return error;
    }else {if (error==0) return (error=21); else return error;};
}
int biaozhifu(){
    getsym();
    putsym();
    if(sym==1){
        return error;
    }else {if (error==0) return (error=22); else return error;};
    
}

/*################################语法分析部分##############################*/








/*################################输出四元式部分##############################*/


void putsym(){
    
    
    strOfExpression = strOfExpression+TOKEN+" ";
}

int nextNumOfFour(){
    numOfFourGen++;
    return numOfFourGen;

}
string nextT(){
    numOfT++;
    string tempT = "T" +to_string(numOfT);
    return tempT;
}

int issign(string c){

    if(c=="+"||c=="-"||c=="*"||c=="/"){
        return true;
    }else return false;


}
void Gen_biaodashi(string final){
    
    char buf[100];
    char res[100] = {0};
    trim(strOfExpression);
    strcpy(buf, strOfExpression.c_str());
    transform(buf,res);
    cout<<"\n";
    string tempOfAllString(&res[0],&res[strlen(res)]);
    string tempOfSign;
    stack<string> stackOfExpression;
    
    
    
    
    
    //cout<<tempOfAllString<<endl;
    stringstream ss;
    ss<<tempOfAllString;

    while(ss>>tempOfSign){
        if(tempOfSign=="("||tempOfSign==")"){
            continue;
        }
        if(issign(tempOfSign)){
            string tempT;
            tempT = nextT();
            string a = stackOfExpression.top();
            stackOfExpression.pop();
            
            
            
            //cout<<nextNumOfFour()<<"."<<"("<<tempOfSign<<","<<stackOfExpression.top()<<","<<a<<","<<tempT<<")"<<endl;
            
            quadList temp1;
            temp1.numOfFourGen = ++numOfFourGen;
            temp1.op = tempOfSign;
            temp1.op1 = stackOfExpression.top();
            temp1.op2 = a;
            temp1.result = tempT;
            
            vecOfQuadList.push_back(temp1);
            
            
            
            stackOfExpression.pop();
            stackOfExpression.push(tempT);
        }else{
            stackOfExpression.push(tempOfSign);
        }
    
    
    }
    //cout<<nextNumOfFour()<<"."<<"("<<":="<<","<<stackOfExpression.top()<<","<<" "<<","<<final<<")"<<endl;
    
    quadList temp2;
    temp2.numOfFourGen = ++numOfFourGen;
    temp2.op = ":=";
    temp2.op1 = stackOfExpression.top();
    temp2.op2 = " ";
    temp2.result = final;
    vecOfQuadList.push_back(temp2);


}
void Gen_boolbiaodashi(){
    stringstream ss;
    string temp;
    string operation;
    string op1;
    string op2;
    string next;
    ss<<strOfExpression;
    while(ss>>op1){
        ss>>operation;
        ss>>op2;
        if(ss>>next){
            if(next == "||"){
                quadList temp1;
                temp1.numOfFourGen = ++numOfFourGen;
                temp1.op = "j" + operation;
                temp1.op1 = op1;
                temp1.op2 = op2;
                temp1.result = to_string(0);
                vecOfQuadList.push_back(temp1);
                Tchain.push_back(numOfFourGen);
                
                quadList temp2;
                temp2.numOfFourGen = ++numOfFourGen;
                temp2.op = "j";
                temp2.op1 = "0";
                temp2.op2 = "0";
                temp2.result = to_string(numOfFourGen+1);
                vecOfQuadList.push_back(temp2);
            
            }else if(next == "&&"){
            
                quadList temp1;
                temp1.numOfFourGen = ++numOfFourGen;
                temp1.op = "j" + operation;
                temp1.op1 = op1;
                temp1.op2 = op2;
                temp1.result = to_string(numOfFourGen+2);
                vecOfQuadList.push_back(temp1);
               
                
                quadList temp2;
                temp2.numOfFourGen = ++numOfFourGen;
                temp2.op = "j";
                temp2.op1 = "0";
                temp2.op2 = "0";
                temp2.result = to_string(0);
                vecOfQuadList.push_back(temp2);
                Fchain.push(numOfFourGen);
            }
        
        }else{
            
            quadList temp1;
            temp1.numOfFourGen = ++numOfFourGen;
            temp1.op = "j" + operation;
            temp1.op1 = op1;
            temp1.op2 = op2;
            temp1.result = to_string(numOfFourGen+2);
            vecOfQuadList.push_back(temp1);
            
            
            quadList temp2;
            temp2.numOfFourGen = ++numOfFourGen;
            temp2.op = "j";
            temp2.op1 = "0";
            temp2.op2 = "0";
            temp2.result = to_string(0);
            vecOfQuadList.push_back(temp2);
            Fchain.push(numOfFourGen);

            
            int Tnum = ++numOfFourGen;
        
            for(int i = 0; i < Tchain.size(); i++){
                for(int j = 0; j< vecOfQuadList.size();j++){
                    if(vecOfQuadList[j].numOfFourGen == Tchain[i]){
                        vecOfQuadList[j].result = to_string(Tnum);
                    
                    }
                
                }
                
            }
            numOfFourGen--;
        
        
        
        }
    
    }
    
    
    
    /*typedef struct {
     int numOfFourGen;
     string op;
     string op1;
     string op2;
     int result;
     
     }quadList;*/
    
 
    
}
void printFourGen(){




    for(int i = 0; i < vecOfQuadList.size(); i++){
        cout << vecOfQuadList[i].numOfFourGen<<".("<<vecOfQuadList[i].op<<", "<<vecOfQuadList[i].op1<<", "<<vecOfQuadList[i].op2<<", "<<vecOfQuadList[i].result<<")"<<endl;
    }


}






void fillFchain(int x1,int x2){//限定回填的范围，仅仅如果F栈里的是在这个范围且vec中的等于栈里的数字的时候才会填
    while(!Fchain.empty()&&Fchain.top() <=x2 &&Fchain.top()>=x1){
        for(int i = 0; i < vecOfQuadList.size();i++){
            if(vecOfQuadList[i].numOfFourGen == Fchain.top()){
                vecOfQuadList[i].result = to_string(numOfFourGen+1);
                Fchain.pop();
                break;
            }
        
        
        }
    }

}
void fillFchainWhile(int x1,int x2){//限定回填的范围，仅仅如果F栈里的是在这个范围且vec中的等于栈里的数字的时候才会填
    while(!Fchain.empty()&&Fchain.top() <=x2 &&Fchain.top()>=x1){
        for(int i = 0; i < vecOfQuadList.size();i++){
            if(vecOfQuadList[i].numOfFourGen == Fchain.top()){
                vecOfQuadList[i].result = to_string(numOfFourGen+2);
                Fchain.pop();
                break;
            }
            
            
        }
    }
    
}






/*################################输出四元式部分##############################*/






                  



int main(){
    
    char scanin[100] = "/Users/lmy/Documents/151100331-李名扬-词法分析/语法分析/input2.txt";
    
    
    
    if ((fp=fopen(scanin,"r"))==NULL) //判断输入文件名是否正确
    {
        printf("\n打开语法分析输入文件出错!\n");
        return(1);//输入文件出错返回错误代码1
    }
    
    error = program();
    
    printFourGen();
    fclose(fp);
    
    
    switch(error){
        case 0:printf("语法分析无错误!\n");break;
        case 1:printf("程序应从program开头！\n"); break;
        case 2:printf("program后面必须是标识符！\n");break;
        case 3:printf("变量说明后面必须加分号!\n");break;
        case 4:printf("程序体中缺少begin!\n");break;
        case 5:printf("程序体后部语句出现错误或缺少end!\n");break;
        case 6:printf("程序体的end后面缺少句号!\n");break;
        case 7:printf("变量说明开头缺少var!\n");break;
        case 8:printf("变量表后面缺少：!\n");break;
        case 9:printf("变量名非法！(这里只能是integer)\n");break;
        case 10:printf("标识符非法！\n");break;
        case 11:printf("变量标识符后面出现错误！\n");break;
        case 13:printf("语句中出现语法错误！\n");break;
        case 14:printf("程序中存在一个语句不属于任何一种语句!"); break;
        case 15:printf("复合语句中表达式出现错误!");break;
        case 16:printf("语句中标识符后面有非法字符!");break;
        case 17:printf("条件语句中出现错误!"); break;
        case 19:printf("循环语句中出现错误!"); break;
        case 20:printf("关系符号不正确!"); break;
        case 21:printf("常数非法!"); break;
        case 22:printf("标识符有问题\n");break;
        case 23:printf("关系表达式不正确!");break;
        case 24:printf("因子中出现错误!");break;
        case 25:printf("算数表达式不正确!\n");break;
        case 26:printf("语句中出现语法错误!\n");break;
            
            
    }
    

    
    
    
}
