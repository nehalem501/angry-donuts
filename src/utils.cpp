/* utils.cpp */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <uuid/uuid.h>

#include "utils.h"

using namespace std;

string get_path(uuid_t id, string directory) {
    char path_str[37];
    uuid_unparse(id, path_str);
    string path(path_str);
    directory.append(path);
    return directory;
}

// A tester (Il ne devrait pas y avoir de problème ) Valloris
string get_path2 (uuid_t id , string directory ) {
  char path_str[37];
  uuid_unparse(id, path_str);
  for(int i = 0 ; i < 37 ; i ++)
    if(path_str[i] == '-')
      path_str =='\\'; 
  string path(path_str);
  directory.append(path);
  return directory;
}

// Karim -----------------------------------------------------------------------

// 	Split un string avec le charactere donne en argument et renvoie un vecteur 
//	de string.

vector<string> splitStringToVector(string str, char char_splitter) {
	vector<string> vectored_tokens;
	stringstream myStringAsStream(str); // Turn the string into a stream.
	string resulted_token;

	while(getline(myStringAsStream, resulted_token, char_splitter)) {
		vectored_tokens.push_back(resulted_token);
	}

	return vectored_tokens;
}

// Creer l'arborescence de dossier object_path à partir d'une racine root_path
void create_path(string root_path, string object_path) {
	char char_splitter = '/';
	vector<string> v = splitStringToVector(object_path,char_splitter);
	string fil_dAriane = root_path;
	for(string s : v){
		fil_dAriane += char_splitter + s;
		mkdir(fil_dAriane.c_str(), ACCESSPERMS);
	}
}
// Fin Karim -------------------------------------------------------------------
