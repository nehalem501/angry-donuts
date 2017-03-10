/* main.cpp */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <uuid/uuid.h>
#include <sys/mman.h>

#include "index.h"
#include "status.h"
#include "data.h"
#include <sys/stat.h>
#include <sys/types.h>


bool fileExist(const std::string& file){
    struct stat buf;
    return (stat(file.c_str(),&buf) == 0 ); 
}


//Angry nom du dossier commande UID

int main(int argc, char *argv[]) {
    if(argc == 4){
		//index fait directement le test pour savoir si c'est un dossier
	    int file_descriptor;
	    struct stat fileStat;
	    Index index(argv[1]);
	    std::string t = "Bla bla bla!";
	    if !fileExist(argv[1]){
	    	std::cout << "erreur le fichier n'existe pas " << std::endl;
	    }
	    std::fstream fs;
		fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		file_descriptor = open(argv[1],O_RDONLY);
        if(stat(argv[1],&fileStat) < 0){    
        	printf("erreur lies a stat \n");
       	 	return EXIT_FAILURE;
       	}
	    char * mapped_addr = mmap(NULL,fileStat.st_size,PROT_READ,MAP_PRIVATE,fd,fileStat.st_size);
	    //const char *test = t.c_str();
	    uint64_t length = strlen(mapped_addr);
	    Data data((uint8_t*) mapped_addr, st.st_size);
		Data data2;
	    uuid_t uuid;

        switch(argv[1]){
            case "put":
            	if (index.put(uuid, &data) != Status::Success){
        			std::cout << "error put" << std::endl;
        			munmap(mapped_addr);
        			exit(EXIT_FAILURE);
            	}
               printf("%s \n",put(uuid_t returned_id, argv[2]));
            case "get":
            	if (index.get(uuid, &data2) != Status::Success){
       				std::cout << "error get" << std::endl;
       				munmap(mapped_addr);
       				exit(EXIT_FAILURE);
       			}
                else
                	get(uuid_t id, Data *data);
        	case "delete":
        		if (index.get(uuid, &data2) != Status::Success){
       				std::cout << "error get" << std::endl;
       				munmap(mapped_addr);
       				exit(EXIT_FAILURE);
       			}
       			else{
	        	    if (index.del(uuid) == Status::Success)
	        			std::cout << "success on delete!" << std::endl;
				    else
	        			std::cout << "delete error..." << std::endl;
	        	}
        }   
    }
    else{
        std::cout << "Error: missing argument" << std::endl;
        std::cout << "Usage: angry-donuts argument /path/to/data" << std::endl;
        std::cout << "argument : get,put,delete" << std::endl;
        exit(EXIT_FAILURE);
    }

    
    /* on lui donne un UUID vide et si ça réussit ça retourne un UUID valide par pointeut */
   
   /* 
    if (length != data2.length) {
        std::cout << "error, different content (length)" << std::endl;
    } else {
        if (memcmp(data.bytes, data2.bytes, length) != 0)
            std::cout << "error, different content (bytes)" << std::endl;
        else
            std::cout << "success on put and get!" << std::endl;
    }
*/

    return 0;
}
