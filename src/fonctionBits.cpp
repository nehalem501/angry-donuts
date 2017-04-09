#include <iostream>
#include <string>
#include <uuid/uuid.h>
#include "status.h"
#include<math.h>
using namespace std;

#define NB_CARACTERE 2 
#define NB_POSSIBILITE 256
#define NB_OCTET NB_POSSIBILITE / 8

// structure permettant de recuperer tout le tableau d'octet dans index 
struct uuid_bit {
  uint8_t tableauBit  [NB_OCTET]; 
}uuid_bit ; 


// fonction qui pour chaque chaine hexadecimal renvoie en int sa valeur decimal 
int transformeChaineEnInt (string uuid) {
  if(uuid.length() != NB_CARACTERE) 
    return -1 ; 
  else {
    int retour = stoi(uuid,0,16);
    cout << retour << endl ; 
    return retour ; 
  }
}

// envoie error si le bit est deja a 1 , et success si il est a 0 ,il met le bit a 1 
Status putBit (struct uuid_bit * tab , string uuid) {
  Status status ; 
  int num = transformeChaineEnInt (uuid);
  if(num == -1){
    status = Status::Error ;
     return status ;
  }
  int position = num / 8 ; 
  int reste = num% 8 ; 
  if( (tab->tableauBit[position]>>reste)&1)
    status = Status::Error ; 
  else {
    tab->tableauBit[position] = tab->tableauBit[position] | (1<<reste) ;
    status = Status::Success ; 
  }
  return status ;
}

// envoie success si le bit est a 1 , et noId si le bit est a 0 
Status getBit (struct uuid_bit * tab , string uuid) {
  Status status ; 
  int num = transformeChaineEnInt (uuid);
  if(num == -1){
    status = Status::Error ;
     return status ;
  }
  int position = num / 8 ; 
  int reste = num% 8 ; 
  if( (tab->tableauBit[position]>>reste)&1)
    status = Status::Success ; 
  else {
    status = Status::NoID ; 
  }
  return status ;
}
// permet de mettre un bit a 0 , renvoie noId si le bit en question n'est pas à 1 ; 
Status delBit  (struct uuid_bit * tab , string uuid) {
  Status status ; 
  int num = transformeChaineEnInt (uuid);
  if(num == -1){
    status = Status::Error ;
     return status ;
  }
  int position = num / 8 ; 
  int reste = num% 8 ; 
  if( (tab->tableauBit[position]>>reste)&1){
    tab->tableauBit[position] = tab->tableauBit[position] & ~(1<<reste) ;
    status = Status::Success ; 
  }
  else {
    status = Status::NoID ; 
  }
  return status ;
}

// test des fonctions , utilise la valeur des bits de charateres pour verifier
int main () {
  cout << "test de gerer index Bit" << endl ;
  struct uuid_bit tab ; 
  tab.tableauBit[0] = 'c' ; //01100011
  tab.tableauBit[1]= 'c' ;  //01100011 
  Status st = getBit(&tab , "00");
  switch(st){
  case Status::Error : cout << "Error" <<endl ;  break ; 
  case Status::Success : cout << "Success" << endl; break ;
  case Status::NoID : cout <<"NoID" << endl ; break ; 
  }
  cout << tab.tableauBit[0] << endl; 
  cout << tab.tableauBit[1] <<endl ; 
  return 0 ; 
}
