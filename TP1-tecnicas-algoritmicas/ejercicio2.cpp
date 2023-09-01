#include <iostream>
#include <vector>

using namespace std;

#define tripla pair<double, pair<int64_t, int64_t>>

void merge(tripla arr[], int l, int mid, int r){

    int n1=mid-l+1;
    int n2=r-mid;

    tripla a[n1];
    tripla b[n2]; // temp arrays

    for(int i=0;i<n1;i++){
        a[i]=arr[l+i];
    }
    for(int i=0;i<n2;i++){
        b[i]=arr[mid+1+i];
    }
    int i=0;
    int j=0;
    int k=l;
    while(i<n1 && j<n2){
        if(a[i].first>b[j].first || (a[i].first==b[j].first && a[i].second.second > b[j].second.second)){
            arr[k]=a[i];
            k++; i++;
        }
        else {
            arr[k]=b[j];
            k++; j++;
        }
    }
    while(i<n1){
        arr[k]=a[i];
        k++; i++;
    }

    while(i<n2){
        arr[k]=b[j];
        k++; j++;
    }
}

void mergeSort(tripla arr[], int l, int r){
    if(l<r){
        int mid=(l+r)/2;
        mergeSort(arr,l,mid);
        mergeSort(arr,mid+1,r);

        merge(arr,l,mid,r);
    }
    // espera que vaytamos paso a paso hdp, estamos testeando haceme caso boludo, mira geeks el mergesort
}

int main() {

    int tests = 0;
    cin >> tests;

    int64_t outputs[tests];

    for(int i = 0; i != tests; i++){
        int largo = 0;
        cin >> largo;

        int64_t desc[largo];
        int64_t minutos[largo];
        tripla coeficientes[largo];

        for(int j = 0; j != largo; j++){
            int64_t num = 0;
            cin >> num;
            desc[j] = num;
        }
        for(int j = 0; j != largo; j++){
            int64_t num = 0;
            cin >> num;
            minutos[j] = num;

            float coef = double(desc[j]) / double(minutos[j]);
            tripla tripla_con_coef = make_pair(coef, make_pair(minutos[j], desc[j]));
            coeficientes[j] = tripla_con_coef;
        }

        int64_t result = 0;
        int64_t minutos_acum = 0;

        mergeSort(coeficientes, 0, largo-1);

        for(int k = 0; k < largo; k++){
            minutos_acum += coeficientes[k].second.first;
            result += minutos_acum * coeficientes[k].second.second;
        }

        outputs[i] = result;
    }

    for (int l = 0; l < tests; l++){
        if (l == tests - 1) cout<< outputs[l] % int64_t (1000000000+7);
        else cout<< outputs[l] % int64_t (1000000000+7) << endl;
    }
    return 0;
}