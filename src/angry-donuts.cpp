/* main.cpp */

using namespace std;

#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <uuid/uuid.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <regex.h>
#include <unistd.h>

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

bool is_dir(const char * fileName){
  struct stat st;
  if (stat(fileName,&st)){
     fprintf(stderr,"stat ISDIR %s %d \n",fileName,errno);
    return EXIT_FAILURE;
  }
    return st.st_mode && S_IFDIR;
  
}

void get_uiid_from_string(const char * string,unsigned char * uiid){
  cout << string << endl;
  cout << uiid << endl;

  /*
    Il faut tester si l'entree est bien un uiid:
      si ça ne contient pas de slash par exemple ou de caractere speciaux.
  */
  if(uuid_parse(string,uiid) == -1){
        printf("error uuid_parse \n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
  std::cout << "argc "  << argc << std::endl;
  if(argc==3 || argc ==4 || argc == 5){
    Index index(argv[1]);
    uuid_t uuid;
    uint64_t length;
    void * mmapped_zone;
    if (!is_dir(argv[1])){
      std::cout << "Second argument is not a directory" << std::endl;
      exit(EXIT_FAILURE);
    }

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
      if(argc == 4){
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
            std::cout << uuid << std::endl;
      }
      if(argc == 5){
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
        if (index.get(uuid, &data2) != Status::Success)
          std::cout << "error get" << std::endl;
        
        if(argc==4){
          std::cout << data2.bytes << endl;
      }

      if(argc == 5){
          /*ama
            angry-donut nom_dossier get uuid fichier 
            -> cree un fichier avec le contenu de l'uiid
          */
     //   char * path_beginning;
    //  ssize_t src_size;
        /*
        for(int i = 0;i<argc;i++){
          cout << "index " << i << " = " <<   argv[i] << endl;
        }
        *
        if(strchr(argv[1],'/')==NULL){
          path_beginning = strcat(argv[1],"/");
        }
        cout << path_beginning << endl;
        if(chdir(path_beginning)==-1){
          perror("chdir path_beginning \n");
          exit(EXIT_FAILURE);
        }
        int src = open(argv[3],O_RDONLY);
        
        if(src < 0 ){
          perror("erreur open fichier src get");
          exit(EXIT_FAILURE);
        }
        src_size = get_file_size(argv[3]);
        void * mapped_zone = mmap(NULL, src_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, src, 0);
        if(mmapped_zone == MAP_FAILED){
          perror("erreur lies a mmapped_zone GET");
          exit(EXIT_FAILURE);
        }
        
        if(chdir("..")==-1){
          perror("chdir ..");
          exit(EXIT_FAILURE);
        }
        */
        int dst = open(argv[4],O_RDWR | O_CREAT | O_TRUNC,0644);
        if(dst < 0){
          perror("erreur open fichier dst get \n");
          exit(EXIT_FAILURE);
        }
        
        if(pwrite(dst,data2.bytes,data2.length,0)<0){
          perror("erreur lies a pwrite ");
          exit(EXIT_FAILURE);
        }
        if(close(dst)<0){
          perror("close dst \n");
          exit(EXIT_FAILURE);
        }
        //close(src);

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
    if (argc == 2){
      std::cout << "argv[2]" << std::endl;
    }


    std::cout << "Error: missing argument" << std::endl;
        //std::cout << "Usage: angry-donuts /path/to/data" << std::endl;
    /*
          angry-donuts nom_dossier put fichier
          -> renvoie l'uiid du nouveau fichier cree dans l'arborescence
        */
        std::cout << "Usage : angry-donuts /path/to/data commande uuid" << std::endl;
        std::cout << "common arguments " << std::endl;
        std::cout << "\tnom_dossier commande" << std::endl;
        std::cout << "options : put,get,del" << std::endl;
        std::cout << "\tput option" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "\tget option" << std::endl;
        std::cout <<" angry-donut nom_dossier get uuid"<<std::endl;
        std::cout << "\taffiche le contenu du fichier" << std::endl;
        std::cout <<" angry-donut nom_dossier get uuid fichier"<<std::endl;
        std::cout << "\tcreer un fichier avec le contenu du fichier ayant pour uuid l'uiid donné en paramétre" << std::endl;
        

        std::cout << "\tdel option" << std::endl;
        std::cout <<"" << std::endl;

        std::cout << "angry-donuts nom_dossier put fichier " << std::endl;


        exit(EXIT_FAILURE);
  }
  return 0;
}