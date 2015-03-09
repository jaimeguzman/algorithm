#include<iostream>
 
using namespace std;




LinkedListNode* reverse_iterateive(LinkedListNode* head){

		if(head == nullptr || head->next == nullptr ){
			return head;
		}

	LinkedListNode* list_to_do = head->next;
	LinkedListNode* reverse_list = head;
	reverse_list-> next = nullptr;

		while( list_to_do!=nullptr){
			LinkedListNode* temp = list_to_do;
			list_to_do = list_to_do->next

			temp->next = reverse_list;
			reverse_list = temp;
		}



	return reverse_list;
}





int main(){

	int uno =0;
	cin >> uno;
	cout << "HOLA MUNDO "<< endl;


	return 0;
}