//tim McVicker
//this program takes 1-20 lines of MIPS instructions, from stdin,
//and prnts the 5-stage pipeline diagram to stdout
#include <iostream>
#include <fstream>
using namespace std;

struct Inst
{
  string type;
  string dest;
  string src1;
  string src2;
  int wb;
  int IF;
  int id;
  int ex;
  int dm;
  Inst* next;
};



int main(void)
{
  Inst* head = NULL, *iter;
  string* list = new string[20];

  int* regStop = new int[16];
  for(int k = 0; k < 16; k++){

    regStop[k] = 0;
  }

  string s, t;
  int i = 0;
  while(cin >> s)
    {
      cin >> t;
      if(head == NULL){

	head = new Inst();
	iter = head;
      }
      else{
	iter->next = new Inst();
	iter = iter->next;
      }
      if(s == "sw" || s == "lw")
	list[i++] = s + "  " + t;
      else
	list[i++] = s + " " + t;
      iter->type = s;
      if(s == "lw"){
	iter->dest = t.substr(0, 2);
	
	iter->src1 = t.substr(5, 2);     
      }
      else if(s == "sw"){
	iter->src2 = t.substr(5, 2);
	iter->src1 = t.substr(0, 2);
      }
      else{
	iter->dest = t.substr(0, 2);
	iter->src1 = t.substr(3, 2);
	iter->src2 = t.substr(6, 2);
      }

    }

  iter = head;
  Inst* last = NULL;
  i = 0;
  while(iter != NULL)
    {
      int srcreg, srcreg2, destreg;
      if(iter->type == "lw"){
	srcreg = (iter->src1)[1] - '0';
	srcreg2 = -1;
	destreg = (iter->dest)[1] - '0';
      }
      else if(iter->type == "sw"){
	srcreg = (iter->src1)[1] - '0';
	srcreg2 = (iter->src2)[1] - '0';
	destreg = -1;
      }
      else{
	srcreg = (iter->src1)[1] - '0';
	srcreg2 = (iter->src2)[1] - '0';
	destreg = (iter->dest)[1] - '0';
      }
      if(srcreg > 9)
	srcreg = ((iter->src1)[1] - 'a') + 9;
      if(srcreg2 >9)
	srcreg2 = ((iter->src2)[1] - 'a') + 9;
      if(destreg > 9)
	destreg = ((iter->dest)[1] - 'a') + 9;

      iter->IF = i++;
      int waits = 0;
      if(regStop[srcreg] > i)
	i = regStop[srcreg];
      if(regStop[srcreg2] > i)
	i = regStop[srcreg2];

      iter->id = i;
      iter->ex = i+1;
      iter->dm = i+2;
      iter->wb = i+3;

      if(destreg > -1)
	regStop[destreg] = iter->wb;

      iter = iter->next;
    }
  iter = head;
 
  i = 0;
  while(iter != NULL)
    {
      cout << list[i] << "  ";


   for(int k = 0; k <= iter->wb; k++){
	if(k == iter->IF)
	  cout << "IF ";
	else if(k == iter->id)
	  cout << "ID ";
	else if(k == iter->ex)
	  cout << "EX ";
	else if(k == iter->dm)
	  cout << "DM ";
	else if(k == iter->wb)
	  cout << "WB" << endl;
	else
	  cout << "   ";

      }
      i++;
      iter = iter->next;
    }
 


  return 0;
}
