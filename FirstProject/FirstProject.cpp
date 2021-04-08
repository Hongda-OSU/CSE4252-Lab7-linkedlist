#include <iostream>

using namespace std;

void swap_values(int *ptr_first, int *ptr_scond){
     int temp = *ptr_first;
     *ptr_first = *ptr_scond;
     *ptr_scond = temp;

}

int main()
{
    int first_num, second_num;
    cout<<"Enter two number : ";
    cin>>first_num>>second_num;
    int *ptr_first = &first_num, *ptr_scond = &second_num;
    swap_values(ptr_first, ptr_scond);
    cout<<"The value now is: " <<first_num<<" "<<second_num;

}
