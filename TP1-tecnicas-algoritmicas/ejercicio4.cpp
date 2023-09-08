#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int provedMasCercana(int n, vector<int> proved){
    int res=proved[0];
    int distanciaMin=abs(n-proved[0]);

    for(int i=0;i<proved.size();i++){
        int distanciaActual=abs(n-proved[i]);

        if(distanciaActual<distanciaMin){
            distanciaMin=distanciaActual;
            res=proved[i];
        }
    }
    //qe pasa perkin//  esta bien // ta lista
    return res;
}

int calcularCosto(vector<int> chori, vector<int> proved){
    int res=0;
    for(int n: chori){
        int k = provedMasCercana(n,proved);
        res+=k;
    }
    return res;
}

int getMedian(vector<int> puestos, int begin, int end){ // end es exclusive!!!
    if(end - begin <= 1) return puestos[end]; // no toques nada puto
    int median = (end - begin)/2;
    return puestos[median];
// hacela de 0
}

vector<int> dondeChuchaPongoProov(vector<int> puestos, int k){

    vector<int> res;

    int begin = 0;
    int end = puestos.size()/k;
    int pasos = puestos.size()/k;

    for(int i = 0; i < k; i++){
        if(end + pasos == puestos.size()-1)
            res.push_back(getMedian(puestos,begin,end));
        else {
            res.push_back(getMedian(puestos, begin, end-1));
            begin = end;
            end += pasos;
        }//hola
    }
}

/*
 * partes = 7/3 = 2
 *
 * k = 3
 * 10 11 14 20 22 27 30
 *
 * getMedian(10,11,14
 *
 *
 * */


int main(){
    int tests;
    cin >> tests;
    vector<int> resCostos;
    vector<vector<int>> results;
    vector<int> mejorDisp;
    int puesto=0;
    int cantPuestos=0;
    int proved=0;
    int costoActual=0;
    vector<int> chori;

    for(int i=0;i<=tests;i++){
        cantPuestos=0;
        proved=0;

        cin >> cantPuestos >> proved;

        vector<int> choriNuevo(cantPuestos,0);
        chori=choriNuevo;

        for(int i=0;cantPuestos;i++){
            puesto=0;
            cin >> puesto;
            chori[puesto];
        }

    vector<int> mejorDisp=dondeChuchaPongoProov(chori,proved);
    int costoActual=calcularCosto(chori,mejorDisp);

    results.push_back(mejorDisp);
    resCostos.push_back(costoActual);
    }

    for(int i = 0; i < tests;i++){
        cout << resCostos[i] << endl;
        for (int j = 0; j < results[i].size(); j++) {
            cout<< results[i][j];
        }
        if(i != tests-1) cout << endl;
    }
    return 0;
}


