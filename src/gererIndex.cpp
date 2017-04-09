#include <iostream>
#include <string>
#include <uuid/uuid.h>
#include <cerrno>
#include "status.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h> 
#include<math.h>
using namespace std;


string get_pathIndex (uuid_t id , string directory , string *nomFichier ) {
  char path_str[37];
  uuid_unparse(id, path_str);
  string pathTest (path_str) ;
  cout << pathTest << endl ; 
  int compteur = 0 ;
  for(int i = 0 ; i < 37 ; i ++){
    if(compteur < 4 ) {
      if(path_str[i] == '-'){
	compteur ++ ; 
	path_str[i]='/'; 
      }
    }
    else {
      *nomFichier += path_str[i] ; 
      path_str[i] = '\0' ; 
    }
  }
  string path(path_str);
  directory.append(path);
  return directory;
}


Status putIndex  (uuid_t id, string directory) {
  cout << "fonction put index" << endl ; 
  Status status;
  string nomFichier ;
  string path = get_pathIndex(id,directory,&nomFichier);
  path.append("index.txt") ; 
  cout << "path put : "+ path << endl ; 
  int fd = open (path.c_str(), O_CREAT|O_WRONLY);
  if(fd == -1){
    if(errno == ENOENT) {
      cout << "erreur path n'existe pas " << endl ; 
    }
    status = Status::Error ; 
  }
  else {
    
  }
  return status ; 
}

Status getIndex (uuid_t id, string directory) {
  cout << "fonction get index" << endl ; 
  Status status;
  string nomFichier ;
  string path = get_pathIndex(id,directory,&nomFichier); 
  cout << "je suis ici" + path + " fichier : " + nomFichier << endl ; 
  return status ;
}

Status delIndex  (uuid_t id, string directory) {
  cout << "fonction del index" << endl ; 
  Status status;
  string nomFichier ;
  string path = get_pathIndex(id,directory,&nomFichier); 	
  return status ; 
}

int main () {
  cout << "test de gerer index " << endl ;
  uuid_t id ;
  uuid_generate(id); 
  string directory = "../../test/";
  putIndex(id,directory);
  return 0 ; 
}
