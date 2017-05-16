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


#include <cstdio>
#include <cctype>
#include <cstring>
#include <map>
#include <string>
#define ID 1
#define INT 2
#define PROGRAM 3
#define PROCEDURE 5
#define VAR 4
#define BEGIN 6
#define END 7
#define IF 8
#define THEN 9
#define ELSE 10
#define WHILE 11
#define DO 12
#define CALL 13
#define INTEGER 14
#define REAL 15
#define SIGN16 16
#define SIGN17 17
#define SIGN18 18
#define SIGN19 19
#define SIGN20 20
#define SIGN21 21
#define SIGN22 22
#define SIGN23 23
#define SIGN24 24
#define SIGN25 25
#define SIGN26 26
#define SIGN27 27
#define SIGN28 28
#define SIGN29 29
#define SIGN30 30
#define SIGN31 31
#define SIGN32 32
#define SIGN33 33
#define SIGN34 34
using namespace std;
char  TOKEN[200];
int error1 = 1;
int numOfID = 0;
char* keyword[16]= { " "," "," ","program","var","varprocedure","begin","end","if","then","else","while","do","call","integer","real"};
map <string,int> map1;


int lookup(char* str)
{
    for(int i = 1; i <=15; i++ )
    {
        if(strcmp(str,keyword[i])==0)
        {
            return i;
        }
    }
    return 0;
}


void out(int num, char* c,FILE* fout)
{

    if(num==1)
    {
        string str(c);
        if(map1[str]!=0)
        {
            fprintf(fout,"(%d,%d)%s\n",num,map1[str],c);
        }
        else
        {

            numOfID++;
            map1[str] = numOfID;
            fprintf(fout,"(%d,%d)%s\n",num,numOfID,c);
        }
    }
    else if(num==2)
    {
        fprintf(fout,"(%d,%s)%s\n",num,c,c);

    }
    else if(num>=3&&num<=15)
    {
        fprintf(fout,"(%d,0)%s\n",num,keyword[num]);

    }
    else if(num == 24)
    {
        fprintf(fout,"(24,0)<=\n");
    }
    else if(num == 26)
    {
        fprintf(fout,"(26,0)>=\n");
    }
    else if(num == 28)
    {
        fprintf(fout,"(28,0)<>\n");
    }
    else if(num == 29)
    {
        fprintf(fout,"(29,0):=\n");
    }
    else
    {
        fprintf(fout,"(%d,0)%s\n",num,c);

    }

}


void report_error(int error,FILE *fout)
{
    fprintf(fout,"**error(%d)**\n",error);

}

void scanner(FILE *fp,FILE *fout)
{
    char ch = '\0';
    int i,c;

    while(fscanf(fp,"%c",&ch)!=EOF)
    {
        if(isspace(ch))
        {

            continue;
        }
        else if(isalpha(ch))
        {
            TOKEN[0] = ch;
            ch = fgetc(fp);
            i = 1;
            while(isalnum(ch))
            {
                TOKEN[i] = ch;
                i++;
                ch = fgetc(fp);

            }
            TOKEN[i] = '\0';
            fseek(fp,-1,1);
            c = lookup(TOKEN);
            if(c == 0) {
                    if(strlen(TOKEN) <=8)
                    out(1,TOKEN,fout);
                    else{
                        report_error(error1++,fout);
                    }

            }
            else out(c," ",fout);


        }
        else if(isdigit(ch))
        {
            TOKEN[0] = ch;
            ch = fgetc(fp);
            i = 1;
            while(isdigit(ch))
            {
                TOKEN[i] = ch;
                i++;
                ch = fgetc(fp);
            }
            TOKEN[i] = '\0';
            fseek(fp,-1,1);
            out(INT,TOKEN,fout);
        }
        else
        {
            switch(ch)
            {
            case'/':
                ch = fgetc(fp);
                if(ch == '*')
                {
                    char a,b;
                    while(fscanf(fp,"%c",&a)!=EOF)
                    {
                        if(a=='*')
                        {
                            b=fgetc(fp);
                            if(b=='/')
                            {
                                break;
                            }
                            else
                            {
                                fseek(fp,-1,1);
                                continue;
                            }
                        }
                    }
                }
                else
                {
                    fseek(fp,-1,1);
                    out(SIGN19,"/",fout);
                    break;


                }
                break;

            case'<':
                ch = fgetc(fp);
                if(ch=='=')out(SIGN24,">=",fout);
                else if(ch=='>') out(SIGN28,"<>",fout);
                else
                {
                    fseek(fp,-1,1);
                    out(SIGN23,"<",fout);
                }
                break;
            case'=':
                out(SIGN27,"=",fout);
                break;

            case'>':
                ch = fgetc(fp);
                if(ch=='=') out(SIGN27,">=",fout);
                else
                {
                    fseek(fp,-1,1);
                    out(SIGN25,">",fout);
                }
                break;

            case'+':
                out(SIGN16,"+",fout);
                break;
            case'-':
                out(SIGN17,"-",fout);
                break;
            case'*':
                out(SIGN18,"*",fout);
                break;
            case'~':
                out(SIGN20,"~",fout);
                break;
            case'&':
                ch = fgetc(fp);
                if(ch=='&')out(SIGN21,"&&",fout);
                else
                {
                    report_error(error1++,fout);
                    fseek(fp,-1,1);
                }
                break;
            case'|':
                ch = fgetc(fp);
                if(ch=='|')out(SIGN21,"||",fout);
                else
                {
                    report_error(error1++,fout);
                    fseek(fp,-1,1);
                }
                break;
            case'(':
                out(SIGN32,"(",fout);
                break;
            case')':
                out(SIGN33,")",fout);
                break;
            case';':
                out(SIGN30,";",fout);
                break;


            case':':
                ch = fgetc(fp);
                if(ch == '=') out(SIGN29,":=",fout);
                else
                {
                    out(SIGN34,":",fout);
                    fseek(fp,-1,1);

                }
                break;



            case',':
                out(SIGN32,",",fout);
                break;
                 case'.':
                out(SIGN31,".",fout);
                break;
            default:
                report_error(error1++,fout);
                break;



            }
        }

    }

}
int main()
{
    char scanin[100];
    char scanout[100];
    FILE *fin,*fout;
    printf("请输入源程序文件名（包括路径）：");
    scanf("%s",scanin);

    printf("请输入词法分析输出文件名（包括路径）：");
    scanf("%s",scanout);

    if ((fin=fopen(scanin,"r"))==NULL) //判断输入文件名是否正确
    {
        printf("\n打开词法分析输入文件出错!\n");
        return(1);//输入文件出错返回错误代码1
    }
    if ((fout=fopen(scanout,"w"))==NULL) //判断输出文件名是否正确
    {
        printf("\n创建词法分析输出文件出错!\n");
        return(2); //输出文件出错返回错误代码2
    }
    scanner(fin,fout);
    fclose(fin);
    fclose(fout);



}




