/*





                                                                        ...............
                                                ..:^~~!77JJYY55PPGBBBBBB##############BBBBBBBBGGGPPP555YYYYY55P55Y?~.
                                       .:~!?J5PG##&@@@@@@@@&&&##BGGPPP55YYYJJJJJJJJJJ????777777????JJJJJJYYY5PPGB&@@#5!.
                                 :~?YPB#&@@@@@@&GP5YJ?7!!~~^^^^^^^~~!!!!777!!!~~~~~^^^~!!!!!~^:.                 :~?G@@BJ:
                            :~JP#&&BGYJ7~^^^^^^^:::^~~~~!!!!!!!!!~^^::................     .:^!7??7~:                ^Y&@#J:
                        .~JB&@#P?~:.:^~!77!!!~^:....    .....::^^~!777?77!!!!!!!!!!7!7777?7!~^.  .^!?J7~.              :5@@#?
                     .75#@@GJ^.   .7!:.:::^^~~~~~~~!!!7777???JJJ?77!^:..        ..........:^~!??J?!:. ^!J?!:             !#@@G^
                   ^Y#@@BJ^       .      ...:::::::...                      :~^~~~!!!!7!7777!~^^^^!?JJ!: .~?J!:           ^B@@#~
                  ~&@@G!.           :~!7!~!~~~^~~!!7???Y?.                 ~Y7.           ..:^~!777!~^!?J7^  ^77~:         :G@@#^
                  7@&!            !5J~:.             .^.^.                JJ.                     .:~77~:^7J!.  :~^.        .G@@G.
                  5@&.           ~J:                 :57                 .G.                          .^7! .^!~.             .P@@P
                 7@@G           .~                     Y^                 ~       .:^~!777??77!~^:.      :^   .:.             .5@@P.
                J&@&!                                  Y~                    .~?5G#&&&#@@@@@@@@@&&BGY7:                         J@@B!
              !B@@#!                ^7YPGBBBBGP5J7~:   ?^                 .7P#@@#GY7~::G@&&&&&&&&&@&&@&P!                        !B@@G!
            !G@@#J.        ....   ^G&@@BP555P&@@@@@&B57:                .J#@@G?^.    ..?@&&&@@@@@@@Y!7J#@G:  ~!^:::        :~~~~~^!B@@@B?:
          7B@@#?..!J5J7^^^^~!!7~ .Y##&&####&&@@@@@@@@@@#5^^~!!:         G@@@7   .~JPB&@&&&#BBBBBB##&&&B#@@G. .~?YG?      .:~~!!!!777?YP#@&5~
        ~G@@&J.^Y5J!^:.             :^^~!7??JJY5PGG#&@@&@&@@&B!         J#@@5Y5G#@&BGY?!~^:~!:  ..:^!7JJJ?^ .!~..  :~!7???7!~^.   ..:^!7!5&@P!
       ~&@@#^.YY^:~77^                             .^!5@&#J!^.           :7P&@#P?~:.       !@&G7:             .^75B&@@&#####&&#GJ~     ^!::J&@G^
       G@&&^^P~ !5~: ~?5PGGP5J?~:                     ~@@J                  :^.             7B@@&P?~:....:^~?5B&@@@#P?:.:...:^75#@B7.    ~. ^G@&?
      .&&@5 P:  ?^ :P@&&BGGPPG#@&B57: .~JY^           ~@@J                                   .~JPB&&######&&&#GPJ7~.  ^#G.      .7#@G^   .~  .G@@?
      .#&@77J  .Y: :!^:..  .. .7&@@@&G#@@#^         ^Y#@@J                                        .:^^~~~^^::.      .:J@@J        ^#@#:   7:  ^&@&:
       Y@@JJ?  .J.        .B&~  75Y555Y?~.       :?G@@#P?:                ^!?7!^.  ::                           :~?PB@@@&@G7:      7@@Y   ?:   P@@!
       ^#@B~P   77.       7@@J                .!P#@&5!.                  ~G&&&&@#G!!J:::::::::.            :~?5B&@&BPJ7!B@@@&P?^   ~&@P   !.   P@@7
        !@@Y57  .?Y!.    7&&@5             :!5#@@@@!                 ........::~B@&.^~~~~~~~~~7.     .:~?5G&@@@B5!:    ^&&@BB#&&P^ P@@!  :?   :&&@~
         7&@G5?7~:..    7@&&@#:        .^!??7G@#G&@B!            .?GB#&&##BP^  ^#@G             .^7JPB&@@@&B57^.      ^B@&J. .:::.Y@&?   7!   P@@P
          7&@B7^!7JJ?. ~&&&B&@B?:    :!7!^.  .7: :J#@5^     .    ^Y5YYJ??JPB:.G@@&~      .:^7JPB&@@@&#GB&@J         ^J&@&&.      :#G~   7G  .P@@B:
           !&@&?   .~. G@@BJ&&@@&P?^.              .J&@G?~!5#?               .JY?: :^!?5G#&@@&BP5?!^:. Y@@Y     :~?G&@&@&P:      .^  .^?5^ 7#@@5.
            !&@@7     :&&&&&@&7G@@@@B5?~:.           .?B&@@&J.           ..:~!7J5GB#&&#BPY?!^.        7&&@5!?YPB&@@@&@@G~         :~~~^..7G@@G!
             7@@#:    ~@&&&@&~ P@&PYB@@@&#GPY?7!^^:::..:~77^.:^^~!!7?Y5PG##&@&&&#GG@@B:            .!P@&&&&@@@#PJ?G@@#7           ....~5#@@P~
              P@@7    7@&&&@J  G@B  .^~5@@&B&@@@@&&&&###&&&&&&&&&&@@&##G5Y?7~^:.. .G@@!      .:~7JP#@@@&&&@G?^. ^G&@P:              ~?B@&5~
              7@@P    ?@&&&@? ~&@B.   .G@@7 :^~~!!7?5@&@YJJ?7~~^:J@@7.             7@@G.~7J5GB&&@@@@@&B&&&7    ?&@&?              .J#@@5^
              ^&@#    7@&&&&&PB@&@7.. P@@B.         J@@P         7@@!           .::!#@&#@@@@@@@@&#GY!:~@@G   ^P@@G^              .P@@B~
              .B@#.   ~@&&&&&@@&&&&#BPB@&B5J?7!~~~~^J@@?^~~~~~~~^Y@@J^^^^~!7?YPGB#&&&&&&@@@&BPY7^.    :#@&77P&@#?                5@@5.
              .B@#.   .&&&&&&&&&&&&&@@&&&&@@@@@&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@@@@&##&@5!~:.          ^B@@@@&5:                7@@5
              .B@#     5@&&@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@@@@&#BPJ7^.J@@?             ^?G@@&5^                 !&@G
              ^#@G     ~&@#Y&@&&&@@&&&@@&&&&&&&&&@&&&&&&&@@@@@@@@@@@&&&GP5Y7!^.      !@@#~         ^JB&@@#J^                  ?&@B:
              !@@J      Y@@5!B@@P!B@&&GG#&&&&&&##B#&@@&&&GBBGGGPYJ7~5@#:              ?&@&!    .^JG@@@#5!.                  ~G@@P:
              ?@@!      .G@@P~&@&~ 5@@P:.^~G@@?...:^7B@@#:          5@&~               !&@&~:!YB@@@B5!.                   ~P@@B!
              G@&^       :P@@G&BB?  Y@@B^  !&@&!      5@@?          G@@?              .:5@@#&@@#GJ~.    ..:.    .:^.   :?G@@G7.
             :&@G.        .?#@@&GYJ7!B&@5   7&@&~     .#@G          Y@@J       .:~7J5G#&@@&#PJ~.   .^!77!^:.:!JYY7^ :7P&@&P!
             !@@5           .!YG#@@@@@@@&BP5J#@@#?!^^^^P@@!^^^^^^^^~J@@BP555PGB#&@@@@&BPJ7^.   :~7JJ7~:.:!YPPY!:.:7P&@&G?:
             Y@@?               .^!7JY5GB##&@&&&@@@@@@@@@@@@@@@@@@@@@&&@@&&##BGP5J7!^:    .^!?J?!^..^7YP5J!: .~JB@@&P?^
             P@&^     :      ^~          ..:^^^~~~!!777???????777!!!~~~^^::..         :~7JJ?~^:^!JY5Y7^. .~JG&@&BY!:
            :B@&.     5:      ?5!:             .:^^~~~~~~~^^:^^^^^^:            .:~!???7~~~!?YYJ7^.  :!YB&@&B57:
            ^&@#      J^       ^JP5J!^:..       ..................... ...:^^~!777777!77???7~:.  .~?P#@@#GJ!:
            ~@@G       ~7~:       :~7????77!~^::.......::::::...::^~~~!!!!!7!77777!!~^:.   .^75B&@&B5?^.
            ~@@P        .~JJ?!^:.                          .....:::^~~~!!~~~^^:..      :~JP#@@#PJ!:
            ^&@#:          .^!?J?JJ?77!~~^^^^^^^^^^^^~~~^^^~!~^^^^^::..            :!JG&@&BY7^.
             ?@@G:                ...::::::::::..........                      :~JG&@&GJ!:
              !B@&?.                                               :^!7???77?5B&@#GJ~.
               .J#@#Y~.                                     .:~7JPB&@@@@@@@&#G57^.
                 .7G&@&GY7~:..                   ..::^!7?YPG#&@&&#BGP5J?7!^:.
                    :7YB&@@&&BGPP5YJJJJJJJYY5PPGB#&&&&&##GP5?7~^:.
                        .^!JYPGBB####&&####BBBP5YJ?7~^:..
                                 ..........



*/