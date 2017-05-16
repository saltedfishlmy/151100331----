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
#include <cstring>

using namespace std;
char  TOKEN[200];
int value;
int sym = 0;
int error = 0;
FILE *fp;

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

char str[100];

void getsym(){

    fscanf(fp,"%s\n",str);
    sscanf(str,"(%d,%d)%s",&sym,&value,TOKEN);
    printf("%d\n",sym);

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
            }else return(error=2);

        }else return(error=2);

    }else{
        return(error=1);
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
                    else return(error=6);
                }else  return(error=5);
            }else return(error);
        }else return(error=4);



    }else return(error);
}
int bianliangshuoming(){
    getsym();
    if(sym == 4){
        error = shuomingbiao();
        return error;
    }else return (error=7);


}

int shuomingbiao(){
    error = bianliangbiao();
    if(error==0){
        getsym();
        if(sym==34){
            error = leixing();

        }else return(error=8);

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
    }else return(error=9);
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
                }else return(error=10);
            }else return(error = 11);
        }

    }else return(error=10);
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
            }else return(error);
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
        return (error=14);
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
        }else return (error=15);
    }
    return error;
}
int fuzhiyuju(){
    getsym();
    getsym();
    if(sym == 29){
        error = biaodashi();
        return error;
    }else return (error=16);


}
int tiaojianyuju(){
    getsym();
    error = guanxibiaodashi();
    if(error==0){
        getsym();
        if(sym==9){
            error = yuju();
            if(error == 0){
                while(!check_tiaojianyuju()){
                    getsym();
                    error = yuju();
                    return error;
                }
            }
        }else return (error=17);
    }
    return error;
}
int xunhuanyuju(){
    getsym();
    if(sym==11){
        error = guanxibiaodashi();
        if(error==0){
            getsym();
            if(sym==12){
                error=yuju();
                return error;
            }else return (error=19);
                }
        return error;
    }else return(error=18);
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
        error = xiang();
        }else return(error=25);
        continue;

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
        if(sym==18||sym==16){
        error = yinzi();
        }else return(error=25);
        continue;

    }
    return error;
}
bool check_xiang(){
    FILE* temp = fp;
    getsym();
    if(sym!=18){
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
        error = biaodashi();
        getsym();
        if(sym==33){
            return error;
        }else return (error=19);
    }else if(sym==1){
        trace_back();
        error = biaozhifu();
        return error;
    }



    else return (error=24);


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
    if(sym>=23&&sym<=28){
        return error;
    }else return (error=23);
        }


int boolbiaodashi(){

    check_boolbiaodashi();


    return 0;

}

bool check_boolbiaodashi(){

    int back_value = 0;

    while( fscanf(fp,"%s\n",str)){
        back_value+=strlen(str);

        sscanf(str,"(%d,%d)%s",&sym,&value,TOKEN);
        if(sym==9||sym==12||sym==23||sym==24||sym==25||sym==26||sym==27||sym==28){
            fseek(fp,-back_value,SEEK_CUR);
            return 0;
        }else if(sym==21||sym==22){
            fseek(fp,-back_value,SEEK_CUR);
            return 1;

        }else{

        }

    }
    fseek(fp,-back_value,SEEK_CUR);

    return 0;













}




int changshu(){
    getsym();
    if(sym==2){
        return error;
    }else return (error=21);
}
int biaozhifu(){
    getsym();
    if(sym==1){
        return error;
    }else return (error=22);

}



int main(){

    char scanin[100];
    printf("请输入源程序文件名（包括路径）：");
    scanf("%s",scanin);


    if ((fp=fopen(scanin,"r"))==NULL) //判断输入文件名是否正确
    {
        printf("\n打开词法分析输入文件出错!\n");
        return(1);//输入文件出错返回错误代码1
    }

    error = program();
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
        case 11:printf("变量标识符之间没有用逗号分隔！\n");break;
        case 13:printf("语句和语句串之间应该用缺少分号！\n");break;
        case 14:printf("程序中存在一个语句不属于任何一种语句!"); break;
        case 15:printf("复合语句中表达式出现错误!");break;
        case 16:printf("语句中标识符后面有非法字符!");break;
        case 17:printf("条件语句中出现错误!"); break;
        case 19:printf("循环语句中缺少do!"); break;
        case 20:printf("关系符号不正确!"); break;
        case 21:printf("常数非法!"); break;
        case 22:printf("标识符有问题\n");break;
        case 23:printf("关系表达式不正确!");break;
        case 24:printf("因子不正确!");break;
        case 25:printf("算数表达式不正确!\n");break;
        case 26:printf("语句中出现错误!\n");break;


    }



}
