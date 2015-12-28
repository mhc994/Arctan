/*************************************************************/
/*      #                         #                          */
/*      #                         #                          */
/*     ###     # ###    #####   ######    ######  # ####     */
/*     # #     ##      #          #      #     #  ##    #    */
/*    #####    #       #          #      #     #  #     #    */
/*    #   #    #       #          #      #    ##  #     #    */
/*   ##   ##   #        #####      ###    #### #  #     #    */
/*                                                           */
/*                马浩程     自34     2013011504              */
/*************************************************************/

#include <iostream>
#include "FPNum.h"

using namespace std;

int main(int argc, char *args[])
{
//    cout<<"*************************************************************"<<endl;
//    cout<<"*      #                         #                          *"<<endl;
//    cout<<"*      #                         #                          *"<<endl;
//    cout<<"*     ###     # ###    #####   ######    ######  # ####     *"<<endl;
//    cout<<"*     # #     ##      #          #      #     #  ##    #    *"<<endl;
//    cout<<"*    #####    #       #          #      #     #  #     #    *"<<endl;
//    cout<<"*    #   #    #       #          #      #    ##  #     #    *"<<endl;
//    cout<<"*   ##   ##   #        #####      ###    #### #  #     #    *"<<endl;
//    cout<<"*************************************************************"<<endl;


//    FPNum *a,*b;
//    char s[999];
    int i=1000;

//    int32_t a=999999999,b=999999999;
//    cout<<a*(int64_t)b<<endl<<sizeof(a*(int64_t)b)<<endl<<endl;
    while(i--)
        try
        {
            char a[999],b[999];
            int32_t d;

//            cin>>a>>d;
//            FPNum *na=new FPNum(a);
//            FPNum *nq=new FPNum((*na)/d);
//
//            cout<<*nq<<endl;
//
//            delete(na);
//            delete(nq);

            cin>>a;
            FPNum *na=new FPNum(a);
            cout<<*na<<endl;

            cin>>b;
            FPNum *nb=new FPNum(b);
            cout<<*nb<<endl;
//
//
            cout<<(*na+*nb)<<endl<<(*na-*nb)<<endl<<(*na**nb)<<endl<<endl;

            delete na;
            delete nb;
//            cin>>s;
//            n=new FPNum(s);
//            FPNum d(*n);
//            FPNum k;
//
//            cout<<k<<endl;
//
//            k=d;
//
//            cout<<k<<endl;


        }
        catch (char const *s)
        {
            cout<<s<<endl<<endl;
        }
    return 0;
}