![Alt text](angry_donuts_logo_v2_small.jpg?raw=true "Logo")

# Angry Donuts

Key-Value Objects storage.


### Membres du groupe
- Kevin Youna kevin.youna@gmail.com
- Tomek Lecocq tomek.lecocq@hotmail.fr
- Karim Yahiaoui karimmurcielago@gmail.com
- Valloris Cylly navarna@hotmail.fr
- Nguyen Luan nguyendavid75013@gmail.com

### Basic client

To build the client, just run make inside the src folder.

Usage:
```
./angry-donuts /path/to/data command
```

##### Put
```
./angry-donuts /path/to/data put file
```
Will create a new object containing the file's content and will print the uuid of this new object.
* file: the file containing the new object's content

```
./angry-donuts /path/to/data put uuid file
```
Will create or update the object (depending on if the uuid is already used) for the given uuid with the file's content.
* uuid: the object's ID
* file: the file containing the new or updated object's content

##### Get
```
./angry-donuts /path/to/data get uuid file
```
If the object exists, it's content will be written to the file. If the file already exists, it's content will be replaced by the new content.
* uuid: the object's ID
* file: the file where the content will be written

```
./angry-donuts /path/to/data get uuid
```
If you don't specify a file, the object's content will be directly outputed to stdout.
* uuid: the object's ID

##### Delete
```
./angry-donuts /path/to/data del uuid
```
Will delete the object identified by this uuid.
* uuid: the object's ID


### node.js HTTP REST server

The server only supports GET and DELETE methods.

You need to have a recent version of node.js, the one from your distribution's repository might be too old.
Link for node.js installation https://nodejs.org/en/download/package-manager/

To build the nodejs target and install dependencies, run 'npm install' from the server directory.

To run the server just run the 'start.sh' shell script. The server will run on port 8080. 

##### GET
```
GET http://localhost:8080/uuid
```
Will reply with status 200 if successful, with 404 if no object with this uuid exists, with 500 if an error occured.
* uuid: the object's ID

##### DELETE
```
DELETE http://localhost:8080/uuid
```
Will reply with status 200 if successful, with 404 if no object with this uuid exists, with 500 if an error occured.
* uuid: the object's ID


### git

GIT TUTO NO BULLSHIT : http://rogerdudler.github.io/git-guide/ 
