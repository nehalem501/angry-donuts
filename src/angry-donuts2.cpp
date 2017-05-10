/* main.cpp */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <uuid/uuid.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "index.h"
#include "status.h"
#include "data.h"

size_t get_file_size(const char * fileName){
  struct stat st;
  if (stat(fileName,&st)){
    fprintf(stderr,"stat %s %d \n",fileName,errno);
    return EXIT_FAILURE;
  }
  return st.st_size;
}

uuid_t get_uiid_from_string(const char * string,const char * uiid_t uiid){
	if(uuid_parse(string,uuid) == -1){
        printf("error uuid_parse \n");
        exit(EXIT_FAILURE);
  	}
    return string;
}

int main(int argc, char *argv[]) {
	if(argc==3 || argc ==4){
		Index index(argv[1]);
		uuid_t uuid;
		uint64_t length;
		void * mmapped_zone;

		if (strcmp(argv[2],"put") == 0){
			int src = open(argv[3],'r');
			if(src < 0){
				perror("erreur lies a open\n");
				exit(EXIT_FAILURE);
			}
			mmapped_zone = mmap(NULL, get_file_size(argv[3]), PROT_READ, MAP_PRIVATE | MAP_POPULATE, src, 0);
			if(mmapped_zone == MAP_FAILED){
				perror("erreur lies a mmapped_zone PUT\n");
				exit(EXIT_FAILURE);
			}
			length = get_file_size(argv[2]);
			Data data((uint8_t*) mmapped_zone, length);
			if(argc == 3){
				/*
					angry-donuts nom_dossier put fichier
					-> renvoie l'uiid du nouveau fichier cree dans l'arborescence
				*/
				if (index.put(uuid, &data) != Status::Success)
			        std::cout << "error put" << std::endl;
			   	else
			   		std::cout << uuid << std::endl;
		      	if(munmap(mmapped_zone,length)==-1){
		        	perror("erreur lies a munmap\n");
			        return EXIT_FAILURE;
		      	}

			}
			if(argc == 4){
				/*
					angry-donuts nom_dossier put uuid fichier 
					-> met a jour le fichier avec le même uiid
					TOMEK A L'AIDE
				*/


			}
		}
		if(strcmp(argv[2],"get") == 0 ){

					/*
						angry-donut nom_dossier get uuid
						-> affiche le contenu du fichier
					*/
				get_uiid_from_string(argv[3],uuid);
			  	Data data2;
  			if(argc==3){
  				if (index.get(uuid, &data2) != Status::Success)
   	 				std::cout << "error get" << std::endl;
			}

			if(argc == 4){
					/*
						angry-donut nom_dossier get uuid fichier 
						-> cree un fichier avec le contenu de l'uiid
					*/
				int dst = open(argv[4],O_RDWR | O_CREAT | O_TRUNC,0644);
				if(dst < 0){
					perror("erreur open \n");
					exit(EXIT_FAILURE);
				}
				void * mapped_zone = mmap(NULL, data2.length, PROT_READ, MAP_PRIVATE | MAP_POPULATE, src, 0);
				if(mmapped_zone == MAP_FAILED){
					perror("erreur lies a mmapped_zone GET");
					exit(EXIT_FAILURE);
				}
				memcpy(mapped_zone,data2,data2.length);
				exit(EXIT_SUCCESS);


			}
		}
		if (strcmp(argv[2],"del") == 0 ){
      		if (index.del(uuid) == Status::Success)
        		std::cout << "success on delete!" << std::endl;
      		else
        		std::cout << "delete error..." << std::endl;
    	}
	}
	else{
		std::cout << "Error: missing argument" << std::endl;
        //std::cout << "Usage: angry-donuts /path/to/data" << std::endl;
        std::cout << "Usage : Angry nom du dossier commande UID" << std::endl;
        exit(EXIT_FAILURE);
	}
	return 0;
}