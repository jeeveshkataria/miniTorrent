#include"server.h"
#include<iostream>
#include<pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
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



void *thread_function_for_verify(void *arguments_of_thread)
{
  struct tracker * tr=(struct tracker*)arguments_of_thread;
  string client_user_name=tr->username;
  string password=tr->password;
  int port_to_send=tr->port;

  int socket_id=socket(AF_INET, SOCK_STREAM, 0);
      if(socket_id<0)
      cout<<"Error in connection"<<endl;
      struct sockaddr_in serveraddr;
      bzero((char *) &serveraddr, sizeof(serveraddr));


           port_to_send=tracker_port;
        serveraddr.sin_family=AF_INET;
          serveraddr.sin_port=htons(port_to_send);
          serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
          int connection_id= connect(socket_id,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
            if(connection_id < 0)
            perror("ERROR connecting");



              
    string create_user="login";
    //string download_file="download_file";
    int create_user_len=strlen(create_user.c_str());
    char create[create_user_len];
    strcpy(create,create_user.c_str());

    int send_status;
    
    
    send_status=send(socket_id,&create_user_len,sizeof(create_user_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    send_status=send(socket_id,&create,sizeof(create),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
        //cout<<"send:"<<create<<endl;



        int client_user_name_len=strlen(client_user_name.c_str());
    char client_user[client_user_name_len];
    strcpy(client_user,client_user_name.c_str());


    //i
    int count=0;

  send_status=send(socket_id,&client_user_name_len,sizeof(client_user_name_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    else ++count;
    send_status=send(socket_id,&client_user,sizeof(client_user),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
    else ++count;
        //cout<<"send:"<<client_user<<endl;

    //

    //send password


        int password_len=strlen(password.c_str());
    char pass[password_len];
    strcpy(pass,password.c_str());


  send_status=send(socket_id,&password_len,sizeof(password_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
     else ++count;
    send_status=send(socket_id,&pass,sizeof(pass),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
    else ++count;

    if(count == 4)
    {
      int return_value;
      int recv_status;
      recv_status=recv(socket_id,&return_value,sizeof(return_value),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }  

        if(return_value == count)
        {
          cout<<endl<<"User name has been verified"<<endl;
        }
        else
        {
          cout<<endl<<"PASSWORD IS WRONG,GO BACK ,COMPILE AGAIN"<<endl;
        }




    } 




}

void *thread_function_for_upload(void *arguments_of_thread)
{
  
  
  //string port_tr=argv[2];
  
  struct upload_file_arg * up=(struct upload_file_arg*)arguments_of_thread;
  string file_name = up->file_name;
  int  file_size = up->file_size;
  int  port_no_of_server = up->port;

  int socket_id=socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id<0)
    cout<<"Error in connection"<<endl;
  struct sockaddr_in serveraddr;
    bzero((char *) &serveraddr, sizeof(serveraddr));

 //int port_tra=atoi(port_tr.c_str());
 int port_to_send=tracker_port;
  serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port_to_send);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int connection_id= connect(socket_id,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
      if(connection_id < 0)
      perror("ERROR connecting");


    int file_length=strlen(file_name.c_str());
    char send_file_path[file_length];
    strcpy(send_file_path,file_name.c_str());
    
    string upload_file="upload_file";
    int upload_file_len=strlen(upload_file.c_str());
    char upload[upload_file_len];
    strcpy(upload,upload_file.c_str());

    int send_status;
    
    
    send_status=send(socket_id,&upload_file_len,sizeof(upload_file_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    send_status=send(socket_id,&upload,sizeof(upload),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
        cout<<"send:"<<upload<<endl;
    
    
    
    
    
    
    send_status=send(socket_id,&file_length,sizeof(file_length),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    send_status=send(socket_id,&send_file_path,sizeof(send_file_path),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
    
    
    
    send_status=send(socket_id,&port_no_of_server,sizeof(port_number_of_server),0);
    if(send_status<0)
      {
                cout<<"error while send status";
                 exit(0);
      }
    int upload_status=0;
    int recv_status=recv(socket_id,&upload_status,sizeof(upload_status),0);
    if(recv_status<0)
        {
              cout<<endl<<"error in receiving chunk characters"<<endl;
        }

    if(upload_status == 1)
       {
         cout<<endl<<"file_uploaded_successfully"<<endl;
       }
       else
       {
         cout<<endl<<"problem in uploading"<<endl;
       }

    pthread_exit(NULL);



}



void *thread_function_for_tracker(void *arguments_of_thread)
{
  struct tracker * tr=(struct tracker*)arguments_of_thread;
  string client_user_name=tr->username;
  string password=tr->password;
  int port_to_send=tr->port;




    ///*

      int socket_id=socket(AF_INET, SOCK_STREAM, 0);
      if(socket_id<0)
      cout<<"Error in connection"<<endl;
      struct sockaddr_in serveraddr;
      bzero((char *) &serveraddr, sizeof(serveraddr));


           port_to_send=tracker_port;
        serveraddr.sin_family=AF_INET;
          serveraddr.sin_port=htons(port_to_send);
          serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
          int connection_id= connect(socket_id,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
            if(connection_id < 0)
            perror("ERROR connecting");

    //
        
        
        string create_user="create_user";
    //string download_file="download_file";
    int create_user_len=strlen(create_user.c_str());
    char create[create_user_len];
    strcpy(create,create_user.c_str());

    int send_status;
    
    
    send_status=send(socket_id,&create_user_len,sizeof(create_user_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    send_status=send(socket_id,&create,sizeof(create),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
        //cout<<"send:"<<create<<endl;



        int client_user_name_len=strlen(client_user_name.c_str());
    char client_user[client_user_name_len];
    strcpy(client_user,client_user_name.c_str());


    //i
    int count=0;

  send_status=send(socket_id,&client_user_name_len,sizeof(client_user_name_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    else ++count;
    send_status=send(socket_id,&client_user,sizeof(client_user),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
    else ++count;
        //cout<<"send:"<<client_user<<endl;

    //

    //send password


        int password_len=strlen(password.c_str());
    char pass[password_len];
    strcpy(pass,password.c_str());


  send_status=send(socket_id,&password_len,sizeof(password_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
     else ++count;
    send_status=send(socket_id,&pass,sizeof(pass),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
    else ++count;

    if(count == 4)
    {
      int return_value;
      int recv_status;
      recv_status=recv(socket_id,&return_value,sizeof(return_value),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }  

        if(return_value == count)
        {
          cout<<"user and password data uploaded successfully"<<endl;
        }





    }        

  

}


void *thread_function_for_each(void * arguments_to_connect)
{
    int socket_id=socket(AF_INET, SOCK_STREAM, 0);
    if(socket_id<0)
    cout<<"Error in connection"<<endl;
    struct thread_properties * thread_copy_data=(struct thread_properties*)arguments_to_connect;
    int port_no=thread_copy_data->port_number;
    int chunk_number=thread_copy_data->chunk_number;
    struct sockaddr_in serveraddr;
    bzero((char *) &serveraddr, sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port_no);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int connection_id= connect(socket_id,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    
    if(connection_id < 0)
      perror("ERROR connecting");

    string source_path=thread_copy_data->source_path;
    int file_length=strlen(source_path.c_str());
    char send_file_path[file_length];
    strcpy(send_file_path,source_path.c_str());

    int send_status;
    send_status=send(socket_id,&file_length,sizeof(file_length),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    send_status=send(socket_id,&send_file_path,sizeof(send_file_path),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
    send_status=send(socket_id,&chunk_number,sizeof(chunk_number),0);
    if(send_status<0)
    {
                cout<<"error while send status";
                 exit(0);
    }

    int chunk_caharcters;
    int recv_status=recv(socket_id,&chunk_caharcters,sizeof(chunk_caharcters),0);
    if(recv_status<0)
        {
              cout<<endl<<"error in receiving chunk characters"<<endl;
        }

     FILE *destination_file;
    string dest_path=thread_copy_data->dest_path;
    destination_file=fopen(dest_path.c_str(),"r+");
    if(destination_file==NULL)
        {
          cout<<endl<<"error in opening destination file for writing"<<endl;

        }

    fseek(destination_file,chunk_number*buffer_size,SEEK_SET);
    bzero(buffer,buffer_size);
    int characters_read;
    bzero(buffer,buffer_size);

    while(chunk_caharcters > 0)
    {
         characters_read=recv(socket_id,buffer,buffer_size,0);
          if(characters_read > 0)
          {
            fwrite(buffer,sizeof(char),characters_read,destination_file);
            chunk_caharcters=chunk_caharcters-characters_read;
            bzero(buffer,buffer_size);
          }
          else
          {
            break;
          }

        }

    close(socket_id);
    fclose(destination_file);

    pthread_exit(NULL);


}



int main(int argc, char *argv[])
{

    string ip_client=string(argv[1]);//need correction here argument 1 provided by user
    pthread_t threadserver;

    //string trackerport=argv[2];
    tracker_port=atoi(argv[2]);
    pthread_create(&threadserver, 0, serverfunction, (void *)&ip_client);

  while(1)
  {
    string client_input;
    getline(cin,client_input);
    stringstream ss(client_input);
    string client_first_word;
    ss >> client_first_word;
    cout<<client_first_word;
    string download_file="download_file";
    string create_user="create_user";
    string upload_file="upload_file";
    string login="login";

    if(strcmp(client_first_word.c_str(),download_file.c_str())==0)
    {
        string file_name;
        ss >> file_name;
        string dest_path;
        ss >> dest_path;
        
        // function_for_each_chunk(file_path,dest_path);
        


      int socket_id=socket(AF_INET, SOCK_STREAM, 0);
      if(socket_id<0)
      cout<<"Error in connection"<<endl;
      struct sockaddr_in serveraddr;
      bzero((char *) &serveraddr, sizeof(serveraddr));


          int port_to_send=tracker_port;
        serveraddr.sin_family=AF_INET;
          serveraddr.sin_port=htons(port_to_send);
          serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
          int connection_id= connect(socket_id,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
            if(connection_id < 0)
            perror("ERROR connecting");


//command=download_file


    
    string download_file="download_file";
    int download_file_len=strlen(download_file.c_str());
    char download[download_file_len];
    strcpy(download,download_file.c_str());

    int send_status;
    
    
    send_status=send(socket_id,&download_file_len,sizeof(download_file_len),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
    send_status=send(socket_id,&download,sizeof(download),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
        cout<<"send:"<<download<<endl;




//






    //conert filepath to file name
  int file_name_length=strlen(file_name.c_str());
    char send_file_name[file_name_length];
    strcpy(send_file_name,file_name.c_str());
//

   send_status;
  //
  send_status=send(socket_id,&file_name_length,sizeof(file_name_length),0);
    if(send_status<0)
        {
                cout<<"error while send status";
                 exit(0);
        }
  
  cout<<"send:"<<file_name_length<<endl;
  //


  //
   send_status=send(socket_id,&send_file_name,sizeof(send_file_name),0);
    if(send_status<0)
        {
                 cout<<"error while send status";
                 exit(0);
        }
        cout<<"send:"<<send_file_name<<endl;


  //
      int file_path_size;
        int recv_status=recv(socket_id,&file_path_size,sizeof(file_path_size),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
cout<<"recv:"<<file_path_size<<endl;

  //

      char file_path[file_path_size+1];
        file_path[file_path_size]='\0';
        recv_status=recv(socket_id,file_path,sizeof(file_path)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
        cout<<"recv:"<<file_path<<endl;
        string filepath=file_path;



  //
      int stringportlength;
         recv_status=recv(socket_id,&stringportlength,sizeof(stringportlength),0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }  
cout<<"recv:"<<stringportlength<<endl;

//


  char string_port[stringportlength+1];
        string_port[stringportlength]='\0';
        recv_status=recv(socket_id,string_port,sizeof(string_port)-1,0);
        if(recv_status<0)
        {
            cout<<"error in recv signal " << errno << " " << EBADF << " " << ECONNREFUSED << " " << EFAULT << " " << EINVAL << " " << ENOMEM << " "<< ENOTCONN;
            exit(0);
        }
       cout<<"recv:"<<string_port<<endl;
        string stringport=string_port;


//

  int number_of_port=0;
  stringstream ss(stringport);
  string word;
  while(ss >> word)
  ++number_of_port;

  
  string temp=stringport;
  stringstream diffport(temp);
  string temp1;
  int different_port[number_of_port];
  int j=0;
  while(j<number_of_port)
  {
    diffport >> temp1;
    different_port[j]=atoi(temp1.c_str());
    cout<<different_port[j]<<endl;
    ++j;
  }

//

//now find no of chunks

  FILE *fp=fopen(filepath.c_str(),"rb");
        fseek(fp,0,SEEK_END);
        int file_size=ftell(fp);
        rewind(fp);
        fclose(fp);
        cout<<"at download side"<<file_size<<endl;

        int number_of_chunks=ceil((double)file_size/buffer_size);
        cout<<"no of chunks"<<number_of_chunks<<endl;


        
      for(int chunk_num=0;chunk_num<=number_of_chunks;chunk_num++)
      {

        int port_index;

      if(chunk_num == 0 )
    {
        
        port_index=0;
        int port_to_send=different_port[port_index];
        cout<<"port_to:"<<port_to_send<<endl;



         fp=fopen(dest_path.c_str(),"wb");//changed file name here
        fseek(fp,file_size-1,SEEK_SET);
        fputc('\0',fp);
        rewind(fp);
        fclose(fp);



        pthread_t  thread_for_chunk;
        struct thread_properties *thread_pointer  =(struct thread_properties *)malloc(sizeof(thread_properties));
        thread_pointer->chunk_number=chunk_num;
       // strcpy(thread_pointer->ip,ip_source.c_str());
        strcpy(thread_pointer->source_path,filepath.c_str());
        strcpy(thread_pointer->dest_path,dest_path.c_str());
        
          thread_pointer->port_number=port_to_send;
        
        //thread_pointer->port_number=atoi(port_source.c_str());
        if(int thread_status=pthread_create(&thread_for_chunk,0,thread_function_for_each,(void *)thread_pointer))
            {
              cout<<endl<<"error in creating thread"<<endl;
              pthread_exit(NULL);
            }
        pthread_detach(thread_for_chunk);
    
    
    
    
    
    }
    else
    {



        //port_index=chunk_num;
        port_index=chunk_num%number_of_port;
        int port_to_send=different_port[port_index];
        cout<<"port_to:"<<port_to_send<<endl;



        pthread_t  thread_for_chunk;
        struct thread_properties *thread_pointer  =(struct thread_properties *)malloc(sizeof(thread_properties));
        thread_pointer->chunk_number=chunk_num;
       // strcpy(thread_pointer->ip,ip_source.c_str());
        strcpy(thread_pointer->source_path,filepath.c_str());
        strcpy(thread_pointer->dest_path,dest_path.c_str());
        
        thread_pointer->port_number=port_to_send;
        
        //thread_pointer->port_number=atoi(port_source.c_str());
        if(int thread_status=pthread_create(&thread_for_chunk,0,thread_function_for_each,(void *)thread_pointer))
            {
              cout<<endl<<"error in creating thread"<<endl;
              pthread_exit(NULL);
            }
        pthread_detach(thread_for_chunk);
    


    }
      
      
      
      
      }
      
    }
    else if(strcmp(client_first_word.c_str(),create_user.c_str())==0)
    {
        string client_user_name;
        string password;
        ss >> client_user_name;
        ss >> password;
        int port_number_of_tracker=tracker_port;


        struct tracker *tr=(struct tracker*)malloc(sizeof(tracker));
        strcpy(tr->password,password.c_str());
        strcpy(tr->username,client_user_name.c_str());
        tr->port=port_number_of_tracker;
        pthread_t thread_for_tracker;
        if(int thread_status=pthread_create(&thread_for_tracker,0,thread_function_for_tracker,(void *)tr))
            {
              cout<<endl<<"error in creating thread"<<endl;
              pthread_exit(NULL);
            }
        pthread_detach(thread_for_tracker);
        

    }
    else if(strcmp(client_first_word.c_str(),upload_file.c_str())==0)
    {


      string file_path;
      ss >> file_path;
    string file_name=file_path;


    cout<<endl<<file_name<<endl;
    cout<<port_number_of_server<<endl;
    
    FILE *fp=fopen(file_path.c_str(),"rb");
    fseek(fp,0,SEEK_END);
    int file_size=ftell(fp);
    rewind(fp);
    fclose(fp);

    struct upload_file_arg *up=(struct upload_file_arg *)malloc(sizeof(upload_file_arg));
    strcpy(up->file_name,file_name.c_str());
    
    up->file_size=file_size;
    up->port=port_number_of_server;
    pthread_t thread_for_upload;
    int thread_status;
    cout<<"thread creating"<<endl;
    if( thread_status=pthread_create(&thread_for_upload,0,thread_function_for_upload,(void *)up))
        {
              cout<<endl<<"error in creating thread"<<endl;
              pthread_exit(NULL);
        }
            cout<<"thread status:"<<thread_status<<endl;
            
    pthread_detach(thread_for_upload);
      

    }
    if(strcmp(client_first_word.c_str(),login.c_str())==0)
    {
      string client_user_name;
        string password;
        ss >> client_user_name;
        ss >> password;
        int port_number_of_tracker=tracker_port;

        struct tracker *tr=(struct tracker*)malloc(sizeof(tracker));
        strcpy(tr->password,password.c_str());
        strcpy(tr->username,client_user_name.c_str());
        tr->port=port_number_of_tracker;
        pthread_t thread_for_tracker;
        if(int thread_status=pthread_create(&thread_for_tracker,0,thread_function_for_verify,(void *)tr))
            {
              cout<<endl<<"error in creating thread"<<endl;
              pthread_exit(NULL);
            }
        pthread_detach(thread_for_tracker);






    }
    else cout<<"NOT MATCHING ANY COMMAND"<<endl;





  }



    pthread_join(threadserver,0);
}
