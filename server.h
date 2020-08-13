


#include<iostream>
#include<pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<bits/stdc++.h>
#include<strings.h>
#include<unistd.h>
#include <fcntl.h>
#include<string.h>
#include<arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<sstream>
using namespace std;
//#define  tracker_port 8000
int tracker_port;



char buffer[24];
    int buffer_size=24;


struct thread_properties
{
  int port_number,file_descriptor;
  char source_path[256];
  char dest_path[256];
  char ip[15];
  int chunk_number;
};



struct upload_file_arg
{
char file_name[255];
int port;
int  file_size;
};


struct tracker
{
  char username[20];
  char password[20];
  int port;
  
};



int port_number_of_server;


void *server_side_method(void *file_descriptor_id)
{
int new_sock=*((int * )file_descriptor_id);
memset(buffer, '\0', sizeof(buffer));
//bzero(buffer,4*1024);

int file_name_size;
int recv_status=recv(new_sock,&file_name_size,sizeof(file_name_size),0);
if(recv_status<0)
    {
        cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
        exit(0);
    }

printf("\n %d\n",file_name_size);

char file_name[file_name_size+1];
file_name[file_name_size]='\0';
recv_status=recv(new_sock,file_name,sizeof(file_name)-1,0);
if(recv_status<0)
    {
        cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
        exit(0);
    }
printf("\n %s\n",file_name);



FILE *fp=fopen(file_name,"rb");
if(fp == NULL)
    {
        cout<<"Error in Opening file";
        exit(0);
    }

fseek(fp,0,SEEK_END);
int file_size=ftell(fp);
cout<<endl<<"pkb: "<<file_size<<endl;
rewind(fp);

int number_of_chunks=ceil(file_size/buffer_size);

int chunk_number;

recv_status=recv(new_sock,&chunk_number,sizeof(chunk_number),0);
if(recv_status<0)
    {
        cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
        exit(0);
    }
//bzero(buffer,buffer_size);
memset(buffer, '\0', sizeof(buffer));


int read_characters=buffer_size;
if((file_size-chunk_number*buffer_size)<buffer_size)
read_characters=file_size-chunk_number*buffer_size;


cout<<"file_size"<<file_size<<endl;
cout<<"chunk_number"<<chunk_number<<endl;
cout<<endl<<"buffer_size"<<buffer_size<<endl;
cout<<endl<<"file_size-chunk_number*buffer_size"<<file_size-chunk_number*buffer_size<<endl;
cout<<endl<<"read_characters"<<read_characters<<endl;

int send_status=send(new_sock,&read_characters,sizeof(read_characters),0);
if(send_status<0)
    {
        cout<<endl<<"error in sending"<<endl;
    }
//bzero(buffer,buffer_size);
memset(buffer, '\0', sizeof(buffer));
fseek(fp,chunk_number*buffer_size,SEEK_SET);

cout<<"my file pointer is:at read side before"<<fp<<endl;

while(read_characters>0)
    {
        int read_status=fread(buffer,sizeof(char),read_characters,fp);

        if(read_status>0)
            {
                int send_status=send(new_sock,buffer,read_status,0);
               // cout<<"send buffer:"<<buffer<<endl;
                if(send_status<0){ pthread_exit(NULL);}
                read_characters=read_characters-read_status;
                ///bzero(buffer,buffer_size);
                memset(buffer, '\0', sizeof(buffer));

            }
            else
            {
                break;
            }

    }
cout<<"my file pointer is:at read side before"<<fp<<endl;
fclose(fp);
close(new_sock);

}





void *serverfunction(void *ip_client)
{

string ipport=*(string *)ip_client;

    string server_ip_port=ipport;
    string ip_server;
    string port_server;
    char ch=':';
    int i=0;
    //while(s[i] != ':')
    while(server_ip_port[i] != ch)
    {
        ip_server=ip_server+server_ip_port[i];
        //cout<<endl;
        ++i;
    }
    ip_server[i+1]='\0';
    ++i;


   // cout<<endl<<strlen(argv[1])<<endl;

    while(i < server_ip_port.size() )
    {
        port_server=port_server+server_ip_port[i];
        ++i;
    }
    port_server[i+1]='\0';


    int socket_id=socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id<0)
    cout<<"Error in connection"<<endl;

        cout<<"socket id:"<<socket_id;


    struct sockaddr_in serveraddr,clientaddr;
    bzero((char *) &serveraddr, sizeof(serveraddr));


    serveraddr.sin_family=AF_INET;
    int port=atoi(port_server.c_str());
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    port_number_of_server=port;

    int bind_return=bind(socket_id,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    if(bind_return<0)
    {
        cout<<"Error in Binding"<<endl;
        exit(1);
    }


    cout<<"bind_return:"<<bind_return;

        cout<<"listeing state:";
    int listen_status=listen(socket_id,1100);
    if(listen_status<0)
    {
        cout<<"ERROR IN LISTEN"<<endl;
        exit(1);
    }
    int clientlen=sizeof(clientaddr);

    while(1)
    {
      //  int clientlen=sizeof(clientaddr);
        int new_sock=accept(socket_id, (struct sockaddr *) &clientaddr, (socklen_t*)&clientlen);
        if(new_sock<=0)
            {
                 cout<<"ERROR IN CONNECTING CLIENT"<<endl;
                 exit(1);
            }
            else
            {
                pthread_t thread_for_listen;
                int *accept_id=(int *)malloc(sizeof(*accept_id));
                *accept_id=new_sock;
                pthread_create(&thread_for_listen,0,server_side_method,(void *)accept_id);
                pthread_detach(thread_for_listen);
            }




    }



}



